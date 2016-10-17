<?php
/**
 * @file
 * Webform module Cleverreach component.
 *
 * Code heavily borrowed from webform_mailchimp.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_cleverreach() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'extra' => array(
      'title_display' => 0,
      'field_prefix' => '',
      'field_suffix' => '',
      'description' => '',
      'attributes' => array(),
      'cleverreach_group' => '',
      'double_opt_in_form' => 0,
      'use_existing_email_field' => '',
      'private' => FALSE,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_cleverreach() {
  return array(
    'webform_display_cleverreach' => array(
      'render element' => 'element',
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_cleverreach($component) {
  drupal_add_js(drupal_get_path('module', 'cleverreach') . '/webform_cleverreach.js');

  $node = node_load($component['nid']);
  $form = array();

  $options = array('none' => 'Select group');
  try {
    $api = cleverreach_get_soap_client();
  }
  catch (SoapFault $e) {
    watchdog_exception('cleverreach', $e);
  }
  if ($api) {
    $groups = cleverreach_get_group_options();
    if (!empty($groups)) {
      $options += $groups;
    }
    else {
      drupal_set_message(t('You do not have any cleverreach groups defined.'), 'error');
    }
  }
  else {
    drupal_set_message(t('Could not get valid cleverreach API object'), 'error');
  }

  $form['extra']['cleverreach_group'] = array(
    '#type' => 'select',
    '#title' => t('Choose group'),
    '#default_value' => !empty($component['extra']['cleverreach_group']) ? $component['extra']['cleverreach_group'] : 0,
    '#description' => t('Choose which group that the user can subscribe to.'),
    '#options' => $options,
    '#element_validate' => array('_webform_cleverreach_group_validate'),
    '#ajax' => array(
      'callback' => '_webform_edit_cleverreach_refresh',
      'wrapper' => 'webform-component-form-wrapper',
    ),
  );
  // Specify the wrapper div used by #ajax.
  $form['#prefix'] = '<div id="webform-component-form-wrapper">';
  $form['#suffix'] = '</div>';

  $double_opt_in_options = array(0 => t('No Double Opt-In'));
  if (!empty($component['extra']['cleverreach_group'])) {
    $double_opt_in_options += cleverreach_get_form_options($component['extra']['cleverreach_group']);
  }
  $form['extra']['double_opt_in_form'] = array(
    '#type' => 'select',
    '#title' => t('Double Opt-In Form'),
    '#default_value' => !empty($component['extra']['double_opt_in_form']) ? $component['extra']['double_opt_in_form'] : 0,
    '#description' => t('Choose if and which double opt-in form is used.'),
    '#options' => $double_opt_in_options,
  );

  $form['user_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('User email as default'),
    '#default_value' => $component['value'] == '[current-user:mail]' ? 1 : 0,
    '#attributes' => array('onclick' => 'getElementById("email-value").value = (this.checked ? "[current-user:mail]" : ""); getElementById("email-value").disabled = this.checked;'),
    '#description' => t('Set the default value of this field to the user email, if he/she is logged in.'),
    '#weight' => 0,
    '#element_validate' => array('_webform_cleverreach_user_email_validate'),
  );

  $options = array('cleverreach_field' => 'Create field');

  // Fetches existing components, checks if any of them are e-mail fields.
  // Let's the user choose which field to use for the newsletter e-mail address.
  if (!empty($node->webform['components'])) {
    foreach ($node->webform['components'] as $field) {
      if ($field['type'] == 'email') {
        $options[$field['form_key']] = $field['name'];
      }
    }
  }

  $form['extra']['use_existing_email_field'] = array(
    '#type' => 'select',
    '#title' => t('Select an existing e-mail field, or create one'),
    '#default_value' => !empty($component['extra']['use_existing_email_field']) ? $component['extra']['use_existing_email_field'] : 'create',
    '#description' => t('If you select an existing email field, that fields input will be used. If not, a field will be shown to the user.'),
    '#weight' => 1,
    '#options' => $options,
  );

  $form['extra']['checkbox_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Checkbox label'),
    '#default_value' => !empty($component['extra']['checkbox_label']) ? $component['extra']['checkbox_label'] : t('Subscribe to newsletter'),
    '#description' => t("If using an existing field you can edit the default label that's printed here."),
    '#weight' => 2,
    '#prefix' => '<div id="field_settings" style="display:none;">',
  );

  $form['extra']['checkbox_checked_by_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Checked by default.'),
    '#description' => t('If using an existing field, make the checkbox checked by default.'),
    '#default_value' => !empty($component['extra']['checkbox_checked_by_default']) ? $component['extra']['checkbox_checked_by_default'] : 0,
    '#weight' => 3,
  );

  $form['extra']['checkbox_hidden'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the checkbox.'),
    '#description' => t('Check this if users do not need to be able to set or unset wether they want to subscribe. Note that you still need to check wether the checkbox should be checked by default.'),
    '#default_value' => !empty($component['extra']['checkbox_hidden']) ? $component['extra']['checkbox_hidden'] : 0,
    '#weight' => 4,
    '#suffix' => '</div>',
  );

  $form['extra']['attributefields'] = array(
    '#type' => 'textarea',
    '#title' => t('Cleverreach Attribute fields'),
    '#description' => t('Enter one key|value pair per line. Use the cleverreach variable key as the key and the webform field key as the value. For example "fname|firstname"'),
    '#default_value' => !empty($component['extra']['attributefields']) ? $component['extra']['attributefields'] : '',
    '#weight' => 5,
  );
  // Add the available attributes list.
  $form['extra']['attributefields_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available Group Attributes'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 6,
  );
  if (!empty($component['extra']['cleverreach_group'])) {
    $rows = array();
    $group_name = '';
    if ($group = cleverreach_get_single_group($component['extra']['cleverreach_group'])) {
      $group_name = $group->name;
      foreach (array('attributes', 'globalAttributes') as $attribute_type) {
        if (!empty($group->{$attribute_type})) {
          foreach ($group->{$attribute_type} as $attribute) {
            $row = (array) $attribute;
            unset($row['is_global']);
            $row['key'] = array('header' => TRUE, 'data' => $row['key']);
            $rows[] = $row;
          }
        }
      }
    }
    $form['extra']['attributefields_help']['table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#caption' => t('Known attributes for group %group', array('%group' => $group_name)),
      '#empty' => t('No known attributes found'),
      '#header' => array(
        t('Attribute Key'),
        t('Type'),
        t('Variable'),
      ),
    );
  }

  return $form;
}

/**
 * Ajax callback.
 */
function _webform_edit_cleverreach_refresh($form, &$form_state) {
  $double_opt_in_options = array(0 => t('No Double Opt-In'));
  if (!empty($form_state['values']['extra']['cleverreach_group'])) {
    $double_opt_in_options += cleverreach_get_form_options($form_state['values']['extra']['cleverreach_group']);
  }
  $form['extra']['double_opt_in_form']['#options'] = $double_opt_in_options;
  return $form;
}

/**
 * Validation function for the email edit form.
 */
function _webform_cleverreach_user_email_validate($element, &$form_state) {
  if ($form_state['values']['user_email']) {
    $form_state['values']['value'] = '[current-user:mail]';
  }
}

/**
 * Form element validator for cleverreach_group element.
 */
function _webform_cleverreach_group_validate($element, &$form_state) {
  if ($form_state['values']['extra']['cleverreach_group'] == 'none') {
    form_error($element, t('You need to select a cleverreach group.'));
  }
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_cleverreach($component, $value = NULL, $filter = TRUE) {
  if ($value[0]) {
    $default_value = $value[0];
  }
  else {
    $default_value = webform_replace_tokens($component['value']);
  }

  $element = array();

  // Creates a field if the user hasn't chosen another email field.
  if ($component['extra']['use_existing_email_field'] == 'cleverreach_field') {
    $element['cleverreach_email_address'] = array(
      '#type'              => 'textfield',
      '#title'             => $filter ? webform_filter_xss($component['name']) : $component['name'],
      '#title_display'     => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
      '#required'          => $component['mandatory'],
      '#description'       => $filter ? webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
      '#default_value'     => webform_replace_tokens($component['value']),
      '#theme_wrappers'    => array('webform_element'),
      '#webform_component' => $component,
      '#weight'            => $component['weight'],
    );
  }
  else {
    // Creates a checkbox to subscribe, or a hidden form element if configured.
    if ($component['extra']['checkbox_hidden'] == 1) {
      $element['cleverreach_signup'] = array(
        '#type'              => 'hidden',
        '#default_value'     => !empty($component['extra']['checkbox_checked_by_default']) ? $component['extra']['checkbox_checked_by_default'] : 0,
      );
    }
    else {
      $element['cleverreach_signup'] = array(
        '#type'              => 'checkbox',
        '#title'             => !empty($component['extra']['checkbox_label']) ? webform_filter_xss($component['extra']['checkbox_label']) : t('Subscribe to newsletter'),
        '#default_value'     => !empty($component['extra']['checkbox_checked_by_default']) ? $component['extra']['checkbox_checked_by_default'] : 0,
        '#description'       => $filter ? webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
        '#theme_wrappers'    => array('webform_element'),
        '#webform_component' => $component,
        '#weight'            => $component['weight'],
      );
    }
  }

  $cleverreach_group = $component['extra']['cleverreach_group'];
  $element['cleverreach_group'] = array(
    '#prefix' => '',
    '#type' => 'value',
    '#value' => $cleverreach_group,
  );

  $element['#weight'] = $component['weight'];
  return $element;
}

/**
 * A Drupal Forms API Validation function.
 *
 * Validates the entered values from email components on the client-side form.
 *
 * @param array $form_element
 *   The e-mail form element.
 * @param array $form_state
 *   The full form state for the webform.
 *
 * @return void
 *   None. Calls a form_set_error if the e-mail is not valid.
 */
function _webform_validate_cleverreach_email($form_element, $form_state) {
  $component = $form_element['#webform_component'];
  if (!empty($form_element['cleverreach_email_address']['#value']) && !valid_email_address($form_element['cleverreach_email_address']['#value'])) {
    form_error($form_element, t('%value is not a valid email address.', array('%value' => $form_element['cleverreach_email_address']['#value'])));
  }
  elseif (empty($form_element['cleverreach_email_address']['#value']) && $form_element['#required']) {
    form_error($form_element, t('E-mail address for newsletter "%name" is required.', array('%name' => $component['name'])));
  }
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_cleverreach($component, $value, $format = 'html') {
  return array(
    '#title' => $component['name'],
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_cleverreach',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#format' => $format,
    '#value' => isset($value[0]) ? $value[0] : '',
    '#webform_component' => $component,
  );
}

/**
 * Format the output of data for this component.
 */
function theme_webform_display_cleverreach($variables) {
  $element = $variables['element'];
  $element['#value'] = empty($element['#value']) ? ' ' : $element['#value'];
  return $element['#format'] == 'html' ? check_plain($element['#value']) : $element['#value'];
}

/**
 * Implements _webform_submit_component().
 */
function _webform_submit_cleverreach($component, $value) {
  $return_val = NULL;

  if (!empty($value['cleverreach_signup'])) {
    $return_val = array(0 => $value['cleverreach_signup']);
  }

  if (!empty($value['cleverreach_signup'])) {
    $return_val = array(0 => $value['cleverreach_signup']);
  }
  if (!empty($value['cleverreach_email_address'])) {
    $return_val = array(0 => $value['cleverreach_email_address']);
  }

  return $return_val;
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_cleverreach($component, $sids = array()) {
  $query = db_select('webform_submitted_data', 'wsd', array('fetch' => PDO::FETCH_ASSOC))
    ->fields('wsd', array('data'))
    ->condition('nid', $component['nid'])
    ->condition('cid', $component['cid']);

  if (count($sids)) {
    $query->condition('sid', $sids, 'IN');
  }

  $nonblanks = 0;
  $submissions = 0;
  $wordcount = 0;

  $result = $query->execute();
  foreach ($result as $data) {
    if (drupal_strlen(trim($data['data'])) > 0) {
      $nonblanks++;
      $wordcount += str_word_count(trim($data['data']));
    }
    $submissions++;
  }

  $rows[0] = array(t('Left Blank'), ($submissions - $nonblanks));
  $rows[1] = array(t('User entered value'), $nonblanks);
  $rows[2] = array(
    t('Average submission length in words (ex blanks)'),
    ($nonblanks != 0 ? number_format($wordcount / $nonblanks, 2) : '0'),
  );
  return $rows;
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_cleverreach($component, $value) {
  return check_plain(empty($value[0]) ? '' : $value[0]);
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_cleverreach($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $component['name'];
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_cleverreach($component, $export_options, $value) {
  return !isset($value[0]) ? '' : $value[0];
}
