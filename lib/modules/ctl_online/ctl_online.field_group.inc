<?php
/**
 * @file
 * ctl_online.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ctl_online_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic|user|user|form';
  $field_group->group_name = 'group_basic';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Basic Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_first_name',
      1 => 'field_last_name',
      2 => 'field_phone_number',
      3 => 'account',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Basic Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-basic field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_basic|user|user|form'] = $field_group;

  return $export;
}
