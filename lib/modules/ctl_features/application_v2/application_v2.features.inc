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
      'name' => t('Application_2'),
      'base' => 'node_content',
      'description' => t('This is the CTL Volunteer Application.'),
      'has_title' => '1',
      'title_label' => t('Email'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
