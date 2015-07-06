<?php
/**
 * @file
 * ctl_roleplays.features.inc
 */

/**
 * Implements hook_node_info().
 */
function ctl_roleplays_node_info() {
  $items = array(
    'roleplay' => array(
      'name' => t('Roleplay'),
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
