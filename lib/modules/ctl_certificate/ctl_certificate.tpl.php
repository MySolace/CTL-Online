<?php
/**
 * @file
 * Example template file for TCPDF Example module.
 */
?>
<html>
<head>
  <title>TCPDF for Drupal</title>
</head>
<body>
<span><?php print theme('image', array('path' => $certificate_image)); ?></span>
<span><?php print $graduate_name; ?></span>
<span><?php print $certification_date; ?></span>
</body>
</html>
