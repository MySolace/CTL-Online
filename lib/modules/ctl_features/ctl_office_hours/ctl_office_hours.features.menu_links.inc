<?php
/**
 * @file
 * ctl_office_hours.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ctl_office_hours_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-site-navigation_office-hours:office-hours
  $menu_links['menu-site-navigation_office-hours:office-hours'] = array(
    'menu_name' => 'menu-site-navigation',
    'link_path' => 'office-hours',
    'router_path' => 'office-hours',
    'link_title' => 'Office Hours',
    'options' => array(
      'identifier' => 'menu-site-navigation_office-hours:office-hours',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 5,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Office Hours');


  return $menu_links;
}
