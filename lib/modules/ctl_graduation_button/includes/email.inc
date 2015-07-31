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
  $module       = 'ctl_graduation_button';
  $key          = 'graduate';
  $params       = $form_values;
  $uid          = $form_values['uid'];
  $user         = user_load($uid);
  $language     = user_preferred_language($user);
  $from         = 'volunteers@crisistextline.org';
  $to           = $user->mail;
  $subject      = 'Congratulations, you are a counselor now!';
  $first_name   = $user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
  $last_name    = $user->field_last_name[LANGUAGE_NONE][0]['safe_value'];
  $trainer_name = '';
  $body         = _ctl_graduation_button_mail_body($uid, "$first_name $last_name", $trainer_name);
  $send         = TRUE;
  $result       = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  return $result;
}


/**
 * Builds the graduation email message body.
 */
function _ctl_graduation_button_mail_body($uid, $graduate_name, $trainer_name) {
  return implode(PHP_EOL, array(
    "<p>Hi </strong>$graduate_name</strong>,</p>",
    '<p>Congratulations on graduating from the Crisis Counselor Training Program! I am so excited to welcome you to the amazing team of crisis counselors who help save lives every day.</p>',
    '<p><strong>You’re a newly minted crisis counselor, now what?</strong></p>',
    '<p><strong>First, sign up for your weekly counseling shift.</strong></p>',
    '<ul>',
      '<li>Use the scheduling tool in CTL Online: <a href="https://online.crisistextline.org/schedule/">https://online.crisistextline.org/schedule/</a></li>',
      '<li>See detailed instructions here:</li>',
      '<li>Remember, crisis counselors commit to a minimum of one four-hour shift per week for one year</li>',
      '<li>Contact <a href="volunteers@crisistextline.org">volunteers@crisistextline.org</a> for any questions about scheduling policies or the scheduling tool</li>',
    '</ul>',
    '<p><strong>Say hello to the supervisors.</strong> Our team of amazing supervisors have your back - they’re on the platform 24/7 to support you during your weekly shifts. They’ll answer your questions and work with in cases of imminent harm or suspected abuse/neglect.</p>',
    '<p><strong>Bookmark these links.</strong></p>',
    '<ul>',
      '<li>',
        'CTL Online: <a href="https://online.crisistextline.org">https://online.crisistextline.org</a>',
        '<ul>',
          '<li><a href="https://online.crisistextline.org/schedule/my-schedule">Shift scheduling</a></li>',
          '<li><a href="https://online.crisistextline.org/training">Access training materials</a></li>',
        '</ul>',
      '</li>',
      '<li>',
        'The Platform: <a href="https://app.crisistextline.org">https://app.crisistextline.org</a>',
        '<ul>',
          '<li>This is where you’ll go each week for your crisis counseling shift</li>',
          '<li>Make sure to keep your phone on hand for the two-step verification each time you log in</li>',
        '</ul>',
      '</li>',
    '</ul>',
    '<p><strong>Celebrate your accomplishment.</strong><br />',
    "Access your certificate of completion <a href=\"https://online.crisistextline.org/user/$uid/certificate\">here</a><br />",
    'Print it out and display it proudly!</p>',
    '<p>nbsp;</p>',
    '<p>Onward,</p>',
    "<p><strong>$trainer_name, Crisis Counselor Trainer</strong></p>",
  ));
}
