<?php
/**
 * @file
 * application_v2.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function application_v2_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create application_2 content'.
  $permissions['create application_2 content'] = array(
    'name' => 'create application_2 content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any application_2 content'.
  $permissions['delete any application_2 content'] = array(
    'name' => 'delete any application_2 content',
    'roles' => array(
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own application_2 content'.
  $permissions['delete own application_2 content'] = array(
    'name' => 'delete own application_2 content',
    'roles' => array(
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any application_2 content'.
  $permissions['edit any application_2 content'] = array(
    'name' => 'edit any application_2 content',
    'roles' => array(

    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own application_2 content'.
  $permissions['edit own application_2 content'] = array(
    'name' => 'edit own application_2 content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
