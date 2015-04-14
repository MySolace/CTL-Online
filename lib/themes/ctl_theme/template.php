<?php

function ctl_theme_preprocess_html(&$vars) {
    $adminimal_path = drupal_get_path('theme', 'ctl_theme');

    drupal_set_message('status', 'status', true);
    drupal_set_message('warning', 'warning', true);
    drupal_set_message('error', 'error', true);

    drupal_add_css($adminimal_path . '/css/style.css',
        array(
            'group' => CSS_THEME,
            'media' => 'all',
            'weight' => 5
        )
    );

    drupal_add_js($adminimal_path . '/scripts/scroll-left.js');

    // Adding path chunks to body class

    $path = drupal_get_path_alias();
    $aliases = explode('/', $path);

    foreach($aliases as $alias) {
        $vars['classes_array'][] = drupal_clean_css_identifier($alias);
    }

}

function ctl_theme_css_alter(&$css) {
    unset($css[drupal_get_path('module','system').'/system.messages.css']);
}

function ctl_theme_date_combo($variables) {
    return theme('form_element', $variables);
}

function ctl_theme_breadcrumb($variables) {
  $breadcrumb = $variables ['breadcrumb'];

  $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
  $output .= '<div class="breadcrumb">&nbsp;';

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output .= implode(' » ', $breadcrumb);
  }

  $output .= '</div>';
  return $output;
}

function ctl_theme_form_element($variables) {
  $element = &$variables ['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element ['#markup']) && !empty($element ['#id'])) {
    $attributes ['id'] = $element ['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes ['class'] = array('form-item');
  $attributes ['class'][] = 'form-group';
  if (!empty($element ['#type'])) {
    $attributes ['class'][] = 'form-type-' . strtr($element ['#type'], '_', '-');
  }
  if (!empty($element ['#name'])) {
    $attributes ['class'][] = 'form-item-' . strtr($element ['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element ['#attributes']['disabled'])) {
    $attributes ['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element ['#title'])) {
    $element ['#title_display'] = 'none';
  }
  $prefix = isset($element ['#field_prefix']) ? '<span class="field-prefix">' . $element ['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element ['#field_suffix']) ? ' <span class="field-suffix">' . $element ['#field_suffix'] . '</span>' : '';

  switch ($element ['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element ['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element ['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element ['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element ['#description'])) {
    $output .= '<div class="description">' . $element ['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

function ctl_theme_form_element_label($variables) {
  $element = $variables ['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element ['#title']) || $element ['#title'] === '') && empty($element ['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element ['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element ['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element ['#title_display'] == 'after') {
    $attributes ['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element ['#title_display'] == 'invisible') {
    $attributes ['class'] = 'element-invisible';
  }

  if (!empty($element ['#id'])) {
    $attributes ['for'] = $element ['#id'];
  }

  // Adding input type to label, for checkbox and radio styling
  switch($element ['#type']) {
    case 'radio':
    case 'checkbox':
      $attributes ['class'] = array(
        $attributes ['class'],
        $element ['#type']
      );
      break;
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}

function ctl_theme_button($variables) {
  $element = $variables ['element'];
  $element ['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element ['#attributes']['class'][] = 'form-' . $element ['#button_type'];
  switch ($element ['#value']) {
    case 'Preview':
      $element ['#attributes']['class'][] = 'secondary';
      break;
    default:
      $element ['#attributes']['class'][] = 'primary';
      break;
  }
  if (!empty($element ['#attributes']['disabled'])) {
    $element ['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element ['#attributes']) . ' />';
}

function ctl_theme_status_messages($variables) {
  $display = $variables ['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"messages $type\">\n";
    if (!empty($status_heading [$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading [$type] . "</h2>\n";
    }
    switch ($type) {
      case 'error':
        $typeFa = 'fa-exclamation-triangle';
        break;
      case 'warning':
        $typeFa = 'fa-exclamation-triangle';
        break;
      case 'status':
      default:
        $typeFa = 'fa-info-circle';
        break;
    }
    $output .= '<div class="message-inner"><div class="message-icon fa '.$typeFa.'"></div><div class="message-content">';
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= reset($messages);
    }
    $output .= "</div></div><button id=\"message-btn-close\"><i class=\"fa fa-times fa-2x\"></i></button></div>\n";
  }
  return $output;
}
