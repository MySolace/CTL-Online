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
  $field_group->identifier = 'group_additional|node|application_2|form';
  $field_group->group_name = 'group_additional';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_more_info';
  $field_group->data = array(
    'label' => 'Additional Info',
    'weight' => '8',
    'children' => array(
      0 => 'field_armed_forces_2',
      1 => 'field_disabilities_',
      2 => 'field_disabilities_other',
      3 => 'field_race',
      4 => 'field_race_other',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
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
  $field_group->parent_name = 'group_you';
  $field_group->data = array(
    'label' => 'Counseling',
    'weight' => '131',
    'children' => array(
      0 => 'field_crisis_services_2',
      1 => 'field_in_counseling',
      2 => 'field_in_counseling_spoke',
      3 => 'field_in_counseling_spoke_ready',
      4 => 'field_used_crisis_support',
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
      0 => 'field_emergencies',
      1 => 'field_empathytest_daydream',
      2 => 'field_likert_arguments',
      3 => 'field_likert_book',
      4 => 'field_likert_characterplace',
      5 => 'field_likert_characters',
      6 => 'field_likert_control',
      7 => 'field_likert_emergency',
      8 => 'field_likert_emergency_situation',
      9 => 'field_likert_helpless',
      10 => 'field_likert_less_fortunate',
      11 => 'field_likert_misfortunes',
      12 => 'field_likert_movie',
      13 => 'field_likert_myself',
      14 => 'field_likert_not_sorry',
      15 => 'field_likert_novel',
      16 => 'field_likert_other_hurt',
      17 => 'field_likert_others_opinions',
      18 => 'field_likert_perspective',
      19 => 'field_likert_pity',
      20 => 'field_likert_place',
      21 => 'field_likert_pov',
      22 => 'field_likert_protective',
      23 => 'field_likert_scares',
      24 => 'field_likert_shoes',
      25 => 'field_likert_storyevents',
      26 => 'field_likert_touched',
      27 => 'field_likert_two_sides',
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
    'weight' => '9',
    'children' => array(
      0 => 'field_friend_words',
      1 => 'group_empathytest',
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
      1 => 'field_commitment_2',
      2 => 'field_english',
      3 => 'field_felony',
      4 => 'field_felony_violent_sex',
      5 => 'field_misdemeanor_violent_sex',
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
  $field_group->identifier = 'group_family_planning|node|application_2|form';
  $field_group->group_name = 'group_family_planning';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_uncomfortable';
  $field_group->data = array(
    'label' => 'Family Planning',
    'weight' => '4',
    'children' => array(
      0 => 'field_familyplanning_1',
      1 => 'field_familyplanning_2',
      2 => 'field_familyplanning_3',
      3 => 'field_familyplanning_4',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Family Planning',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-family-planning field-group-div',
        'description' => 'Crisis Text Line believes in supporting  texters in making choices that are best for them. This might mean discussing birth control and abortion and possibly, directing a texter to a local clinic. Your answers to the questions below help us to know that you’re on board in doing so. ',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_family_planning|node|application_2|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_lgbtq|node|application_2|form';
  $field_group->group_name = 'group_lgbtq';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_uncomfortable';
  $field_group->data = array(
    'label' => 'LGBTQ',
    'weight' => '5',
    'children' => array(
      0 => 'field_lgbtq_1',
      1 => 'field_lgbtq_2',
      2 => 'field_lgbtq_3',
      3 => 'field_lgbtq_4',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'LGBTQ',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-lgbtq field-group-div',
        'description' => 'Crisis Text Line believes in supporting texters in living their true identities. This might mean discussing LGBTQ related issues with a texter. Your answers to the questions below help us to know that you’re on board in doing so. ',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_lgbtq|node|application_2|form'] = $field_group;

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
    'weight' => '10',
    'children' => array(
      0 => 'field_education',
      1 => 'field_education_field',
      2 => 'field_education_field_other',
      3 => 'field_employment_2',
      4 => 'field_employment_2_requirement',
      5 => 'field_employment_school',
      6 => 'field_employment_employer',
      7 => 'group_additional',
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
      0 => 'group_empathy',
      1 => 'group_expectations',
      2 => 'group_more_info',
      3 => 'group_you',
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
  $field_group->identifier = 'group_religion|node|application_2|form';
  $field_group->group_name = 'group_religion';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application_2';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_uncomfortable';
  $field_group->data = array(
    'label' => 'Religious  questions',
    'weight' => '6',
    'children' => array(
      0 => 'field_religion_1',
      1 => 'field_religion_2',
      2 => 'field_religion_3',
      3 => 'field_religion_4',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Religious  questions',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-religion field-group-div',
        'description' => 'Crisis Text Line believes in supporting texters in making choices that are best for them. This might mean conversing with texters who are devoutly religious. Your answers to the questions below help us to know that you’re on board in doing so. ',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_religion|node|application_2|form'] = $field_group;

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
      2 => 'group_family_planning',
      3 => 'group_lgbtq',
      4 => 'group_religion',
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
    'weight' => '8',
    'children' => array(
      0 => 'field_motivation',
      1 => 'field_past_crisis_work_type',
      2 => 'field_referal_friend',
      3 => 'field_referral_2',
      4 => 'field_referral_2_news',
      5 => 'field_referral_2_other',
      6 => 'field_referral_2_other_keyword',
      7 => 'field_referral_2_social_media',
      8 => 'group_counseling',
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
  t('Counseling');
  t('Counselor Expectations');
  t('Family Planning');
  t('LGBTQ');
  t('More About You');
  t('Religious  questions');
  t('Why Crisis Text Line');
  t('empathytest');
  t('shift attendance ');
  t('uncomfortable');

  return $field_groups;
}
