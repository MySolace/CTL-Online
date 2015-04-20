<?php
/**
 * @file
 * ctl_training.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function ctl_training_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-site-navigation.
  $menus['menu-site-navigation'] = array(
    'menu_name' => 'menu-site-navigation',
    'title' => 'Site Navigation',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Site Navigation');


  return $menus;
}
