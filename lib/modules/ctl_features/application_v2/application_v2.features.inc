<?php
/**
 * @file
 * application_v2.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function application_v2_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function application_v2_node_info() {
  $items = array(
    'application_2' => array(
      'name' => t('Application_v2'),
      'base' => 'node_content',
      'description' => t('This is the CTL Volunteer Application.

Note: If you are below 18, have been convicted of a felony in the last 7 years, or do not fulfill our technology requirements we are not able to accept you at this time.
'),
      'has_title' => '1',
      'title_label' => t('Email'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
