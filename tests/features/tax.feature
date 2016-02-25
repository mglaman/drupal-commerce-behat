Feature: Commerce Tax

  @api
  Scenario: Test createSalesTaxType
    Given the sales tax type:
      | name      | title     | display_title |
      | my_tax    | My tax    | My tax        |

  @api
  Scenario: Test createSalesTaxRate
     Given  "sales_tax" sales tax rate:
       | name      | title        | display_title    | rate |
       | wi_tax    | WI Sales tax | WI Sales tax     | 0.05 |

  @api
  Scenario: Normal user cannot administer taxes
    Given I am logged in as a user with the "authenticated" role
      And I am on "admin/commerce/config/taxes"
    Then I should get a "403" HTTP response

  @api
  Scenario: As an admin, I can administer taxes
    Given I am logged in as a user with the "administer taxes" permission
      And I am on "admin/commerce/config/taxes"
    Then I should get a "200" HTTP response
      And I should see the link "Add a tax rate"
    Given  "sales_tax" sales tax rate:
      | name      | title        | display_title    | rate |
      | wi_tax    | WI Sales tax | WI Sales tax     | 0.05 |
    When I reload the page
    Then I should see "WI Sales Tax"

  @api
  Scenario: Create a tax rate
    Given I am logged in as a user with the "administer taxes" permission
      And I am on "admin/commerce/config/taxes"
      Then I click "Add a tax rate"
      And I should be on "admin/commerce/config/taxes/rates/add"
    Then I should see the link "Cancel"
    When I fill in the following:
    | tax_rate[title]         | Example tax rate |
    | tax_rate[name]          | example_tax_rate |
    | tax_rate[display_title] | Taxes            |
    | tax_rate[description]   | Example for test |
    | tax_rate[rate]          | 0.055            |
    | tax_rate[type]          | sales_tax        |
    And I press "Save tax rate"
      Then I should be on "admin/commerce/config/taxes"
      And I should see "Example for test"

