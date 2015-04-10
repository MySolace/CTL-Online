<?php

/**
 * Implements hook_entity_info().
 */
function schedule_recurring_entity_info() {
  $entities = array(
    'time_off' => array(
      'label'            => t('Time Off'),
      'base table'       => 'time_off',
      'fieldable'        => TRUE,
      'uri_callback'     => 'time_off_uri',
      'controller class' => 'TimeOffController',
      'entity class'     => 'TimeOff',
      'entity keys'      => array(
        'id' => 'id',
        'bundle' => 'type',
      ),
    ),
  );

  return $entities;
}

class TimeOff extends Entity {
  protected function defaultUri() {
    return array('path' => 'time_off/' . $this->identifier());
  }
}

class TimeOffController extends EntityAPIController {
}

function time_off_uri($entity) {
  return array(
    'path' => 'time_off/' . $entity->id,
  );
}

function time_off_load($id = NULL, $reset = FALSE) {
  $ids = (isset($id) ? array($id) : array());
  $time_off = time_off_load_multiple($ids, $reset);

  return $time_off ? reset($time_off) : FALSE;
}

function time_off_load_multiple($ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('time_off', $ids, $conditions, $reset);
}

function time_off_add() {
  $time_off = entity_create('time_off', array(
    'id' => '',
    'start' => date('Y-m-d'),
    'end' => date('Y-m-d', strtotime('+7 days')),
    'type' => 'user',
  ));

  return drupal_get_form('time_off_form', $time_off);
}

function time_off_date_format() {
  return 'Y-m-d';
}

function time_off_form($form, &$form_state, $time_off) {
  $format = time_off_date_format();
  $form = array(
    '#submit' => array('time_off_form_submit'),
    '#validate' => array(
      'time_off_convert_dates',
      'time_off_form_validate',
    ),
  );

  $form['start'] = array(
    '#type' => 'date_select',
    '#title' => t('Start date'),
    '#required' => TRUE,
    '#default_value' => $time_off->start,
    '#date_format' => $format,
    '#date_year_range' => '0:+1',
    '#date_label_position' => 'none',
  );

  $form['end'] = array(
    '#type' => 'date_select',
    '#title' => t('End date'),
    '#required' => TRUE,
    '#default_value' => $time_off->end,
    '#date_format' => $format,
    '#date_year_range' => '0:+1',
    '#date_label_position' => 'none',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  field_attach_form('time_off', $time_off, $form, $form_state);

  return $form;
}

function time_off_convert_dates($form, &$form_state) {
  $start = date_create_from_format(time_off_date_format(), $form_state['values']['start']);
  $end = date_create_from_format(time_off_date_format(), $form_state['values']['end']);

  $start->setTime(0,0,0);
  $end->setTime(23,59,59);

  $form_state['values']['start'] = $start->getTimestamp();
  $form_state['values']['end'] = $end->getTimestamp();
}

function time_off_form_validate($form, &$form_state) {
  if ($form_state['values']['start'] > $form_state['values']['end']) {
    form_set_error('end', t('Start date must be before the end day.'));
  }
}

function time_off_form_submit($form, &$form_state) {
  global $user;

  $time_off = entity_create('time_off', $form_state['values']);
  $time_off->type = end($user->roles);
  $time_off->author = $user->uid;
  $time_off->save();

  $form_state['redirect'] = 'time-off/' . $time_off->id;
}

function time_off_save(&$time_off) {
  return $time_off->save();
}

function time_off_view($id) {
  $time_off = entity_load('time_off', array($id));
  $time_off = array_shift($time_off);

  $time_off->start = date(time_off_date_format(), $time_off->start);
  $time_off->end = date(time_off_date_format(), $time_off->end);

  $rows = array();

  $rows[] = array('Start', $time_off->start);
  $rows[] = array('End', $time_off->end);

  return array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array('Label', 'Value'),
  );
}
