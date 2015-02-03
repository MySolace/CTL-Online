<?php
/**
 * @file
 * ctl_online.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ctl_online_user_default_roles() {
  $roles = array();

  // Exported role: Staff.
  $roles['Staff'] = array(
    'name' => 'Staff',
    'weight' => 3,
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  return $roles;
}
