<?php
/**
 * @file
 * application_v2.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function application_v2_field_group_info() {
  $export = array();

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
    'weight' => '1',
    'children' => array(
      0 => 'field_birthdate',
      1 => 'field_first_name',
      2 => 'field_last_name',
      3 => 'field_phone_number',
      4 => 'field_zip_code',
      5 => 'field_zip_code_text',
      6 => 'field_preferred_name',
      7 => 'account',
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
  $export['group_about|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional|node|application|form';
  $field_group->group_name = 'group_additional';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Additional Info',
    'weight' => '11',
    'children' => array(
      0 => 'field_armed_forces',
      1 => 'field_disabilities_',
      2 => 'field_race',
      3 => 'field_race_other',
      4 => 'field_disabilities_other',
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
  $export['group_additional|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_counseling|node|application|form';
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
  $export['group_counseling|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_empathytest|node|application|form';
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
      9 => 'field_empathytest_daydream',
      10 => 'field_likert_pov',
      11 => 'field_likert_novel',
      12 => 'field_likert_emergency_situation',
      13 => 'field_likert_movie',
      14 => 'field_likert_protective',
      15 => 'field_likert_perspective',
      16 => 'field_likert_book',
      17 => 'field_likert_misfortunes',
      18 => 'field_likert_arguments',
      19 => 'field_likert_characters',
      20 => 'field_likert_scares',
      21 => 'field_likert_pity',
      22 => 'field_emergencies',
      23 => 'field_likert_myself',
      24 => 'field_likert_characterplace',
      25 => 'field_likert_control',
      26 => 'field_likert_storyevents',
      27 => 'field_likert_place',
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
  $export['group_empathytest|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_empathy|node|application|form';
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
  $export['group_empathy|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_expectations|node|application|form';
  $field_group->group_name = 'group_expectations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Counselor Expectations',
    'weight' => '7',
    'children' => array(
      0 => 'field_commitment',
      1 => 'field_english',
      2 => 'field_felony',
      3 => 'field_felony_violent_sex',
      4 => 'field_misdemeanor_violent_sex',
      5 => 'field_bkg_check',
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
  $export['group_expectations|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_more_info|node|application|form';
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
      3 => 'field_employment',
      4 => 'field_employment_requirement',
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
  $export['group_more_info|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_time|node|application|form';
  $field_group->group_name = 'group_time';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_expectations';
  $field_group->data = array(
    'label' => 'shift attendance ',
    'weight' => '15',
    'children' => array(
      0 => 'field_shift',
      1 => 'field_yes',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'shift attendance ',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => 'Volunteering with Crisis Text Line is a serious (and incredibly rewarding) commitment. We invest a lot in you during training. It costs us money to hire trainers, build the training modules, support the technology, etc. In return, we count on you to staff a 4 hour shift every week for a year. Yes. Thats a heavy commitment. (We do understand that there might be an exceptional reason why you’d need to miss a shift.)',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_time|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_uncomfortable|node|application|form';
  $field_group->group_name = 'group_uncomfortable';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_expectations';
  $field_group->data = array(
    'label' => 'uncomfortable',
    'weight' => '19',
    'children' => array(
      0 => 'field_uncomfortable',
      1 => 'field_uncomfortable_cont',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'uncomfortable',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => 'Occasionally, some of our conversations bring up controversial topics. We are looking for volunteers who are open-minded and willing to text with people regardless of the issue(s) they are facing. Below are situations that HAVE happened on our platform.',
        'show_label' => '0',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_uncomfortable|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_you|node|application|form';
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
      2 => 'field_crisis_services',
      3 => 'field_referal_friend',
      4 => 'field_referral_news',
      5 => 'field_referral_other',
      6 => 'field_referral',
      7 => 'field_referral_celeb',
      8 => 'field_referral_other_keyword',
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
  $export['group_you|node|application|form'] = $field_group;

  return $export;
}
