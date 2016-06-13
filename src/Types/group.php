<?php

namespace Drupal\cleverreach\Types;

/**
 * group
 */
class group {
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
  public $description;

  /**
   * @var integer
   */
  public $last_mailing;

  /**
   * @var integer
   */
  public $last_changed;

  /**
   * @var integer
   */
  public $count;

  /**
   * @var integer
   */
  public $inactive_count;

  /**
   * @var integer
   */
  public $total_count;

  /**
   * @var receiverAttributes
   */
  public $attributes;

  /**
   * @var receiverAttributes
   */
  public $globalAttributes;

}
