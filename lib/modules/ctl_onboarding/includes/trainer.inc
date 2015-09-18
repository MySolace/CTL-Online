<?php

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
  $admin_uids = array_intersect($trainer_uids, $uids);
  $admin_uid  = !empty($admin_uids) ? $admin_uids[0] : NULL;

  // Build the list of trainers.
  $options = array();
  $users   = user_load_multiple($trainer_uids);
  foreach ($users as $user) {
    $options[$user->uid] = $user->field_first_name[LANGUAGE_NONE][0]['value'] . ' ' . $user->field_last_name[LANGUAGE_NONE][0]['value'];
  }

  $form['trainer_uid'] = array(
    '#type'          => 'select',
    '#title'         => t('Select the trainer for the team'),
    '#default_value' => $admin_uid,
    '#options'       => $options,
  );
  $form['make_selection'] = array(
    '#type'   => 'submit',
    '#value'  => 'Select',
    '#submit' => array('_ctl_onboarding_trainer_selection_form_submit'),
  );
  $form['prev_trainer_uid'] = array(
    '#type'  => 'hidden',
    '#value' => $admin_uid,
  );

  return $form;
}


function _ctl_onboarding_trainer_selection_form_submit($form, &$form_state) {
  $values           = $form_state['values'];
  $trainer_uid      = $values['trainer_uid'];
  $prev_trainer_uid = $values['prev_trainer_uid'];
  $nid              = arg(1);
  $node             = node_load($nid);

  // if ($trainer_uid !== $prev_trainer_uid) {
    _ctl_onboarding_set_team_trainer($nid, $trainer_uid, $prev_trainer_uid);
  // }


  drupal_set_message('The trainer has been assigned!');
}


/**
 * Assigns/reassigns the trainer to a team and makes them the group admin.
 * @param  int $uid    The user ID for the trainer to assign.
 */
function _ctl_onboarding_set_team_trainer($nid, $trainer_uid, $prev_trainer_uid) {
  $roles     = og_roles('node', NULL, $nid);
  $admin_rid = NULL;
  foreach ($roles as $k => $v) {
    if ($v === OG_ADMINISTRATOR_ROLE) {
      $admin_rid = $k;
      break;
    }
  }

  // A bit paranoid but better safe than sorry.
  if (!$admin_rid) {
    drupal_set_message('There is no group administrator role!', 'error');
    return;
  }

  // Remove the previous trainer.
  if ($prev_trainer_uid !== NULL) {
    og_role_revoke('node', $nid, $prev_trainer_uid, $admin_rid);
    og_ungroup('node', $nid, 'user', $prev_trainer_uid);

  }

  // Add the new trainer.
  $trainer_user = user_load($trainer_uid);
  og_group('node', $nid, array(
    'entity type'     => 'user',
    'entity'          => $trainer_user,
    'membership type' => OG_MEMBERSHIP_TYPE_DEFAULT,
  ));
  og_role_grant('node', $nid, $trainer_uid, $admin_rid);

  // Get all the members of the group.
  $node  = node_load($nid);
  $uids  = og_get_group_members_properties($node, array(), 'members', 'node');
  $users = user_load_multiple($uids);

  // Assign/reassign the newly-selected trainer to the group members.
  foreach ($users as $user) {
    // The trainer cannot be their own trainer.
    if ($user->uid !== $trainer_uid) {
      $user->field_trainer = array(
        LANGUAGE_NONE => array(
          array('target_id' => $trainer_uid),
        ),
      );
      user_save($user);
    }
  }


  // // Get all the member uids of the group.
  // $uids = og_get_group_members_properties($node, array(), 'members', 'node');

  // OG_ADMINISTRATOR_ROLE

  // og_get_user_roles()
  // og_role_grant()
  // og_role_revoke()

  // og_role_load()

  // og_get_groups_by_user()
  // og_get_entity_groups()

}
