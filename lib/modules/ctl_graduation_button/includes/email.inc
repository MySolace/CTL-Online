<?php

function ctl_graduation_button_mail($key, &$message, $params) {
  global $user;

  $options = array(
    'langcode' => $message['language']->language,
  );

  switch ($key) {
    // Send a simple message from the contact form.
    case 'contact_message':
      $message['subject'] = t('E-mail sent from @site-name', array('@site-name' => variable_get('site_name', 'Drupal')), $options);
      // Note that the message body is an array, not a string.
      $message['body'][] = t('@name sent you the following message:', array('@name' => $user->name), $options);
      // Because this is just user-entered text, we do not need to translate it.
      // Since user-entered text may have unintentional HTML entities in it like
      // '<' or '>', we need to make sure these entities are properly escaped,
      // as the body will later be transformed from HTML to text, meaning
      // that a normal use of '<' will result in truncation of the message.
      $message['body'][] = check_plain($params['message']);
      break;
  }
}


/**
 * Notifies the trainee that they have graduated.
 */
function _ctl_graduation_button_mail_send($form_values) {
  $module   = 'ctl_graduation_button';
  $key      = 'graduate';
  $language = user_preferred_language();
  $params   = $form_values;

  $uid = $form_values['uid'];

  $to      = $form_values['email'];
  $from    = 'volunteers@crisistextline.org';
  $subject = 'Congratulations, you are a counselor now!';

  // $first_name = $user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
  // $last_name  = $user->field_last_name[LANGUAGE_NONE][0]['safe_value'];

  $body = '';

  $send = FALSE;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);

  return $result;
}


/**
 * Form validation logic for the contact form.
 */
// function ctl_graduation_button_form_validate($form, &$form_state) {
//   if (!valid_email_address($form_state['values']['email'])) {
//     form_set_error('email', t('That e-mail address is not valid.'));
//   }
// }


/**
 * Form submission logic for the contact form.
 */
// function ctl_graduation_button_form_submit($form, &$form_state) {
//   email_example_mail_send($form_state['values']);
// }
