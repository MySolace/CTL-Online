<?php
/**
 * @file
 * application_v2.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function application_v2_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'app_status';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Application Status';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CTL Volunteer Application';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'field_status' => 'field_status',
    'status' => 'status',
    'sid' => 'sid',
    'nid_1' => 'nid_1',
    'view' => 'view',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<p>In order to complete your application, please provide contact information for two references. Click "Request a reference" below and fill in the reference form two times.</p>

  <p>Your references will receive an automated email asking them to complete a form. You can check back here to see when their forms have been submitted.</p>';
  $handler->display->display_options['header']['area']['format'] = 'html';
  $handler->display->display_options['header']['area']['roles_fieldset'] = array(
    'roles' => array(
      'anonymous user' => 0,
      'authenticated user' => 0,
      'administrator' => 0,
      'Staff' => 0,
      'Applicant' => 0,
      'Lead' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h2>Welcome to Part Two of the application. <a href="/node/add/application">Let\'s get started!</a></h2>';
  $handler->display->display_options['empty']['area']['format'] = 'html';
  $handler->display->display_options['empty']['area']['roles_fieldset'] = array(
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 0,
      'administrator' => 0,
      'Staff' => 0,
      'Applicant' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area_2']['id'] = 'area_2';
  $handler->display->display_options['empty']['area_2']['table'] = 'views';
  $handler->display->display_options['empty']['area_2']['field'] = 'area';
  $handler->display->display_options['empty']['area_2']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_2']['content'] = '
  <h3>Already started an application? <a href="/user?destination=application">Log in.</a></h3>
  <h3>Otherwise, <a href="application">Apply now!</a></h3>';
  $handler->display->display_options['empty']['area_2']['format'] = 'html';
  $handler->display->display_options['empty']['area_2']['roles_fieldset'] = array(
    'roles' => array(
      'Staff' => 'Staff',
      'Applicant' => 'Applicant',
      'anonymous user' => 0,
      'authenticated user' => 'Authenticated User',
      'administrator' => 0,
      'Lead' => 0,
    ),
  );
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_reference_node']['id'] = 'reverse_field_reference_node';
  $handler->display->display_options['relationships']['reverse_field_reference_node']['table'] = 'users';
  $handler->display->display_options['relationships']['reverse_field_reference_node']['field'] = 'reverse_field_reference_node';
  $handler->display->display_options['relationships']['reverse_field_reference_node']['relationship'] = 'uid';
  $handler->display->display_options['relationships']['reverse_field_reference_node']['label'] = 'Reference';
  /* Relationship: User: Webform submission */
  $handler->display->display_options['relationships']['webform_submission']['id'] = 'webform_submission';
  $handler->display->display_options['relationships']['webform_submission']['table'] = 'users';
  $handler->display->display_options['relationships']['webform_submission']['field'] = 'webform_submission';
  $handler->display->display_options['relationships']['webform_submission']['relationship'] = 'uid';
  $handler->display->display_options['relationships']['webform_submission']['label'] = 'Webform Submissions';
  /* Relationship: Webform submissions: Node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'webform_submission';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['path'] = 'node/[nid]/edit';
  $handler->display->display_options['fields']['status']['empty'] = 'Submitted';
  $handler->display->display_options['fields']['status']['type'] = 'custom';
  $handler->display->display_options['fields']['status']['type_custom_false'] = '! Not Submitted';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: COUNT(DISTINCT Webform submissions: Sid) */
  $handler->display->display_options['fields']['sid']['id'] = 'sid';
  $handler->display->display_options['fields']['sid']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['sid']['field'] = 'sid';
  $handler->display->display_options['fields']['sid']['relationship'] = 'webform_submission';
  $handler->display->display_options['fields']['sid']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['sid']['label'] = 'Reference requests sent';
  $handler->display->display_options['fields']['sid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['sid']['alter']['text'] = '<a href="/reference-request">[sid] [Request a reference]</a>';
  /* Field: COUNT(DISTINCT Content: Nid) */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'reverse_field_reference_node';
  $handler->display->display_options['fields']['nid_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['nid_1']['label'] = 'References Received';
  $handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['alter']['text'] = '[nid_1] / 2';
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = 'Received References';
  $handler->display->display_options['fields']['view']['view'] = 'app_status';
  $handler->display->display_options['fields']['view']['display'] = 'attachment_1';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'application' => 'application',
    'application_2' => 'application_2',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '
  <h3>Already started an application? <a href="/user?destination=application">Log in.</a></h3>
  <h3>Otherwise, <a href="application">Apply now!</a></h3>';
  $handler->display->display_options['empty']['area']['format'] = 'html';
  $handler->display->display_options['empty']['area']['roles_fieldset'] = array(
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 0,
      'administrator' => 0,
      'Staff' => 0,
      'Applicant' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area_1']['id'] = 'area_1';
  $handler->display->display_options['empty']['area_1']['table'] = 'views';
  $handler->display->display_options['empty']['area_1']['field'] = 'area';
  $handler->display->display_options['empty']['area_1']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_1']['content'] = '<h2>Alright! Thanks for creating your account. <a href="/application">Let\'s get started!</a></h2>';
  $handler->display->display_options['empty']['area_1']['format'] = 'html';
  $handler->display->display_options['empty']['area_1']['roles_fieldset'] = array(
    'roles' => array(
      'Lead' => 'Lead',
      'anonymous user' => 0,
      'authenticated user' => 0,
      'administrator' => 0,
      'Staff' => 0,
      'Applicant' => 0,
      'Trainer' => 0,
      'Trainee' => 0,
      'Applied' => 0,
      'Applicant-Reminded' => 0,
      'Submitted' => 0,
      'Incomplete' => 0,
      'Accepted' => 0,
      'Pending' => 0,
      'Pending-failed' => 0,
      'Rejected' => 0,
      'Dropout' => 0,
      'Test Account' => 0,
      'Supervisor' => 0,
      'Crisis Counselor I' => 0,
      'Crisis Counselor II' => 0,
      'Crisis Counselor III' => 0,
      'Former Counselor' => 0,
      'Deferred' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area_2']['id'] = 'area_2';
  $handler->display->display_options['empty']['area_2']['table'] = 'views';
  $handler->display->display_options['empty']['area_2']['field'] = 'area';
  $handler->display->display_options['empty']['area_2']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_2']['content'] = 'Oops! Looks like you haven\'t started your application yet.

<a href="/application">Get started now.</a>';
  $handler->display->display_options['empty']['area_2']['format'] = 'auto_breaking';
  $handler->display->display_options['empty']['area_2']['roles_fieldset'] = array(
    'roles' => array(
      'Applicant' => 'Applicant',
      'Applicant-Reminded' => 'Applicant-Reminded',
      'Submitted' => 'Submitted',
      'Incomplete' => 'Incomplete',
      'Lead' => 'Lead',
      'Accepted' => 'Accepted',
      'anonymous user' => 0,
      'authenticated user' => 0,
      'administrator' => 0,
      'Staff' => 0,
      'Trainer' => 0,
      'Offboarder' => 0,
      'Trainee' => 0,
      'Graduate' => 0,
      'Applied' => 0,
      'Pending' => 0,
      'Pending-failed' => 0,
      'Rejected' => 0,
      'Dropout' => 0,
      'Test Account' => 0,
      'Supervisor' => 0,
      'Crisis Counselor I' => 0,
      'Crisis Counselor II' => 0,
      'Crisis Counselor III' => 0,
      'Former Counselor' => 0,
      'Deferred' => 0,
    ),
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'application' => 'application',
    'application_2' => 'application_2',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['path'] = 'apply';

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Your Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'reverse_field_reference_node';
  $handler->display->display_options['fields']['field_full_name']['label'] = '';
  $handler->display->display_options['fields']['field_full_name']['element_label_colon'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_status']['id'] = 'field_status';
  $handler->display->display_options['fields']['field_status']['table'] = 'field_data_field_status';
  $handler->display->display_options['fields']['field_status']['field'] = 'field_status';
  $handler->display->display_options['fields']['field_status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_status']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['path'] = 'node/[nid]/edit';
  $handler->display->display_options['fields']['status']['empty'] = '[field_status]';
  $handler->display->display_options['fields']['status']['type'] = 'custom';
  $handler->display->display_options['fields']['status']['type_custom_false'] = 'Incomplete';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: COUNT(DISTINCT Webform submissions: Sid) */
  $handler->display->display_options['fields']['sid']['id'] = 'sid';
  $handler->display->display_options['fields']['sid']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['sid']['field'] = 'sid';
  $handler->display->display_options['fields']['sid']['relationship'] = 'webform_submission';
  $handler->display->display_options['fields']['sid']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['sid']['label'] = 'Reference requests sent';
  $handler->display->display_options['fields']['sid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['sid']['alter']['text'] = '<a href="/reference-request">[sid] [Request a reference]</a>';
  /* Field: COUNT(DISTINCT Content: Nid) */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'reverse_field_reference_node';
  $handler->display->display_options['fields']['nid_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['nid_1']['label'] = 'References Received';
  $handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['alter']['text'] = '[nid_1] / 2';
  $export['app_status'] = $view;

  return $export;
}
