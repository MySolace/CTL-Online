<?php
/**
 * @file
 * ctl_training.features.inc
 */

/**
 * Implements hook_default_course_enrollment_type().
 */
function ctl_training_default_course_enrollment_type() {
  $items = array();
  $items['course_enrollment'] = entity_import('course_enrollment_type', '{ "type" : "course_enrollment", "label" : "Course" }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function ctl_training_node_info() {
  $items = array(
    'course' => array(
      'name' => t('Course'),
      'base' => 'node_content',
      'description' => t('A <em>course</em> containing Drupal learning objects.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'reading' => array(
      'name' => t('Reading'),
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
