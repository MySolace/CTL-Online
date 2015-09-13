<?php

/**
 * Registers an accepted user to a timeslot.
 */
function _ctl_onboarding_slot_register($slot_code, $uid) {
  if (is_null($slot_code)) {
    form_set_error('training_slot', t('A time slot must be chosen!'));
    return;
  }

  $cohort_id = intval(variable_get('ctl_onboarding_cohort_id'));

  $query = db_select('ctl_onboarding_slot', 's');
  $query->addField('s', 'max_trainers');
  $query->addField('s', 'num_registrants');
  $result = $query
    ->condition('s.cohort_id', $cohort_id)
    ->condition('s.slot_code', $slot_code)
    ->execute()
    ->fetchAll();

  if (empty($result)) {
    drupal_set_message(t("Could not find info for the !slot_code time slot!  Please notify a trainer or site administrator.", array('!slot_code' => $slot_code)), 'error');
    return;
  }

  $slot             = $result[0];
  $max_trainers     = $slot->max_trainers;
  $num_registrants  = $slot->num_registrants;
  $trainer_capacity = variable_get('ctl_onboarding_trainer_capacity', CTL_ONBOARDING_DEFAULT_TRAINER_CAPACITY);

  if ($num_registrants >= $trainer_capacity * $max_trainers) {
    drupal_set_message(t('Sorry, registration is for this time slot is full!  Please select another time slot'), 'error');
    // TODO
    // - future work for wait listing would happen here
    return;
  }

  // See if the user has attempted registering already.
  $query = db_select('ctl_onboarding_registrant', 'r');
  $query->addField('r', 'uid');
  $query->addField('r', 'status');
  $result = $query
    ->condition('r.cohort_id', $cohort_id)
    ->execute()
    ->fetchAll();

// define('CTL_ONBOARDING_STATUS_PENDING', 0);
// define('CTL_ONBOARDING_STATUS_ACCEPTED', 1);
// define('CTL_ONBOARDING_STATUS_WAIT_LISTED', 2);
// define('CTL_ONBOARDING_STATUS_DROPPED_FAILED_BACKGROUND_CHECK', 3);
// define('CTL_ONBOARDING_STATUS_DROPPED_CANCELED_BY_REGISTRANT', 4);
// define('CTL_ONBOARDING_STATUS_DROPPED_OTHER', 5);

  // If the user has not registered for this cohort before
  // then record their attempt.
  if (empty($result)) {
    $query = db_insert('ctl_onboarding_registrant')
      ->fields(array(
        'uid'       => $uid,
        'cohort_id' => $cohort_id,
        'slot_code' => $slot_code,
        'status'    => CTL_ONBOARDING_STATUS_PENDING,
      ));
    try {
      $query->execute();
    }
    catch (PDOException $e) {
      // // Check if the user has already signed up for this time slot.
      // // https://dev.mysql.com/doc/refman/5.5/en/error-messages-server.html#error_er_dup_entry
      // if ($e->errorInfo[1] === 1062) {
      //   drupal_set_message(t('You have already signed up for this time slot!'), 'error');
      // }
      // else {
      drupal_set_message(t('Error: %message', array('%message' => $e->getMessage())), 'error');
      // }
      return;
    }
  }


  // // One more registrant has signed up.
  // db_update('ctl_onboarding_slot')
  //   ->fields(array('num_registrants' => $num_registrants + 1))
  //   ->condition('cohort_id', $cohort_id)
  //   ->condition('slot_code', $slot_code)
  //   ->execute();
}
