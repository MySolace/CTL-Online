<?php
/**
 * @file
 * ctl_application.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ctl_application_user_default_roles() {
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

  // Exported role: Lead.
  $roles['Lead'] = array(
    'name' => 'Lead',
    'weight' => 5,
  );

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
