<?php

namespace Drupal\cleverreach\Types;

/**
 * receiverData
 */
class receiverData {
  /**
   * @var integer
   */
  public $id;

  /**
   * @var string
   */
  public $email;

  /**
   * @var integer
   */
  public $registered;

  /**
   * @var integer
   */
  public $activated;

  /**
   * @var integer
   */
  public $deactivated;

  /**
   * @var boolean
   */
  public $active;

  /**
   * @var string
   */
  public $source;

  /**
   * @var integer
   */
  public $quality;

  /**
   * @var receiverAttributes
   */
  public $attributes;

  /**
   * @var receiverAttributes
   */
  public $globalAttributes;

  /**
   * @var receiverEvents
   */
  public $events;

  /**
   * @var receiverOrders
   */
  public $orders;

}
