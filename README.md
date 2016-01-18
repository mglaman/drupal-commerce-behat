# Drupal Commerce Behat Extension [![Build Status](https://travis-ci.org/mglaman/drupal-commerce-behat.svg?branch=master)](https://travis-ci.org/mglaman/drupal-commerce-behat)

Integrates with Behat Drupal Extension for Drupal Commerce support.

## Using the provided contexts

The simplest way to incorporate the provided contexts is to add the *tests/steps* directory to your *behat.yml* configuration.

The following will load all the contexts and steps provided by this module for use in your features.

````
Drupal\DrupalExtension:
  subcontexts:
    paths:
      - "/path/to/drupal/sites/all/modules/commerce_behat/tests/steps"
````
