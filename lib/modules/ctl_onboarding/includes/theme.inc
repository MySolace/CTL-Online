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

  $days = array('m', 'tu', 'w', 'th', 'f', 'sa', 'su');
  $rows = array();

  // Setup the table.
  for ($hour = CTL_ONBOARDING_FIRST_START_HOUR; $hour <= CTL_ONBOARDING_LAST_START_HOUR; $hour += CTL_ONBOARDING_ONE_HOUR) {
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


function theme_ctl_onboarding_table_2($variables) {
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

  $days = array('m', 'tu', 'w', 'th', 'f', 'sa', 'su');
  $rows = array();

  // Setup the table.
  for ($hour = CTL_ONBOARDING_FIRST_START_HOUR; $hour <= CTL_ONBOARDING_LAST_START_HOUR; $hour += CTL_ONBOARDING_ONE_HOUR) {
    $row = array();
    for ($i = 0, $l = count($days); $i < $l; ++$i) {
      $slot_id = $days[$i] . '-' . $hour;
      $slot    = isset($element[$slot_id]) ? $element[$slot_id] : NULL;


      $slot = array();
      $slot['a'] = array(
        '#type'    => 'select',
        '#title'   => $slot_id,
        '#options' => range(0, 10),
      );


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
