<?php

require_once __DIR__ . '/email.inc';


/**
 * Trainee progress page.
 */
function _ctl_graduation_button_progress_page($user) {
  $uid = $user->uid;

  $view = views_get_view('trainee_course_progress');
  $result = $view->preview('default', array($uid));

  $markup = implode('<br />', array(
    '<strong>' . var_export($result, TRUE) . '</strong>',
  ));

  if (in_array('Graduate', $user->roles)) {
    $content['course_progress'] = array(
      '#type'   => 'markup',
      '#markup' => '<p>This person has already graduated.',
    );
  }
  else {
    $content['course_progress'] = array(
      '#type'   => 'markup',
      '#markup' => '<p>Has this trainee completed all the course modules?</p><p>' . '' . '</p>',
    );
    $content['graduate'] = drupal_get_form('ctl_graduation_button_form', $uid);
  }

  return $content;
}


/**
 * Implements hook_form().
 */
function ctl_graduation_button_form($form, &$form_state, $uid) {
  $form['additional_requirements'] = array(
    '#type'     => 'checkboxes',
    '#title'    => t('Additional requirements'),
    '#required' => TRUE,
    '#options' => array(
      'did_live_sessions'     => t('This trainee has attended all live sessions.'),
      'did_observation_shift' => t('This trainee has completed 1 observation shift.'),
      'did_roleplays'         => t('This trainee has completed 5 roleplays.'),
    ),
  );

  $form['uid'] = array(
    '#type'  => 'hidden',
    '#value' => $uid,
  );

  // $form['update'] = array(
  //   '#type'     => 'submit',
  //   '#value'    => 'Update',
  //   '#validate' => array('_ctl_graduation_button_form_validate_update'),
  //   '#submit'   => array('_ctl_graduation_button_form_submit_update'),
  // );

  $form['graduate'] = array(
    '#type'     => 'submit',
    '#value'    => 'Graduate',
    '#validate' => array('_ctl_graduation_button_form_validate_graduate'),
    '#submit'   => array('_ctl_graduation_button_form_submit_graduate'),
  );

  return $form;
}


// /**
//  * Records the trainer's updates on the trainee's progress.
//  */
// function _ctl_graduation_button_form_submit_update($form, &$form_state) {
// }


/**
 * Verifies that all the graduation requirements have been met.
 */
function _ctl_graduation_button_form_validate_graduate($form, &$form_state) {
  $form_values                 = $form_state['values'];
  $additional_requirements     = $form_values['additional_requirements'];
  $unmet_additional_requirements = array_filter($additional_requirements, function ($v) {
    return empty($v);
  });

  if (!empty($unmet_additional_requirements)) {
    form_set_error('additional_requirements', t('The trainee must pass all the additional requirements.'));
  }
}


/**
 * Updates the trainee's roles and sends them a graduation email.
 */
function _ctl_graduation_button_form_submit_graduate($form, &$form_state) {
  $form_values = $form_state['values'];

  $uid = $form_values['uid'];

  // // The graduate is no longer a trainee.
  // $cur_role = 'Trainee';
  // $role = user_role_load_by_name($cur_role);
  // user_multiple_role_edit(array($uid), 'remove_role', $role->rid);

  // // Assign new roles.
  // $next_roles = array('Graduate', 'Crisis Counselor I');
  // foreach ($next_roles as $next_role) {
  //   $role = user_role_load_by_name($next_role);
  //   user_multiple_role_edit(array($uid), 'add_role', $role->rid);
  // }

  // drupal_write_record('ctl_graduation_button_requirements', $record);
  // drupal_write_record('ctl_graduation_button_requirements', $record, 'uid');

  drupal_set_message(t('This trainee has now been graduated!'));

  // $result = _ctl_graduation_button_mail_send($form_state['values']);
  // if ($result['result'] == TRUE) {
  //   drupal_set_message(t('An graduation email has been sent to the trainee.'));
  // }
  // else {
  //   drupal_set_message(t('There was a problem sending the trainee the graduation message.'), 'error');
  // }
}
