<?php


function schedule_recurring_make_up_entity() {
  return array(
    'label'            => t('Make up'),
    'base table'       => 'make_up',
    'fieldable'        => TRUE,
    'uri_callback'     => 'make_up_uri',
    'controller class' => 'MakeUpController',
    'entity class'     => 'MakeUp',
    'entity keys'      => array(
      'id' => 'id',
      'bundle' => 'type',
    ),
  );
}

class MakeUp extends Entity {
  protected function defaultUri() {
    return array('path' => 'make-up/' . $this->identifier());
  }
}

class MakeUpController extends EntityAPIController {
}

function make_up_uri($entity) {
  return array(
    'path' => 'make-up/' . $entity->id,
  );
}

function make_up_load($id = NULL, $reset = FALSE) {
  $ids = (isset($id) ? array($id) : array());
  $make_up = make_up_load_multiple($ids, $reset);

  return $make_up ? reset($make_up) : FALSE;
}

function make_up_load_multiple($ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('make_up', $ids, $conditions, $reset);
}

function make_up_add() {
  $make_up = entity_create('make_up', array(
    'id' => '',
    'start' => time(),
    'end' => strtotime('+4 hours'),
    'type' => 'user',
  ));

  return drupal_get_form('make_up_form', $make_up);
}

function make_up_form($form, &$form_state, $make_up) {
  $day = !empty($form_state['values']['date']) ? $form_state['values']['date'] : date('Y-m-d', strtotime('+1 day'));

  $form['date'] = array(
    '#title' => t('Pick a day for your make-up shift.'),
    '#prefix' => t('<p>If you need to miss a shift - that\'s okay, life happens! We ask that you schedule a make up shift to fulfill your commitment to taking one four hour shift a week.'),
    '#type' => 'date_select',
    '#required' => TRUE,
    '#default_value' => $day,
    '#date_format' => 'Y-m-d',
    '#date_year_range' => '0:+1',
    '#date_label_position' => 'none',
    '#ajax' => array(
      'callback' => 'make_up_ajax_form',
      'wrapper' => 'shift-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['entity'] = array(
    '#type' => 'value',
    '#value' => $make_up,
  );

  $shifts = make_up_get_shifts_for_day($day);

  $form['shift_wrapper'] = array(
    '#title' => 'Select a shift',
    '#prefix' => '<div id="shift-wrapper">',
    '#suffix' => '</div>',
    '#type' => 'markup',
  );

  $form['shift_wrapper']['shift'] = array(
    '#type' => 'tableselect',
    '#options' => $shifts,
    '#empty' => t('There are no shifts available on this date.'),
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
    '#value' => t('Submit'),
  );

  return $form;
}

function make_up_get_shifts_for_day($date) {
  module_load_include('inc', 'schedule_recurring', 'schedule');

  $shift_day = (int) date('w', strtotime($date));

  $off = schedule_recurring_get_off(strtotime($date . ' 0:00:00'), strtotime($date . ' 23:59:59'), FALSE, 'raw');
  $off_uids = $off['uids'];

  if (empty($off_uids)) {
    $off_uids = array(0);
  }

  // Select all shifts on this day where people have taken time off
  // spit out how many people have made a make-up shift at that time
  $time_off = db_query('
    SELECT * FROM time_off t
    JOIN field_data_field_shifts s on s.entity_id = t.author
    WHERE t.author IN (:uids)
    AND s.field_shifts_day = :day
  ', array(
    ':uids' => $off_uids,
    ':day' => $shift_day,
  ));

  $make_ups = db_query('
    SELECT * FROM make_up m
    JOIN field_data_field_shifts s on s.entity_id = m.author
    WHERE m.start BETWEEN :start AND :end
  ', array(
    ':start' => strtotime($date . ' 0:00:00'),
    ':end' => strtotime($date . ' 23:59:59'),
  ));

  $available_make_ups = array();
  foreach ($time_off as $res) {
    if (!isset($available_make_ups[$res->field_shifts_start])) {
      $available_make_ups[$res->field_shifts_start] = 0;
    }

    $available_make_ups[$res->field_shifts_start]++;
  }

  foreach ($make_ups as $m) {
    $available_make_ups[$res->field_shifts_start]--;
  }

  $time_off = array(
    $shift_day => array()
  );

  foreach ($available_make_ups as $time => $val) {
    if ($val <= 0) continue;

    if (isset($time_off[$shift_day][$time])) {
      $time_off[$shift_day][$time]['availability']++;
    } else {
      $time_off[$shift_day][$time] = array(
        'validate' => FALSE,
        'availability' => 1,
      );
    }
  }

  //$slots = $time_off;
  $slots = schedule_recurring_get_slots() + $time_off;

  $days = _schedule_recurring_days(FALSE);
  $start_times = _schedule_recurring_times();
  $end_times = _schedule_recurring_times(TRUE);

  $shifts = array();
  foreach ($slots as $day => $day_shifts) {
    if ($day !== $shift_day) continue;
    foreach ($day_shifts as $time => $availability) {
      $shift = array(
        'day'   => $day,
        'start' => $time,
      );
      if ((_schedule_recurring_is_available($shift, $slots, NULL, 2) && _make_up_shift_is_available($date, $shift)) ||
          (is_array($availability) && $availability['validate'] == FALSE)
      ) {
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
              (isset($time_off[$day][$time])) ? 'priority' : '',
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

  return $shifts;
}

/**
 * For now, we only allow one make up per time slot.
 */
function _make_up_shift_is_available($day, $shift) {
  $time = str_pad($shift['start'], 4, '0', STR_PAD_LEFT);
  $timestamp = strtotime("$day $time");
  $interval = variable_get('schedule_recurring_shift_duration');

  $q = db_select('make_up', 'm');

  $q->fields('m');
  $q->condition('m.start', $timestamp - $interval, '>');
  $q->condition('m.start', $timestamp + $interval, '<');

  $res = $q->execute()->fetchAll();

  return (count($res) == 0);
}

function make_up_ajax_form($form, $form_state) {
  return $form['shift_wrapper'];
}

function make_up_form_submit($form, &$form_state) {
  global $user;

  $date = $form_state['values']['date'];
  $shift = explode(':', $form_state['values']['shift']);

  $start_time = str_pad($shift[1], 4, '0', STR_PAD_LEFT);
  $end_time = $shift[2];

  $make_up = $form_state['values']['entity'];
  $make_up->start = strtotime("$date $start_time");
  $make_up->end = strtotime("$date $start_time");
  $make_up->type = end($user->roles);
  $make_up->author = $user->uid;
  $make_up->save();

  $form_state['redirect'] = 'schedule';
}

function make_up_save(&$make_up) {
  return $make_up->save();
}

function make_up_delete($make_up) {
  drupal_set_message(t('Sorry to see you can\'t do that make up shift. Please select a different time that works for you.'));
  entity_delete('make_up', $make_up);

  drupal_goto('make-up');
}

function make_up_view($id) {
  $make_up = entity_load('make_up', array($id));
  $make_up = array_shift($make_up);

  $rows = array();

  $rows[] = array('Start', $make_up->start);
  $rows[] = array('End', $make_up->end);

  return array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array('Label', 'Value'),
  );
}
