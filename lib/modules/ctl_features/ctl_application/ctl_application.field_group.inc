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
      6 => 'account',
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
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Additional Info',
    'weight' => '66',
    'children' => array(
      0 => 'field_felony',
      1 => 'field_felony_more',
      2 => 'field_felony_m_violent_sex',
      3 => 'field_felony_m_description',
      4 => 'field_felony_m_date',
      5 => 'field_felony_m_reform',
      6 => 'field_felony_violent_sex',
      7 => 'field_felony_description',
      8 => 'field_felony_date',
      9 => 'field_felony_reform',
      10 => 'field_misdemeanor',
      11 => 'field_misdemeanor_more',
      12 => 'field_misdemeanor_m_violent_sex',
      13 => 'field_misdemeanor_m_description',
      14 => 'field_misdemeanor_m_date',
      15 => 'field_misdemeanor_m_reform',
      16 => 'field_misdemeanor_violent_sex',
      17 => 'field_misdemeanor_description',
      18 => 'field_misdemeanor_date',
      19 => 'field_misdemeanor_reform',
      20 => 'field_cell_phone',
      21 => 'field_on_phone',
      22 => 'field_training_days',
      23 => 'field_training_time',
      24 => 'group_commitment',
      25 => 'group_counseling',
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
  $field_group->identifier = 'group_agreement|user|user|form';
  $field_group->group_name = 'group_agreement';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Background Information',
    'weight' => '2',
    'children' => array(
      0 => 'field_has_ssn',
      1 => 'field_referral',
      2 => 'field_referral_other',
      3 => 'field_user_acceptance',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Background Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-agreement field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_agreement|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assessment|node|application|form';
  $field_group->group_name = 'group_assessment';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_you';
  $field_group->data = array(
    'label' => '',
    'weight' => '42',
    'children' => array(
      0 => 'field_likert_less_fortunate',
      1 => 'field_likert_others_opinions',
      2 => 'field_likert_other_hurt',
      3 => 'field_likert_touched',
      4 => 'field_likert_helpless',
      5 => 'field_likert_two_sides',
      6 => 'field_likert_emergency',
      7 => 'field_likert_not_sorry',
      8 => 'field_likert_shoes',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-assessment field-group-fieldset',
        'description' => '<p>For each statement below, indicate how well it describes you.</p>
1 = Does Not Describe Me Well<br>
5 = Describes Me Very Well<br>',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_assessment|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_background|node|application|form';
  $field_group->group_name = 'group_background';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'Background',
    'weight' => '63',
    'children' => array(
      0 => 'field_volunteered_before',
      1 => 'field_volunteered_duration',
      2 => 'field_past_crisis_work_type',
      3 => 'field_employment',
      4 => 'field_employment_office',
      5 => 'field_employment_employer',
      6 => 'field_employment_school',
      7 => 'field_employment_requirement',
      8 => 'field_education',
      9 => 'field_education_field',
      10 => 'field_education_field_other',
      11 => 'field_armed_forces',
      12 => 'field_time_zone',
      13 => 'field_has_twitter',
      14 => 'field_twitter',
      15 => 'field_has_facebook',
      16 => 'field_facebook',
      17 => 'field_english',
      18 => 'field_blogs',
      19 => 'field_position_level',
      20 => 'field_additional_social_media',
      21 => 'title',
      22 => 'redirect',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-background',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_background|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_commitment|node|application|form';
  $field_group->group_name = 'group_commitment';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_additional';
  $field_group->data = array(
    'label' => 'Volunteering with CTL is a big and incredibly rewarding commitment.',
    'weight' => '78',
    'children' => array(
      0 => 'field_commitment',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Volunteering with CTL is a big and incredibly rewarding commitment.',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-commitment field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_commitment|node|application|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_counseling|node|application|form';
  $field_group->group_name = 'group_counseling';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_additional';
  $field_group->data = array(
    'label' => '',
    'weight' => '53',
    'children' => array(
      0 => 'field_in_counseling',
      1 => 'field_in_counseling_spoke',
      2 => 'field_in_counseling_spoke_ready',
      3 => 'field_in_counseling_hesitation',
      4 => 'field_used_crisis_support',
      5 => 'field_crisis_services',
      6 => 'field_crisis_last_time',
      7 => 'field_crisis_helpful',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-counseling field-group-fieldset',
        'description' => 'Some of our best crisis counselors have received crisis services or counseling. Answering yes to any of the below will not disqualify you.',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_counseling|node|application|form'] = $field_group;

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
  $field_group->identifier = 'group_more_info|node|application|form';
  $field_group->group_name = 'group_more_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'More About You',
    'weight' => '64',
    'children' => array(
      0 => 'field_video_volunteer',
      1 => 'field_essay_criticized',
      2 => 'field_friend_words',
      3 => 'field_talker_listener',
      4 => 'field_introvert_extrovert',
      5 => 'field_difficult_decision',
      6 => 'field_stress_management',
      7 => 'field_uncomfortable',
      8 => 'field_video_feeling_supplement',
      9 => 'group_self_care_ratings',
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
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'CTL Application',
    'weight' => '1',
    'children' => array(
      0 => 'group_background',
      1 => 'group_more_info',
      2 => 'group_additional',
      3 => 'group_you',
      4 => 'group_vetting',
    ),
    'format_type' => 'multipage-group',
    'format_settings' => array(
      'label' => 'CTL Application',
      'instance_settings' => array(
        'nonjs_multistep' => '0',
        'ajaxify' => '0',
        'multipage_jumplist_block' => 1,
        'classes' => 'group-mp field-group-multipage-group',
        'page_header' => '1',
        'page_counter' => '1',
        'move_button' => '0',
        'move_additional' => '1',
      ),
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
    'weight' => '23',
    'children' => array(),
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
    'weight' => '25',
    'children' => array(),
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
  $field_group->identifier = 'group_reference|node|recommendation|form';
  $field_group->group_name = 'group_reference';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'recommendation';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Reference',
    'weight' => '2',
    'children' => array(
      0 => 'field_reference',
      1 => 'field_relationship',
      2 => 'field_known_time',
      3 => 'field_essay',
      4 => 'field_good_fit',
      5 => 'field_yes',
      6 => 'field_no',
      7 => 'field_full_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Reference',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-reference field-group-fieldset',
        'description' => '<p>Crisis Text Line is the first, free, national 24/7 text line for teens in crisis. Our crisis counselors are volunteers who, after being accepted to the program, complete a 34 hour training and make a one year commitment to serve one 4 hour shift each week. </p>
<p>The person named above has listed you as a reference in their application. Please complete this form in the next week in order for us to process their application.</p>
<p>Questions? Please send them to volunteers@crisistextline.org. Thank you!</p>',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_reference|node|recommendation|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_self_care_ratings|node|application|form';
  $field_group->group_name = 'group_self_care_ratings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_more_info';
  $field_group->data = array(
    'label' => '',
    'weight' => '24',
    'children' => array(
      0 => 'field_self_care_1',
      1 => 'field_self_care_2',
      2 => 'field_self_care_3',
      3 => 'field_self_care_4',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-self-care-ratings field-group-fieldset',
        'description' => 'For each of the statements below, rate how true the statement is for you on a scale of 1 - 3, from very true to rarely true.',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_self_care_ratings|node|application|form'] = $field_group;

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
  $field_group->identifier = 'group_vetting|node|application|form';
  $field_group->group_name = 'group_vetting';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'vetting',
    'weight' => '67',
    'children' => array(
      0 => 'field_vetting_score_video',
      1 => 'field_vetting_score_overall',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-vetting field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_vetting|node|application|form'] = $field_group;

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

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_you|node|application|form';
  $field_group->group_name = 'group_you';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'application';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_mp';
  $field_group->data = array(
    'label' => 'You + Crisis Counseling',
    'weight' => '65',
    'children' => array(
      0 => 'field_friends_crisis',
      1 => 'field_concerns',
      2 => 'field_why_volunteer',
      3 => 'group_assessment',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'label' => 'You + Crisis Counseling',
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
