<?php
/**
 * @file
 * This file provides the rules integration for cleverreach.
 */

/**
 * Implements of hook_rules_action_info().
 *
 * @see hook_rules_action_info()
 */
function cleverreach_rules_action_info() {
  $actions = array(
    'cleverreach_rules_receiver_add' => array(
      'label' => t('Receiver Add'),
      'parameter' => array(
        'listId' => array(
          'type' => 'integer',
          'label' => t('ListID'),
          'options list' => 'cleverreach_get_group_options',
          'optional' => FALSE,
        ),
        'email' => array(
          'type' => 'text',
          'label' => t('E-Mail'),
          'optional' => FALSE,
        ),
        'active' => array(
          'type' => 'boolean',
          'label' => t('Active'),
          'default value' => TRUE,
          'optional' => TRUE,
        ),
        'source' => array(
          'type' => 'text',
          'label' => t('Source'),
          'description' => t('Defined the source where this user came from.'),
          'default value' => variable_get('site_name', 'CleverReach Drupal Module'),
        ),
        'quality' => array(
          'type' => 'decimal',
          'label' => t('Quality'),
          'optional' => TRUE,
          'allow null' => TRUE,
          'default value' => NULL,
        ),
        'attributes' => array(
          'type' => 'text',
          'label' => t('Attributes'),
          'description' => t('Enter one key|value pair per line. Use the cleverreach attribute key as the key and then set the value, you may use tokens. For example "site_name|[site:name]"'),
          'optional' => TRUE,
        ),
      ),
      'provides' => array(
        'cleverreach_user_id' => array(
          'label' => t('CleverReach User ID'),
          'type' => 'integer',
        ),
      ),
      'callbacks' => array(
        'form_alter' => 'cleverreach_rules_receiver_add_form_alter',
      ),
      'group' => t('CleverReach'),
    ),
  );
  return $actions;
}

/**
 * Callback: Form alteration for rules action cleverreach_rules_receiver_add.
 */
function cleverreach_rules_receiver_add_form_alter(&$form, &$form_state, $options, RulesAbstractPlugin $element) {
  // Ensure this file is loaded.
  form_load_include($form_state, 'inc', 'cleverreach', 'cleverreach.rules');

  $first_step = empty($element->settings['listId']);
  $form['reload'] = array(
    '#weight' => 5,
    '#type' => 'submit',
    '#name' => 'reload',
    '#value' => $first_step ? t('Continue') : t('Reload form'),
    '#limit_validation_errors' => array(array('parameter', 'listId')),
    '#submit' => array('cleverreach_rules_receiver_add_form_submit_rebuild'),
    '#ajax' => rules_ui_form_default_ajax(),
  );
  // Use ajax and trigger as the reload button.
  $form['parameter']['listId']['settings']['listId']['#ajax'] = $form['reload']['#ajax'] + array(
      'event' => 'change',
      'trigger_as' => array('name' => 'reload'),
    );

  if ($first_step) {
    // In the first step show only the listId select.
    foreach (element_children($form['parameter']) as $key) {
      if ($key != 'listId') {
        unset($form['parameter'][$key]);
      }
    }
    unset($form['submit']);
    unset($form['provides']);
    // Disable #ajax for the first step as it has troubles with lazy-loaded JS.
    // @todo: Re-enable once JS lazy-loading is fixed in core.
    unset($form['parameter']['listId']['settings']['listId']['#ajax']);
    unset($form['reload']['#ajax']);
  }
  else {
    // Hide the reload button in case js is enabled and it's not the first step.
    $form['reload']['#attributes'] = array('class' => array('rules-hide-js'));

    // Add the available attributes list.
    $form['parameter']['attributes']['settings']['help']['group_attributes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available Group Attributes'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $rows = array();
    $group_name = '';
    if ($group = cleverreach_get_single_group($element->settings['listId'])) {
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
    $form['parameter']['attributes']['settings']['help']['group_attributes']['table'] = array(
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
}

/**
 * FAPI submit callback for reloading the listid form for cleverreach.
 */
function cleverreach_rules_receiver_add_form_submit_rebuild($form, &$form_state) {
  rules_form_submit_rebuild($form, $form_state);
  // Clear the parameter modes for the parameters, so they get the proper
  // default values based upon the data types on rebuild.
  $form_state['parameter_mode'] = array();
}

/**
 * Adds a new user to list.
 *
 * @TODO Order handling.
 */
function cleverreach_rules_receiver_add($list_id, $email, $active, $source, $quality, $attributes) {
  $prepared_attributes = NULL;
  if (!empty($attributes)) {
    $prepared_attributes = array();
    $attributes = explode("\n", str_replace("\r", '', $attributes));
    foreach ($attributes as $attribute) {
      $attribute = explode('|', $attribute, 2);
      $prepared_attributes[$attribute[0]] = $attribute[1];
    }
  }
  $user_id = cleverreach_receiver_add($list_id, $email, $active, $source, $quality, $prepared_attributes);
  return array('cleverreach_user_id' => $user_id);
}