<?php
/**
 * @file
 * ctl_migration.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ctl_migration_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_migrated'.
  $field_bases['field_migrated'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_migrated',
    'field_permissions' => array(
      'type' => 2,
    ),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
