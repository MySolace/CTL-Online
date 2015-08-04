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

  $roles['Applicant'] = array(
    'name' => 'Applicant',
    'weight' => 4,
  );

  $roles['Applied'] = array(
    'name' => 'Applied',
    'weight' => 6,
  );

  $roles['Submitted'] = array(
    'name' => 'Submitted',
    'weight' => 8,
  );

  $roles['Incomplete'] = array(
    'name' => 'Incomplete',
    'weight' => 9,
  );

  $roles['Lead'] = array(
    'name' => 'Lead',
    'weight' => 9,
  );

  return $roles;
}
