Feature: Access checkout
  As a customer
  I can add a product to my cart
  Which allows me to purchase the product

  @api
  Scenario: Add product to cart as an anonymous user, with checkout enabled.
    Given I am an anonymous user
      And anonymous checkout is enabled
    When I am viewing a "behat_product_display" and product of "product" with the title "Behat Product"
    Then I should see "Behat Product"
      And I press "Add to cart"
      Then I should see "Behat Product added to your cart."
    When I click "your cart"
      Then I should see the heading "Shopping cart"
      And I should see the link "Behat Product"
    When I press "Checkout"
      Then I should see "Shopping cart contents"
      And I fill in the following:
        | account[login][mail]                                                              | demo@demo.com |
        # Billing
        | customer_profile_billing[commerce_customer_address][und][0][name_line]            | Behat User    |
        | customer_profile_billing[commerce_customer_address][und][0][thoroughfare]         | 1234 56th St  |
        | customer_profile_billing[commerce_customer_address][und][0][locality]             | Kenosha       |
        | customer_profile_billing[commerce_customer_address][und][0][administrative_area]  | WI            |
        | customer_profile_billing[commerce_customer_address][und][0][postal_code]          | 53140         |
    When I press "Continue to next step"
      Then I should see "Review your order before continuing."
    # @todo: Open ticket to change last page button to "finish"
    When I press "Continue to next step"
      Then I should see "Checkout complete"

  @api
  Scenario: Add product to cart as an anonymous user, with checkout disabled.
    Given I am an anonymous user
      And anonymous checkout is disabled
    When I am viewing a "behat_product_display" and product of "product" with the title "Behat Product"
    Then I should see "Behat Product"
      And I press "Add to cart"
      Then I should see "Behat Product added to your cart."
    When I click "your cart"
      Then I should see the heading "Shopping cart"
      And I should see the link "Behat Product"
    When I go to "checkout"
      Then I should get a "403" HTTP response

