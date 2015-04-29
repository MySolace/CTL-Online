<?php
/**
 * @file
 * ctl_office_hours.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ctl_office_hours_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer big blue button'.
  $permissions['administer big blue button'] = array(
    'name' => 'administer big blue button',
    'roles' => array(),
    'module' => 'bbb',
  );

  // Exported permission: 'attend meetings'.
  $permissions['attend meetings'] = array(
    'name' => 'attend meetings',
    'roles' => array(),
    'module' => 'bbb',
  );

  // Exported permission: 'moderate meetings'.
  $permissions['moderate meetings'] = array(
    'name' => 'moderate meetings',
    'roles' => array(),
    'module' => 'bbb',
  );

  // Exported permission: 'moderate own meetings'.
  $permissions['moderate own meetings'] = array(
    'name' => 'moderate own meetings',
    'roles' => array(),
    'module' => 'bbb',
  );

  // Exported permission: 'record meetings'.
  $permissions['record meetings'] = array(
    'name' => 'record meetings',
    'roles' => array(),
    'module' => 'bbb',
  );

  return $permissions;
}
