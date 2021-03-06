<?php
/**
 * @file
 * This file contains admin UI callbacks.
 */

/**
 * Generates the profile type editing form.
 *
 * @todo: field weight / tabledrag
 */
function cleverreach_block_form($form, &$form_state, $block, $op = 'edit', $entity_type = NULL) {

  if ($op == 'clone') {
    // Only label is provided for cloned entities.
    $block->name = $entity_type . '_clone';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => isset($block->label) ? $block->label : '',
  );

  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#required' => TRUE,
    '#default_value' => isset($block->name) ? $block->name : '',
    '#machine_name' => array(
      'exists' => 'cleverreach_get_block',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this block. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate Block'),
    '#default_value' => $block->active,
    '#description' => t('Check to make the block usable on the block admin page.'),
  );

  $form['listid'] = array(
    '#type' => 'select',
    '#options' => cleverreach_get_group_options(),
    '#title' => t('Group'),
    '#description' => t('Select the cleverreach group'),
    '#default_value' => $block->listid,
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => '_cleverreach_block_form_ajax_fields',
      'wrapper' => 'cleverreach-fields',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['send_activation_mail'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send activation mail'),
    '#default_value' => $block->send_activation_mail,
    '#description' => t('When checked, an activation mail is send to verify the user (Double Opt-In).'),
  );

  // Get the latest values from the form state as we have an ajaxified form.
  $listid = isset($form_state['values']['listid']) ? $form_state['values']['listid'] : $block->listid;
  $values = isset($form_state['values']['fields']) ? $form_state['values']['fields'] : $block->fields;

  $form['listid_dependent'] = array(
    '#type' => 'container',
    '#id' => 'cleverreach-fields',
  );

  if (!empty($listid)) {

    $form['listid_dependent']['formid'] = array(
      '#type' => 'select',
      '#title' => t('Form configuration'),
      '#description' => t('Select the associated CleverReach form to be used for activation mail.'),
      '#options' => cleverreach_get_form_options($listid),
      '#empty_option' => '- No form -',
      '#default_value' => $block->formid,
    );

    $form['listid_dependent']['fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Fields'),
      '#id' => 'cleverreach-fields',
      '#tree' => TRUE,
      '#theme' => 'cleverreach_tableform',
      '#columns' => array(
        'active' => t('Active'),
        'name' => t('Name'),
        'type' => t('Type'),
        'label' => t('Label'),
        'required' => t('Required'),
        'display' => t('Display'),
        'display_options' => t('Display options'),
        'weight' => t('Weight'),
      ),
      '#caption' => t('Select fields'),
    );

    $form['listid_dependent']['fields']['email'] = array(
      'name' => array(
        '#type' => 'item',
        '#markup' => 'email',
      ),
      'label' => array(
        '#type' => 'textfield',
        '#default_value' => isset($values['email']['label']) ? $values['email']['label'] : 'E-Mail:',
        '#size' => 30,
      ),
      'type' => array(
        '#type' => 'item',
        '#markup' => 'email',
      ),
      'weight' => array(
        '#type' => 'weight',
        '#default_value' => isset($values['email']['weight']) ? $values['email']['weight'] : 0,
        '#attributes' => array('class' => array('draggable-weight')),
      ),
    );

    // Add additional attribute based fields.
    $form['listid_dependent']['fields'] += _cleverreach_block_fields_subform($listid, $values);
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save block'),
    '#weight' => 40,
  );
  return $form;
}

/**
 * Form API validate callback for the block form.
 */
function cleverreach_block_form_validate(&$form, &$form_state) {
  if ($form_state['values']['send_activation_mail']
    && empty($form_state['values']['formid'])) {
    form_set_error('formid', t('Currently activation mails can only be send via
      a pre-configured CleverReach form. Therefore you must select a form.'));
  }
}

/**
 * Form API submit callback for the type form.
 */
function cleverreach_block_form_submit(&$form, &$form_state) {
  $block = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $block->save();
  $form_state['redirect'] = 'admin/config/services/cleverreach';
}

/**
 * Ajax callback for the block form.
 *
 * @return mixed
 */
function _cleverreach_block_form_ajax_fields($form, &$form_state) {
  return $form['listid_dependent'];
}

/**
 * Provides subform for fields of a given cleverreach group.
 *
 * @param int $gid
 *   CleverReach Group ID
 * @param $values
 *   Array of field values, either from the block object or the form state.
 *
 * @return array
 *   Form array to implement in
 */
function _cleverreach_block_fields_subform($gid, $values) {
  $subforms = array();
  $group = cleverreach_get_single_group($gid);

  foreach ($group->getAllAttributes() as $attr) {

    $val = _cleverreach_block_form_get_field_values($attr, $values);

    $subform['active'] = array(
      '#type' => 'checkbox',
      '#default_value' => $val['active'],
    );
    $subform['required'] = array(
      '#type' => 'checkbox',
      '#default_value' => $val['required'],
    );
    $subform['name'] = array(
      '#type' => 'item',
      '#markup' => check_plain($attr->key),
    );
    $subform['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#description' => t('Field label to display in the form presented to the user'),
      '#default_value' => !empty($val['label']) ? $val['label'] : ucwords($attr->key) . ':',
      '#size' => 30,
    );
    $subform['type'] = array(
      '#type' => 'item',
      '#markup' => check_plain($attr->type),
    );

    $options = $attr->getDisplayTypes();
    if (empty($val['display'])) {
      // By default we chose the first option to be preselected.
      $val['display'] = key($options);
    }

    $subform['display'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $val['display'],
      '#ajax' => array(
        'callback' => '_cleverreach_block_form_ajax_fields',
        'wrapper' => 'cleverreach-fields',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );

    switch ($val['display']) {
      case 'select':
        $subform['display_options'] = array(
          '#type' => 'textarea',
          '#description' => t('Select options. One per line. key|value Example: men|Men'),
          '#default_value' => $val['display_options'],
        );
        break;

      case 'textfield':
        $subform['display_options'] = array(
          '#type' => 'textfield',
          '#description' => t('A default field value (optional)'),
          '#default_value' => $val['display_options'],
        );
        break;

      case 'date':
        $subform['display_options'] = array(
          '#type' => 'textfield',
          '#default_value' => !empty($val['display_options']) ? $val['display_options'] : 'Y-m-d',
          '#disabled' => TRUE,
          '#description' => t('Date format, default: Y-m-d'),
        );
        break;
    }

    $subform['weight'] = array(
      '#type' => 'weight',
      '#default_value' => isset($val['weight']) ? $val['weight'] : 0,
      '#attributes' => array('class' => array('draggable-weight')),
    );

    $subforms[$attr->key] = $subform;
  }

  return $subforms;
}

/**
 * Helper to ge the right value for the given attribute.
 *
 * @param \Drupal\cleverreach\CleverReachGroupAttribute $attr
 * @param $values
 *
 * @return mixed
 */
function _cleverreach_block_form_get_field_values(\Drupal\cleverreach\CleverReachGroupAttribute $attr, $values) {
  if (isset($values[$attr->key])) {
    $val = $values[$attr->key];
  }
  else {
    $val = array();
  }

  return array_merge(array(
    'active' => 0,
    'required' => 0,
    'display' => '',
    'display_options' => '',
    'weight' => 0,
  ), $values[$attr->key]);
}

/**
 * Returns a renderable overview of the cached groups.
 *
 * @return array
 *   Render array as group overview table.
 */
function cleverreach_groups_overview() {
  $rows = array();
  $groups = cleverreach_get_all_groups();

  foreach ($groups as $group) {
    $rows[] = array(
      l($group->id, 'admin/config/services/cleverreach/group/' . $group->id . '/view'),
      l($group->name, 'admin/config/services/cleverreach/group/' . $group->id . '/view'),
      $group->count,
      $group->inactive_count,
      (!empty($group->last_mailing)) ? format_date($group->last_mailing) : t('No mailing yet'),
      format_date($group->last_changed),
    );
  }

  $group_header = array(
    t('ID'),
    t('Name'),
    t('Active Count'),
    t('Inactive Count'),
    t('Last mailing'),
    t('Last changed'),
  );

  return array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => $group_header,
  );
}

/**
 * Returns a renderable overview of the cached groups.
 *
 * @return array
 *   Render array as group overview table.
 */
function cleverreach_groups_group_detail($group) {
  if ($group) {
    $rows = array();
    foreach ($group as $name => $data) {
      if (!is_scalar($data)) {
        $data = '<pre>' . print_r($data, TRUE) . '</pre>';
      }
      $name = strtr($name, array('_' => ' ', '-' => ' '));
      $rows[] = array(
        ucfirst($name),
        $data,
      );
    }

    $group_header = array(
      t('Name'),
      t('Data'),
    );

    return array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => $group_header,
    );
  }
  return t('Failed to load group');
}

/**
 * The admin settings (api details) system form.
 */
function _cleverreach_admin_settings() {
  $form = array();
  $form['api_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('CleverReach API Details'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['api_details']['cleverreach_api_key'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('cleverreach_api_key', ''),
    '#title' => t('Your CleverReach API-Key'),
    '#description' => t('Enter your personal CleverReach API-Key.'),
  );
  $form['api_details']['cleverreach_wsdl_url'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('cleverreach_wsdl_url', 'http://api.cleverreach.com/soap/interface_v5.1.php?wsdl'),
    '#title' => t('CleverReach WSDL-URL'),
    '#description' => t('Enter the CleverReach WSDL-URL.'),
  );
  $form['grp_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('CleverReach Group Sync'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // If we got a cache, show the date it was last updated.
  $group_cache = cache_get(CLEVERREACH_GROUPS_CACHE_ID);
  $date = ($group_cache && $group_cache->created) ? format_date($group_cache->created) : t('never');
  $form['grp_details']['#description'] = t('Last update: @date', array(
    '@date' => $date,
  ));

  $form['grp_details']['update_button'] = array(
    '#type' => 'button',
    '#value' => t('Fetch groups now'),
    '#limit_validation_errors' => array(),
    '#executes_submit_callback' => TRUE,
    '#submit' => array('_cleverreach_admin_settings_submit_fetch_groups'),
  );
  return system_settings_form($form);
}

/**
 * Validation callback for the admin settings form.
 */
function _cleverreach_admin_settings_validate($form, &$form_state) {

  // Validate connection.
  try {
    $api = new SoapClient($form_state['values']['cleverreach_wsdl_url']);
  }
  catch (SoapFault $e) {
    watchdog_exception('cleverreach', $e);
  }
  $response = $api->clientGetDetails($form_state['values']['cleverreach_api_key']);
  if ($response->status == 'ERROR') {
    form_set_error('cleverreach_api_key', t('Could not connect to the Server: %message', array(
      '%message' => $response->message,
    )));
  }
}

/**
 * Submission callback for updating group cache.
 */
function _cleverreach_admin_settings_submit_fetch_groups($form, &$form_state) {

  $result = _cleverreach_update_group_cache();

  if (empty($result)) {
    drupal_set_message(t('No groups were synced. Make sure you already have created customer groups on cleverreach.com.'), 'warning');
  }
  else {
    drupal_set_message(t('Groups succesfully synced.'));
  }
}