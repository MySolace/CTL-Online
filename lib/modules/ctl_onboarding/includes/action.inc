<?php

//
// TODO later?
//

// /**
//  * Implements hook_user_operations().
//  */
// function ctl_onboarding_user_operations() {
//   $operations = array(
//     'Assign trainer' => array(
//       'label' => t('Do something to user(s)'),
//       'callback' => 'ctl_onboarding_operation_callback_1',
//     ),
//   );

//   return $operations;
// }


// /**
//  * The callback function.
//  * @param array $accounts (This is a list of uids to affect)
//  */
// function ctl_onboarding_operation_callback_1($accounts) {
//   foreach ($accounts as $uid) {
//     // Do something.
//   }
// }


// /**
//  * Implements hook_action_info().
//  */
// function ctl_onboarding_action_info() {
//   $actions = array(
//     '_ctl_onboarding_bulk_action' => array(
//       'type'         => 'user',
//       'label'        => t('Do something else to user(s)'),
//       'configurable' => FALSE,
//       'triggers'     => array('any'),
//     ),
//   );
//   return $actions;
// }


// function _ctl_onboarding_bulk_action(&$entity, $context = array()) {
//   dsm($entity);
//   dsm($context);
// }
