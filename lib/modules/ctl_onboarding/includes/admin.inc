<?php

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding') . '/includes/team.inc';


function _ctl_onboarding_settings_form() {
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
  // We have the same range of choices as the cohort user field.
  $form['ctl_onboarding_cohort_id'] = array(
    '#type'          => 'select',
    '#title'         => t('Cohort #'),
    '#default_value' => variable_get('ctl_onboarding_cohort_id'),
    '#empty_value'   => 0,
    '#options'       => range(0, 20),
    '#required'      => TRUE,
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

  // Setup the selectable time slots.
  $days       = array('m', 'tu', 'w', 'th', 'f', 'sa', 'su');
  $slot_codes = array();
  for ($i = 0, $l = count($days); $i < $l; ++$i) {
    for ($hour = CTL_ONBOARDING_FIRST_START_HOUR; $hour <= CTL_ONBOARDING_LAST_START_HOUR; $hour += CTL_ONBOARDING_ONE_HOUR) {
      $start_hour_display  = _ctl_onboarding_format_hour_display($hour);
      $finish_hour_display = _ctl_onboarding_format_hour_display($hour + CTL_ONBOARDING_SESSION_DURATION);
      $slot_codes[$days[$i] . '-' . $hour] = $start_hour_display . ' - ' . $finish_hour_display;
    }
  }

  $slot_trainers = variable_get('ctl_onboarding_slot_trainers');
  $form['ctl_onboarding_slot_trainers'] = array(
    '#tree'        => TRUE,
    '#theme'       => array('ctl_onboarding_table'),
    '#showing_all' => TRUE,
  );
  foreach ($slot_codes as $slot_code => $slot_display) {
    $form['ctl_onboarding_slot_trainers'][$slot_code] = array(
      '#type'          => 'select',
      '#title'         => $slot_display,
      '#default_value' => isset($slot_trainers[$slot_code]) ? $slot_trainers[$slot_code] : 0,
      '#options'       => range(0, 10),
    );
  }

  $pages_text = variable_get('ctl_onboarding_pages_text');
  $form['ctl_onboarding_pages_text'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Pages text',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_pages_text']['registration-open'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Registration page while registration is open'),
    '#default_value' => isset($pages_text['registration-open']) ? $pages_text['registration-open'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['registration-closed'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Registration page while registration is closed'),
    '#default_value' => isset($pages_text['registration-closed']) ? $pages_text['registration-closed'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['deferred-confirmation-title'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Confirmation page title for deferring'),
    '#default_value' => isset($pages_text['deferred-confirmation-title']) ? $pages_text['deferred-confirmation-title'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['deferred-confirmation-message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Confirmation message for deferring'),
    '#default_value' => isset($pages_text['deferred-confirmation-message']) ? $pages_text['deferred-confirmation-message'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['declined-confirmation-title'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Confirmation page title for declining'),
    '#default_value' => isset($pages_text['declined-confirmation-title']) ? $pages_text['declined-confirmation-title'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['declined-confirmation-message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Confirmation message for declining'),
    '#default_value' => isset($pages_text['declined-confirmation-message']) ? $pages_text['declined-confirmation-message'] : NULL,
  );

  $email = variable_get('ctl_onboarding_email');
  $form['ctl_onboarding_email'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Email',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_email']['subject_for_registered'] = array(
    '#type'          => 'textfield',
    '#title'         => t('"Registered" email subject'),
    '#default_value' => isset($email['subject_for_registered']) ? $email['subject_for_registered'] : NULL,
  );
  $form['ctl_onboarding_email']['body_for_registered'] = array(
    '#type'          => 'textarea',
    '#title'         => t('"Registered" email body'),
    '#default_value' => isset($email['body_for_registered']) ? $email['body_for_registered'] : NULL,
  );
  $form['ctl_onboarding_email']['subject_for_deferred'] = array(
    '#type'          => 'textfield',
    '#title'         => t('"Deferred" email subject'),
    '#default_value' => isset($email['subject_for_deferred']) ? $email['subject_for_deferred'] : NULL,
  );
  $form['ctl_onboarding_email']['body_for_deferred'] = array(
    '#type'          => 'textarea',
    '#title'         => t('"Deferred" email body'),
    '#default_value' => isset($email['body_for_deferred']) ? $email['body_for_deferred'] : NULL,
  );
  $form['ctl_onboarding_email']['subject_for_declined'] = array(
    '#type'          => 'textfield',
    '#title'         => t('"Declined" email subject'),
    '#default_value' => isset($email['subject_for_declined']) ? $email['subject_for_declined'] : NULL,
  );
  $form['ctl_onboarding_email']['body_for_declined'] = array(
    '#type'          => 'textarea',
    '#title'         => t('"Declined" email body'),
    '#default_value' => isset($email['body_for_declined']) ? $email['body_for_declined'] : NULL,
  );

  $goodhire = variable_get('ctl_onboarding_goodhire');
  $form['ctl_onboarding_goodhire'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'GoodHire',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_goodhire']['endpoint'] = array(
    '#type'          => 'textfield',
    '#title'         => t('API Endpoint'),
    '#description'   => t('NOTE:  Do not include the "https://" part.'),
    '#default_value' => isset($goodhire['endpoint']) ? $goodhire['endpoint'] : NULL,
  );
  $form['ctl_onboarding_goodhire']['username'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Username'),
    '#default_value' => isset($goodhire['username']) ? $goodhire['username'] : NULL,
  );
  $form['ctl_onboarding_goodhire']['password'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Password'),
    '#default_value' => isset($goodhire['password']) ? $goodhire['password'] : NULL,
  );
  $form['ctl_onboarding_goodhire']['company_id'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Company ID'),
    '#default_value' => isset($goodhire['company_id']) ? $goodhire['company_id'] : NULL,
  );
  $form['ctl_onboarding_goodhire']['requestor_id'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Requestor ID'),
    '#default_value' => isset($goodhire['requestor_id']) ? $goodhire['requestor_id'] : NULL,
  );
  $form['ctl_onboarding_goodhire']['testing'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Test mode'),
    '#default_value' => isset($goodhire['testing']) ? $goodhire['testing'] : FALSE,
  );
  $form['ctl_onboarding_goodhire']['test_email'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Test email'),
    '#default_value' => isset($goodhire['test_email']) ? $goodhire['test_email'] : NULL,
  );

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
  $cohort_id      = intval($values['ctl_onboarding_cohort_id']);
  $creating_teams = $values['ctl_onboarding_creating_teams'];
  if ($creating_teams) {
    _ctl_onboarding_setup_teams($cohort_id);
    return;
  }
  $slot_trainers = $values['ctl_onboarding_slot_trainers'];
  _ctl_onboarding_set_slots($cohort_id, $slot_trainers);
}


function _ctl_onboarding_set_slots($cohort_id, $slot_trainers) {
  foreach ($slot_trainers as $slot_code => $num_trainers) {
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
          'num_trainers'    => $num_trainers,
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