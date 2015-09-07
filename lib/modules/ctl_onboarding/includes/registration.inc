<?php

/**
 * Implements hook_form().
 */
function ctl_onboarding_form($form, &$form_state) {
  if (isset($form_state['storage'])) {
    $storage = $form_state['storage'];
    if (isset($storage['confirm_defer']) && $storage['confirm_defer']) {
      $question    = 'Are you sure?';
      $path        = 'training-session-registration';
      $description = 'Defer !!!';
      $yes         = 'Continue';
      $no          = 'Start again';
      $name        = 'qqqqqqqqqqqqqq';
      return confirm_form($form, $question, $path, $description, $yes, $no, $name);
    }
    if (isset($storage['confirm_decline']) && $storage['confirm_decline']) {
      $question    = 'Are you sure?';
      $path        = 'training-session-registration';
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

  $form['instructions'] = array(
    '#type'   => 'markup',
    '#markup' => '<p>Choose a training session to register for.</p>',
  );

  $form['policies'] = array(
    '#type'   => 'markup',
    '#markup' => '<p>Policies: Registration occurs between [X] date and [X] date. After that, we are only able to accomodate 2 schedule changes.  Training will occur for 6 weeks.</p>',
  );

  $form['training_slot'] = array(
    '#type'    => 'radios',
    '#options' => variable_get('ctl_onboarding_slots'),
    '#theme'   => array('ctl_onboarding_table'),
  );

  // $form['uid'] = array(
  //   '#type'  => 'hidden',
  //   '#value' => $uid,
  // );

  $form['register'] = array(
    '#type'     => 'submit',
    '#value'    => 'Register',
    '#validate' => array('_ctl_onboarding_form_validate_register'),
    '#submit'   => array('_ctl_onboarding_form_submit_register'),
  );

  $form['defer'] = array(
    '#type'     => 'submit',
    '#value'    => 'Defer',
    '#validate' => array('_ctl_onboarding_form_validate_defer'),
    '#submit'   => array('_ctl_onboarding_form_submit_defer'),
  );

  $form['decline'] = array(
    '#type'     => 'submit',
    '#value'    => 'Decline',
    '#validate' => array('_ctl_onboarding_form_validate_decline'),
    '#submit'   => array('_ctl_onboarding_form_submit_decline'),
  );

  return $form;
}


/**
 *
 */
function _ctl_onboarding_form_validate_register($form, &$form_state) {
  // drupal_set_message(t("hi"));

  // $form_values = $form_state['values'];
  // $unmet_requirements = array(_ctl_graduation_courses_completed($form_values['uid']))
  //                     + $form_values['additional_requirements'];
  // $unmet_requirements = array_filter($unmet_requirements, function ($v) { return empty($v); });
  // if (!empty($unmet_requirements)) {
  //   form_set_error('additional_requirements', t('The trainee must pass all the requirements.'));
  // }
}


/**
 *
 */
function _ctl_onboarding_form_submit_register($form, &$form_state) {
  // drupal_set_message(t("register"));

  $form_values = $form_state['values'];
  // $slot = $form_values['training_slot'];

  // drupal_set_message($slot);

  drupal_set_message(var_export($form_values, TRUE));
}


function _ctl_onboarding_form_validate_defer($form, &$form_state) {
  // drupal_set_message(t("hi"));
}


function _ctl_onboarding_form_submit_defer($form, &$form_state) {
  drupal_set_message(t("defer"));

  $form_state['rebuild'] = TRUE;
  $form_state['storage']['confirm_defer'] = TRUE;

  // drupal_set_message(var_export($form_state['clicked_button'], TRUE));
}


function _ctl_onboarding_form_validate_decline($form, &$form_state) {
  // drupal_set_message(t("hi"));
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
