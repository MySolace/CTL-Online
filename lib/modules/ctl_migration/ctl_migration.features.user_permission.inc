<?php
/**
 * @file
 * ctl_migration.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ctl_migration_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create field_migrated'.
  $permissions['create field_migrated'] = array(
    'name' => 'create field_migrated',
    'roles' => array(
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_migrated'.
  $permissions['edit field_migrated'] = array(
    'name' => 'edit field_migrated',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_migrated'.
  $permissions['edit own field_migrated'] = array(
    'name' => 'edit own field_migrated',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_migrated'.
  $permissions['view field_migrated'] = array(
    'name' => 'view field_migrated',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_migrated'.
  $permissions['view own field_migrated'] = array(
    'name' => 'view own field_migrated',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
