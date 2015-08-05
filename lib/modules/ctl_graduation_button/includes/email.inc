<?php

/**
 * Implements hook_mail().
 */
function ctl_graduation_button_mail($key, &$message, $params) {
  if ($key !== 'graduate') {
    return;
  }

  $graduate_uid        = $params['uid'];
  $graduate_user       = user_load($graduate_uid);
  $graduate_first_name = $graduate_user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
  $graduate_last_name  = $graduate_user->field_last_name[LANGUAGE_NONE][0]['safe_value'];

  $trainer_uid        = $graduate_user->field_trainer[LANGUAGE_NONE][0]['target_id'];
  $trainer_user       = user_load($trainer_uid);
  $trainer_first_name = $trainer_user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
  $trainer_last_name  = $trainer_user->field_last_name[LANGUAGE_NONE][0]['safe_value'];

  $email_message = theme('graduation_message', array(
    'graduate_name' => "$graduate_first_name $graduate_last_name",
    'graduate_uid'  => $graduate_uid,
    'trainer_name'  => "$trainer_first_name $trainer_last_name",
  ));

  $options = array(
    'langcode' => $message['language']->language,
  );

  $message['subject'] = t('Congratulations, @graduate_name, you are a counselor now!', array('@graduate_name' => "$graduate_first_name $graduate_last_name"), $options);
  $message['body']    = explode(PHP_EOL, $email_message);
}


/**
 * Notifies the trainee that they have graduated.
 */
function _ctl_graduation_button_mail_send($form_values) {
  $module   = 'ctl_graduation_button';
  $key      = 'graduate';
  $params   = $form_values;
  $uid      = $form_values['uid'];
  $user     = user_load($uid);
  $language = user_preferred_language($user);
  $from     = 'volunteers@crisistextline.org';

  // $to       = $user->mail;
  $to       = 'ramartin.net@gmail.com';

  $send     = TRUE;
  $result   = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  return (isset($result['result']) && $result['result']);
}
