<?php

function _ctl_graduation_settings_form() {
  $message = variable_get('ctl_graduation_message');
  $form['ctl_graduation_message'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Graduation email message'),
    '#default_value' => isset($message) ? $message : NULL,
  );
  return system_settings_form($form);
}
