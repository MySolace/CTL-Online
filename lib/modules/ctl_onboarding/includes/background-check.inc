<?php

define('CTL_ONBOARDING_GOODHIRE_USERNAME', 'crisistextline');
define('CTL_ONBOARDING_GOODHIRE_PASSWORD', 'F6sWFyDEWcGmCPyg4dcm');

function _ctl_onboarding_do_background_check($user) {
  $goodhire     = variable_get('ctl_onboarding_goodhire');
  $endpoint     = isset($goodhire['endpoint']) ? $goodhire['endpoint'] : '';
  $username     = isset($goodhire['username']) ? $goodhire['username'] : '';
  $password     = isset($goodhire['password']) ? $goodhire['password'] : '';
  $company_id   = isset($goodhire['company_id']) ? $goodhire['company_id'] : '';
  $requestor_id = isset($goodhire['requestor_id']) ? $goodhire['requestor_id'] : '';

  $testing = isset($goodhire['testing']) ? $goodhire['testing'] : FALSE;
  if ($testing) {
    $email = isset($goodhire['test_email']) ? $goodhire['test_email'] : '';
  }
  else {
    $email = $user->field_email[LANGUAGE][0]['value'];
  }

  $url = "$endpoint/Company/$company_id/Requestor/$requestor_id/Report/";
  $data = array(
    'candidate' => array(
      'firstName' => $user->field_first_name[LANGUAGE][0]['value'],
      'lastName'  => $user->field_last_name[LANGUAGE][0]['value'],
      'email'     => $email,
    ),
    'offer' => array(
      'products' => array('RPT_BASIC'),
    ),
  );
  $options = array(
    'data'    => drupal_http_build_query($data),
    'method'  => 'POST',
    'headers' => array(
      'Content-Type' => 'application/json',
    ),
  );

  // TODO
  dsm($url);
  dsm($options);
  return;

  $result = drupal_http_request($url, $options);

// result =
// request: A string containing the request body that was sent.
// code: An integer containing the response status code, or the error code if an error occurred.
// protocol: The response protocol (e.g. HTTP/1.1 or HTTP/1.0).
// status_message: The status message from the response, if a response was received.
// redirect_code: If redirected, an integer containing the initial response status code.
// redirect_url: If redirected, a string containing the URL of the redirect target.
// error: If an error occurred, the error message. Otherwise not set.
// headers: An array containing the response headers as name/value pairs. HTTP header names are case-insensitive (RFC 2616, section 4.2), so for easy access the array keys are returned in lower case.
// data: A string containing the response body that was received.

}
