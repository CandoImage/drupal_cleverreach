<?php

/**
 * @file
 * Contains handling for subscribe forms.
 */

/**
 * Function for buildung the subscribing blockform.
 */
function cleverreach_subscribe_form($form, &$form_state, \Drupal\cleverreach\CleverReachBlock $block) {
  $form = array();
  $form['#tree'] = TRUE;

  // Ensure this include file is loaded when the form is rebuilt from cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'cleverreach') . '/cleverreach.subscribe.inc';

  $form['block_name'] = array(
    '#type' => 'value',
    '#value' => $block->name,
  );

  $form['fields'] = array(
    '#tree' => TRUE,
  );

  $form['fields']['email'] = array(
    '#type' => 'textfield',
    '#title' => isset($block->fields['email']['label']) ? t($block->fields['email']['label']) : t('E-Mail:'),
    '#required' => 1,
    '#size' => 25,
    '#weight' => isset($block->fields['email']['weight']) ? t($block->fields['email']['weight']) : 0,
    '#parents' => array('email'),
  );

  foreach ($block->fields as $field_name => $field) {
    if (!empty($field['active'])) {
      $form['fields'][$field_name] = _cleverreach_build_block_field($field_name, $field);
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('subscribe'),
    '#weight' => 100,
  );
  return $form;
}

/**
 * Implements hook_form_validate().
 */
function cleverreach_subscribe_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['email'])) {
    form_set_error('email', t('Please enter a valid email address.'));
  }
}

/**
 * Function for assign a customer to a group.
 */
function cleverreach_subscribe_form_submit($form, &$form_state) {

  $block = cleverreach_get_block($form_state['values']['block_name']);

  // Collect information from the fields.
  $subscribe_attributes = array();
  foreach ($block->fields as $field_name => $field) {

    if (!empty($field['active'])) {
      if ($field['display'] == 'date') {
        $subscribe_attributes[] = array(
          'key' => $field_name,
          'value' => sprintf('%s-%s-%s',
            $form_state['values']['fields'][$field_name]['year'],
            $form_state['values']['fields'][$field_name]['month'],
            $form_state['values']['fields'][$field_name]['day']
          ),
        );
      }
      else {
        $subscribe_attributes[] = array(
          'key' => $field_name,
          'value' => $form_state['values']['fields'][$field_name],
        );
      }
    }
  }

  if (cleverreach_receiver_add($form_state['values']['email'], TRUE, variable_get('site_name', 'CleverReach Drupal Module'), NULL, $subscribe_attributes)) {

    // Show a simple message if no activation mail shall be sent.
    if (!empty($block->send_activation_mail)) {
      drupal_set_message(t('Your submission was successful.'));
    }
    // Otherwise we prepare an activation mail with relevant data for
    // cleverreach.
    else {
      $iodata = array(
        'user_ip' => ip_address(),
        'user_agent' => isset($_SERVER['HTTP_USER_AGENT']) ? $_SERVER['HTTP_USER_AGENT'] : '',
        'referer' => isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : '',
        'postdata' => '',
        'info' => '',
      );
      $settings = _cleverreach_get_settings();
      try {
        $result = cleverreach_get_soap_client()->formsSendActivationMail($settings['key'], $block->formid, $form_state['values']['email'], $iodata);
      }
      catch (SoapFault $e) {
        watchdog_exception('cleverreach', $e);
      }

      if (!empty($result->status) && $result->status == 'SUCCESS') {
        drupal_set_message(t('Your submission was successful. A mail has been sent to you for confirming your subscription.'));
      }
      else {
        drupal_set_message(t('An error occured while sending the confirmation mail.'), 'error');
      }
    }
  }
  else {
    drupal_set_message(t('Error: Your submission failed.'), 'error');
  }
}

/**
 * Function for buildung the blockform fields.
 */
function _cleverreach_build_block_field($name, $field_data) {
  $field = array(
    '#title' => isset($field_data['label']) ? $field_data['label'] : ucwords($name) . ":",
    '#required' => $field_data["required"],
    '#weight' => isset($field_data['weight']) ? $field_data['weight'] : 0,
  );

  if ($field_data["display"] == "textfield") {
    $field['#type'] = 'textfield';
    $field['#size'] = 25;
    $field['#default_value'] = isset($field_data["display_options"]) ? $field_data["display_options"] : '';
  }

  elseif ($field_data["display"] == "select") {
    $field['#type'] = 'select';
    $field['#multiple'] = FALSE;
    $options = explode("\n", $field_data["display_options"]);
    $select_options = array();

    foreach ($options as $value) {
      $tmp = explode("|", $value);

      if (count($tmp) == 2) {
        $select_options[trim($tmp[0])] = trim($tmp[1]);
      }

      else {
        $select_options[trim($tmp[0])] = trim($tmp[0]);
      }

    }

    $field['#options'] = isset($select_options) ? $select_options : array();
  }

  elseif ($field_data["display"] == "date") {
    $field['#type'] = 'date';
  }

  else {
    $field['#type'] = 'textfield';
  }

  return $field;
}
