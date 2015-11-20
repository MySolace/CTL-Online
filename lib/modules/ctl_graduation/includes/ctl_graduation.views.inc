<?php

/**
 * Implements hook_views_data().
 */
// TODO
function ctl_graduation_views_data() {
  $default_field_info = array(
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['ctl_graduation_info'] = array(
    'table' => array(
      'group' => t('CTL Graduation Info'),
      'base' => array(
        'field' => 'uid',
        'title' => t('CTL Graduation Info'),
        'help'  => t('This table conatins graduation info for trainees.'),
      ),
      'join' => array(
        'users' => array(
          'left_field' => 'uid',
          'field'      => 'uid',
        ),
      ),
    ),
    'uid' => array(
      'title' => t('User ID'),
      'help'  => t('The user ID for the registrant.'),
      'relationship' => array(
        'base'       => 'users',
        'base field' => 'uid',
        'handler'    => 'views_handler_relationship',
        'label'      => t('Referring relationship to user'),
        'title'      => t('User ID'),
        'help'       => t('The relationship between registrants and users.'),
      ),
    ),
    'follows_protocol' => array_merge($default_field_info, array(
      'title' => t('Follows protocol'),
      'help'  => t('Follows risk assessment protocol'),
    )),
    'shows_progress' => array_merge($default_field_info, array(
      'title' => t('Shows progress'),
      'help'  => t("Considers + implements trainer's feedback (shows progress)"),
    )),
    'engaged' => array_merge($default_field_info, array(
      'title' => t('Engaged'),
      'help'  => t('Present, prepared, + engaged in ALL live training sessions/observations'),
    )),
    'participates' => array_merge($default_field_info, array(
      'title' => t('Participates'),
      'help'  => t('Participates in activities and acts in helpful and respectful ways.'),
    )),
    'honors_agreements' => array_merge($default_field_info, array(
      'title' => t('Honors agreements'),
      'help'  => t('Agrees to CTL TOS, maintains confidentiality, maintains appropriate boundaries'),
    )),
    'graduation_timestamp' => array_merge($default_field_info, array(
      'title' => t('Graduation timestamp'),
      'help'  => t('Agrees to CTL TOS, maintains confidentiality, maintains appropriate boundaries'),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    )),
  );
  return $data;
}
