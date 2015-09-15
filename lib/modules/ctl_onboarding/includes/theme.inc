<?php

function theme_ctl_onboarding_table($variables) {
  // TODO
  // - add visual indicators to communicate time slot state

  $element     = $variables['element'];
  $slots       = $element['#options'];
  $showing_all = isset($element['#showing_all']) ? $element['#showing_all'] : FALSE;
  $header = array(
    t('Monday'),
    t('Tuesday'),
    t('Wednesday'),
    t('Thursday'),
    t('Friday'),
    t('Saturday'),
    t('Sunday'),
  );

  $days             = array('m', 'tu', 'w', 'th', 'f', 'sa', 'su');
  $first_start_hour = 800;
  $last_start_hour  = 1900;
  $rows             = array();

  // Setup the table.
  for ($hour = $first_start_hour; $hour <= $last_start_hour; $hour += 100) {
    $row = array();
    for ($i = 0, $l = count($days); $i < $l; ++$i) {
      $slot_id = $days[$i] . '-' . $hour;
      $slot    = isset($element[$slot_id]) ? $element[$slot_id] : NULL;
      $row[]   = (isset($slot) && ($showing_all || $slot['#title'])) ? drupal_render($slot) : NULL;
    }
    // Only add rows if they are not completely empty.
    $r = array_filter($row, function ($x) { return isset($x); });
    if (!empty($r)) {
      $rows[$hour] = $row;
    }
  }

  $table = theme('table', array(
    'header' => $header,
    'rows'   => $rows,
  ));

  return $table;
}
