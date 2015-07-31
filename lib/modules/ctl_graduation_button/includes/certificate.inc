<?php

/**
 * Trainee certificate page.
 */
function _ctl_graduation_button_certificate_page() {
  // $path = drupal_get_path('module', 'ctl_graduation_button');

  $content['stuff'] = array(
    '#type'   => 'markup',
    '#markup' => '<strong>certificate goes here</strong>',
  );

  return $content;
}


function _ctl_graduation_button_generate_certificate() {
  $tcpdf = tcpdf_get_instance();
  $tcpdf->DrupalInitialize(array(
    'footer' => array(
      'html' => 'This is the <em>footer</em>',
    ),
    'header' => array(
      'callback' => 'tcpdf_example_custom_pdf_header',
    ),
  ));
}


function tcpdf_example_default_header(&$tcpdf) {
  $theme_settings = variable_get('theme_' . variable_get('theme_default', '') . '_settings', '');
  $logo_path = isset($theme_settings['logo_path']) ? $theme_settings['logo_path'] : PDF_HEADER_LOGO;
  $tcpdf->Image(drupal_realpath($logo_path), 10, 10, 30, 0, '', variable_get('site_url', ''), '', TRUE, 150, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
}
