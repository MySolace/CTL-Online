<?php
/**
 * @file
 * ctl_training.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ctl_training_user_default_roles() {
  $roles = array();

  // Exported role: Trainee.
  $roles['Trainee'] = array(
    'name' => 'Trainee',
    'weight' => 8,
  );

  // Exported role: Trainer.
  $roles['Trainer'] = array(
    'name' => 'Trainer',
    'weight' => 7,
  );

  return $roles;
}
