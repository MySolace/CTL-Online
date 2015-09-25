<?php

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding') . '/includes/background-check.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding') . '/includes/helper.inc';
require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding') . '/includes/slot.inc';


/**
 * Implements hook_form().
 */
function ctl_onboarding_form($form, &$form_state) {
  $pages_text = variable_get('ctl_onboarding_pages_text');

  if (isset($form_state['storage'])) {
    $storage = $form_state['storage'];
    if (isset($storage['confirm_defer']) && $storage['confirm_defer']) {
      $question    = isset($pages_text['deferred-confirmation-title'])
                   ? token_replace($pages_text['deferred-confirmation-title'])
                   : 'Are you sure you want to defer?';
      $description = isset($pages_text['deferred-confirmation-message'])
                   ? token_replace($pages_text['deferred-confirmation-message'])
                   : 'If you defer you can come back and sign up for training at a later date.';
      $path        = 'registration';
      $yes         = 'Yes, I wish to defer';
      $no          = 'No, I do not wish to defer';
      $name        = 'defer';
      return confirm_form($form, $question, $path, $description, $yes, $no, $name);
    }
    if (isset($storage['confirm_decline']) && $storage['confirm_decline']) {
      // $question    = '';
      $question    = isset($pages_text['declined-confirmation-title'])
                   ? token_replace($pages_text['declined-confirmation-title'])
                   : 'Are you sure you want to decline?';
      $description = isset($pages_text['declined-confirmation-message'])
                   ? token_replace($pages_text['declined-confirmation-message'])
                   : 'If you decline you will not be able to sign up for training later.';
      $path        = 'registration';
      $yes         = 'Yes, I wish to decline';
      $no          = 'No, I do not wish to decline';
      $name        = 'decline';
      return confirm_form($form, $question, $path, $description, $yes, $no, $name);
    }
  }

  // TODO
  // - add visual indicators for statuses

  $registration_period = intval(variable_get('ctl_onboarding_registration_period', CTL_ONBOARDING_REGISTRATION_CLOSED));
  if ($registration_period === CTL_ONBOARDING_REGISTRATION_CLOSED) {
    $registration_closed_text = isset($pages_text['registration-closed']) ? token_replace($pages_text['registration-closed']) : '';
    $form['registration_closed'] = array(
      '#type'   => 'markup',
      '#markup' => $registration_closed_text,
    );
    return $form;
  }

  $registration_open_text = isset($pages_text['registration-open']) ? token_replace($pages_text['registration-open']) : '';

  $form['registration'] = array(
    '#type'   => 'markup',
    '#markup' => $registration_open_text,
  );

  $slot_trainers = variable_get('ctl_onboarding_slot_trainers');
  $slots = array();
  foreach ($slot_trainers as $slot_code => $v) {
    if ($v > 0) {
      $times               = explode('-', $slot_code);
      $start_hour_display  = _ctl_onboarding_format_hour_display($times[1]);
      $finish_hour_display = _ctl_onboarding_format_hour_display($times[1] + CTL_ONBOARDING_SESSION_DURATION);
      $slots[$slot_code]   = $start_hour_display . ' - ' . $finish_hour_display;
    }
  }
  $form['training_slot'] = array(
    '#type'    => 'radios',
    '#options' => $slots,
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

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'ctl_onboarding') . '/ctl_onboarding.css',
  );

  return $form;
}


// Used by the confirmation forms.
function ctl_onboarding_form_submit($form, &$form_state) {
  $values    = $form_state['values'];
  $deferring = $values['defer'];
  $declining = $values['decline'];

  if ($deferring) {
    global $user;
    // TODO
    // - remove all roles from the user before adding the defer role
    _ctl_onboarding_set_user_role($user->uid, CTL_ONBOARDING_ROLE_DEFERRED);
    // TODO
    // - send defer email
    drupal_set_message(t('You have confirmed your deferral.'));
  }
  elseif ($declining) {
    global $user;
    // TODO
    // - remove all roles from the user before adding the dropout role
    _ctl_onboarding_set_user_role($user->uid, CTL_ONBOARDING_ROLE_DECLINED);
    // TODO
    // - send decline email
    drupal_set_message(t('You have confirmed your decline.'));
  }
}


// TODO later ?
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


// TODO
function _ctl_onboarding_form_submit_defer($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $form_state['storage']['confirm_defer'] = TRUE;

  // drupal_set_message(var_export($form_state['clicked_button'], TRUE));
}


// TODO
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
