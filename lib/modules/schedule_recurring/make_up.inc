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
    'reason' => '',
    'type' => 'user',
  ));

  return drupal_get_form('make_up_form', $make_up);
}

function make_up_form($form, &$form_state, $make_up) {
  $default = !empty($form_state['values']['howmany_select']) ? $form_state['values']['howmany_select'] : 1;

  $form['howmany_select'] = array(
    '#title' => t('How many checkboxes do you want?'),
    '#type' => 'select',
    '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4),
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => 'ajax_example_autocheckboxes_callback',
      'wrapper' => 'checkboxes-div',
      'method' => 'replace',
      'effect' => 'fade',
    ),

  );


  $form['checkboxes_fieldset'] = array(
    '#title' => t("Generated Checkboxes"),
    // The prefix/suffix provide the div that we're replacing, named by
    // #ajax['wrapper'] above.
    '#prefix' => '<div id="checkboxes-div">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
    '#description' => t('This is where we get automatically generated checkboxes'),
  );

  $num_checkboxes = !empty($form_state['values']['howmany_select']) ? $form_state['values']['howmany_select'] : 1;
  for ($i = 1; $i <= $num_checkboxes; $i++) {
    $form['checkboxes_fieldset']["checkbox$i"] = array(
      '#type' => 'checkbox',
      '#title' => "Checkbox $i",
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function ajax_example_autocheckboxes_callback($form, $form_state) {
  return $form['checkboxes_fieldset'];
}

function make_up_convert_dates($form, &$form_state) {
  $start = date_create_from_format(make_up_date_format(), $form_state['values']['start']);
  $end = date_create_from_format(make_up_date_format(), $form_state['values']['end']);

  $start->setTime(0,0,0);
  $end->setTime(23,59,59);

  $form_state['values']['start'] = $start->getTimestamp();
  $form_state['values']['end'] = $end->getTimestamp();
}

function make_up_form_validate($form, &$form_state) {
  if ($form_state['values']['start'] > $form_state['values']['end']) {
    form_set_error('end', t('Start date must be before the end day.'));
  }
}

function make_up_form_submit($form, &$form_state) {
  global $user;

  $make_up = $form_state['values']['entity'];
  $make_up->start = $form_state['values']['start'];
  $make_up->end = $form_state['values']['end'];
  $make_up->reason = $form_state['values']['reason'];
  $make_up->type = end($user->roles);
  $make_up->author = $user->uid;
  $make_up->save();

  $form_state['redirect'] = 'time-off/' . $make_up->id;
}

function make_up_save(&$make_up) {
  return $make_up->save();
}

function make_up_delete($make_up) {
  entity_delete('make_up', $make_up);

  drupal_goto('time-off');
}

function make_up_view($id) {
  $make_up = entity_load('make_up', array($id));
  $make_up = array_shift($make_up);

  $make_up->start = date(make_up_date_format(), $make_up->start);
  $make_up->end = date(make_up_date_format(), $make_up->end);

  $rows = array();

  $rows[] = array('Start', $make_up->start);
  $rows[] = array('End', $make_up->end);
  $rows[] = array('Reason', check_plain($make_up->reason));

  return array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array('Label', 'Value'),
  );
}
