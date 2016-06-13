<?php

namespace Drupal\cleverreach\Types;

/**
 * mailingData
 */
class mailingData {
  /**
   * @var integer
   */
  public $id;

  /**
   * @var string
   */
  public $name;

  /**
   * @var string
   */
  public $type;

  /**
   * @var string
   */
  public $subject;

  /**
   * @var string
   */
  public $sender_name;

  /**
   * @var string
   */
  public $sender_email;

  /**
   * @var integer
   */
  public $groupId;

  /**
   * @var mailingGroupIds
   */
  public $groupIds;

  /**
   * @var string
   */
  public $html;

  /**
   * @var string
   */
  public $text;

}
