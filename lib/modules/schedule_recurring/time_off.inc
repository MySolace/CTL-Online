<?php


function schedule_recurring_time_off_entity() {
  return array(
    'label'                  => t('Time Off'),
    'base table'             => 'time_off',
    'fieldable'              => TRUE,
    'uri_callback'           => 'time_off_uri',
    'controller class'       => 'EntityAPIController',
    'entity class'           => 'TimeOff',
    'views controller class' => 'EntityDefaultViewsController',
    'entity keys' => array(
      'id'     => 'id',
      'bundle' => 'type',
    ),
  );
}

/**
 * Implements hook_entity_property_info_alter().
 */
function schedule_recurring_entity_property_info_alter(&$info) {
  $info['time_off']['properties']['id']['type'] = 'user';
  $info['time_off']['properties']['start']['handler'] = 'date_views_filter_handler';
  $info['time_off']['properties']['start']['is date'] = TRUE;
}

class TimeOff extends Entity {
  protected function defaultUri() {
    return array('path' => 'time-off/' . $this->identifier());
  }
}

function time_off_uri($entity) {
  return array(
    'path' => 'time-off/' . $entity->id,
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
    'start' => time(),
    'end' => strtotime('+7 days'),
    'reason' => '',
    'type' => 'user',
  ));

  return drupal_get_form('time_off_form', $time_off);
}

function time_off_date_format() {
  return 'Y-m-d';
}

function time_off_form($form, &$form_state, $time_off) {
  if (!is_object($time_off)) {
    $time_off = entity_load('time_off', array($time_off));
    $time_off = array_shift($time_off);
  }

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
    '#default_value' => date('Y-m-d', $time_off->start),
    '#date_format' => $format,
    '#date_year_range' => '0:+1',
    '#date_label_position' => 'none',
  );

  $form['end'] = array(
    '#type' => 'date_select',
    '#title' => t('End date'),
    '#required' => TRUE,
    '#default_value' => date('Y-m-d', $time_off->end),
    '#date_format' => $format,
    '#date_year_range' => '0:+1',
    '#date_label_position' => 'none',
  );

  $form['reason'] = array(
    '#type' => 'textarea',
    '#title' => t('Reason for taking time off'),
    '#required' => FALSE,
    '#default_value' => $time_off->reason,
    '#rows' => 2,
  );

  $form['entity'] = array(
    '#type' => 'value',
    '#value' => $time_off,
  );

  field_attach_form('time_off', $time_off, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

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

  $time_off = $form_state['values']['entity'];
  $time_off->start = $form_state['values']['start'];
  $time_off->end = $form_state['values']['end'];
  $time_off->reason = $form_state['values']['reason'];
  $time_off->type = end($user->roles);
  $time_off->author = $user->uid;
  $time_off->save();

  $form_state['redirect'] = 'time-off/' . $time_off->id;
}

function time_off_save(&$time_off) {
  return $time_off->save();
}

function time_off_delete($time_off) {
  entity_delete('time_off', $time_off);

  drupal_goto('time-off');
}

function time_off_view($id) {
  $time_off = entity_load('time_off', array($id));
  $time_off = array_shift($time_off);

  $time_off->start = date(time_off_date_format(), $time_off->start);
  $time_off->end = date(time_off_date_format(), $time_off->end);

  $rows = array();

  $rows[] = array('Start', $time_off->start);
  $rows[] = array('End', $time_off->end);
  $rows[] = array('Reason', check_plain($time_off->reason));

  return array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array('Label', 'Value'),
  );
}
