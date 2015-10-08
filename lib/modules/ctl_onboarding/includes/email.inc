<?php

/**
 * Implements hook_mail().
 */
function ctl_onboarding_mail($key, &$message, $params) {
  $statuses = array('register', 'defer', 'decline');
  if (!in_array($key, $statuses)) {
    return;
  }

  $user = $params['user'];

  $preferred_name = field_get_items('user', $user, 'field_preferred_name');
  if (empty($preferred_name)) {
    $field_first_name = field_get_items('user', $user, 'field_first_name');
    $field_last_name  = field_get_items('user', $user, 'field_last_name');
    $first_name       = $field_first_name ? $field_first_name[0]['value'] : '';
    $last_name        = $field_last_name ? $field_last_name[0]['value'] : '';
    $name             = implode(' ', array($first_name, $last_name));
  }
  else {
    $name = $preferred_name[0]['value'];
  }

  $email = variable_get('ctl_onboarding_email');

  switch ($key) {
    case 'register':
      $slot_code = '';

      $query = db_select('ctl_onboarding_registrant', 'r');
      $query->addField('r', 'slot_code');
      $result = $query
        ->condition('r.uid', $user->uid)
        ->execute()
        ->fetchAll();

      if (!empty($result)) {
        $slot_code = $result[0]->slot_code;
      }

      $register_email = isset($email['register']) ? $email['register'] : NULL;
      $subject        = isset($register_email['subject']) ? $register_email['subject'] : '';
      $body           = isset($register_email['body']) ? $register_email['body'] : '';
      $replacements   = array('name' => $name, 'slot_code' => $slot_code);
      break;

    case 'defer':
      $defer_email  = isset($email['defer']) ? $email['defer'] : NULL;
      $subject      = isset($defer_email['subject']) ? $defer_email['subject'] : '';
      $body         = isset($defer_email['body']) ? $defer_email['body'] : '';
      $replacements = array('name' => $name);
      break;

    case 'decline':
      $decline_email = isset($email['decline']) ? $email['decline'] : NULL;
      $subject       = isset($decline_email['subject']) ? $decline_email['subject'] : '';
      $body          = isset($decline_email['body']) ? $decline_email['body'] : '';
      $replacements  = array('name' => $name);
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
  return !empty($result['result']);
}


// TODO later
// - separate this into a submodule
function _ctl_onboarding_registration_email_test() {
  $email = variable_get('ctl_onboarding_email');
  $email_subject = token_replace($email['register']['subject']);
  $email_message = token_replace($email['register']['body'], array(
    'name' => 'dsgfhjdsljghldjshfg',
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


// TODO later
// - separate this into a submodule
function _ctl_onboarding_deferred_email_test() {
  $email = variable_get('ctl_onboarding_email');
  $email_subject = token_replace($email['defer']['subject']);
  $email_message = token_replace($email['defer']['body']);

  $content = '<h5>Subject:</h5>';
  $content .= $email_subject;
  $content .= '<h5>Body:</h5>';
  $content .= $email_message;

  return $content;
}


// TODO later
// - separate this into a submodule
function _ctl_onboarding_declined_email_test() {
  $email = variable_get('ctl_onboarding_email');
  $email_subject = token_replace($email['decline']['subject']);
  $email_message = token_replace($email['decline']['body']);

  $content = '<h5>Subject:</h5>';
  $content .= $email_subject;
  $content .= '<h5>Body:</h5>';
  $content .= $email_message;

  return $content;
}
