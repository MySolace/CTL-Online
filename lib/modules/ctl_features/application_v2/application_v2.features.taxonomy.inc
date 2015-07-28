<?php
/**
 * @file
 * application_v2.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function application_v2_taxonomy_default_vocabularies() {
  return array(
    'application_status' => array(
      'name' => 'Application Status',
      'machine_name' => 'application_status',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
