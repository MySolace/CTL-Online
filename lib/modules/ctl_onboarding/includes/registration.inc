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
  if (isset($form_state['storage']) && isset($form_state['storage']['confirm_defer']) && $form_state['storage']['confirm_defer']) {
    $question    = 'Are you sure?';
    $path        = 'training-session-registration';
    $description = 'Defer !!!';
    $yes         = 'Continue';
    $no          = 'Start again';
    $name        = 'qqqqqqqqqqqqqq';
    return confirm_form($form, $question, $path, $description, $yes, $no, $name);
  }

  if (isset($form_state['storage']) && isset($form_state['storage']['confirm_decline']) && $form_state['storage']['confirm_decline']) {
    $question    = 'Are you sure?';
    $path        = 'training-session-registration';
    $description = 's;ghj;dlghjldg;jh;lfkdjg';
    $yes         = 'Continue';
    $no          = 'Start again';
    $name        = 'gdhdfghfg';
    return confirm_form($form, $question, $path, $description, $yes, $no, $name);
  }

  $form['instructions'] = array(
    '#type'   => 'markup',
    '#markup' => '<p>Choose a training session to register for.</p>',
  );


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


  $form['test'] = array(
    '#type'   => 'markup',
    '#markup' => '<input type="text" name="test" value="test" />',
  );


  $training_session_slots = array(
    array(
      NULL,
      'tu0810' => '8am-10am',
      'w0810'  => '8am-10am',
      'th0810' => '8am-10am',
      NULL,
      'sa0810' => '8am-10am',
      'su0810' => '8am-10am',
    ),
    array(
      NULL,
      'tu1012' => '10am-12pm',
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
    ),
    array(
      'm0608'  => '6pm-8pm',
      'tu0608' => '6pm-8pm',
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
    ),
    array(
      'm0910'  => '9pm-10pm',
      NULL,
      'w0910'  => '9pm-10pm',
      'th0910' => '9pm-10pm',
      NULL,
      'sa0910' => '9pm-10pm',
      'su0910' => '9pm-10pm',
    ),
    array(
      NULL,
      NULL,
      'w1012'  => '10pm-12am',
      NULL,
      NULL,
      NULL,
      'su1012' => '10pm-12am',
    ),
  );

  //
  // Populate the table.
  //
  $slots_rows = array('#tree' => TRUE);
  for ($i = 0, $l = count($training_session_slots); $i < $l; ++$i) {
    $slots_row = array();
    $slots = $training_session_slots[$i];
    foreach ($slots as $k => $v) {
      if ($v) {
        $slots_row[$k] = array(
          '#type'  => 'radio',
          '#title' => t($v),
          '#name'  => 'training_session_slot',
          '#value' => $k,
        );
      }
      else {
        $slots_row[$k] = '';
      }
    }
    $slots_rows['r' . $i] = $slots_row;
  }

  $form['training_session_table'] = array(
    '#theme' => 'ctl_onboarding_form_table',
    // '#default_value' => $defaults,
    '#header' => array(
      t('Monday'),
      t('Tuesday'),
      t('Wednesday'),
      t('Thursday'),
      t('Friday'),
      t('Saturday'),
      t('Sunday'),
    ),
    '#tree' => TRUE,
    'rows' => $slots_rows,
  );

  // $form['training_session_radios'] = array(
  //   '#type' => 'radios',
  //   '#options' => array(
  //     'm0608'  => t('Monday: 6:00pm-8:00pm'),
  //     'm0910'  => t('Monday: 9:00pm-10:00pm'),
  //     'tu0810' => t('Tuesday: 8:00am-10:00am'),
  //     'tu1012' => t('Tuesday: 10:00am-12:00pm'),
  //     'tu0608' => t('Tuesday: 6:00pm-8:00pm'),
  //     'w0810'  => t('Wednesday: 8:00am-10:00am'),
  //     'w0910'  => t('Wednesday: 9:00pm-10:00pm'),
  //     'w1012'  => t('Wednesday: 10:00pm-12:00am'),
  //     'th0810' => t('Thursday: 8:00am-10:00am'),
  //     'th0910' => t('Thursday: 9:00pm-10:00pm'),
  //     'sa0810' => t('Saturday: 8:00am-10:00am'),
  //     'sa0910' => t('Saturday: 9:00pm-10:00pm'),
  //     'su0810' => t('Sunday: 8:00am-10:00am'),
  //     'su0910' => t('Sunday: 9:00pm-10:00pm'),
  //     'su1012' => t('Sunday: 10:00pm-12:00am'),
  //   ),
  // );

  $defaults = array();

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
 * Creates our custom table.
 *
 * Based on:
 * http://e9p.net/theming-drupal-7-form-elements-table
 */
function theme_ctl_onboarding_form_table(&$variables) {
  $form   = $variables['form'];
  $rows   = $form['rows'];
  $header = $form['#header'];

  $content = array(
    '#theme'  => 'table',
    '#header' => $header,
    '#rows'   => array(),
  );

  foreach (element_children($rows) as $row_index) {
    $row = array();
    foreach (element_children($rows[$row_index]) as $col_index) {
      $row[] = drupal_render($rows[$row_index][$col_index]);
    }
    $content['#rows'][] = $row;
  }

  return drupal_render($content);
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
  drupal_set_message(t("register"));

  $form_values = $form_state['values'];
  $slot = $form_values['training_session_slot'];

  drupal_set_message($slot);

  drupal_set_message(var_export($form_values, TRUE));

  // $form_values = $form_state['values'];
  // $uid = $form_values['uid'];

  // // Upsert trainee info.
  // db_merge('ctl_graduation_progress')
  //   ->key(array('uid' => $uid))
  //   ->fields(array(
  //     'graduation_timestamp' => time(),
  //   ))
  //   ->execute();

  // // The trainee now becomes a graduate.

  // $cur_role = 'Trainee';
  // $role = user_role_load_by_name($cur_role);
  // user_multiple_role_edit(array($uid), 'remove_role', $role->rid);

  // $next_roles = array('Graduate', 'Crisis Counselor I');
  // foreach ($next_roles as $next_role) {
  //   $role = user_role_load_by_name($next_role);
  //   user_multiple_role_edit(array($uid), 'add_role', $role->rid);
  // }
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
