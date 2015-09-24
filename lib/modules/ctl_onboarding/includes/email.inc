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

  return;

  // // $x = token_replace($email_settings['subject_for_registered']);
  // $x = token_replace($email_settings['body_for_registered']);
  // dsm($x);

  // $graduate_uid        = $params['uid'];
  // $graduate_user       = user_load($graduate_uid);
  // $graduate_first_name = $graduate_user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
  // $graduate_last_name  = $graduate_user->field_last_name[LANGUAGE_NONE][0]['safe_value'];
  // $graduate_name       = "$graduate_first_name $graduate_last_name";

  // $trainer_uid = $graduate_user->field_trainer[LANGUAGE_NONE][0]['target_id'];
  // $trainer_user = user_load($trainer_uid);
  // if ($trainer_user) {
  //   // $trainer_name = format_username($user);
  //   $trainer_first_name = $trainer_user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
  //   $trainer_last_name  = $trainer_user->field_last_name[LANGUAGE_NONE][0]['safe_value'];
  //   $trainer_name = "$trainer_first_name $trainer_last_name";
  // }
  // else {
  //   $trainer_name = 'Patty Morrissey';
  // }


  // $email_message = theme('graduation_message', array(
  //   'graduate_name' => $graduate_name,
  //   'graduate_uid'  => $graduate_uid,
  //   'trainer_name'  => $trainer_name,
  // ));

  // $options = array(
  //   'langcode' => $message['language']->language,
  // );

  // $message['subject'] = t('Congratulations, @graduate_name, you are a counselor now!', array('@graduate_name' => "$graduate_first_name $graduate_last_name"), $options);
  // $message['body']    = explode(PHP_EOL, $email_message);
}


// /**
//  * Notifies the trainee that they have graduated.
//  */
// function _ctl_graduation_mail_send($form_values) {
//   $module   = 'ctl_graduation';
//   $key      = 'graduate';
//   $params   = $form_values;
//   $uid      = $form_values['uid'];
//   $user     = user_load($uid);
//   $language = user_preferred_language($user);
//   $from     = 'volunteers@crisistextline.org';
//   $to       = $user->mail;
//   $send     = TRUE;
//   $result   = drupal_mail($module, $key, $to, $language, $params, $from, $send);
//   return (isset($result['result']) && $result['result']);
// }







// /**
//  * Updates the trainee's roles and sends them a graduation email.
//  */
// function _ctl_graduation_form_submit_graduate($form, &$form_state) {


//   drupal_set_message(t('This trainee has now been graduated!'));

//   if (_ctl_graduation_mail_send($form_values)) {
//     drupal_set_message(t('A graduation email has been sent to the new graduate.'));
//   }
//   else {
//     drupal_set_message(t('There was a problem sending the new graduate the graduation email.'), 'error');
//   }
// }






function _ctl_onboarding_registration_email_test() {
  $email = variable_get('ctl_onboarding_email');
  $email_subject = token_replace($email['subject_for_registered']);
  $email_message = token_replace($email['body_for_registered'], array(
    'user-name' => 'dsgfhjdsljghldjshfg',
  ));

  $content = '<h5>Subject:</h5>';
  $content .= $email_subject;

  // TODO
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
