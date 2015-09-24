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
 * Ensures that a user has only a one role out of a set of related roles.
 * @param int    $uid               The user ID.
 * @param string $next_role_name    The name of the role to set.
 */
function _ctl_onboarding_set_user_role($uid, $next_role_name) {
  // Remove all the roles we don't want the user to have.
  $role_names = array(
    CTL_ONBOARDING_ROLE_ACCEPTED,
    CTL_ONBOARDING_ROLE_INVITED,
    CTL_ONBOARDING_ROLE_DEFERRED,
    CTL_ONBOARDING_ROLE_DECLINED,
    CTL_ONBOARDING_ROLE_TRAINEE,
  );
  foreach ($role_names as $role_name) {
    if ($role_name !== $next_role_name) {
      $role = user_role_load_by_name($role_name);
      user_multiple_role_edit(array($uid), 'remove_role', $role->rid);
    }
  }
  // Assign the user the role we want them to have.
  $role = user_role_load_by_name($next_role_name);
  user_multiple_role_edit(array($uid), 'add_role', $role->rid);
}
