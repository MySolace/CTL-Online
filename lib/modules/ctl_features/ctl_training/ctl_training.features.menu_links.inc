<?php
/**
 * @file
 * test.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ctl_training_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-site-navigation_messages:messages
  $menu_links['menu-site-navigation_messages:messages'] = array(
    'menu_name' => 'menu-site-navigation',
    'link_path' => 'messages',
    'router_path' => 'messages',
    'link_title' => 'Messages',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-site-navigation_messages:messages',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );

  t('Messages');
  t('Training');


  return $menu_links;
}
