<?php

/**
 * Trainee certificate page.
 */
function _ctl_graduation_button_certificate_page() {
  // $path = drupal_get_path('module', 'ctl_graduation_button');

  $content['stuff'] = array(
    '#type'   => 'markup',
    '#markup' => '<strong>certificate goes here</strong>',
  );

  return $content;
}
