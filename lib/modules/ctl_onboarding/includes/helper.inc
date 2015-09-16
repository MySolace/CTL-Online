<?php

/**
 * Displays times in 12-hour clock style.
 * @param  int $hour    24-hour clock time.
 * @return string       12-hour clock time for display.
 */
function _ctl_onboarding_format_hour_display($hour) {
  if ($hour >= 1200) {
    if ($hour > 1200) {
      $hour -= 1200;
    }
    return ($hour / 100) . 'pm';
  }
  return ($hour / 100) . 'am';
}


/**
 * Adds a user to an organic group.
 * @param  int $nid        The group ID.
 * @param  object $user    The user object.
 */
function _ctl_onboarding_add_group_user($nid, $user) {
  og_group('node', $nid, array(
    'entity type'     => 'user',
    'entity'          => $user,
    'membership type' => OG_MEMBERSHIP_TYPE_DEFAULT,
  ));
}


/**
 * Assigns roles to a user.
 * @param int      $uid           The user ID.
 * @param [string] $role_names    The names of the roles to add.
 */
function _ctl_onboarding_add_user_roles($uid, $role_names) {
  foreach ($role_names as $role_name) {
    $role = user_role_load_by_name($role_name);
    user_multiple_role_edit(array($uid), 'add_role', $role->rid);
  }
}


/**
 * Unassigns a role from a user.
 * @param int    $uid          The user ID.
 * @param string $role_name    The name of the role to remove.
 */
function _ctl_onboarding_remove_user_role($uid, $role_name) {
  $role = user_role_load_by_name($role_name);
  user_multiple_role_edit(array($uid), 'remove_role', $role->rid);
}
