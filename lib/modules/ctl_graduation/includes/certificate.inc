<?php

/**
 * Trainee progress page.
 */
function _ctl_graduation_certificate_page($user) {
  $graduate_first_name = $user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
  $graduate_last_name  = $user->field_last_name[LANGUAGE_NONE][0]['safe_value'];
  $graduate_name       = "$graduate_first_name $graduate_last_name";

  // Find out the graduate's graduation date.
  $query = db_select('ctl_graduation_progress', 'gp');
  $query->addField('gp', 'graduation_timestamp');
  $result = $query
    ->condition('uid', $user->uid)
    ->execute()
    ->fetchAssoc();
  $graduation_date = format_date($result['graduation_timestamp'], 'custom', 'F j, Y');

  $content['certificate'] = array(
    '#type' => 'markup',
    '#markup' => theme('page__certificate', array(
      'certificate_image' => base_path() . drupal_get_path('module', 'ctl_graduation') . '/images/ctl-certificate-template.png',
      'graduate_name'     => $graduate_name,
      'graduation_date'   => $graduation_date,
    )),
  );
  return $content;
}
