<?php

$path = DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding');
require_once "$path/includes/team.inc";


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

  // TODO later
  // - this has been punted for now
  // $form['ctl_onboarding_creating_teams'] = array(
  //   '#type'          => 'checkbox',
  //   '#title'         => 'Create teams upon saving this settings screen',
  //   '#default_value' => FALSE,
  //   '#description'   => 'Note: You can use this to recreate teams if they already exist.  With great power comes great repsonsibility!',
  // );

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

  $capacity_range = range(20, 50, 5);
  $form['ctl_onboarding_trainer_capacity'] = array(
    '#type'          => 'select',
    '#title'         => t('Number of trainees per team'),
    '#default_value' => variable_get('ctl_onboarding_trainer_capacity', CTL_ONBOARDING_DEFAULT_TRAINER_CAPACITY),
    '#options'       => array_combine($capacity_range, $capacity_range),
    '#required'      => TRUE,
  );

  // Setup the selectable time slots.
  $days       = array('su', 'm', 'tu', 'w', 'th', 'f', 'sa');
  $slot_codes = array();
  for ($i = 0, $l = count($days); $i < $l; ++$i) {
    for ($hour = CTL_ONBOARDING_FIRST_START_HOUR; $hour <= CTL_ONBOARDING_LAST_START_HOUR; $hour += CTL_ONBOARDING_ONE_HOUR) {
      $start_hour_display  = _ctl_onboarding_format_hour_display($hour);
      $finish_hour_display = _ctl_onboarding_format_hour_display($hour + CTL_ONBOARDING_SESSION_DURATION);
      $slot_codes[$days[$i] . '-' . $hour] = $start_hour_display . ' - ' . $finish_hour_display . ' ET';
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

  $register_text = isset($pages_text['register']) ? $pages_text['register'] : NULL;
  $form['ctl_onboarding_pages_text']['register'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Registration pages',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_pages_text']['register']['open_message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Message while registration is open'),
    '#default_value' => isset($register_text['open_message']) ? $register_text['open_message'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['register']['closed_message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Message while registration is closed'),
    '#default_value' => isset($register_text['closed_message']) ? $register_text['closed_message'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['register']['success_message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Message for successful registration'),
    '#default_value' => isset($register_text['success_message']) ? $register_text['success_message'] : NULL,
  );

  $defer_text = isset($pages_text['defer']) ? $pages_text['defer'] : NULL;
  $form['ctl_onboarding_pages_text']['defer'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Defer page',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_pages_text']['defer']['confirmation_title'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Title for confirmation'),
    '#default_value' => isset($defer_text['confirmation_title']) ? $defer_text['confirmation_title'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['defer']['confirmation_message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Message for confirmation'),
    '#default_value' => isset($defer_text['confirmation_message']) ? $defer_text['confirmation_message'] : NULL,
  );

  $decline_text = isset($pages_text['decline']) ? $pages_text['decline'] : NULL;
  $form['ctl_onboarding_pages_text']['decline'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Decline page',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_pages_text']['decline']['confirmation_title'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Title for confirmation'),
    '#default_value' => isset($decline_text['confirmation_title']) ? $decline_text['confirmation_title'] : NULL,
  );
  $form['ctl_onboarding_pages_text']['decline']['confirmation_message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Message for confirmation'),
    '#default_value' => isset($decline_text['confirmation_message']) ? $decline_text['confirmation_message'] : NULL,
  );

  $email = variable_get('ctl_onboarding_email');
  $form['ctl_onboarding_email'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Email',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );

  $register_email = isset($email['register']) ? $email['register'] : NULL;
  $form['ctl_onboarding_email']['register'] = array(
    '#type'        => 'fieldset',
    '#title'       => '"Register" confirmation',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_email']['register']['subject'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Subject'),
    '#default_value' => isset($register_email['subject']) ? $register_email['subject'] : NULL,
  );
  $form['ctl_onboarding_email']['register']['body'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Body'),
    '#default_value' => isset($register_email['body']) ? $register_email['body'] : NULL,
  );

  $defer_email = isset($email['defer']) ? $email['defer'] : NULL;
  $form['ctl_onboarding_email']['defer'] = array(
    '#type'        => 'fieldset',
    '#title'       => '"Defer" confirmation',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_email']['defer']['subject'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Subject'),
    '#default_value' => isset($defer_email['subject']) ? $defer_email['subject'] : NULL,
  );
  $form['ctl_onboarding_email']['defer']['body'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Body'),
    '#default_value' => isset($defer_email['body']) ? $defer_email['body'] : NULL,
  );

  $decline_text = isset($email['decline']) ? $email['decline'] : NULL;
  $form['ctl_onboarding_email']['decline'] = array(
    '#type'        => 'fieldset',
    '#title'       => '"Decline" confirmation',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_email']['decline']['subject'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Subject'),
    '#default_value' => isset($decline_text['subject']) ? $decline_text['subject'] : NULL,
  );
  $form['ctl_onboarding_email']['decline']['body'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Body'),
    '#default_value' => isset($decline_text['body']) ? $decline_text['body'] : NULL,
  );

  $goodhire = variable_get('ctl_onboarding_goodhire');
  $form['ctl_onboarding_goodhire'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'GoodHire',
    '#collapsed'   => TRUE,
    '#collapsible' => TRUE,
    '#tree'        => TRUE,
  );
  $form['ctl_onboarding_goodhire']['enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable automatic background check requests'),
    '#default_value' => isset($goodhire['enabled']) ? $goodhire['enabled'] : FALSE,
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
    drupal_get_path('module', 'ctl_onboarding') . '/ctl_onboarding.css',
  );

  // // TODO nice to have
  // $form['#attached']['js'] = array(
  //   drupal_get_path('module', 'ctl_onboarding') . '/ctl_onboarding.js',
  // );

  // We'll need to do additional setup.
  $form['#submit'][] = '_ctl_onboarding_settings_submit_extra';

  return system_settings_form($form);
}


function _ctl_onboarding_settings_submit_extra($form, &$form_state) {
  $values    = $form_state['values'];
  $cohort_id = intval($values['ctl_onboarding_cohort_id']);

  // TODO later
  // - actually use our ctl_onboarding_cohort database table

  // TODO later
  // - this has been punted for now
  // $creating_teams = $values['ctl_onboarding_creating_teams'];
  // if ($creating_teams) {
  //   _ctl_onboarding_setup_teams($cohort_id);
  //   return;
  // }

  $slot_trainers = $values['ctl_onboarding_slot_trainers'];
  _ctl_onboarding_set_slots($cohort_id, $slot_trainers);
}


function _ctl_onboarding_set_slots($cohort_id, $slot_trainers) {
  foreach ($slot_trainers as $slot_code => $num_trainers) {
    // TODO later
    // - account for the case where registration is reopened from being previously closed

    // Upsert time slot info.
    db_merge('ctl_onboarding_slot')
      ->key(array('cohort_id' => $cohort_id, 'slot_code' => $slot_code))
      ->fields(array('num_trainers' => $num_trainers))
      ->execute();
  }
}
