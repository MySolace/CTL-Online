<?php
/**
 * @file
 * ctl_roleplays.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ctl_roleplays_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create roleplay content'.
  $permissions['create roleplay content'] = array(
    'name' => 'create roleplay content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any roleplay content'.
  $permissions['delete any roleplay content'] = array(
    'name' => 'delete any roleplay content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own roleplay content'.
  $permissions['delete own roleplay content'] = array(
    'name' => 'delete own roleplay content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any roleplay content'.
  $permissions['edit any roleplay content'] = array(
    'name' => 'edit any roleplay content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own roleplay content'.
  $permissions['edit own roleplay content'] = array(
    'name' => 'edit own roleplay content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
