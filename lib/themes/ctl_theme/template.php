<?php
function ctl_theme_preprocess_html(&$vars) {
    $path = drupal_get_path('theme', 'ctl_theme');

    drupal_add_css($path . '/css/ctl.css',
        array(
            'group' => CSS_THEME,
            'media' => 'all',
            'weight' => 5
        )
    );

    //drupal_add_js($path . '/scripts/scroll-left.js');
    drupal_add_js('//ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js', 'external');
    drupal_add_js('//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.js', 'external');
    drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/marked/0.3.2/marked.min.js', 'external');
    drupal_add_js('var $jq = jQuery.noConflict(true);', 'inline');
    drupal_add_js($path . '/js/md.js');
    drupal_add_js($path . '/js/label.js');
    drupal_add_js($path . '/js/lesson.js');
    drupal_add_js($path . '/js/ctl.js');

    drupal_add_js(
      'Drupal.settings.tableHeaderOffset = "Drupal.ctlThemeTableHeaderOffset";',
      array(
        'type'  => 'inline',
        'scope' => 'footer',
      )
    );
}

function ctl_theme_date_combo($variables) {
    return theme('form_element', $variables);
}

function ctl_theme_menu_local_tasks(&$variables) {
    //var_dump($variables);
    $output = '';

    if (!empty($variables['primary'])) {
        foreach ($variables['primary'] as $key => $link) {
            if (strpos($link['#link']['path'], 'takecourse')) {
                unset($variables['primary'][$key]);
            }
        }

        if (count($variables['primary']) > 1) {
            $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
            $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs">';
            $variables['primary']['#suffix'] = '</ul>';
            $output .= drupal_render($variables['primary']);
        }
    }

    if (!empty($variables['secondary'])) {
        $output .= drupal_render($variables['secondary']);

    }

    return $output;
}

function ctl_theme_preprocess_block(&$variables) {
    if ($variables['block']->region == 'site_nav') {
        $variables['content'] = str_replace('class="menu"', 'class="nav navbar-nav"', $variables['content']);
        $variables['block']->subject = NULL;
    }
}

function ctl_theme_block_view_course_navigation_alter(&$data, $block) {
    $data['content'] = str_replace('id="course-nav"', 'id="course-nav" class="pagination"', $data['content']);
}
