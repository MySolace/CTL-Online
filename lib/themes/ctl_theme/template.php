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

    drupal_add_js($adminimal_path . '/scripts/scroll-left.js');

}

function ctl_theme_date_combo($variables) {
    return theme('form_element', $variables);
}

