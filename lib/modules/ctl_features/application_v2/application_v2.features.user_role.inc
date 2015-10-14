<?php
/**
 * @file
 * application_v2.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function application_v2_user_default_roles() {
  $roles = array();

  // Exported role: Incomplete.
  $roles['Incomplete'] = array(
    'name' => 'Incomplete',
    'weight' => 12,
  );

  // Exported role: Submitted.
  $roles['Submitted'] = array(
    'name' => 'Submitted',
    'weight' => 11,
  );

  return $roles;
}
