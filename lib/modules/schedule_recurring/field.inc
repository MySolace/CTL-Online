<?php


function schedule_recurring_field_info() {
  return array(
    'schedule_recurring_shift' => array(
      'label' => t('Shift'),
      'description' => t('A weekly shift'),
      'settings' => array(
        'allowed_values' => array(),
        'allowed_values_function' => '',
      ),
      'default_widget' => 'schedule_recurring_shift',
      'default_formatter' => 'schedule_recurring_shift',
    ),
  );
}

function schedule_recurring_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  foreach ($items as $delta => $item) {
    if ($item['start'] > -1 && (intval($item['start']) >= intval($item['end']))) {
      $errors[$field['field_name']][$langcode][$delta][] = array(
        'error' => 'schedule_recurring_end_time_invalid',
        'message' => t('%name: The end time of a shift cannot be before or exactly the same as the start time.', array('%name' => $instance['label'])),
      );
    }
  }
}

function schedule_recurring_field_widget_error($element, $error, $form, &$form_state) {
  switch ($error['error']) {
    case 'schedule_recurring_end_time_invalid':
      form_error($element, $error['message']);
      break;
  }
}

function schedule_recurring_field_is_empty($item, $field) {
  switch ($field['type']) {
    case 'schedule_recurring_shift':
      return $item['day'] == -1 || $item['start'] == -1 || $item['end'] == -1;
  }
}

function schedule_recurring_field_widget_info() {
  return array(
    'schedule_recurring_shift' => array(
      'label' => t('Shift'),
      'field types' => array('schedule_recurring_shift'),
    ),
  );
}

function schedule_recurring_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  switch ($instance['widget']['type']) {
    case 'schedule_recurring_shift':
      $settings = $form_state['field'][$instance['field_name']][$langcode]['field']['settings'];

      $fields = array(
        'day' => array(
          'label' => t('Day'),
          'options' => _schedule_recurring_days(),
          'prefix' => t('On'),
        ),
        'start' => array(
          'label' => t('Start Time'),
          'options' => _schedule_recurring_times(),
          'prefix' =>  t('from'),
        ),
        'end' => array(
          'label' => t('End Time'),
          'options' => _schedule_recurring_times(TRUE),
          'prefix' => t('until'),
        ),
      );

      foreach ($fields as $key => $opts) {
        $opts['options'] = array(-1 => '- ' . $opts['label'] . ' -') + $opts['options'];

        $element[$key] = array(
          '#type'          => 'select',
          '#options'       => $opts['options'],
          '#title'         => $opts['label'],
          '#default_value' => isset($items[$delta][$key]) ? $items[$delta][$key] : -1,
          '#attached'      => array(
            'css' => array(drupal_get_path('module', 'schedule_recurring') . '/css/schedule_recurring_fields.css'),
            'js'  => array(),
          ),
          '#prefix'        => (isset($opts['prefix']) ? $opts['prefix'] : '') . ' <div class="schedule-recurring-shift-field">',
          '#suffix'        => '</div> ' . (isset($opts['suffix']) ? $opts['suffix'] : ''),
        );
      }
      break;
  }

  return $element;
}

function schedule_recurring_multiple_field_remove_button_field_widgets_alter(&$field_widgets) {
  $field_widgets[] = 'schedule_recurring_shift';
}

function schedule_recurring_field_formatter_info() {
  return array(
    'schedule_recurring_shift' => array(
      'label' => t('Default'),
      'field types' => array('schedule_recurring_shift'),
    ),
    'schedule_recurring_shift_raw' => array(
      'label' => t('Raw'),
      'field types' => array('schedule_recurring_shift'),
    ),
  );
}

function schedule_recurring_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  switch ($instance['widget']['type']) {
    case 'schedule_recurring_shift':
      usort($items, function ($a, $b) {
        if ($a['day'] == $b['day']) {
          return $a['start'] - $b['start'];
        } else {
          return $a['day'] - $b['day'];
        }
      });
      break;
  }
}

function schedule_recurring_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {
    case 'schedule_recurring_shift':
      $days = _schedule_recurring_days();
      $start_times = _schedule_recurring_times();
      $end_times = _schedule_recurring_times(TRUE);

      $headers = array(
        t('Day'),
        t('Time'),
      );

      $rows = array();
      foreach ($items as $delta => $item) {
        $rows[] = array(
          $days[$item['day']],
          $start_times[$item['start']] . ' - '. $end_times[$item['end']],
        );
      }

      $element[0] = array(
        '#theme' => 'table',
        '#header' => $headers,
        '#rows' => $rows,
      );

      break;
    case 'schedule_recurring_shift_raw':
      foreach ($items as $delta => $item) {
        $element[] = array(
          '#markup' => $item['day'] . ' ' . $item['start'] . '-' . $item['end'],
        );
      }

      break;
  }

  return $element;
}


