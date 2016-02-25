#!/bin/bash

set -e $DRUPAL_TI_DEBUG

# Ensure the right Drupal version is installed.
# Note: This function is re-entrant.
drupal_ti_ensure_drupal

# Add custom modules to drupal build.
cd "$DRUPAL_TI_DRUPAL_DIR"

drupal_ti_ensure_module_linked

drush --yes dl commerce rules entity views
drush --yes en commerce_cart commerce_checkout commerce_order_ui commerce_product_ui commerce_customer_ui commerce_tax_ui
drush --yes en "$DRUPAL_TI_MODULE_NAME"
