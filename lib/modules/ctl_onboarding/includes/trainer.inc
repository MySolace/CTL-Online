<?php

// TODO
// - make a node tab called "Trainer" that has the UI for choosing the trainer
//   - select trainer from drop down just like in the trainer field on user profiles


/**
 * Implements hook_form().
 */
function _ctl_onboarding_trainer_selection_form($form, &$form_state, $node) {
  // Get all the trainer IDs.
  $role = user_role_load_by_name(CTL_ONBOARDING_ROLE_TRAINER);
  $result = db_select('users_roles', 'ur')
    ->fields('ur', array('uid'))
    ->condition('rid', $role->rid)
    ->execute()
    ->fetchAll();
  $trainer_uids = array();
  foreach($result as $record) {
    $trainer_uids[] = $record->uid;
  }

  $options = array();
  $users   = user_load_multiple($trainer_uids);
  foreach ($users as $user) {
    $options[$user->uid] = $user->field_first_name[LANGUAGE_NONE][0]['value'] . ' ' . $user->field_last_name[LANGUAGE_NONE][0]['value'];
  }

  // Get all the member uids of the group.
  $uids = og_get_group_members_properties($node, array(), 'members', 'node');

  // Find the group admins.  In practice there should only be one.
  $admins = array_intersect($trainer_uids, $uids);
  $admin  = !empty($admins) ? $admins[0] : NULL;

  $form['trainer_selection'] = array(
    '#type'          => 'select',
    '#title'         => t('Select the trainer for the team'),
    '#default_value' => $admin,
    '#options'       => $options,
  );
  $form['make_selection'] = array(
    '#type'     => 'submit',
    '#value'    => 'Select',
    // '#validate' => array('_ctl_onboarding_trainer_selection_form_validate'),
    '#submit'   => array('_ctl_onboarding_trainer_selection_form_submit'),
  );

  return $form;
}


// function _ctl_onboarding_trainer_selection_form_validate($form, &$form_state) {
//   $form_values = $form_state['values'];
//   // $unmet_requirements = array(_ctl_graduation_courses_completed($form_values['uid']))
//   //                     + $form_values['additional_requirements'];
//   // $unmet_requirements = array_filter($unmet_requirements, function ($v) { return empty($v); });
//   // if (!empty($unmet_requirements)) {
//   //   form_set_error('additional_requirements', t('The trainee must pass all the requirements.'));
//   // }
// }


function _ctl_onboarding_trainer_selection_form_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  // $uid = $form_values['uid'];

  // // Upsert trainee info.
  // db_merge('ctl_graduation_progress')
  //   ->key(array('uid' => $uid))
  //   ->fields(array(
  //     'graduation_timestamp' => time(),
  //   ))
  //   ->execute();

  // // The trainee now becomes a graduate.

  // $cur_role = 'Trainee';
  // $role = user_role_load_by_name($cur_role);
  // user_multiple_role_edit(array($uid), 'remove_role', $role->rid);

  // $next_roles = array('Graduate', 'Crisis Counselor I');
  // foreach ($next_roles as $next_role) {
  //   $role = user_role_load_by_name($next_role);
  //   user_multiple_role_edit(array($uid), 'add_role', $role->rid);
  // }

  // drupal_set_message(t('This trainee has now been graduated!'));

  // if (_ctl_graduation_mail_send($form_values)) {
  //   drupal_set_message(t('A graduation email has been sent to the new graduate.'));
  // }
  // else {
  //   drupal_set_message(t('There was a problem sending the new graduate the graduation email.'), 'error');
  // }
}
