<?php
/**
 * @file
 * Contains page callbacks and related functions of TCPDF module.
 */


/**
 * Page callback for downloading example pdf files.
 */
function _ctl_certificate_generate($uid) {
  $pdf = _ctl_certificate_pdf();
  if (!$pdf) {
    return t('An error occured.');
  }

  // // Tell the browser that this is not an HTML file to show,
  // // but a PDF file to download.
  header('Content-Type: application/pdf');
  header('Content-Length: ' . strlen($pdf));
  // header('Content-Disposition: attachment; filename="ctl-certificate.pdf"');

  print $pdf;

  return NULL;
}


/**
 * Generates a PDF file using the TCPDF module.
 *
 * @return string
 *   Binary string of the generated pdf.
 */
function _ctl_certificate_pdf() {
  // Get the content we want to convert into pdf.
  $html = theme('ctl_certificate', array(
    'graduate_name' => 'graduate name',
    'certification_date' => 'date of certification',
  ));

  // $class = array(
  //   'class'    => 'TCPDFDrupal',
  //   'filetype' => 'inc',
  //   'filename' => 'tcpdf_import.class',
  //   'module'   => 'ctl_certificate',
  // );
  // $tcpdf = tcpdf_get_instance(array(), $class);

  $tcpdf = tcpdf_get_instance();
  $tcpdf->DrupalInitialize();
  // $tcpdf->DrupalInitialize(array(
  //   'header' => array(
  //     'callback' => array(
  //       // 'function' => 'ctl_certificate_default_header',
  //       // You can pass extra data to your callback.
  //       'context' => array(
  //         'welcome_message' => 'Hello, context array!',
  //       ),
  //     ),
  //   ),
  //   'footer' => array(
  //     'html' => 'This is a test!! <em>Bottom of the page</em>',
  //   ),
  // ));

  // $tcpdf->DrupalInitialize(array(
  //   'header' => array(
  //     'callback' => array(
  //       'function' => '_ctl_certificate_default_header',
  //       'context' => array(
  //         'certificate_image'  => theme('image', array('path' => drupal_get_path('module', 'ctl_certificate') . '/images/ctl-certificate-template.png')),
  //       ),
  //     ),
  //   ),
  // ));

  // Insert the content. Note that DrupalInitialize automaticly adds the first
  // page to the pdf document.
  $tcpdf->writeHTML($html);

  return $tcpdf->Output('', 'S');
}


/**
 * Callback for generating the header. This function acts like if it overridded
 *   the Header() function of tcpdf class except the tcpdf instance is not $this
 *   but a parameter.
 *
 * @param type $tcpdf TCPDFDrupal instance. It can be used as $this in the
 *   Header() function of a siebling of TCPDF.
 */
function _ctl_certificate_default_header(&$tcpdf, $context) {
  // get the current page break margin
  $bMargin = $tcpdf->getBreakMargin();
  // get current auto-page-break mode
  $auto_page_break = $tcpdf->AutoPageBreak;
  // disable auto-page-break
  $tcpdf->SetAutoPageBreak(false, 0);
  // set bacground image
  $img_file = $context['certificate_image'];

  watchdog('ctl_certificate', $context['certificate_image']);

  $tcpdf->Image($img_file, 0, 0, 210, 297, '', '', '', false, 300, '', false, false, 0);
  // restore auto-page-break status
  $tcpdf->SetAutoPageBreak($auto_page_break, $bMargin);
  // set the starting point for the page content
  $tcpdf->setPageMark();

  // // $args contains passed variable...
  // $theme_settings = variable_get('theme_' . variable_get('theme_default', '') . '_settings', '');
  // if (isset($theme_settings['logo_path']) && (file_exists($theme_settings['logo_path']))) {
  //   $tcpdf->Image(drupal_realpath($theme_settings['logo_path']), 10, 10, 30, 0, '', variable_get('site_url', ''), '', TRUE, 150, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
  // }
  // $tcpdf->Write(0, $context['welcome_message'], '', 0, 'J', true, 0, false, true, 0);
}
