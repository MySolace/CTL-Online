<?php

/**
 * Implements hook_form().
 */
function ctl_onboarding_form($form, &$form_state) {
  if (isset($form_state['storage'])) {
    $storage = $form_state['storage'];
    if (isset($storage['confirm_defer']) && $storage['confirm_defer']) {
      $question    = 'Are you sure?';
      $path        = 'registration';
      $description = 'Defer !!!';
      $yes         = 'Continue';
      $no          = 'Start again';
      $name        = 'qqqqqqqqqqqqqq';
      return confirm_form($form, $question, $path, $description, $yes, $no, $name);
    }
    if (isset($storage['confirm_decline']) && $storage['confirm_decline']) {
      $question    = 'Are you sure?';
      $path        = 'registration';
      $description = 's;ghj;dlghjldg;jh;lfkdjg';
      $yes         = 'Continue';
      $no          = 'Start again';
      $name        = 'gdhdfghfg';
      return confirm_form($form, $question, $path, $description, $yes, $no, $name);
    }
  }

  // // TODO:
  // // - Temp code!  Clean this up !
  // // - Fixgure out where #46c7ff comes from.
  // $form['styles'] = array(
  //   '#type' => 'markup',
  //   '#markup' =>
  //     '<style>' .
  //       'table td {' .
  //         'padding: 0' .
  //       '}' .
  //       '.form-type-radio label {' .
  //         'padding: 10px !important;' .
  //       '}' .
  //       '.form-type-radio label:hover {' .
  //         'background-color: #0FF;' .
  //       '}' .
  //       '.form-type-radio label:before {' .
  //         'display: none;' .
  //       '}' .
  //       'input[type=radio]:checked+.radio:before,' .
  //       '.form-type-radio input[type=radio]:checked+label {' .
  //         'background-color: #46c7ff;' .
  //         'color: #FFF;' .
  //       '}' .
  //     '</style>',
  // );

  $registration_period = intval(variable_get('ctl_onboarding_registration_period', CTL_ONBOARDING_REGISTRATION_CLOSED));
  if ($registration_period === CTL_ONBOARDING_REGISTRATION_CLOSED) {
    $form['registration_closed'] = array(
      '#type'   => 'markup',
      '#markup' => "<p>The registration period is closed.</p>",
    );
    return $form;
  }

  $registration_start_date  = variable_get('ctl_onboarding_registration_start_date', '[X]');
  $registration_finish_date = variable_get('ctl_onboarding_registration_finish_date', '[X]');

  $form['instructions'] = array(
    '#type'   => 'markup',
    '#markup' => "<p>Register for a training session.</p>",
  );
  $form['policies'] = array(
    '#type'   => 'markup',
    '#markup' => "<p>Policies: Registration occurs between $registration_start_date date and $registration_finish_date date. After that, we are only able to accomodate 2 schedule changes.  Training will occur for 6 weeks.</p>",
  );
  $form['training_slot'] = array(
    '#type'    => 'radios',
    '#options' => variable_get('ctl_onboarding_slots'),
    '#theme'   => array('ctl_onboarding_table'),
  );
  $form['register'] = array(
    '#type'     => 'submit',
    '#value'    => 'Register',
    '#validate' => array('_ctl_onboarding_form_validate_register'),
    '#submit'   => array('_ctl_onboarding_form_submit_register'),
  );
  $form['defer'] = array(
    '#type'   => 'submit',
    '#value'  => 'Defer',
    '#submit' => array('_ctl_onboarding_form_submit_defer'),
  );
  $form['decline'] = array(
    '#type'   => 'submit',
    '#value'  => 'Decline',
    '#submit' => array('_ctl_onboarding_form_submit_decline'),
  );

  return $form;
}


/**
 *
 */
function _ctl_onboarding_form_validate_register($form, &$form_state) {
  // drupal_set_message(t("hi"));

  // $values = $form_state['values'];
  // $unmet_requirements = array(_ctl_graduation_courses_completed($values['uid']))
  //                     + $values['additional_requirements'];
  // $unmet_requirements = array_filter($unmet_requirements, function ($v) { return empty($v); });
  // if (!empty($unmet_requirements)) {
  //   form_set_error('additional_requirements', t('The trainee must pass all the requirements.'));
  // }
}


/**
 *
 */
function _ctl_onboarding_form_submit_register($form, &$form_state) {
  global $user;

  $values = $form_state['values'];
  $slot   = $values['training_slot'];

  // drupal_set_message($slot);

  if (is_null($slot)) {
    form_set_error('training_slot', t('A time slot must be chosen!'));
    return;
  }

  // $count = db_query('SELECT slot_code FROM {ctl_onboarding_slot} WHERE slot_code = :slot LIMIT 1;', array(':slot' => $slot))->rowCount();
  // dsm($count);

  $query = db_select('ctl_onboarding_slot', 's');
  $query->addField('s', 'cohort_id');
  $query->addField('s', 'slot_code');
  $query->addField('s', 'max_trainers');
  $query->addField('s', 'num_registrants');
  $result = $query
    ->condition('s.slot_code', $slot)
    ->execute()
    ->fetchAll();

  dsm($result);

  // $slot_exists = $count > 0;

  // if ($slot_exists) {


  //   db_insert('ctl_onboarding_registrant')
  //     ->fields(array(


  //       'cohort_id'       => $cohort_id,
  //       'slot_code'       => $slot_code,
  //       'max_trainers'    => 2,
  //       'num_registrants' => 0,


  //     ))
  //     ->execute();


  // }
  // else {
  //   $trainees_per_trainer = variable_get('ctl_onboarding_trainees_per_trainer', CTL_ONBOARDING_DEFAULT_TRAINEES_PER_TRAINER);

  //   // $max_trainers = ...;
  //   // $num_registrants = ...;
  //   // if ($num_registrants < $trainees_per_trainer * $max_trainers) {
  //   //   ++$num_registrants;
  //   //   // variable_set();
  //   //   // add registrant to the ctl_onboarding_registrant table
  //   // }
  //   // else {
  //   //   // show "time slot full" error message
  //   // }
  // }


  // if time slot db entry doesn't exist
  //   error out
  // else
  //   assert time slot is not full
  // increment the registrant count for the time slot entry
  // add registrant to the ctl_onboarding_registrant table

}


function _ctl_onboarding_form_submit_defer($form, &$form_state) {
  drupal_set_message(t("defer"));

  $form_state['rebuild'] = TRUE;
  $form_state['storage']['confirm_defer'] = TRUE;

  // drupal_set_message(var_export($form_state['clicked_button'], TRUE));
}


function _ctl_onboarding_form_submit_decline($form, &$form_state) {
  drupal_set_message(t("decline"));

  // drupal_set_message(var_export($form_state['clicked_button'], TRUE));

  // $form_state['rebuild'] = TRUE;

  // if ($form_state['clicked_button']['#value'] == 'Delete' ) {
  $form_state['rebuild'] = TRUE;
  $form_state['storage']['confirm_decline'] = TRUE;
  // }
  // else if ( isset( $form_state['values']['confirm'] ) && $form_state['values']['confirm'] ) {
  //   $msg = t( "The object has been deleted." );
  //   drupal_set_message( $msg );
  // }
  // else if ($form_state['clicked_button']['#value'] == 'Submit' ) {
  //   $msg = t( "The object information has been updated." );
  //   drupal_set_message( $msg );
  // }

}
