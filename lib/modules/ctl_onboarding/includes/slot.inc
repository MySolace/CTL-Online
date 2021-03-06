<?php

function _ctl_onboarding_slot_save_registrant($cohort_id, $slot_code, $uid) {
  $query = db_insert('ctl_onboarding_registrant')
    ->fields(array(
      'uid'       => $uid,
      'cohort_id' => $cohort_id,
      'slot_code' => $slot_code,
      // TODO later
      // - potential future work for more advanced sign-up strategies would happen here
      // 'status'    => CTL_ONBOARDING_STATUS_PENDING,
      'status' => CTL_ONBOARDING_STATUS_ACCEPTED,
    ));

  try {
    $query->execute();
  }
  catch (PDOException $e) {
    // Check if the user has already signed up for this time slot.
    // https://dev.mysql.com/doc/refman/5.5/en/error-messages-server.html#error_er_dup_entry
    if ($e->errorInfo[1] === 1062) {
      drupal_set_message(t('You have already signed up for this time slot!'), 'error');
    }
    else {
      drupal_set_message(t('Slot error: %message', array('%message' => $e->getMessage())), 'error');
    }
    return FALSE;
  }

  // Make sure we have custom profile fields by reloading the user explicitly
  // before initiating a background check.
  $user = user_load($uid);
  _ctl_onboarding_do_background_check($user);

  $mail_data = array(
    'key'  => 'register',
    'user' => $user,
  );

  // Send the confirmation email for registration.
  if (!_ctl_onboarding_mail_send($mail_data)) {
    drupal_set_message(t('There was a problem sending a confirmation email.'), 'error');
  }

  return TRUE;
}


/**
 * Registers an accepted user to a timeslot.
 */
function _ctl_onboarding_slot_register($slot_code, $uid) {
  if (is_null($slot_code)) {
    form_set_error('training_slot', t('A time slot must be chosen!'));
    return FALSE;
  }

  $cohort_id = intval(variable_get('ctl_onboarding_cohort_id'));

  $slot_status = _ctl_onboarding_slot_status($slot_code);
  if (!$slot_status['available']) {
    drupal_set_message($slot_status['error_message'], 'error');
    return FALSE;
  }

  // See if the user has attempted registering already.
  $query = db_select('ctl_onboarding_registrant', 'r');
  $query->addField('r', 'slot_code');
  $query->addField('r', 'status');
  $result = $query
    ->condition('r.uid', $uid)
    ->condition('r.cohort_id', $cohort_id)
    ->execute()
    ->fetchAll();

  $still_eligible = TRUE;
  $error_msg      = '';

  // If the user has already attempted registering for this cohort then
  // see if they're allowed to attempt registering again.
  if (!empty($result)) {
    // If the user has already attempted registering then check what
    // their status was for the other registration attempts they had.
    // This will determine if they're still eligible to register.
    foreach ($result as $registrant) {
      switch ($registrant->status) {
        // // TODO later
        // // - the "pending" status has future potential usage
        // // The user could waiting to hear about multiple time slots.
        // case CTL_ONBOARDING_STATUS_PENDING:
        //   if ($registrant->slot_code === $slot_code) {
        //   }

        // TODO later
        // - this is for future work related to wait listing
        // A user should be allowed to sign up for an alternate time
        // slot from the one they're wait listed on.
        case CTL_ONBOARDING_STATUS_WAIT_LISTED:
          if ($registrant->slot_code === $slot_code) {
            $error_msg = t('You are already wait listed for this time slot!');
            break 2;
          }

        // There may be many reasons why a user would cancel their registration
        // and then want to register later for perhaps a different time slot.
        // They should have the ability to do so.
        case CTL_ONBOARDING_STATUS_DROPPED_CANCELED_BY_REGISTRANT:
          break;

        // A user can take only register for one of the
        // available training sessions.
        case CTL_ONBOARDING_STATUS_ACCEPTED:
          if ($registrant->slot_code === $slot_code) {
            $error_msg = t('You have already been accepted into this time slot!');
            break 2;
          }

        // A user who has failed their background check should not have another
        // registration attempt for hopefully obvious reasons.
        case CTL_ONBOARDING_STATUS_DROPPED_FAILED_BACKGROUND_CHECK:

        // Without knowing more about other reasons why a user would be dropped
        // from a previous registration attempt, we'll err on the side of
        // caution and prevent the user for attempting to register again.
        case CTL_ONBOARDING_STATUS_DROPPED_OTHER:

        // Any other status is presumed to prohibit the user
        // from registering again.
        default:
          $still_eligible = FALSE;

          // We can skip ahead if we've already attempted to sign up for
          // the chosen time slot previously.
          if ($registrant->slot_code === $slot_code) {
            $error_msg = t('You have already attempted registering for this time slot!');
            break 2;
          }
          else {
            $error_msg = t('You already registered for a time slot. Need to reschedule? email <a href="mailto:volunteers@crisistextline.org">volunteers@crisistextline.org</a>.');
          }
      }
    }
  }

  if (!$still_eligible) {
    drupal_set_message($error_msg, 'error');
    return FALSE;
  }

  $saved = _ctl_onboarding_slot_save_registrant($cohort_id, $slot_code, $uid);
  if (!$saved) {
    return FALSE;
  }

  // TODO later
  // - check that the cohort field on the user profile is updated appropriately

  // Assign the cohort number to the user profile.
  $user = user_load($uid);
  $user->field_cohort[LANGUAGE_NONE][0]['value'] = $cohort_id;
  user_save($user);

  // One more registrant has signed up.
  db_update('ctl_onboarding_slot')
    ->expression('num_registrants', 'num_registrants + 1')
    ->condition('cohort_id', $cohort_id)
    ->condition('slot_code', $slot_code)
    ->execute();

  return TRUE;
}


function _ctl_onboarding_slot_status($slot_code) {
  $cohort_id = intval(variable_get('ctl_onboarding_cohort_id'));

  $query = db_select('ctl_onboarding_slot', 's');
  $query->addField('s', 'num_trainers');
  $query->addField('s', 'num_registrants');
  $result = $query
    ->condition('s.cohort_id', $cohort_id)
    ->condition('s.slot_code', $slot_code)
    ->execute()
    ->fetchAll();

  if (empty($result)) {
    return array(
      'available'     => FALSE,
      'error_message' => t('Could not find info for the @slot_code time slot!  Please notify a trainer or site administrator.', array('@slot_code' => $slot_code)),
    );
  }

  $slot             = $result[0];
  $num_trainers     = intval($slot->num_trainers);
  $num_registrants  = intval($slot->num_registrants);
  $trainer_capacity = intval(variable_get('ctl_onboarding_trainer_capacity', CTL_ONBOARDING_DEFAULT_TRAINER_CAPACITY));

  if ($num_registrants >= $trainer_capacity * $num_trainers) {
    return array(
      'available'     => FALSE,
      'error_message' => t('Sorry, registration for this time slot is full!  Please select another time slot.'),
    );
  }

  // If we haven't aborted yet, the slot is available.
  return array('available' => TRUE);
}
