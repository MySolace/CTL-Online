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

  // Find the group admins.  In practice there should only be one but we're
  // also going to account for multiple group admins.  Note: `array_intersect()`
  // preserves keys which can be problematic so we use `array_values` to do
  // some re-indexing.
  $admin_uids = array_values(array_intersect($trainer_uids, $uids));

  // We pick what we believe is the sole group admin.
  $admin_uid = !empty($admin_uids) ? $admin_uids[0] : NULL;

  // Build the list of trainers.
  $options = array();
  $users   = user_load_multiple($trainer_uids);
  foreach ($users as $user) {
    $field_first_name    = field_get_items('user', $user, 'field_first_name');
    $field_last_name     = field_get_items('user', $user, 'field_last_name');
    $first_name          = $field_first_name ? $field_first_name[0]['value'] : '';
    $last_name           = $field_last_name ? $field_last_name[0]['value'] : '';
    $options[$user->uid] = "$first_name $last_name";
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

  return $form;
}


function _ctl_onboarding_trainer_selection_form_submit($form, &$form_state) {
  $values      = $form_state['values'];
  $trainer_uid = $values['trainer_uid'];
  $nid         = arg(1);
  $node        = node_load($nid);

  _ctl_onboarding_set_team_trainer($nid, $trainer_uid);

  drupal_set_message('The trainer has been assigned!');
}


/**
 * Assigns/reassigns the trainer to a team and makes them the group admin.
 * @param  int $trainer_uid    The user ID for the trainer to assign.
 */
function _ctl_onboarding_set_team_trainer($nid, $trainer_uid) {
  $node        = node_load($nid);
  $member_uids = og_get_group_members_properties($node, array(), 'members', 'node');
  $users       = user_load_multiple($member_uids);
  foreach ($users as $user) {
    if ($user->uid !== $trainer_uid) {
      $roles = og_get_user_roles('node', $nid, $user->uid, FALSE);
      // Previous trainers get removed from the team.
      $admin_rid = array_search(OG_ADMINISTRATOR_ROLE, $roles);
      if ($admin_rid) {
        og_role_revoke('node', $nid, $user->uid, $admin_rid);
        og_ungroup('node', $nid, 'user', $user->uid);
      }
      // Trainees get their trainer assigned to them.
      else {
        $user->field_trainer = array(
          LANGUAGE_NONE => array(
            array('target_id' => $trainer_uid),
          ),
        );
        user_save($user);
      }
    }
  }

  // Add the new trainer to the team.
  $trainer_user = user_load($trainer_uid);
  og_group('node', $nid, array(
    'entity type'     => 'user',
    'entity'          => $trainer_user,
    'membership type' => OG_MEMBERSHIP_TYPE_DEFAULT,
  ));
  $admin_rid = db_query('SELECT rid FROM {og_role} WHERE name = :name', array(':name' => OG_ADMINISTRATOR_ROLE))->fetchField();
  og_role_grant('node', $nid, $trainer_uid, $admin_rid);
}
