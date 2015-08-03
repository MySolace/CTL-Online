<?php

/**
 * Implements hook_mail().
 */
function ctl_graduation_button_mail($key, &$message, $params) {
   switch ($key) {
    // Send a simple message from the contact form.
    case 'graduate':
      $uid  = $params['uid'];
      $user = user_load($uid)

      // $options = array(
      //   'langcode' => $message['language']->language,
      // );
      // $message['body'][] = t('@name sent you the following message:', array('@name' => $user->name), $options);

      $first_name   = $user->field_first_name[LANGUAGE_NONE][0]['safe_value'];
      $last_name    = $user->field_last_name[LANGUAGE_NONE][0]['safe_value'];
      $trainer_name = '';

      $message['subject'] = t('Congratulations, you are a counselor now!');
      $message['body']    = _ctl_graduation_button_mail_body($uid, "$first_name $last_name", $trainer_name);

      break;
  }
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
  $to       = $user->mail;
  $send     = TRUE;
  $result   = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  return $result;
}


/**
 * Builds the graduation email message body.
 */
function _ctl_graduation_button_mail_body($uid, $graduate_name, $trainer_name) {
  return array(
    "<p>Hi </strong>$graduate_name</strong>,</p>",
    '<p>Congratulations on graduating from the Crisis Counselor Training Program! I am so excited to welcome you to the amazing team of crisis counselors who help save lives every day.</p>',
    '<p><strong>You’re a newly minted crisis counselor, now what?</strong></p>',
    '<p><strong>First, sign up for your weekly counseling shift.</strong></p>',
    '<ul>',
      '<li>Use the scheduling tool in CTL Online: <a href="https://online.crisistextline.org/schedule/">https://online.crisistextline.org/schedule/</a></li>',
      '<li>Click "<strong>Sign up for Shift</strong>" &gt; choose a day of the week &gt; select an available shift (note: all times are in EST) &gt; confirm by hitting "<strong>Sign up for this shift</strong>" button at the bottom</li>',
      '<li>See detailed instructions here for scheduling shifts and make-ups:</li>',
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
  );
}
