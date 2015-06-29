<?php

function schedule_recurring_available($form, $form_state) {
  $slots = schedule_recurring_get_slots();

  $days = _schedule_recurring_days();
  $start_times = _schedule_recurring_times();
  $end_times = _schedule_recurring_times(TRUE);

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
        if (_schedule_recurring_time_increment($end_time, variable_get('schedule_recurring_shift_duration')) === FALSE) {
          $suffix = ' the next morning';
        }

        $shifts[$day.':'.$time.':'.$end_time] = array(
          'day'        => $days[$day],
          'start_time' => $start_times[$time],
          'end_time'   => $end_times[$end_time] . $suffix,
          '#attributes' => array(
            'class' => array(
              'day-' . $day,
              (schedule_recurring_is_priority_shift($day, $time, $end_time)) ? 'priority' : '',
            )
          ),
        );
      }
    }
  }

  uksort($shifts, function ($a, $b) {
    list($day_a, $time_a,) = explode(':', $a);
    list($day_b, $time_b,) = explode(':', $b);

    return (($day_a * 100000) + $time_a) - (($day_b * 100000) + $time_b);
  });

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

  $form['#validate'][] = 'schedule_recurring_picked_shift';
  $form['#validate'][] = 'schedule_recurring_overlapping_shift';
  $form['#validate'][] = 'schedule_recurring_shift_available';

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Sign up for this shift',
  );

  return $form;
}

function schedule_recurring_get_slots() {
  $setter_roles = schedule_recurring_get_mapping_value('subscriber', 'publisher');
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
    for ($i = $result->start; $i < $result->end; _schedule_recurring_time_increment($i)) {
      if (!isset($slots[$result->day])) {
        $slots[$result->day] = array();
      }

      if (!isset($slots[$result->day][$i])) {
        $slots[$result->day][$i] = 0;
      }

      $slots[$result->day][$i] += variable_get('schedule_recurring_points_per_block', 100);
    }
  }

  return $slots;
}

function schedule_recurring_shift_available(&$form, &$form_state) {
  $slots = schedule_recurring_get_slots();

  $days = _schedule_recurring_days();
  $times = _schedule_recurring_times();
  $shift = explode(':', $form_state['values']['shift']);

  $shift = array(
    'day' => $shift[0],
    'start' => $shift[1],
    'end' => $shift[2],
  );

  if(!_schedule_recurring_is_available($shift, $slots)) {
    form_set_error('schedule_recurring', t('Oops! It looks like someone booked that shift while you were choosing. Please select a different shift.'));
  }
}

function schedule_recurring_is_priority_shift($day, $start, $end) {
  $shifts = &drupal_static(__FUNCTION__);

  if (!$shifts) {
    $shifts_unordered = variable_get('schedule_recurring_priority_shifts');

    foreach ($shifts_unordered as $shift) {
      $shift = preg_replace('/\s+/', '', $shift);
      $shift = explode(':', $shift);
      $time = explode('-', $shift[1]);

      $shifts[$shift[0]][] = array(
        'start' => $time[0],
        'end' => $time[1]
      );
    }
  }

  if (isset($shifts[$day])) {
    foreach ($shifts[$day] as $shift) {
      if (($start >= $shift['start'] && $start < $shift['end']) ||
        ($end > $shift['start'] && $end <= $shift['end'])
      ) {
        return true;
      }
    }
  }
}

function schedule_recurring_picked_shift(&$form, &$form_state) {
  if (empty($form_state['values']['shift'])) {
    form_set_error('schedule_recurring', t('Oops! You didn\'t select a shift. Please try again.'));
  }
}

function schedule_recurring_overlapping_shift(&$form, &$form_state) {
  global $user;

  $account = user_load($user->uid);

  if (empty($account->field_shifts) || empty($account->field_shifts[LANGUAGE_NONE])) {
    return;
  }

  list($day, $start, $end) = explode(':', $form_state['values']['shift']);

  $check = array();
  foreach ($account->field_shifts[LANGUAGE_NONE] as $shift) {
    if ($shift['day'] == $day) {
      $wrapping_shifts = schedule_recurring_wrapping_shifts($shift['start']);
      $check = array_merge($check, $wrapping_shifts);
    }
  }

  if (in_array($start, $check)) {
    form_set_error('schedule_recurring', t('It looks like you already have a shift that overlaps with this one. No need to sign up twice!'));
  }
}

function schedule_recurring_wrapping_shifts($start) {
  $times = _schedule_recurring_times();

  $num_wrapping = variable_get('schedule_recurring_shift_duration') / variable_get('schedule_recurring_shift_increment');

  $i = 0;
  $count = FALSE;
  $wrapping_shifts = array();

  foreach ($times as $time => $time_string) {
    if ($time == $start) {
      $count = TRUE;
      $i++;
    }

    if (!$count) {
      // start adding elements to the beginning of the array
      $wrapping_shifts[] = $time;

      // if we have as many shifts as there are supposed to be wrapping, pull out the first element of the array
      if (count($wrapping_shifts) > $num_wrapping) {
        array_shift($wrapping_shifts);
      }
    } else {
      if ($i > $num_wrapping) {
        break;
      } else {
        $i++;
        $wrapping_shifts[] = $time;
      }
    }
  }

  return $wrapping_shifts;
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

  if (!$account->field_shifts) {
    $account->field_shifts = array(
      LANGUAGE_NONE => array(),
    );
  }

  $account->field_shifts[LANGUAGE_NONE] = array_merge($account->field_shifts[LANGUAGE_NONE], $shifts);

  user_save($account);

  $mail_params = array(
    'account' => $account,
    'shift' => $shifts[0],
  );

  drupal_mail('schedule_recurring', 'shift_confirmation', $account->mail, user_preferred_language($account), $mail_params);

  $form_state['redirect'] = array(
    'schedule/confirm',
    array(
      'query' => array(
        'shift' => $form_state['values']['shift'],
      ),
    ),
  );
}

function schedule_recurring_get_mapping_value($searchField, $returnField) {
  global $user;

  $mapping = variable_get('schedule_recurring_shift_mapping');

  $return = array();

  foreach ($mapping as $map) {
    foreach ($user->roles as $key => $role) {
      if ($key == $map[$searchField]) {
        $return[] = $map[$returnField];
      }
    }
  }

  if (empty($return)) {
    $return[] = -1;
  }

  return $return;
}

function schedule_recurring_get_off($am, $pm) {
  module_load_include('inc', 'schedule_recurring', 'time_off');

  $query = db_select('time_off', 't');
  $query->leftJoin('users', 'u', 'u.uid=t.author');
  $query->condition('u.uid', schedule_recurring_role_subquery('subscriber'), 'IN');
  $query->fields('t', array('start', 'end', 'id'));
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
      date(time_off_date_format(), $res->end),
      l('View reason', 'time-off/' . $res->id)
    );
  }

  return array(
    'results' => $off,
    'uids' => $uids,
  );
}

function schedule_recurring_role_subquery($role) {
  $search = ($role == 'subscriber') ? 'publisher' : 'subscriber';

  $subq = db_select('users_roles', 'r');
  $subq->condition('r.rid', schedule_recurring_get_mapping_value($search, $role), 'IN');
  $subq->fields('r', array('uid'));

  return $subq;
}

function schedule_recurring_get_on($day, $exclude = array(), $all_shifts = FALSE, $format = 'output') {
  $today = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user')
    ->fieldCondition('field_shifts', 'day', $day);

  if (!$all_shifts) {
    $query->entityCondition('entity_id', schedule_recurring_role_subquery('subscriber'), 'IN');
  }

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
        switch ($format) {
          case 'output':
            $today[$shift['day'] . ':' . $shift['start'] . ':' . $user->uid] = array(
              '<a href="/user/'.$user->uid.'">'.format_username($user).'</a>',
              $times_start[$shift['start']] . ' - ' . $times_end[$shift['end']],
              implode(', ', $user->roles)
            );
            break;
          case 'raw':
            $today[] = array(
              'shift' => $shift,
              'user' => $user,
            );
            break;
        }
      }
    }
  }

  if ($format == 'output') {
    uksort($today, function ($a, $b) {
      list($day_a, $time_a,) = explode(':', $a);
      list($day_b, $time_b,) = explode(':', $b);

      return (($day_a * 100000) + $time_a) - (($day_b * 100000) + $time_b);
    });
  }

  return $today;
}

function schedule_recurring_schedule($form, $form_state) {
  global $user;
  $uid = $user->uid;

  if (!schedule_recurring_is_publisher()) {
    drupal_goto('schedule/my-schedule');
    return;
  }

  module_load_include('inc', 'schedule_recurring', 'time_off');

  $form = schedule_recurring_schedule_filter($form, $form_state);

  $prefix = array(
    '#markup' => l('Edit my supervisor shifts', 'user/'.$uid.'/edit', array(
      'query' => array('destination' => 'schedule'),
      'attributes' => array(
        'class' => array('button'),
      )
    )),
  );

  array_unshift($form, $prefix);

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
    $on = schedule_recurring_get_on($today, $off_res['uids']);
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
    '#header' => array('Name', 'Out', 'Reason'),
    '#empty' => t('No one is out @l.', array('@l' => $off_label)),
  );

  return $form;
}

function schedule_recurring_my_schedule() {
  global $user;

  $account = user_load($user->uid);
  $rows = array();

  if (isset($account->field_shifts[LANGUAGE_NONE])) {
    $shifts = $account->field_shifts[LANGUAGE_NONE];

    $days = _schedule_recurring_days();
    $start_times = _schedule_recurring_times();
    $end_times = _schedule_recurring_times(TRUE);

    foreach ($shifts as $shift) {
      $rows[] = array(
        $days[$shift['day']],
        $start_times[$shift['start']],
        $end_times[$shift['end']],
      );
    }
  }

  $time_off = schedule_recurring_my_time_off();

  $off = array();
  foreach ($time_off as $time) {
    $off[] = array(
      date('F d, Y', $time->start),
      date('F d, Y', $time->end),
      l('Edit', 'time-off/' . $time->id . '/edit', array('query' => array('destination' => 'schedule'))) . ' | ' .
      l('Delete', 'time-off/' . $time->id . '/delete', array('query' => array('destination' => 'schedule'))),
    );
  }

  $link_options = array(
    'html' => FALSE,
    'attributes' => array(
      'class' => array(
        'button',
      ),
    ),
  );

  return array(
    array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(
        'Day',
        'Start Time',
        'End Time',
      ),
      '#empty' => t('You are not signed up for any shifts yet.'),
    ),
    array(
      '#prefix' => '<h3>Time Off</h3>',
      '#theme' => 'table',
      '#rows' => $off,
      '#header' => array(
        'Start date',
        'End date',
      ),
      '#empty' => t('You don\'t have any time off requests in the future.'),
    ),
    array(
      '#theme' => 'link',
      '#text' => t('Sign up for a shift'),
      '#path' => 'schedule/sign-up',
      '#options' => $link_options,
    ),
    array(
      '#theme' => 'link',
      '#text' => t('Take time off'),
      '#path' => 'time-off',
      '#options' => $link_options + array('query' => array('destination' => 'schedule')),
    ),
  );
}

function schedule_recurring_my_time_off() {
  global $user;

  $query = db_select('time_off', 't');
  $query->leftJoin('users', 'u', 'u.uid=t.author');
  $query->condition('u.uid', $user->uid);
  $query->fields('t', array('start', 'end', 'id'));
  $query->fields('u', array('uid', 'name'));
  $query->condition('t.end', time(), '>=');
  $query->orderBy('t.end', 'ASC');

  $results = $query->execute()->fetchAll();

  return $results;
}

function schedule_recurring_schedule_submit($form, &$form_state) {
  $form_state['filters']['date'] = $form_state['values']['filter_day'];
  $form_state['rebuild'] = TRUE;
}

function schedule_recurring_schedule_filter() {
  module_load_include('inc', 'schedule_recurring', 'time_off');

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

function _schedule_recurring_is_available($shift, $shifts, $account = NULL) {
  global $user;

  $roles = variable_get('schedule_recurring_shift_mapping');
  $filter_roles = array();
  $role_indexed = array();
  foreach ($roles as $role) {
    $filter_roles[] = $role['subscriber'];
    $role_indexed[$role['subscriber']] = $role['points'];
  }

  if (is_null($account)) {
    $account = $user;
  }

  $points = schedule_recurring_get_mapping_value('subscriber', 'points');
  $points = (int)$points[0];

  $time = $shift['start'];
  $day = $shift['day'];

  $increment = variable_get('schedule_recurring_shift_increment');
  $end_time = $time;
  _schedule_recurring_time_increment($end_time, variable_get('schedule_recurring_shift_duration'));

  while ($time < $end_time) {
    $q = db_query("
      SELECT r.rid, count(r.rid) as count FROM users u
      JOIN users_roles r ON r.uid=u.uid
      JOIN field_data_field_shifts s ON s.entity_id = u.uid
      WHERE r.rid IN (:roles)
      AND s.field_shifts_day = :day
      AND :time >= s.field_shifts_start
      AND :time < s.field_shifts_end
      GROUP BY r.rid
    ", array(
      ':roles' => $filter_roles,
      ':day' => $day,
      ':time' => $time,
    ));

    $results = $q->fetchAll();

    $used_points = 0;
    foreach ($results as $res) {
      $used_points += $role_indexed[$res->rid] * $res->count;
    }

    if (!isset($shifts[$day][$time]) || ($used_points + $points) >= $shifts[$day][$time]) {
      return FALSE;
    }

    if (_schedule_recurring_time_increment($time, $increment) === FALSE) {
      $day = ($day + 1 > 6) ? 0 : $day + 1;
    }
  }

  return TRUE;
}

function _schedule_recurring_get_mapping($role, $account) {
  $points = &drupal_static(__FUNCTION__);

  if (!$points) {
    foreach ($mapping as $map) {
      foreach ($account->roles as $key => $role) {
        if ($key == $map[$input]) {
          $points = $map['points'];
        }
      }
    }
  }

  return $points;
}

/**
 * Given a military time input, output a time incremented
 * by $amount.
 */
function _schedule_recurring_time_increment(&$val, $amount = NULL) {
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

