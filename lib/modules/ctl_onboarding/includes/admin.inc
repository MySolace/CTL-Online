<?php

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding') . '/includes/team.inc';


function _ctl_onboarding_settings_form() {
  $days       = array('m', 'tu', 'w', 'th', 'f', 'sa', 'su');
  $slot_codes = array();

  // Setup the selectable time slots.
  for ($i = 0, $l = count($days); $i < $l; ++$i) {
    for ($hour = CTL_ONBOARDING_FIRST_START_HOUR; $hour <= CTL_ONBOARDING_LAST_START_HOUR; $hour += CTL_ONBOARDING_ONE_HOUR) {
      $start_hour_display  = _ctl_onboarding_format_hour_display($hour);
      $finish_hour_display = _ctl_onboarding_format_hour_display($hour + CTL_ONBOARDING_SESSION_DURATION);
      $slot_codes[$days[$i] . '-' . $hour] = $start_hour_display . ' - ' . $finish_hour_display;
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
  $form['ctl_onboarding_creating_teams'] = array(
    '#type'          => 'checkbox',
    '#title'         => 'Create teams upon saving this settings screen',
    '#default_value' => FALSE,
    '#description'   => 'Note: You can use this to recreate teams if they already exist.  With great power comes great repsonsibility!',
  );
  $form['ctl_onboarding_cohort_id'] = array(
    '#type'          => 'select',
    '#title'         => t('Cohort #'),
    '#default_value' => variable_get('ctl_onboarding_cohort_id'),
    '#required'      => TRUE,
    // We have the same range of choices as the cohort user field.
    '#options' => range(1, 20),
  );
  $form['ctl_onboarding_registration_start_date'] = array(
    '#type'          => 'date',
    '#title'         => t('Start of sign-up'),
    '#default_value' => variable_get('ctl_onboarding_registration_start_date'),
  );
  $form['ctl_onboarding_registration_finish_date'] = array(
    '#type'          => 'date',
    '#title'         => t('End of sign-up'),
    '#default_value' => variable_get('ctl_onboarding_registration_finish_date'),
  );
  $form['ctl_onboarding_trainer_capacity'] = array(
    '#type'          => 'select',
    '#title'         => t('Number of trainees per team'),
    '#default_value' => variable_get('ctl_onboarding_trainer_capacity', CTL_ONBOARDING_DEFAULT_TRAINER_CAPACITY),
    '#options'       => range(20, 50, 5),
    '#required'      => TRUE,
  );
  $form['ctl_onboarding_slot_codes'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Choose time slots to have available for registration'),
    '#options'       => $slot_codes,
    '#default_value' => variable_get('ctl_onboarding_slot_codes'),
    '#theme'         => array('ctl_onboarding_table'),
    '#showing_all'   => TRUE,
  );


  $z = variable_get('ctl_onboarding_slot_codes_3', array());
  $form['ctl_onboarding_slot_codes_3'] = array(
    '#tree' => TRUE,
  );
  $form['ctl_onboarding_slot_codes_3']['m-800'] = array(
    '#type'          => 'select',
    '#title'         => t('8am - 12pm'),
    '#default_value' => $z['m-800'],
    '#options'       => range(0, 10),
  );



  $form['ctl_onboarding_email_settings'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Email settings',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $email_settings = variable_get('ctl_onboarding_email_settings');
  $form['ctl_onboarding_email_settings']['subject_for_registered'] = array(
    '#type'          => 'textfield',
    '#title'         => t('"Registered" email subject'),
    '#default_value' => $email_settings['subject_for_registered'],
  );
  $form['ctl_onboarding_email_settings']['body_for_registered'] = array(
    '#type'          => 'textarea',
    '#title'         => t('"Registered" email body'),
    '#default_value' => $email_settings['body_for_registered'],
  );


  // // $x = token_replace($email_settings['subject_for_registered']);
  // $x = token_replace($email_settings['body_for_registered']);
  // dsm($x);

  // $form['my_module_config_node'] = array(
  //   '#type' => 'fieldset',
  //   '#title' => 'Node type configuration',
  //   '#tree' => TRUE, //  $label) {
  //   $form['my_module_config_node'][$type] = array(
  //     '#type' => 'select',
  //     '#options' => $opts,
  //     '#title' => t('Select value for %type', array('%type' => $label)),
  //     '#default_value' => !empty($values[$type]) ? $values[$type] : 5,
  //   );
  // }


  $form['#attached']['css'] = array(
    drupal_get_path('module', 'ctl_onboarding') . '/scripts/ctl_onboarding.css',
  );
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'ctl_onboarding') . '/scripts/ctl_onboarding.js',
  );

  // We'll need to do additional setup.
  $form['#submit'][] = '_ctl_onboarding_settings_submit_extra';

  return system_settings_form($form);
}


function _ctl_onboarding_settings_submit_extra($form, &$form_state) {
  $values         = $form_state['values'];

  // dsm($values);

  $cohort_id      = intval($values['ctl_onboarding_cohort_id']);
  $creating_teams = $values['ctl_onboarding_creating_teams'];
  if ($creating_teams) {
    _ctl_onboarding_setup_teams($cohort_id);
    return;
  }
  $slot_codes = $values['ctl_onboarding_slot_codes'];
  _ctl_onboarding_set_slots($cohort_id, $slot_codes);
}


function _ctl_onboarding_set_slots($cohort_id, $slot_codes) {
  foreach ($slot_codes as $slot_code) {

    // dsm($slot_code);

    if ($slot_code) {
      // TODO
      // - account for the case where registration is reopened from being previously closed

      // Upsert time slot info.
      db_merge('ctl_onboarding_slot')
        ->key(array(
          'cohort_id' => $cohort_id,
          'slot_code' => $slot_code,
        ))
        ->fields(array(
          'num_trainers'    => 2,
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
}
