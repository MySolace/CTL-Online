<?php
/**
 * @file
 * application_v2.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function application_v2_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|user|user|form';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact Information',
    'weight' => '2',
    'children' => array(
      0 => 'field_birthdate',
      1 => 'field_first_name',
      2 => 'field_last_name',
      3 => 'field_phone_number',
      4 => 'field_zip_code',
      5 => 'field_zip_code_text',
      6 => 'field_preferred_name',
      7 => 'field_address',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Contact Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-about field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_about|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional|node|application_2|form';
  $field_group->group_name = 'group_additional';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Additional Info',
    'weight' => '11',
    'children' => array(
      0 => 'field_armed_forces_2',
      1 => 'field_disabilities_',
      2 => 'field_disabilities_other',
      3 => 'field_race',
      4 => 'field_race_other',
      5 => 'group_counseling',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-additional',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_additional|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_counseling|node|application_2|form';
  $field_group->group_name = 'group_counseling';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_additional';
  $field_group->data = array(
    'label' => 'Counseling',
    'weight' => '125',
    'children' => array(
      0 => 'field_in_counseling',
      1 => 'field_in_counseling_spoke',
      2 => 'field_in_counseling_spoke_ready',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Counseling',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-counseling field-group-div',
        'description' => 'Some of our best crisis counselors have received crisis services or counseling. Answering yes to any of the below will not disqualify you.',
        'show_label' => '1',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_counseling|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_empathytest|node|application_2|form';
  $field_group->group_name = 'group_empathytest';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_empathy';
  $field_group->data = array(
    'label' => 'empathytest',
    'weight' => '16',
    'children' => array(
      0 => 'field_likert_emergency',
      1 => 'field_likert_helpless',
      2 => 'field_likert_less_fortunate',
      3 => 'field_likert_not_sorry',
      4 => 'field_likert_other_hurt',
      5 => 'field_likert_others_opinions',
      6 => 'field_likert_shoes',
      7 => 'field_likert_touched',
      8 => 'field_likert_two_sides',
      9 => 'field_emergencies',
      10 => 'field_empathytest_daydream',
      11 => 'field_likert_arguments',
      12 => 'field_likert_book',
      13 => 'field_likert_characterplace',
      14 => 'field_likert_characters',
      15 => 'field_likert_control',
      16 => 'field_likert_emergency_situation',
      17 => 'field_likert_misfortunes',
      18 => 'field_likert_movie',
      19 => 'field_likert_myself',
      20 => 'field_likert_novel',
      21 => 'field_likert_perspective',
      22 => 'field_likert_pity',
      23 => 'field_likert_place',
      24 => 'field_likert_pov',
      25 => 'field_likert_protective',
      26 => 'field_likert_scares',
      27 => 'field_likert_storyevents',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'empathytest',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => 'The following statements inquire about your thoughts and feelings in a variety of situations. For each item, indicate how well it describes you. READ EACH ITEM CAREFULLY BEFORE RESPONDING. Answer as honestly as you can. Thank you. ',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_empathytest|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_empathy|node|application_2|form';
  $field_group->group_name = 'group_empathy';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Attitude',
    'weight' => '8',
    'children' => array(
      0 => 'field_friend_words',
      1 => 'field_motivation',
      2 => 'group_empathytest',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'label' => 'Attitude',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'no-start',
    ),
  );
  $field_groups['group_empathy|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_expectations|node|application_2|form';
  $field_group->group_name = 'group_expectations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Counselor Expectations',
    'weight' => '7',
    'children' => array(
      0 => 'field_bkg_check',
      1 => 'field_english',
      2 => 'field_felony',
      3 => 'field_felony_violent_sex',
      4 => 'field_misdemeanor_violent_sex',
      5 => 'field_commitment_2',
      6 => 'field_triggers',
      7 => 'field_triggers_list',
      8 => 'group_time',
      9 => 'group_uncomfortable',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'label' => 'Counselor Expectations',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-expectations',
        'description' => '',
      ),
      'formatter' => 'no-start',
    ),
  );
  $field_groups['group_expectations|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_more_info|node|application_2|form';
  $field_group->group_name = 'group_more_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'More About You',
    'weight' => '9',
    'children' => array(
      0 => 'field_education',
      1 => 'field_education_field',
      2 => 'field_education_field_other',
      3 => 'field_employment_2',
      4 => 'field_employment_2_requirement',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-more-info',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_more_info|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_mp|node|application_2|form';
  $field_group->group_name = 'group_mp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'CTL Application',
    'weight' => '1',
    'children' => array(
      0 => 'group_additional',
      1 => 'group_empathy',
      2 => 'group_expectations',
      3 => 'group_more_info',
      4 => 'group_you',
    ),
    'format_type' => 'multipage-group',
    'format_settings' => array(
      'formatter' => '',
      'label' => 'CTL Application',
      'instance_settings' => array(
        'nonjs_multistep' => 0,
        'ajaxify' => 0,
        'classes' => 'group-mp field-group-multipage-group',
        'page_header' => 1,
        'page_counter' => 1,
        'move_button' => 0,
        'move_additional' => 1,
      ),
    ),
  );
  $field_groups['group_mp|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_time|node|application_2|form';
  $field_group->group_name = 'group_time';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_expectations';
  $field_group->data = array(
    'label' => 'shift attendance ',
    'weight' => '15',
    'children' => array(
      0 => 'field_yes',
      1 => 'field_shift',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'shift attendance ',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_time|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_uncomfortable|node|application_2|form';
  $field_group->group_name = 'group_uncomfortable';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_expectations';
  $field_group->data = array(
    'label' => 'uncomfortable',
    'weight' => '19',
    'children' => array(
      0 => 'field_uncomfortable_2',
      1 => 'field_uncomfortable_2_cont',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'uncomfortable',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_uncomfortable|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_you|node|application_2|form';
  $field_group->group_name = 'group_you';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Why Crisis Text Line',
    'weight' => '10',
    'children' => array(
      0 => 'field_past_crisis_work_type',
      1 => 'field_used_crisis_support',
      2 => 'field_crisis_services_2',
      3 => 'field_referal_friend',
      4 => 'field_referral_2',
      5 => 'field_referral_2_celeb',
      6 => 'field_referral_2_news',
      7 => 'field_referral_2_other',
      8 => 'field_referral_2_other_keyword',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'label' => 'Why Crisis Text Line',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-you',
        'description' => '',
      ),
      'formatter' => 'no-start',
    ),
  );
  $field_groups['group_you|node|application_2|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Info');
  t('Attitude');
  t('CTL Application');
  t('Contact Information');
  t('Counseling');
  t('Counselor Expectations');
  t('More About You');
  t('Why Crisis Text Line');
  t('empathytest');
  t('shift attendance ');
  t('uncomfortable');

  return $field_groups;
}
