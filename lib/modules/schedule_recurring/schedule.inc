<?php

function schedule_recurring_schedule() {
  $setter_roles = _schedule_recurring_setters();

  // Users base table
  $q = db_select('users', 'u');

  // Filter by those who are setters
  $subq = db_select('users_roles', 'r');
  $subq->condition('r.rid', $setter_roles, 'IN');
  $subq->fields('r', array('uid'));
  $q->condition('u.uid', $subq, 'IN');

  // Get the fields
  $q->join('field_data_field_shifts', 'shifts', 'u.uid = shifts.entity_id');
  $q->condition('shifts.entity_type', 'user', '=');
  
  $q->addField('shifts', 'field_shifts_day', 'day');
  $q->addField('shifts', 'field_shifts_start', 'start');
  $q->addField('shifts', 'field_shifts_end', 'end');

  $results = $q->execute()->fetchAll();

  $slots = array();

  foreach ($results as $result) {
    for ($i = $result->start; $i < $result->end; time_increment($i)) {
      if (!isset($slots[$result->day])) {
        $slots[$result->day] = array();
      }

      if (!isset($slots[$result->day][$i])) {
        $slots[$result->day][$i] = 0;
      }

      $slots[$result->day][$i] += variable_get('schedule_recurring_users_per_block', 50);
    }
  }

  $days = _schedule_recurring_days();
  $times = _schedule_recurring_times();
  $shifts = array();
  foreach ($slots as $day => $day_shifts) {
    foreach ($day_shifts as $time => $availability) {
      $shift = array(
        'day'   => $day,
        'start' => $time,
      );
      if (_schedule_recurring_is_available($shift, $slots)) {
        $end_time = $time;
        $suffix = '';
        if (time_increment($end_time, variable_get('schedule_recurring_shift_duration')) === FALSE) {
          $suffix = ' the next morning';
        }

        $shifts[] = array(
          $days[$day],
          $times[$time],
          $times[$end_time] . $suffix,
        );
      }
    }
  }

  return array(
    '#theme' => 'table',
    '#rows' => $shifts,
    '#header' => array('Day', 'Start time', 'End time'),
  );
}

function _schedule_recurring_is_available($shift, $shifts) {
  $time = $shift['start'];
  $day = $shift['day'];

  $increment = variable_get('schedule_recurring_shift_increment');
  $end_time = $time;
  time_increment($end_time, variable_get('schedule_recurring_shift_duration'));

  while ($time < $end_time) {
    if (!isset($shifts[$day][$time]) || $shifts[$day][$time] <= 0) {
      return FALSE;
    }

    if (time_increment($time, $increment) === FALSE) {
      $day = ($day + 1 > 6) ? 0 : $day + 1;
    }
  }

  return TRUE;
}

/**
 * Given a military time input, output a time incremented
 * by $amount.
 */
function time_increment(&$val, $amount = NULL) {
  if ($amount == NULL) {
    $amount = variable_get('schedule_recurring_shift_increment');
  }

  if ($amount > 60) {
    $amount = 100 * floor($amount / 60) + ($amount % 60);
  }

  $val += $amount;

  if (intval(substr($val, -2)) >= 60) {
    // add 100 then subtract 60
    $val += 40;
  }

  if ($val > 2400) {
    $val = $val % 2400;
    return FALSE;
  }
}

