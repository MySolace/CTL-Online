<?php

/**
 * Implements hook_filter_info().
 */
function ctl_training_filter_info() {
    $filters = array();

    $filters['markdown'] = array(
        'title' => t('Markdown'),
        'description' => t('Parsed as markdown. Do not enable any other filters.'),
        'process callback' => '_ctl_training_preprocess_markdown'
    );

    return $filters;
}

function _ctl_training_preprocess_markdown($text, $format) {
    return '<div class="parse-md">' . $text . '</div>';
}

/**
 * Implements hook_node_view().
 */
function _ctl_training_filter_node_view($node) {
    if (isset($node->content)
        && isset($node->content['body'])
        && isset($node->content['body']['#items'])
        && $node->content['body']['#items'][0]['format'] == 'markdown'
    ) {

    }
}
