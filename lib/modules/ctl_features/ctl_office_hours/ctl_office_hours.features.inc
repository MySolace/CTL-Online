<?php
/**
 * @file
 * ctl_office_hours.features.inc
 */

/**
 * Implements hook_views_api().
 */
function ctl_office_hours_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ctl_office_hours_node_info() {
  $items = array(
    'office_hours' => array(
      'name' => t('Office Hours'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
