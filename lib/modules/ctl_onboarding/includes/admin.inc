<?php

function _ctl_onboarding_settings_form() {
  $days             = array('m', 'tu', 'w', 'th', 'f', 'sa', 'su');
  $first_start_hour = 800;
  $last_start_hour  = 1900;
  $slots            = array();

  // Setup the selectable time slots.
  for ($i = 0, $l = count($days); $i < $l; ++$i) {
    for ($hour = $first_start_hour; $hour <= $last_start_hour; $hour += 100) {
      $start_hour_display  = _ctl_onboarding_format_hour_display($hour);
      $finish_hour_display = _ctl_onboarding_format_hour_display($hour + 400);

      $slots[$days[$i] . '-' . $hour] = $start_hour_display . ' - ' . $finish_hour_display;
    }
  }

  $form['ctl_onboarding_registration_open'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable registration'),
    '#default_value' => variable_get('ctl_onboarding_registration_open', FALSE),
  );

  // cohort start date

  // cohort finish date

  $form['ctl_onboarding_slots'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Choose time slots to have available for registration'),
    '#options'       => $slots,
    '#default_value' => variable_get('ctl_onboarding_slots'),
    '#theme'         => array('ctl_onboarding_table'),
    '#showing_all'   => TRUE,
  );

  return system_settings_form($form);
}
