<?php

define('CTL_ONBOARDING_GOODHIRE_USERNAME', 'crisistextline');
define('CTL_ONBOARDING_GOODHIRE_PASSWORD', 'F6sWFyDEWcGmCPyg4dcm');

define('CTL_ONBOARDING_HTTP_CODE_CREATED', 201);


function _ctl_onboarding_do_background_check($user) {
  $goodhire     = variable_get('ctl_onboarding_goodhire');
  $endpoint     = isset($goodhire['endpoint']) ? $goodhire['endpoint'] : '';
  $username     = isset($goodhire['username']) ? $goodhire['username'] : '';
  $password     = isset($goodhire['password']) ? $goodhire['password'] : '';
  $company_id   = isset($goodhire['company_id']) ? $goodhire['company_id'] : '';
  $requestor_id = isset($goodhire['requestor_id']) ? $goodhire['requestor_id'] : '';

  $field_first_name = field_get_items('user', $user, 'field_first_name');
  $field_last_name  = field_get_items('user', $user, 'field_last_name');
  $first_name       = $field_first_name ? $field_first_name[0]['value'] : '';
  $last_name        = $field_last_name ? $field_last_name[0]['value'] : '';

  $testing = isset($goodhire['testing']) ? $goodhire['testing'] : FALSE;
  if ($testing) {
    $email = isset($goodhire['test_email']) ? $goodhire['test_email'] : '';
  }
  else {
    $email = $user->mail;
  }

  $url = "https://$username:$password@$endpoint/Company/$company_id/Requestor/$requestor_id/Report";
  $data = array(
    'candidate' => array(
      'firstName' => $first_name,
      'lastName'  => $last_name,
      'email'     => $email,
    ),
    'offer' => array(
      'products' => array('RPT_BASIC'),
    ),
  );
  $options = array(
    'data'    => drupal_json_encode($data),
    'method'  => 'POST',
    'headers' => array(
      'Content-Type'  => 'application/json',
    ),
  );

  $result = drupal_http_request($url, $options);
  if ($result === 'CTL_ONBOARDING_HTTP_CODE_CREATED') {
    // TODO
    // - complete this
    // // The background check request has been successfully made.
    // drupal_set_message(t(":url", array(':url' => 'https://www.goodhire.com/')));
  }
  else {
    // Everything else is considered an error.
    drupal_set_message(t("Error :error_code:  :error_message", array(
      ':error_code' => $result->code,
      ':error_message' => $result->error)
    ), 'error');
  }
}
