<?php
function ctl_theme_preprocess_html(&$vars) {
    $adminimal_path = drupal_get_path('theme', 'ctl_theme');

    drupal_add_css($adminimal_path . '/css/ctl.css',
        array(
            'group' => CSS_THEME,
            'media' => 'all',
            'weight' => 5
        )
    );

    //drupal_add_js($adminimal_path . '/scripts/scroll-left.js');
    drupal_add_js($adminimal_path . '/js/label.js');
}

function ctl_theme_date_combo($variables) {
    return theme('form_element', $variables);
}

function ctl_theme_menu_local_tasks(&$variables) {
    $output = '';

    if (!empty($variables['primary'])) {
        $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
        $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs">';
        $variables['primary']['#suffix'] = '</ul>';
        $output .= drupal_render($variables['primary']);
    }

    if (!empty($variables['secondary'])) {
        $output .= drupal_render($varialbes['secondary']);

    }

    return $output;
}