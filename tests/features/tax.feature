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