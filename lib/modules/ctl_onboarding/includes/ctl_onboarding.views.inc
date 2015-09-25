<?php

/**
 * Implements hook_views_data().
 */
// TODO
function ctl_onboarding_views_data() {
  $data['ctl_onboarding_registrant'] = array(
    'table' => array(
      'group' => t('CTL Onboarding Registrant'),

      'base' => array(
        'field' => 'uid',
        'title' => t('CTL Onboarding Registrant'),
        'help'  => t('This table conatins registrants for training.'),
      ),

      // This table references the user table. The declaration below creates an
      // 'implicit' relationship to the user table so that when 'user' is the base
      // table the fields are automatically available.
      'join' => array(
        'users' => array(
          'left_field' => 'uid',
          'field'      => 'uid',
        ),
      ),
    ),
    'uid' => array(
      'title' => t('User ID'),
      'help' => t('The user ID for the registrant.'),
      'relationship' => array(
        'base'       => 'users',
        'base field' => 'name',
        'handler'    => 'views_handler_relationship',
        'label'      => t('Referring relationship to user'),
        'title'      => t('CTL Onboarding Registrant'),
        // 'help'       => t('More information on this relationship'),
      ),
    ),
    'cohort_id' => array(
      'title' => t('Cohort number'),
      'help'  => t('The cohort ID.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'slot_code' => array(
      'title' => t('Slot code'),
      'help'  => t('The time slot code.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
    'status' => array(
      'title' => t('Status'),
      'help'  => t('The acceptance status of the registrant.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),
  );
  return $data;
}


/**
 * Implements hook_views_data_alter().
 */
function ctl_onboarding_views_data_alter(&$data) {
  $data['users']['ctl_onboarding_registrant'] = array(
    'group' => t('CTL Onboarding Registrant'),
    'title' => t('CTL Onboarding Registrant'),
    'help'  => t('The CTL Onboarding Registrant that is associated with the user.'),
    'relationship' => array(
      'handler'            => 'views_handler_relationship',
      'label'              => t('CTL Onboarding Registrant'),
      'base'               => 'ctl_onboarding_registrant',
      'base field'         => 'uid',
      'relationship field' => 'uid',
    ),
  );
}
