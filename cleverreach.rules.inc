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
        ),
        'email' => array(
          'type' => 'text',
          'label' => t('E-Mail'),
        ),
        'active' => array(
          'type' => 'boolean',
          'label' => t('Active'),
        ),
        'source' => array(
          'type' => 'text',
          'label' => t('Source'),
          'description' => t('Defined the source where this user came from.'),
        ),
        'quality' => array(
          'type' => 'decimal',
          'label' => t('Quality'),
        ),
      ),
      'provides' => array(
        'cleverreach_user_id' => array(
          'label' => t('CleverReach User ID'),
          'type' => 'integer',
        ),
      ),
      'group' => t('CleverReach'),
    ),
  );
  return $actions;
}

/**
 * Adds a new user to list.
 *
 * @TODO Order and Attributes handling.
 */
function cleverreach_rules_receiver_add($list_id, $email, $active, $source, $quality) {
  $user_id = cleverreach_receiver_add($list_id, $email, $active, $source, $quality);
  return array('cleverreach_user_id' => $user_id);
}
