<?php
/**
 * @file
 * ctl_application.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ctl_application_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-ctl-admin_part-one:admin/part-one
  $menu_links['menu-ctl-admin_part-one:admin/part-one'] = array(
    'menu_name' => 'menu-ctl-admin',
    'link_path' => 'admin/part-one',
    'router_path' => 'admin/part-one',
    'link_title' => 'Part One',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-ctl-admin_part-one:admin/part-one',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-ctl-admin_part-two-applications:admin/applications
  $menu_links['menu-ctl-admin_part-two-applications:admin/applications'] = array(
    'menu_name' => 'menu-ctl-admin',
    'link_path' => 'admin/applications',
    'router_path' => 'admin/applications',
    'link_title' => 'Part Two: Applications',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-ctl-admin_part-two-applications:admin/applications',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-ctl-admin_part-two-recommendations:admin/recommendations
  $menu_links['menu-ctl-admin_part-two-recommendations:admin/recommendations'] = array(
    'menu_name' => 'menu-ctl-admin',
    'link_path' => 'admin/recommendations',
    'router_path' => 'admin/recommendations',
    'link_title' => 'Part Two: Recommendations',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-ctl-admin_part-two-recommendations:admin/recommendations',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-ctl-admin_search-users:search/user
  $menu_links['menu-ctl-admin_search-users:search/user'] = array(
    'menu_name' => 'menu-ctl-admin',
    'link_path' => 'search/user',
    'router_path' => 'search/user',
    'link_title' => 'Search Users',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-ctl-admin_search-users:search/user',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: user-menu_log-out:user/logout
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'identifier' => 'user-menu_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 0,
  );
  // Exported menu link: user-menu_user-account:user
  $menu_links['user-menu_user-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'user-menu_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Log out');
  t('Part One');
  t('Part Two: Applications');
  t('Part Two: Recommendations');
  t('Search Users');
  t('User account');


  return $menu_links;
}
