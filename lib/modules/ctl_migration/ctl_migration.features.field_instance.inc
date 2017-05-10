<?php
/**
 * @file
 * ctl_migration.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ctl_migration_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_migrated'.
  $field_instances['user-user-field_migrated'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 18,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_migrated',
    'label' => 'Migrated',
    'required' => 0,
    'settings' => array(
      'course_enrollment' => FALSE,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 32,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Migrated');

  return $field_instances;
}
