<?php

function ctl_admin_preprocess_html(&$vars) {
    $adminimal_path = drupal_get_path('theme', 'ctl_admin');

    drupal_add_css($adminimal_path . '/css/ctl.css',
        array(
            'group' => CSS_THEME,
            'media' => 'all',
            'weight' => 5
        )
    );

    drupal_add_js($adminimal_path . '/scripts/scroll-left.js');

    $path = drupal_get_path_alias();
    $aliases = explode('/', $path);

    foreach($aliases as $alias) {
        $vars['classes_array'][] = drupal_clean_css_identifier($alias);
    }

}

function ctl_admin_date_combo($variables) {
    return theme('form_element', $variables);
}
