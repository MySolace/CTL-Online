<?php
/**
 * @file
 * Contains page callbacks and related functions.
 */


function _ctl_certificate_get_instance($params = array(), $class = array(), $config = array()) {
  $default_params = array(
    'orientation' => 'P',
    'unit' => 'mm',
    'format' => 'A4',
    'unicode' => TRUE,
    'encoding' => 'UTF-8',
    'diskcache' => FALSE,
    'pdfa' => FALSE,
  );

  $params = array_merge($default_params, $params);

  if (!isset($class['class'])) {
    $class = array(
      'class' => 'TCPDFDrupal',
      'filetype' => 'inc',
      'filename' =>  'tcpdf.class',
      'module' => 'tcpdf',
    );
  }

    if (!isset($config['filename'])) {
    $config = array(
      'filetype' => 'inc',
      'filename' =>  'tcpdf.config',
      'module' => 'tcpdf',
    );
  }

  if (!defined('K_TCPDF_EXTERNAL_CONFIG')) {
    define('K_TCPDF_EXTERNAL_CONFIG', TRUE);
  }

  module_load_include($config['filetype'], $config['module'], $config['filename']);

  $path = libraries_get_path('tcpdf');
  if (($path) && (file_exists($path . '/tcpdf_import.php'))) {
    require_once($path . '/tcpdf_import.php');
  }
  else {
    drupal_set_message(t('TCPDF library not found!'), 'error');
    return FALSE;
  }

  module_load_include($class['filetype'], $class['module'], $class['filename']);

  return new $class['class']($params['orientation'], $params['unit'], $params['format'], $params['unicode'], $params['encoding'], $params['diskcache'], $params['pdfa']);
}


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
  header('Content-Length: ' . strlen($pdf));
  header('Content-Type: application/pdf');
  // header('Content-Disposition: attachment; filename="ctl-certificate.pdf"');
  header("Content-Disposition: inline; filename=ctl-certificate.pdf");
  header('Expires: 0');
  header('Cache-Control: must-revalidate, post-check=0, pre-check=0');

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

  // $path = libraries_get_path('tcpdf');
  // if (($path) && (file_exists($path . '/tcpdf_import.php'))) {
  //   require_once($path . '/tcpdf_import.php');
  // }
  // else {
  //   drupal_set_message(t('TCPDF library not found!'), 'error');
  //   return FALSE;
  // }

  // $pdf = new TCPDF_IMPORT();
  // $pdf->importPDF(DRUPAL_ROOT . base_path() . drupal_get_path('module', 'ctl_certificate') . '/ctl-certificate-template.pdf');

  // $params = array(
  //   'orientation' => 'P',
  //   'unit'        => 'mm',
  //   'format'      => 'A4',
  //   'unicode'     => TRUE,
  //   'encoding'    => 'UTF-8',
  //   'diskcache'   => FALSE,
  //   'pdfa'        => FALSE,
  // );

  $params = array();

  $class = array(
    'class'    => 'TCPDFDrupal',
    'filetype' => 'inc',
    'filename' => 'includes/tcpdf.class',
    'module'   => 'ctl_certificate',
  );

  // $class = array(
  //   'class'    => 'TCPDFDrupal',
  //   'filetype' => 'inc',
  //   'filename' => 'tcpdf.class',
  //   'module'   => 'tcpdf',
  // );

  // $pdf = tcpdf_get_instance($params, $class);

  $pdf = _ctl_certificate_get_instance($params, $class);

  // $pdf = tcpdf_get_instance();

  // watchdog('ctl_certificate', var_export($pdf, TRUE));

  $pdf->SetPrintHeader(FALSE);
  $pdf->SetPrintFooter(FALSE);

  $pdf->importPDF(DRUPAL_ROOT . base_path() . drupal_get_path('module', 'ctl_certificate') . '/pdfs/ctl-certificate-template.pdf');
  // $pdf->importPDF(base_path() . drupal_get_path('module', 'ctl_certificate') . '/pdfs/ctl-certificate-template.pdf');
  // $pdf->importPDF(drupal_get_path('module', 'ctl_certificate') . '/pdfs/ctl-certificate-template.pdf');
  // $pdf->importPDF('pdfs/ctl-certificate-template.pdf');

  // // // $img_file  = base_path() . drupal_get_path('module', 'ctl_certificate') . '/images/ctl-certificate-template.png';
  // $img_file  = 'http://placebear.com/200/300';
  // $x         = 0;
  // $y         = 0;
  // $width     = 200;
  // $height    = 0;
  // $type      = '';
  // $link      = '';
  // $align     = '';
  // $resize    = TRUE;
  // $dpi       = 300;
  // $palign    = '';
  // $ismask    = FALSE;
  // $imgmask   = FALSE;
  // $border    = 0;
  // $fitbox    = FALSE;
  // $hidden    = FALSE;
  // $fitonpage = TRUE;
  // $alt       = FALSE;
  // $altimgs   = array();

  // $pdf->Image($img_file, $x, $y, $width, $height, $type, $link, $align,
  //   $resize, $dpi, $palign, $ismask, $imgmask, $border, $fitbox, $hidden,
  //   $fitonpage, $alt, $altimgs);

  $filename = '';
  $dest = 'S';
  return $pdf->Output($filename, $dest);










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
  // $tcpdf = tcpdf_get_instance(array(
  //   'orientation' => 'L',
  //   'unit'        => 'mm',
  //   'format'      => array(200, 300),
  //   'unicode'     => TRUE,
  //   'encoding'    => 'UTF-8',
  //   'diskcache'   => FALSE,
  //   'pdfa'        => FALSE,
  // ));

  // $tcpdf->SetPrintHeader(FALSE);
  // $tcpdf->SetPrintFooter(FALSE);

  $tcpdf->AddPage('L', array(200, 300));

  // // $img_file  = base_path() . drupal_get_path('module', 'ctl_certificate') . '/images/ctl-certificate-template.png';
  $img_file  = 'http://placebear.com/200/300';
  $x         = 0;
  $y         = 0;
  $width     = 200;
  $height    = 0;
  $type      = '';
  $link      = '';
  $align     = '';
  $resize    = TRUE;
  $dpi       = 300;
  $palign    = '';
  $ismask    = FALSE;
  $imgmask   = FALSE;
  $border    = 0;
  $fitbox    = FALSE;
  $hidden    = FALSE;
  $fitonpage = TRUE;
  $alt       = FALSE;
  $altimgs   = array();

  $tcpdf->Image($img_file, $x, $y, $width, $height, $type, $link, $align,
    $resize, $dpi, $palign, $ismask, $imgmask, $border, $fitbox, $hidden,
    $fitonpage, $alt, $altimgs);

  // $tcpdf->DrupalInitialize();

  // $options = array();

  //   $title = isset($options['title']) ? $options['title'] : variable_get('site_name', 'Drupal');
  //   $author = isset($options['author']) ? $options['author'] : variable_get('site_name', 'Drupal');
  //   $subject = isset($options['subject']) ? $options['subject'] : variable_get('site_name', 'Drupal');
  //   $keywords = isset($options['keywords']) ? $options['keywords'] : 'pdf, drupal';

  //   // set document information
  //   $tcpdf->SetCreator(PDF_CREATOR);
  //   $tcpdf->SetAuthor($author);
  //   $tcpdf->SetTitle($title);
  //   $tcpdf->SetSubject($subject);
  //   $tcpdf->SetKeywords($keywords);

  //   // set default header data

  //   // $tcpdf->setFooterFont(Array(PDF_FONT_NAME_DATA, '', 6));

  //   // set default monospaced font
  //   $tcpdf->SetDefaultMonospacedFont(PDF_FONT_MONOSPACED);

  //   //set margins
  //   // $tcpdf->SetMargins(PDF_MARGIN_LEFT, 28, PDF_MARGIN_RIGHT);
  //   // $tcpdf->SetHeaderMargin(PDF_MARGIN_HEADER);
  //   // $tcpdf->SetFooterMargin(PDF_MARGIN_FOOTER);

  //   //set auto page breaks
  //   // $tcpdf->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);

  //   //set image scale factor
    // $tcpdf->setImageScale(PDF_IMAGE_SCALE_RATIO);

  //   // set font
  //   $tcpdf->SetFont('dejavusans', '', 8);

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
  //         'certificate_image' => base_path() . drupal_get_path('module', 'ctl_certificate') . '/images/ctl-certificate-template.png',
  //       ),
  //     ),
  //   ),
  // ));

  // $tcpdf->writeHTML('<img src="http://placebear.com/200/300" />');

  // $tcpdf->writeHTML($html);

// TCPDF::Text (   $x,
//   $y,
//   $txt,
//   $fstroke = false,
//   $fclip = false,
//   $ffill = true,
//   $border = 0,
//   $ln = 0,
//   $align = '',
//   $fill = false,
//   $link = '',
//   $stretch = 0,
//   $ignore_min_height = false,
//   $calign = 'T',
//   $valign = 'M',
//   $rtloff = false
// )

  // $img_file = 'http://192.168.7.7' . base_path() . drupal_get_path('module', 'ctl_certificate') . '/images/ctl-certificate-template.png';


  // $img_file = 'http://192.168.7.7/profiles/ctl/modules/ctl/ctl_certificate/images/ctl-certificate-template.png';
  // $tcpdf->writeHTML('<img src="' . $img_file . '" />');

  $filename = '';
  $dest = 'S';
  return $tcpdf->Output($filename, $dest);
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
  // // get the current page break margin
  // $bMargin = $tcpdf->getBreakMargin();
  // // get current auto-page-break mode
  // $auto_page_break = $tcpdf->AutoPageBreak;
  // // disable auto-page-break
  // $tcpdf->SetAutoPageBreak(false, 0);

  // $bMargin = $tcpdf->getBreakMargin();
  // $auto_page_break = $tcpdf->AutoPageBreak;
  // // disable auto-page-break
  // $this->SetAutoPageBreak(false, 0);
  // // set bacground image
  // $img_file = K_PATH_IMAGES.'image_demo.jpg';
  // $this->Image($img_file, 0, 0, 210, 297, '', '', '', false, 300, '', false, false, 0);
  // // restore auto-page-break status
  // $this->SetAutoPageBreak($auto_page_break, $bMargin);
  // // set the starting point for the page content
  // $this->setPageMark();

  // watchdog('ctl_certificate', $context['certificate_image']);

  // $img_file  = $context['certificate_image'];
  // $x         = 0;
  // $y         = 0;
  // $width     = 100;
  // $height    = 0;
  // $type      = '';
  // $link      = '';
  // $align     = '';
  // $resize    = FALSE;
  // $dpi       = 300;
  // $palign    = '';
  // $ismask    = FALSE;
  // $imgmask   = FALSE;
  // $border    = 0;
  // $fitbox    = FALSE;
  // $hidden    = FALSE;
  // $fitonpage = TRUE;
  // $alt       = FALSE;
  // $altimgs   = array();

  // $tcpdf->Image($img_file, $x, $y, $width, $height, $type, $link, $align,
  //   $resize, $dpi, $palign, $ismask, $imgmask, $border, $fitbox, $hidden,
  //   $fitonpage, $alt, $altimgs);

  // $line_height = '1';
  // $text        = 'hiiiiii';
  // $link        = '';
  // $fill        = FALSE;
  // $align       = 'L';
  // $ln          = FALSE;
  // $stretch     = 0;
  // $firstline   = FALSE;
  // $firstblock  = FALSE;
  // $max_height  = 0;
  // $wadj        = 0;
  // $margin      = array();

  // $tcpdf->Write($line_height, $text, $link, $fill, $align, $ln, $stretch,
  //   $firstline, $firstblock, $max_height, $wadj, $margin);

  // // restore auto-page-break status
  // $tcpdf->SetAutoPageBreak($auto_page_break, $bMargin);
  // // set the starting point for the page content
  // $tcpdf->setPageMark();

  // // $args contains passed variable...
  // $theme_settings = variable_get('theme_' . variable_get('theme_default', '') . '_settings', '');
  // if (isset($theme_settings['logo_path']) && (file_exists($theme_settings['logo_path']))) {
  //   $tcpdf->Image(drupal_realpath($theme_settings['logo_path']), 10, 10, 30, 0, '', variable_get('site_url', ''), '', TRUE, 150, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
  // }
  // $tcpdf->Write(0, $context['welcome_message'], '', 0, 'J', true, 0, false, true, 0);
}
