<?php

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_graduation') . '/includes/email.inc';


/**
 * Checks to see if the trainee has completed all the courses.
 */
function _ctl_graduation_courses_completed($uid) {
  // Find which courses the trainee has not yet completed.
  $query = db_select('course_node', 'cn');
  $query->leftJoin('course_report', 'cr', 'cn.nid = cr.nid');
  $query->addField('cr', 'nid');
  $result = $query
    ->condition('cr.uid', $uid)
    ->condition(
      db_or()
        // This is of course means the course is incomplete.
        ->condition('cr.complete', 0)
        // But this means the course has yet to have been
        // enrolled into in the first place.
        ->condition('cr.complete', NULL)
    )
    ->execute()
    ->fetchAll();
  $completed = empty($result);
  return $completed;
}


/**
 * Trainee progress page.
 */
function _ctl_graduation_progress_page($user) {
  if (in_array('Graduate', $user->roles)) {
    $content['course_progress'] = array(
      '#type'   => 'markup',
      '#markup' => '<p>This person has already graduated.</p>',
    );
  }
  else {
    $uid = $user->uid;
    $courses_completed = _ctl_graduation_courses_completed($uid);
    $content['course_progress'] = array(
      '#type'   => 'markup',
      '#markup' => '<p>Has this trainee completed all the required course modules?</p>'
                . '<p><strong>' . ($courses_completed ? 'Yes!' : 'Not yet') . '</strong></p>',
    );
    $content['graduate'] = drupal_get_form('ctl_graduation_form', $uid);
  }
  return $content;
}


/**
 * Implements hook_form().
 */
function ctl_graduation_form($form, &$form_state, $uid) {
  $query = db_select('ctl_graduation_progress', 'gp');
  $query->addField('gp', 'did_live_sessions');
  $query->addField('gp', 'did_observation_shift');
  $query->addField('gp', 'did_roleplays');
  $query->addField('gp', 'passed_final_evaluation');
  $result = $query
    ->condition('uid', $uid)
    ->execute()
    ->fetchAssoc();

  if ($result !== FALSE) {
    $completed_tasks = array_filter($result);
    $remaining_tasks = array_diff($result, $completed_tasks);
    $defaults        = array_keys($completed_tasks);
  }
  else {
    $remaining_tasks = array(TRUE);       // Slightly hackish.
    $defaults = array();
  }

  $form['additional_requirements'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Additional requirements'),
    '#default_value' => $defaults,
      '#options' => array(
      'did_live_sessions'       => t('This trainee has attended the required live sessions.'),
      'did_observation_shift'   => t('This trainee has completed the required observation shift.'),
      'did_roleplays'           => t('This trainee has completed the required roleplays.'),
      'passed_final_evaluation' => t('This trainee has passed the final evaluation.'),
    ),
  );

  $form['uid'] = array(
    '#type'  => 'hidden',
    '#value' => $uid,
  );

  $form['update'] = array(
    '#type'   => 'submit',
    '#value'  => 'Update',
    '#submit' => array('_ctl_graduation_form_submit_update'),
  );

  // TODO
  // - restore this line when the time is right
  // if (_ctl_graduation_courses_completed($uid) && empty($remaining_tasks)) {
  if (empty($remaining_tasks)) {
    $form['graduate'] = array(
      '#type'     => 'submit',
      '#value'    => 'Graduate',
      '#validate' => array('_ctl_graduation_form_validate_graduate'),
      '#submit'   => array('_ctl_graduation_form_submit_graduate'),
    );
  }

  return $form;
}


/**
 * Records the trainer's updates on the trainee's progress.
 */
function _ctl_graduation_form_submit_update($form, &$form_state) {
  $form_values             = $form_state['values'];
  $uid                     = $form_values['uid'];
  $additional_requirements = $form_values['additional_requirements'];
  $did_live_sessions       = intval(!empty($additional_requirements['did_live_sessions']));
  $did_observation_shift   = intval(!empty($additional_requirements['did_observation_shift']));
  $did_roleplays           = intval(!empty($additional_requirements['did_roleplays']));
  $passed_final_evaluation = intval(!empty($additional_requirements['passed_final_evaluation']));

  // Upsert trainee info.
  db_merge('ctl_graduation_progress')
    ->key(array('uid' => $uid))
    ->fields(array(
      'did_live_sessions'       => $did_live_sessions,
      'did_observation_shift'   => $did_observation_shift,
      'did_roleplays'           => $did_roleplays,
      'passed_final_evaluation' => $passed_final_evaluation,
    ))
    ->execute();

  drupal_set_message(t("The trainee's progress has been updated."));
}


/**
 * Verifies that all the graduation requirements have been met.
 */
function _ctl_graduation_form_validate_graduate($form, &$form_state) {
  $form_values = $form_state['values'];
  $unmet_requirements = array(_ctl_graduation_courses_completed($form_values['uid']))
                      + $form_values['additional_requirements'];
  $unmet_requirements = array_filter($unmet_requirements, function ($v) { return empty($v); });
  if (!empty($unmet_requirements)) {
    form_set_error('additional_requirements', t('The trainee must pass all the requirements.'));
  }
}


/**
 * Updates the trainee's roles and sends them a graduation email.
 */
function _ctl_graduation_form_submit_graduate($form, &$form_state) {
  $form_values = $form_state['values'];
  $uid = $form_values['uid'];

  // Upsert trainee info.
  db_merge('ctl_graduation_progress')
    ->key(array('uid' => $uid))
    ->fields(array(
      'graduation_timestamp' => time(),
    ))
    ->execute();

  // The trainee now becomes a graduate.

  $cur_role = 'Trainee';
  $role = user_role_load_by_name($cur_role);
  user_multiple_role_edit(array($uid), 'remove_role', $role->rid);

  $next_roles = array('Graduate', 'Crisis Counselor I');
  foreach ($next_roles as $next_role) {
    $role = user_role_load_by_name($next_role);
    user_multiple_role_edit(array($uid), 'add_role', $role->rid);
  }

  drupal_set_message(t('This trainee has now been graduated!'));

  if (_ctl_graduation_mail_send($form_values)) {
    drupal_set_message(t('A graduation email has been sent to the new graduate.'));
  }
  else {
    drupal_set_message(t('There was a problem sending the new graduate the graduation email.'), 'error');
  }
}
