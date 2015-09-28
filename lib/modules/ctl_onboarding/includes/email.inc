<?php

/**
 * Implements hook_mail().
 */
// TODO
function ctl_onboarding_mail($key, &$message, $params) {
  $statuses = array('registered', 'deferred', 'declined');
  if (!in_array($key, $statuses)) {
    return;
  }

  $user             = $params['user'];
  $field_first_name = field_get_items('user', $user, 'field_first_name');
  $field_last_name  = field_get_items('user', $user, 'field_last_name');
  $first_name       = $field_first_name ? $field_first_name[0]['value'] : '';
  $last_name        = $field_last_name ? $field_last_name[0]['value'] : '';
  $full_name        = "$first_name $last_name";

  $email = variable_get('ctl_onboarding_email');

  switch ($key) {
    case 'registered':
      $subject      = isset($email['subject_for_registered']) ? $email['subject_for_registered'] : '';
      $body         = isset($email['body_for_registered']) ? $email['body_for_registered'] : '';
      $replacements = array('full-name' => $full_name);
      break;

    case 'deferred':
      $subject      = isset($email['subject_for_deferred']) ? $email['subject_for_deferred'] : '';
      $body         = isset($email['body_for_deferred']) ? $email['body_for_deferred'] : '';
      $replacements = array('full-name' => $full_name);
      break;

    case 'declined':
      $subject      = isset($email['subject_for_declined']) ? $email['subject_for_declined'] : '';
      $body         = isset($email['body_for_declined']) ? $email['body_for_declined'] : '';
      $replacements = array('full-name' => $full_name);
      break;
  }

  $message['subject'] = token_replace($subject);
  $message['body']    = explode(PHP_EOL, token_replace($body, $replacements));
}


/**
 * Sends the potential trainee a message.
 */
function _ctl_onboarding_mail_send($data) {
  $module   = 'ctl_onboarding';
  $key      = $data['key'];
  $user     = $data['user'];
  $to       = $user->mail;
  $language = user_preferred_language($user);
  $params   = $data;
  $from     = 'volunteers@crisistextline.org';
  $send     = TRUE;
  $result   = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  return (isset($result['result']) && $result['result']);
}


function _ctl_onboarding_registration_email_test() {
  $email = variable_get('ctl_onboarding_email');
  $email_subject = token_replace($email['subject_for_registered']);
  $email_message = token_replace($email['body_for_registered'], array(
    'user-name' => 'dsgfhjdsljghldjshfg',
  ));

  $content = '<h5>Subject:</h5>';
  $content .= $email_subject;

  // TODO later
  // - upgrade local PHP to make using markdown possible:
  // https://www.drupal.org/project/commonmark
  // $email_message = commonmark_convert_to_html($email_message);

  $content .= '<h5>Body:</h5>';
  $content .= $email_message;

  return $content;
}


function _ctl_onboarding_deferred_email_test() {
  $email = variable_get('ctl_onboarding_email');
  $email_subject = token_replace($email['subject_for_deferred']);
  $email_message = token_replace($email['body_for_deferred']);

  $content = '<h5>Subject:</h5>';
  $content .= $email_subject;
  $content .= '<h5>Body:</h5>';
  $content .= $email_message;

  return $content;
}


function _ctl_onboarding_declined_email_test() {
  $email = variable_get('ctl_onboarding_email');
  $email_subject = token_replace($email['subject_for_declined']);
  $email_message = token_replace($email['body_for_declined']);

  $content = '<h5>Subject:</h5>';
  $content .= $email_subject;
  $content .= '<h5>Body:</h5>';
  $content .= $email_message;

  return $content;
}
