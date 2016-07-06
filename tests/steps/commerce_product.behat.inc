<?php

/**
 * @file
 * Provide Behat step-definitions for Commerce Product.
 */

use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Hook\Scope\AfterNodeCreateScope;

class CommerceProductContext extends DrupalSubContextBase implements DrupalSubContextInterface {
  /**
   * Contains the DrupalDriverManager.
   *
   * @var \Drupal\DrupalDriverManager
   */
  protected $drupal;

  /**
   * An array of products created during this context to be cleaned up.
   *
   * @var array
   */
  protected $products = array();

  /**
   * The name of the product reference field on the product display node.
   *
   * @var string
   */
  protected $productReferenceFieldName = 'field_product';

  /**
   * {@inheritdoc}
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Provide the name of the product reference field.
   *
   * @Given my product reference field is :field_name
   */
  public function myProductReferenceField($field_name) {
    $this->productReferenceFieldName = $field_name;
  }

  /**
   * Creates content of the given type.
   *
   * @Given I am viewing a/an :nodeType and product of :productType with the title :title
   */
  public function createProductDisplay($nodeType, $productType, $title) {
    $product = $this->productCreate((object) array(
      'sku' => $this->getRandom()->string(10),
      'title' => $title,
      'type' => $productType,
      'uid' => 1,
      'status' => 1,
      'commerce_price' => array(LANGUAGE_NONE => array(array('amount' => '1900', 'currency_code' => commerce_default_currency(), 'data' => array('components' => array())))),
    ));

    $node = (object) array(
      'title' => $title,
      'type' => $nodeType,
      'body' => $this->getRandom()->string(255),
      $this->productReferenceFieldName => $product->product_id
    );
    $saved = $this->nodeCreate($node);

    // @todo: Get AfterNodeCreateScope below working.
    $product_id = $saved->{$this->productReferenceFieldName}[LANGUAGE_NONE][0]['value'];
    unset($saved->{$this->productReferenceFieldName}[LANGUAGE_NONE][0]['value']);
    $saved->{$this->productReferenceFieldName}[LANGUAGE_NONE][0]['product_id'] = $product_id;
    // We have to re-save here because scope hook is being weird.
    node_save($saved);

    // Set internal page on the new node.
    $this->getSession()->visit($this->locatePath('/node/' . $saved->nid));
  }

  /**
   * Create a product.
   *
   * @return object
   *   The created product.
   */
  public function productCreate($product) {
//    $this->dispatchHooks('BeforeProductCreateScope', $product);
    commerce_product_save($product);
//    $this->dispatchHooks('AfterProductCreateScope', $product);
    $this->products[] = $product;
    return $product;
  }

  /**
   * Remove any created products.
   *
   * @AfterScenario
   */
  public function cleanProducts() {
    // Remove any nodes that were created.
    foreach ($this->products as $product) {
      commerce_product_delete($product->product_id);
    }
  }

  /**
   * Fix product reference fields (product_id, not value for key.)
   *
   * @AfterNodeCreateScope
   */
  public function fixProductReferenceField(AfterNodeCreateScope $scope) {
    $entity = $scope->getEntity();
    if (isset($entity->{$this->productReferenceFieldName}) && !empty($entity->{$this->productReferenceFieldName}[LANGUAGE_NONE])) {
      $product_id = $entity->{$this->productReferenceFieldName}[LANGUAGE_NONE][0]['value'];
      unset($entity->{$this->productReferenceFieldName}[LANGUAGE_NONE][0]['value']);
      $entity->{$this->productReferenceFieldName}[LANGUAGE_NONE][0]['product_id'] = $product_id;
    }
  }

}
