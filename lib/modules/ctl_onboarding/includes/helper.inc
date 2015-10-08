<?php

/**
 * Renders a 24-hour clock style time into 12-hour clock style.
 * @param  int $hour    24-hour clock time.
 * @return string       12-hour clock time for display.
 */
function _ctl_onboarding_format_hour_display($hour) {
  $hour %= 2400;
  if ($hour >= 1200) {
    if ($hour > 1200) {
      $hour -= 1200;
    }
    return ($hour / 100) . 'pm';
  }
  elseif ($hour === 0) {
    $hour += 1200;
  }
  return ($hour / 100) . 'am';
}


/**
 * Renders a slot code into a textual representation.
 * @param  string $slot_code    The slot_code to render.
 * @return string               The rendered text.
 */
function _ctl_onboarding_format_slot_code_display($slot_code) {
  $output = '';
  $parts  = explode('-', $slot_code);
  if (empty($parts)) {
    return $output;
  }
  $day  = $parts[0];
  $hour = $parts[1];
  switch ($day) {
    case 'su': $output = 'Sundays'; break;
    case 'm':  $output = 'Mondays'; break;
    case 'tu': $output = 'Tuesdays'; break;
    case 'w':  $output = 'Wednesdays'; break;
    case 'th': $output = 'Thursdays'; break;
    case 'f':  $output = 'Fridays'; break;
    case 'sa': $output = 'Saturdays';
  }
  $output .= ' at ' . _ctl_onboarding_format_hour_display($hour) . ' ET';
  return $output;
}


/**
 * Checks if a given slot code is valid.
 * @param  string $slot_code    The slot_code to check.
 * @return bool                 Whether the slot code is valid.
 */
function _ctl_onboarding_validate_slot_code($slot_code) {
  $days  = array('su', 'm', 'tu', 'w', 'th', 'f', 'sa');
  $hours = range(CTL_ONBOARDING_FIRST_START_HOUR, CTL_ONBOARDING_LAST_START_HOUR, CTL_ONBOARDING_ONE_HOUR);
  $parts = explode('-', $slot_code);
  if (count($parts) !== 2 || !in_array($parts[0], $days, TRUE) || !in_array(intval($parts[1]), $hours, TRUE)) {
    return FALSE;
  }
  return TRUE;
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
