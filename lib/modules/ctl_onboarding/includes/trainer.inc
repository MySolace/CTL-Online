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
  foreach ($result as $record) {
    $trainer_uids[] = $record->uid;
  }

  // Get all the member uids of the group.
  $uids = og_get_group_members_properties($node, array(), 'members', 'node');

  // Find the group admins.  In practice there should only be one.
  $admins = array_intersect($trainer_uids, $uids);
  $admin  = !empty($admins) ? $admins[0] : '';

  // Build the list of trainers.
  $options = array();
  $users   = user_load_multiple($trainer_uids);
  foreach ($users as $user) {
    $options[$user->uid] = $user->field_first_name[LANGUAGE_NONE][0]['value'] . ' ' . $user->field_last_name[LANGUAGE_NONE][0]['value'];
  }

  $form['trainer'] = array(
    '#type'          => 'select',
    '#title'         => t('Select the trainer for the team'),
    '#default_value' => $admin,
    '#options'       => $options,
  );
  $form['make_selection'] = array(
    '#type'   => 'submit',
    '#value'  => 'Select',
    '#submit' => array('_ctl_onboarding_trainer_selection_form_submit'),
  );

  return $form;
}


function _ctl_onboarding_trainer_selection_form_submit($form, &$form_state) {
  $values  = $form_state['values'];
  $trainer = $values['trainer'];
  $nid     = arg(1);
  $node    = node_load($nid);

  // Get all the members of the group.
  $uids  = og_get_group_members_properties($node, array(), 'members', 'node');
  $users = user_load_multiple($uids);

  // Assign/Reassign the newly-selected trainer to the group members.
  foreach ($users as $user) {
    $user->field_trainer = array(
      LANGUAGE_NONE => array(
        array('target_id' => $trainer),
      ),
    );
    user_save($user);
  }

  drupal_set_message('The trainer has been assigned!');
}
