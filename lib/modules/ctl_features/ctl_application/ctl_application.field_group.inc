<?php
/**
 * @file
 * ctl_application.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ctl_application_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_commitment|node|application|form';
  $field_group->group_name = 'group_commitment';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_test';
  $field_group->data = array(
    'label' => 'CTL Volunteer Commitment',
    'weight' => '16',
    'children' => array(
      0 => 'field_commitment',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-commitment',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_commitment|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_education_work|node|application|form';
  $field_group->group_name = 'group_education_work';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_test';
  $field_group->data = array(
    'label' => 'Education and Work',
    'weight' => '14',
    'children' => array(
      0 => 'field_education',
      1 => 'field_work_status',
      2 => 'field_workplace',
      3 => 'field_work_role',
      4 => 'field_employment_duration',
      5 => 'field_work_hours',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-education-work',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_education_work|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_mp2|node|application|form';
  $field_group->group_name = 'group_mp2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_test';
  $field_group->data = array(
    'label' => 'Page 2',
    'weight' => '2',
    'children' => array(
      0 => 'field_last_name',
      1 => 'field_complete',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'label' => 'Page 2',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-mp2',
        'description' => '',
      ),
      'formatter' => 'no-start',
    ),
  );
  $export['group_mp2|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_mp|node|application|form';
  $field_group->group_name = 'group_mp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_test';
  $field_group->data = array(
    'label' => 'About You',
    'weight' => '12',
    'children' => array(
      0 => 'field_facebook',
      1 => 'field_twitter',
      2 => 'field_risk',
      3 => 'field_talk_to',
      4 => 'field_strength',
      5 => 'field_weakness',
      6 => 'field_concerns',
      7 => 'field_special_skill',
      8 => 'title',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'label' => 'About You',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-mp',
        'description' => '',
      ),
      'formatter' => 'start',
    ),
  );
  $export['group_mp|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_r1|node|application|default';
  $field_group->group_name = 'group_r1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Reference 1',
    'weight' => '26',
    'children' => array(
      0 => 'field_r1_full_name',
      1 => 'field_r1_relationship_to_you',
      2 => 'field_r1_phone_number',
      3 => 'field_r1_email_address',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-r1 field-group-fieldset',
      ),
    ),
  );
  $export['group_r1|node|application|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_r2|node|application|default';
  $field_group->group_name = 'group_r2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Reference 2',
    'weight' => '27',
    'children' => array(
      0 => 'field_r2_email_address',
      1 => 'field_r2_full_name',
      2 => 'field_r2_relationship_to_you',
      3 => 'field_r2_phone_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-r2 field-group-fieldset',
      ),
    ),
  );
  $export['group_r2|node|application|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_recommendations|node|application|form';
  $field_group->group_name = 'group_recommendations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_test';
  $field_group->data = array(
    'label' => 'Recommendations',
    'weight' => '17',
    'children' => array(
      0 => 'group_ref_1',
      1 => 'group_ref_2',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-recommendations',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_recommendations|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ref_1|node|application|form';
  $field_group->group_name = 'group_ref_1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_recommendations';
  $field_group->data = array(
    'label' => 'Reference 1',
    'weight' => '28',
    'children' => array(
      0 => 'field_r1_full_name',
      1 => 'field_r1_relationship_to_you',
      2 => 'field_r1_phone_number',
      3 => 'field_r1_email_address',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ref-1 field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ref_1|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ref_2|node|application|form';
  $field_group->group_name = 'group_ref_2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_recommendations';
  $field_group->data = array(
    'label' => 'Reference 2',
    'weight' => '29',
    'children' => array(
      0 => 'field_r2_email_address',
      1 => 'field_r2_full_name',
      2 => 'field_r2_relationship_to_you',
      3 => 'field_r2_phone_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ref-2 field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ref_2|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_test|node|application|form';
  $field_group->group_name = 'group_test';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Main Group',
    'weight' => '2',
    'children' => array(
      0 => 'group_mp',
      1 => 'group_videos',
      2 => 'group_commitment',
      3 => 'group_education_work',
      4 => 'group_volunteer',
      5 => 'group_recommendations',
    ),
    'format_type' => 'multipage-group',
    'format_settings' => array(
      'label' => 'Main Group',
      'instance_settings' => array(
        'classes' => 'group-test field-group-multipage-group',
        'page_header' => '3',
        'page_counter' => '1',
        'move_button' => '0',
        'move_additional' => '1',
      ),
    ),
  );
  $export['group_test|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_videos|node|application|form';
  $field_group->group_name = 'group_videos';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_test';
  $field_group->data = array(
    'label' => 'Video Submissions',
    'weight' => '15',
    'children' => array(
      0 => 'field_why_volunteer_video',
      1 => 'field_great_counselor_video',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_videos|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_volunteer|node|application|form';
  $field_group->group_name = 'group_volunteer';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_test';
  $field_group->data = array(
    'label' => 'Volunteer Details',
    'weight' => '13',
    'children' => array(
      0 => 'field_requirements',
      1 => 'field_crisis_status',
      2 => 'field_past_volunteer_commitment',
      3 => 'field_past_crisis_intervention',
      4 => 'field_access_to',
      5 => 'field_timezone',
      6 => 'field_volunteer_interests',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-volunteer',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_volunteer|node|application|form'] = $field_group;

  return $export;
}
