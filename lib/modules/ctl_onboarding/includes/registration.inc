<?php

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding') . '/includes/slot.inc';


/**
 * Implements hook_form().
 */
function ctl_onboarding_form($form, &$form_state) {
  if (isset($form_state['storage'])) {
    $storage = $form_state['storage'];
    if (isset($storage['confirm_defer']) && $storage['confirm_defer']) {
      $question    = 'Are you sure you want to defer?';
      $path        = 'registration';
      $description = 'If you defer you can come back and sign up for training at a later date.';
      $yes         = 'Yes, I wish to defer';
      $no          = 'No, I do not wish to defer';
      $name        = 'defer';
      return confirm_form($form, $question, $path, $description, $yes, $no, $name);
    }
    if (isset($storage['confirm_decline']) && $storage['confirm_decline']) {
      $question    = 'Are you sure you want to decline?';
      $path        = 'registration';
      $description = 'If you decline you will not be able to sign up for training later.';
      $yes         = 'Yes, I wish to decline';
      $no          = 'No, I do not wish to decline';
      $name        = 'decline';
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

  // TODO
  // - add visual indicators for statuses

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

  $year  = $registration_start_date['year'];
  $month = $registration_start_date['month'];
  $day   = $registration_start_date['day'];
  $registration_start_date = format_date(strtotime("$year-$month-$day"), 'custom', 'F j, Y');

  $year  = $registration_finish_date['year'];
  $month = $registration_finish_date['month'];
  $day   = $registration_finish_date['day'];
  $registration_finish_date = format_date(strtotime("$year-$month-$day"), 'custom', 'F j, Y');

  $form['instructions'] = array(
    '#type'   => 'markup',
    '#markup' => "<p>Register for a training session.</p>",
  );
  $form['policies'] = array(
    '#type'   => 'markup',
    '#markup' => "<p>Policies: Registration occurs between $registration_start_date and $registration_finish_date. After that, we are only able to accomodate 2 schedule changes.  Training will occur for 6 weeks.</p>",
  );
  $form['training_slot'] = array(
    '#type'    => 'radios',
    '#options' => variable_get('ctl_onboarding_slot_codes'),
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
  $values    = $form_state['values'];
  $slot_code = $values['training_slot'];

  global $user;

  _ctl_onboarding_slot_register($slot_code, $user->uid);
}


function _ctl_onboarding_form_submit_defer($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $form_state['storage']['confirm_defer'] = TRUE;

  // drupal_set_message(var_export($form_state['clicked_button'], TRUE));
}


function _ctl_onboarding_form_submit_decline($form, &$form_state) {
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
