<?php

namespace Drupal\CommerceBehat\Context;

use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Hook\Scope\AfterNodeCreateScope;

class DrupalCommerceCheckoutContext extends DrupalSubContextBase implements DrupalSubContextInterface {
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
    $this->drupal = $drupal;
  }

  /**
   * @Given anonymous checkout is enabled
   */
  public function givenAnonymousCheckoutEnabled() {
    user_role_grant_permissions(DRUPAL_ANONYMOUS_RID, array(
      'access checkout',
    ));
  }

  /**
   * @Given anonymous checkout is disabled
   */
  public function givenAnonymousCheckoutDisabled() {
    user_role_revoke_permissions(DRUPAL_ANONYMOUS_RID, array(
      'access checkout',
    ));
  }

}
