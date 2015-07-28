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

  // Exported role: Applicant.
  $roles['Applicant'] = array(
    'name' => 'Applicant',
    'weight' => 4,
  );

  // Exported role: Applied.
  $roles['Applied'] = array(
    'name' => 'Applied',
    'weight' => 6,
  );

  return $roles;
}
