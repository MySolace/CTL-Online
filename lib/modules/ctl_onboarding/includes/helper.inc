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
