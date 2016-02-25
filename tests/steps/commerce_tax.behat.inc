<?php

/**
 * @file
 * Provide Behat step-definitions for Commerce Product.
 */

use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Behat\Gherkin\Node\TableNode;

class CommerceTaxContext extends DrupalSubContextBase implements DrupalSubContextInterface {
  /**
   * Contains the DrupalDriverManager.
   *
   * @var \Drupal\DrupalDriverManager
   */
  protected $drupal;

  /**
   * {@inheritdoc}
   */
  public function __construct(DrupalDriverManager $drupal) {
    parent::__construct($drupal);
    $this->drupal = $drupal;
  }

  /**
   * Creates a new sales tax type in the form of
   * | name      | title     | display_title | display_inclusive |
   * | sales_tax | Sales tax | Sales tax     | false             |
   * | vat       | VAT       | VAT           | true              |
   *
   * @Given the sales tax type:
   */
  public function createSalesTaxType(TableNode $infoTable) {
    $tax_type_defaults = commerce_tax_ui_tax_type_new();
    foreach ($infoTable->getHash() as $value) {
      $tax_type = $tax_type_defaults + $value;
      commerce_tax_ui_tax_type_save($tax_type);
    }
  }

  /**
   * Creates a new sales tax rate in the form of
   * | name      | title     | display_title | rate |
   * | sales_tax | Sales tax | Sales tax     | 0    |
   * | vat       | VAT       | VAT           | 0.25 |              |
   *
   * @Given :type sales tax rate:
   */
  public function createSalesTaxRate($type, TableNode $infoTable) {
    $tax_rate_defaults = commerce_tax_ui_tax_rate_new($type);
    foreach ($infoTable->getHash() as $value) {
      $tax_type = $tax_rate_defaults + $value;
      commerce_tax_ui_tax_rate_save($tax_type);
    }
  }
}
