<?php

/**
 * Implements hook_views_data().
 */
// TODO
function ctl_onboarding_views_data() {
  $data['ctl_onboarding_registrant']['table'] = array(
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
      'user' => array(
        'field'      => 'uid',
        'left_field' => 'uid',
      ),
    ),
  );

  // Next, describe each of the individual fields in this table to Views. This
  // is done by describing $data['ctl_onboarding_registrant']['FIELD_NAME']. This part of
  // the array may then have further entries:
  //   - title: The label for the table field, as presented in Views.
  //   - help: The description text for the table field.
  //   - relationship: A description of any relationship handler for the table
  //     field.
  //   - field: A description of any field handler for the table field.
  //   - sort: A description of any sort handler for the table field.
  //   - filter: A description of any filter handler for the table field.
  //   - argument: A description of any argument handler for the table field.
  //   - area: A description of any handler for adding content to header,
  //     footer or as no result behaviour.

  $data['ctl_onboarding_registrant']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The user ID for the registrant.'),
    'relationship' => array(
      'base'       => 'user',
      'base_field' => 'name',
      'handler'    => 'views_handler_relationship',
      'label'      => t('Referring relationship to user'),
      'title'      => t('CTL Onboarding Registrant'),
      // 'help'       => t('More information on this relationship'),
    ),
  );

  $data['ctl_onboarding_registrant']['cohort_id'] = array(
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
  );

  $data['ctl_onboarding_registrant']['slot_code'] = array(
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
  );

  $data['ctl_onboarding_registrant']['status'] = array(
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
  );

  return $data;
}


/**
 * Implements hook_views_data_alter().
 */
function ctl_onboarding_views_data_alter(&$data) {
  $data['user']['ctl_onboarding_registrant'] = array(
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
