<?php

/**
 * Shows the training session registration page.
 */
function _ctl_onboarding_registration_page() {
  $content['registration'] = drupal_get_form('ctl_onboarding_form');
  return $content;
}


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


  // TODO:
  // - Temp code!  Clean this up !
  // - Fixgure out where #46c7ff comes from.
  $form['styles'] = array(
    '#type' => 'markup',
    '#markup' =>
      '<style>' .
        'table td {' .
          'padding: 0' .
        '}' .
        '.form-type-radio label {' .
          'padding: 10px !important;' .
        '}' .
        '.form-type-radio label:hover {' .
          'background-color: #0FF;' .
        '}' .
        '.form-type-radio label:before {' .
          'display: none;' .
        '}' .
        'input[type=radio]:checked+.radio:before,' .
        '.form-type-radio input[type=radio]:checked+label {' .
          'background-color: #46c7ff;' .
          'color: #FFF;' .
        '}' .
      '</style>',
  );

  // $form['training_session_table'] = array(
  //   // '#type' => 'radios',
  //   '#theme' => 'ctl_onboarding_table',
  //   // '#theme' => 'ctl_onboarding_table_radios',
  //   // '#default_value' => $defaults,
  //   '#header' => array(
  //     t('Monday'),
  //     t('Tuesday'),
  //     t('Wednesday'),
  //     t('Thursday'),
  //     t('Friday'),
  //     t('Saturday'),
  //     t('Sunday'),
  //   ),
  //   '#tree' => TRUE,
  //   'rows' => $slots_rows,
  //   // '#options' => $slots_rows,
  //   // '#return_value' => 'fghyudytjtyj',
  // );


  // $options = array(
  //   1800 => 2,
  //   2100 => 1,
  // );

  // $form['fourth_down'] = array(
  //   '#type'    => 'radios',
  //   '#options' => $options,
  // );

  // $form['test'] = array(
  //   '#type'    => 'ctl_onboarding_table',
  //   '#options' => $options,
  // );


  // $form['optional_field'] = array(
  //   '#type' => 'gitbucket',
  //   '#title' => t('Your least favorite repository'),
  //   '#default_value' => variable_get('optional_field', array()),
  // );

  // // All sessions are 4 hours.  Start times are in military time.
  // $training_session_slots = array(
  //   'monday'    => array(1800, 2100),
  //   'tuesday'   => array(800, 1000, 1800),
  //   'wednesday' => array(800, 900, 2200),
  //   'thursday'  => array(800, 2100),
  //   'friday'    => array(),
  //   'saturday'  => array(800, 2100),
  //   'sunday'    => array(800, 2100, 2200),
  // );

  // $training_session_slots = array(
  //   'monday' => array(
  //     1800 => 2,
  //     2100 => 1,
  //   ),
  //   'tuesday' => array(
  //     800  => 2,
  //     1000 => 2,
  //     1800 => 2,
  //   ),
  //   'wednesday' => array(
  //     800  => 2,
  //     900  => 1,
  //     2200 => 2,
  //   ),
  //   'thursday' => array(
  //     800  => 2,
  //     2100 => 2,
  //   ),
  //   'friday' => array(
  //   ),
  //   'saturday' => array(
  //     800  => 2,
  //     2100 => 1,
  //   ),
  //   'sunday' => array(
  //     800  => 2,
  //     2100 => 1,
  //     2200 => 2,
  //   ),
  // );

  $training_session_slots = array(
    'm-1800'  => '6pm-10pm',
    'm-2100'  => '9pm-1am',
    'tu-800'  => '8am-12pm',
    'tu-1000' => '10am-2pm',
    'tu-1800' => '6pm-10pm',
    'w-800'   => '8am-12pm',
    'w-900'   => '9am-1pm',
    'w-2200'  => '10pm-2am',
    'th-800'  => '8am-12pm',
    'th-2100' => '9pm-1am',
    'sa-800'  => '8am-12pm',
    'sa-2100' => '9pm-1am',
    'su-800'  => '8am-12pm',
    'su-2100' => '9pm-1am',
    'su-2200' => '10pm-2am',
  );

  $form['instructions'] = array(
    '#type'   => 'markup',
    '#markup' => '<p>Choose a training session to register for.</p>',
  );

  $form['training_session_slot'] = array(
    '#type'    => 'radios',
    '#options' => $training_session_slots,
    '#theme'   => array('ctl_onboarding_radios'),
    '#header' => array(
      t('Monday'),
      t('Tuesday'),
      t('Wednesday'),
      t('Thursday'),
      t('Friday'),
      t('Saturday'),
      t('Sunday'),
    ),
  );

  // $form['style'] = array(
  //   '#type' => 'radios',
  //   '#title' => t('Select your style option'),
  //   '#options' => array(
  //     1 => 'a',
  //     2 => 'b',
  //     3 => 'c',
  //   ),
  //   '#default_value' => NULL,
  //   // '#required' => TRUE,
  //   '#after_build' => array(
  //     '_ctl_onboarding_options_after_build'
  //   )
  // );

  // $form['f1'][0]['a1'] = array(
  //   '#type' => 'radio', // Notice no s here; 'radio' not 'radios'
  //   '#name' => 'fruit', // This will ensure the radios are in the same group
  //   '#title' => 'apple',
  //   '#attributes' => array(
  //     'name' => 'fruit',
  //        'value' => 'apple', // I know this is bad but it's the only way I could get setting a value to work
  //        // 'class' => 'class_here' // This will add class_here to the default wrapper
  //    ),
  //   // '#prefix' => '<div class="some-class">',
  //   // '#suffix' => '</div>'
  // );

  // $form['f1'][2]['a2'] = array(
  //   '#type' => 'radio',
  //   '#name' => 'fruit', // Same name
  //   '#title' => 'orange',
  //   '#attributes' => array(
  //     'name' => 'fruit',
  //     'value' => 'orange', // Different value
  //     // 'class' => 'class_here'
  //   ),
  //   // '#prefix' => '<div class="some-class">',
  //   // '#suffix' => '</div>'
  // );

  // for ($i = 0; $i < 10; $i++){
  //   $form['c' . $i] = array(
  //     '#type' => 'radio',
  //     '#name' => 'c',
  //     // '#value' => $i,
  //     // '#return_value' => $i,
  //     '#title' => t('slot ' . $i),
  //     '#attributes' => array(
  //       'value' => 'c' . $i,
  //       // 'class' => 'class_here',
  //     ),
  //   );
  // }



  // $defaults = array();

  // Policies: Registration occurs between [X] date and [X] date. After that, we are only able to accomodate 2 schedule changes.
  // Training will occur for 6 weeks. Note that weeks 4 and 5 will be 4 hours long sessions for live observations.

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
  // $slot = $form_values['training_session_slot'];

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
