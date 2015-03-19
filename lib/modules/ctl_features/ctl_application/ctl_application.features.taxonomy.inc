<?php
/**
 * @file
 * ctl_application.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ctl_application_taxonomy_default_vocabularies() {
  return array(
    'application_status' => array(
      'name' => 'Application Status',
      'machine_name' => 'application_status',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'trainer' => array(
      'name' => 'Trainer',
      'machine_name' => 'trainer',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
