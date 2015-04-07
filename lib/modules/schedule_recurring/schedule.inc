<?php

function schedule_recurring_available($form, $form_state) {
  $setter_roles = schedule_recurring_get_role('publisher');

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

        $shifts[$day.':'.$time.':'.$end_time] = array(
          'day'        => $days[$day],
          'start_time' => $times[$time],
          'end_time'   => $times[$end_time] . $suffix,
        );
      }
    }
  }

  $form = array();
  $form['shift'] = array(
    '#type' => 'tableselect',
    '#options' => $shifts,
    '#empty' => t('There are currently no shifts available.'),
    '#multiple' => FALSE,
    '#attributes' => array(
      'class' => array('tableselect'),
    ),
    '#header' => array(
      'day'        => 'Day',
      'start_time' => 'Start time',
      'end_time'   => 'End time',
    ),
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'schedule_recurring') . '/js/tableselect.js',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Sign up for this shift',
  );

  return $form;
}

function schedule_recurring_confirm() {
  list($day, $start, $end) = explode(':', $_GET['shift']);

  $days = _schedule_recurring_days();
  $start_times = _schedule_recurring_times();
  $end_times = _schedule_recurring_times(TRUE);

  $text = t('Shift confirmed for @day from @start to @end', array(
    '@day' => $days[$day] . 's',
    '@start' => $start_times[$start],
    '@end' => $end_times[$end],
  ));

  return array(
    '#markup' => '<h1>'.$text.'</h1>',
  );
}

function schedule_recurring_available_submit($form, &$form_state) {
  global $user;

  $shift = explode(':', $form_state['values']['shift']);

  $account = user_load($user->uid);

  $shifts = array();
  $shifts[] = array(
    'day'   => $shift[0],
    'start' => $shift[1],
  );

  if ($shift[2] < $shift[1]) {
    $day = ($shift[0] + 1 < 6) ? $shift[0] + 1 : 0;
    $shifts[0]['end'] = 2400;
    $shifts[] = array(
      'day'   => $day,
      'start' => 0,
      'end'   => $shift[2],
    );
  } else {
    $shifts[0]['end'] = $shift[2];
  }

  $account->field_shifts[LANGUAGE_NONE] = array_merge($account->field_shifts[LANGUAGE_NONE], $shifts);

  var_dump($account);
  user_save($account);

  $form_state['redirect'] = array(
    'schedule/confirm',
    array(
      'query' => array(
        'shift' => $form_state['values']['shift'],
      ),
    ),
  );
}

function schedule_recurring_get_role($return) {
  global $user;

  $input = ($return == 'publisher') ? 'publisher' : 'subscriber';
  $output = $return;

  $mapping = variable_get('schedule_recurring_shift_mapping');

  $return = array();
  foreach ($mapping as $map) {
    foreach ($user->roles as $key => $role) {
      if ($key == $map[$input]) {
        $return[] = $map[$output];
      }
    }
  }

  if (empty($return)) {
    $return[] = -1;
  }

  return $return;
}

function schedule_recurring_get_off($am, $pm) {
  $query = db_select('time_off', 't');
  $query->leftJoin('users', 'u', 'u.uid=t.author');
  $query->condition('u.uid', schedule_recurring_role_subquery('subscriber'), 'IN');
  $query->fields('t', array('start', 'end'));
  $query->fields('u', array('uid', 'name'));
  $query->condition('t.start', $am, '<=');
  $query->condition('t.end', $pm, '>=');

  $results = $query->execute()->fetchAll();

  $uids = array();
  $off = array();
  foreach ($results as $res) {
    $uids[] = $res->uid;
  }

  $users = user_load_multiple($uids);

  foreach ($results as $res) {
    $off[] = array(
      '<a href="/user/'.$res->uid.'">'.format_username($users[$res->uid]).'</a>',
      date(time_off_date_format(), $res->start) . ' until ' .
      date(time_off_date_format(), $res->end)
    );
  }

  return array(
    'results' => $off,
    'uids' => $uids,
  );
}

function schedule_recurring_role_subquery($role) {
  $subq = db_select('users_roles', 'r');
  $subq->condition('r.rid', schedule_recurring_get_role($role), 'IN');
  $subq->fields('r', array('uid'));

  return $subq;
}

function schedule_recurring_get_on($am, $pm, $day, $exclude = array()) {
  $today = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user')
    ->entityCondition('entity_id', schedule_recurring_role_subquery('subscriber'), 'IN')
    ->fieldCondition('field_shifts', 'day', $day);

  if (!empty($exclude)) {
    $query->entityCondition('entity_id', $exclude, 'NOT IN');
  }

  $results = $query->execute();
  $users = array();
  if ($results) {
    $users = user_load_multiple(array_keys($results['user']));
  }

  $times_start = _schedule_recurring_times();
  $times_end = _schedule_recurring_times(TRUE);
  foreach ($users as $user) {
    foreach ($user->field_shifts[LANGUAGE_NONE] as $shift) {
      unset($user->roles[2]);
      if ($shift['day'] == $day) {
        $today[] = array(
          '<a href="/user/'.$user->uid.'">'.format_username($user).'</a>',
          $times_start[$shift['start']] . ' - ' . $times_end[$shift['end']],
          implode(', ', $user->roles)
        );
      }
    }
  }

  return $today;
}

function schedule_recurring_schedule($form, $form_state) {
  $form = schedule_recurring_schedule_filter($form, $form_state);
  $am = $pm = $today = NULL;

  if (isset($form_state['filters']['date'])) {
    $am = date_create_from_format(time_off_date_format(), $form_state['filters']['date']);
    $off_label = $form_state['filters']['date'];
  } else {
    $am = new DateTime();
    $off_label = 'Today';
  }

  $am->setTime(0,0,0);
  $am = $am->getTimestamp();

  $pm = $am + (24 * 60 * 60) - 1;
  $today = date('w', $am);

  $on = array();
  $off = array();

  // Only run the DB queries if we're loading the form the first time or
  // this is a rebuild after a submission.
  if (empty($form_state['input']) || $form_state['rebuild'] == true) {
    $off_res = schedule_recurring_get_off($am, $pm);
    $off = $off_res['results'];
    $on = schedule_recurring_get_on($am, $pm, $today, $off_res['uids']);
  }

  $form[] = array(
    '#prefix' => '<h1>Scheduled: '.$off_label.'</h1>',
    '#theme' => 'table',
    '#rows' => $on,
    '#header' => array('', 'Shift', 'Role'),
    '#empty' => t('No one is scheduled @l.', array('@l' => $off_label)),
  );

  $form[] = array(
    '#prefix' => '<h1>Out '.$off_label.'</h1>',
    '#theme' => 'table',
    '#rows' => $off,
    '#header' => array('Name', 'Out'),
    '#empty' => t('No one is out @l.', array('@l' => $off_label)),
  );

  return $form;
}

function schedule_recurring_schedule_submit($form, &$form_state) {
  $form_state['filters']['date'] = $form_state['values']['filter_day'];
  $form_state['rebuild'] = TRUE;
}

function schedule_recurring_schedule_filter() {
  module_load_include('inc', 'schedule_recurring', 'entity');

  $form = array();

  $form['filter'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('View another day')
  );
  $form['filter']['filter_day'] = array(
    '#type' => 'date_popup',
    '#date_format' => time_off_date_format(),
    //'#title' => t('Date'),
    '#default_value' => date(time_off_date_format()),
    '#date_year_range' => '0:+1',
    '#date_label_position' => 'none',
  );
  $form['filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
  );

  return $form;
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

