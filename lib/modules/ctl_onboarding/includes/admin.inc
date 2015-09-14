<?php

function _ctl_onboarding_settings_form() {
  $days  = array('m', 'tu', 'w', 'th', 'f', 'sa', 'su');
  $slots = array();

  // Setup the selectable time slots.
  for ($i = 0, $l = count($days); $i < $l; ++$i) {
    for ($hour = CTL_ONBOARDING_FIRST_START_HOUR; $hour <= CTL_ONBOARDING_LAST_START_HOUR; $hour += CTL_ONBOARDING_ONE_HOUR) {
      $start_hour_display  = _ctl_onboarding_format_hour_display($hour);
      $finish_hour_display = _ctl_onboarding_format_hour_display($hour + CTL_ONBOARDING_SESSION_DURATION);

      $slots[$days[$i] . '-' . $hour] = $start_hour_display . ' - ' . $finish_hour_display;
    }
  }

  $form['ctl_onboarding_registration_period'] = array(
    '#type'          => 'select',
    '#title'         => t('Registration period'),
    '#default_value' => variable_get('ctl_onboarding_registration_period', CTL_ONBOARDING_REGISTRATION_CLOSED),
    '#required'      => TRUE,
    '#options' => array(
      CTL_ONBOARDING_REGISTRATION_CLOSED => t('Closed'),
      CTL_ONBOARDING_REGISTRATION_OPEN   => t('Open'),
    ),
  );
  $form['ctl_onboarding_cohort_id'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Cohort #'),
    '#default_value' => variable_get('ctl_onboarding_cohort_id'),
    // '#element_validate' => array('_ctl_onboarding_cohort_id_validate'),
    '#required'      => TRUE,
  );
  $form['ctl_onboarding_cohort_registration_start_date'] = array(
    '#type'          => 'date',
    '#title'         => t('Start of sign-up'),
    '#default_value' => variable_get('ctl_onboarding_cohort_registration_start_date'),
  );
  $form['ctl_onboarding_cohort_registration_finish_date'] = array(
    '#type'          => 'date',
    '#title'         => t('End of sign-up'),
    '#default_value' => variable_get('ctl_onboarding_cohort_registration_finish_date'),
  );
  $form['ctl_onboarding_trainer_capacity'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Number of trainees per session a trainer can handle'),
    '#default_value' => variable_get('ctl_onboarding_trainer_capacity', CTL_ONBOARDING_DEFAULT_TRAINER_CAPACITY),
    '#required'      => TRUE,
  );
  $form['ctl_onboarding_slots'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Choose time slots to have available for registration'),
    '#options'       => $slots,
    '#default_value' => variable_get('ctl_onboarding_slots'),
    '#theme'         => array('ctl_onboarding_table'),
    '#showing_all'   => TRUE,
  );

  // We'll need to do additional setup.
  $form['#submit'][] = '_ctl_onboarding_settings_submit_extra';

  return system_settings_form($form);
}


function _ctl_onboarding_settings_submit_extra($form, &$form_state) {
  $values    = $form_state['values'];
  $slots     = $values['ctl_onboarding_slots'];
  $cohort_id = $values['ctl_onboarding_cohort_id'];

  foreach ($slots as $slot_code) {
    if ($slot_code) {
      // Upsert time slot info.
      db_merge('ctl_onboarding_slot')
        ->key(array(
          'cohort_id' => $cohort_id,
          'slot_code' => $slot_code,
        ))
        ->fields(array(
          'max_trainers'    => 2,
          'num_registrants' => 0,
        ))
        ->execute();
    }
    else {
      //  TODO

      // if (slot exists) {

      // }
    }
  }

  // // Upsert trainee info.
  // db_merge('ctl_graduation_progress')
  //   ->key(array('uid' => $uid))
  //   ->fields(array(
  //     'did_live_sessions'       => $did_live_sessions,
  //     'did_observation_shift'   => $did_observation_shift,
  //     'did_roleplays'           => $did_roleplays,
  //     'passed_final_evaluation' => $passed_final_evaluation,
  //   ))
  //   ->execute();
}

// function _myelement_value($element, $input = FALSE, $form_state = array()) {
//   if ($input === FALSE) {
//     return isset($element['#default_value']) ? $element['#default_value'] : 0;
//   }
// }
