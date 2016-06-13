<?php

namespace Drupal\cleverreach\Types;

/**
 * receiverOrder
 */
class receiverOrder {
  /**
   * @var string
   */
  public $order_id;

  /**
   * @var integer
   */
  public $purchase_date;

  /**
   * @var string
   */
  public $product_id;

  /**
   * @var string
   */
  public $product;

  /**
   * @var integer
   */
  public $quantity;

  /**
   * @var double
   */
  public $price;

  /**
   * @var integer
   */
  public $mailings_id;

  /**
   * @var string
   */
  public $source;

}
