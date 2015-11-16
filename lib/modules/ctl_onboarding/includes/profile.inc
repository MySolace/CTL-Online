<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ctl_onboarding_form_user_profile_form_alter(&$form, &$form_state, $form_id) {
  $parts = explode('/', current_path());
  $uid   = intval($parts[1]);

  // Get the user's current slot code.
  $query  = 'SELECT slot_code '
          . 'FROM {ctl_onboarding_registrant} '
          . 'WHERE uid = :uid';
  $args   = array(':uid' => $uid);
  $result = db_query($query, $args)->fetchAll();

  $default_slot_code = !empty($result) ? $result[0]->slot_code : '';

  // TODO nice to have
  // - make this a drop-down
  $form['slot_code'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Slot code'),
    '#default_value' => $default_slot_code,
    '#weight'        => 90,
  );

  $form['#validate'][] = '_ctl_onboarding_form_user_profile_form_validate_extra';
  $form['#submit'][]   = '_ctl_onboarding_form_user_profile_form_submit_extra';
}


/**
 * Validates the slot code data.
 */
function _ctl_onboarding_form_user_profile_form_validate_extra($form, &$form_state) {
  $values    = $form_state['values'];
  $cohort_id = intval($values['field_cohort'][LANGUAGE_NONE][0]['value']);
  $slot_code = $values['slot_code'];
  $parts     = explode('/', current_path());
  $uid       = intval($parts[1]);

  // No cohort means unregister.
  if ($cohort_id < 1) {
    if (!empty($slot_code)) {
      form_set_error('slot_code', t('No cohort is selected so the slot code should be left blank.'));
      return;
    }
    $parts = explode('/', current_path());
    $form_state['storage']['unregistering'] = TRUE;
    $form_state['storage']['uid'] = $uid;
    return;
  }

  // Older cohorts don't have valid slots.
  if ($cohort_id < CTL_ONBOARDING_FIRST_COHORT_TO_USE_REGISTRATION_SYSTEM) {
    if (empty($slot_code)) {
      $form_state['storage']['switching'] = FALSE;
    }
    else {
      form_set_error('slot_code', t('There are no valid slot codes for cohorts older than ' . CTL_ONBOARDING_FIRST_COHORT_TO_USE_REGISTRATION_SYSTEM . '.  For these cohorts the slot code should be left blank.'));
    }
    return;
  }
  // else {
  //   // Newer cohorts require a valid slot code to be given.
  //   if (empty($slot_code)) {
  //     form_set_error('slot_code', t('For cohorts ' . CTL_ONBOARDING_FIRST_COHORT_TO_USE_REGISTRATION_SYSTEM . ' and above there must a slot code given.'));
  //     return;
  //   }
  // }

  // Slot codes must be formatted correctly.
  if (!_ctl_onboarding_validate_slot_code($slot_code)) {
    form_set_error('slot_code', t('The slot code is not in a valid format.'));
    return;
  }

  // Check if the slot code exists within the given cohort.
  $query  = 'SELECT num_trainers, num_registrants '
          . 'FROM {ctl_onboarding_slot} '
          . 'WHERE cohort_id = :cohort_id AND slot_code = :slot_code';
  $args   = array(':cohort_id' => $cohort_id, ':slot_code' => $slot_code);
  $result = db_query($query, $args)->fetchAll();
  if (empty($result)) {
    $error_msg = 'Cohort @cohort does not include the @slot_code time slot.';
    $error_msg = t($error_msg, array(
      '@cohort'    => $cohort_id,
      '@slot_code' => $slot_code,
    ));
    form_set_error('slot_code', $error_msg);
    return;
  }

  $slot_info = $result[0];

  // Check if the user had already registered for the slot.
  $query = 'SELECT uid '
         . 'FROM {ctl_onboarding_registrant} '
         . 'WHERE uid = :uid '
         . '  AND cohort_id = :cohort_id '
         . '  AND slot_code = :slot_code;';
  $args = array(
    ':uid'       => $uid,
    ':cohort_id' => $cohort_id,
    ':slot_code' => $slot_code,
  );
  $result = db_query($query, $args)->fetchAll();
  if (!empty($result)) {
    $form_state['storage']['switching'] = FALSE;
    return;
  }

  // Check if the slot is available.
  $num_trainers     = intval($slot_info->num_trainers);
  $num_registrants  = intval($slot_info->num_registrants);
  $trainer_capacity = intval(variable_get('ctl_onboarding_trainer_capacity', CTL_ONBOARDING_DEFAULT_TRAINER_CAPACITY));
  if ($num_trainers < 1) {
    $error_msg = 'Cohort @cohort time slot @slot_code is unavailable.';
    $error_msg = t($error_msg, array(
      '@cohort'    => $cohort_id,
      '@slot_code' => $slot_code,
    ));
    form_set_error('slot_code', $error_msg);
    return;
  }
  if ($num_registrants >= $trainer_capacity * $num_trainers) {
    $error_msg = 'Cohort @cohort time slot @slot_code is full.';
    $error_msg = t($error_msg, array(
      '@cohort'    => $cohort_id,
      '@slot_code' => $slot_code,
    ));
    form_set_error('slot_code', $error_msg);
    return;
  }

  $form_state['storage']['switching'] = TRUE;
  $form_state['storage']['uid'] = $uid;
}


/**
 * Updates registration info.
 */
function _ctl_onboarding_form_user_profile_form_submit_extra($form, &$form_state) {
  $switching     = !empty($form_state['storage']['switching']);
  $unregistering = !empty($form_state['storage']['unregistering']);
  if (!$switching && !$unregistering) {
    return;
  }

  $uid = $form_state['storage']['uid'];

  // Get the user's current relevant training session registration info.
  $query  = 'SELECT cohort_id, slot_code '
          . 'FROM {ctl_onboarding_registrant} '
          . 'WHERE uid = :uid';
  $args   = array(':uid' => $uid);
  $result = db_query($query, $args)->fetchAll();

  if (empty($result)) {
    // If we couldn't find the registrant's info then they're
    // already not registered.
    if ($unregistering) {
      return;
    }
  }
  else {
    $slot_info     = $result[0];
    $cur_cohort_id = intval($slot_info->cohort_id);
    $cur_slot_code = $slot_info->slot_code;

    // Decrease the registrant count of the user's current slot.
    db_update('ctl_onboarding_slot')
      ->expression('num_registrants', 'num_registrants - 1')
      ->condition('cohort_id', $cur_cohort_id)
      ->condition('slot_code', $cur_slot_code)
      ->execute();

    if ($unregistering) {
      db_delete('ctl_onboarding_registrant')
        ->condition('uid', $uid)
        ->execute();
      drupal_set_message(t('Successfully unregistered.'));
      return;
    }
  }

  $values    = $form_state['values'];
  $cohort_id = intval($values['field_cohort'][LANGUAGE_NONE][0]['value']);
  $slot_code = $values['slot_code'];

  // Increase the registrant count of the user's new slot.
  db_update('ctl_onboarding_slot')
    ->expression('num_registrants', 'num_registrants + 1')
    ->condition('cohort_id', $cohort_id)
    ->condition('slot_code', $slot_code)
    ->execute();

  // Upsert time slot info.
  // TODO later
  // - account for the status field
  //   - or not since it's being retired in the future
  db_merge('ctl_onboarding_registrant')
    ->key(array('uid' => $uid))
    ->fields(array(
      'cohort_id' => $cohort_id,
      'slot_code' => $slot_code,
      'status'    => CTL_ONBOARDING_STATUS_ACCEPTED,
    ))
    ->execute();
}
