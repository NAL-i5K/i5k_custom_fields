<?php
/**
 * @class
 * Purpose:
 *
 * Display:
 * Configuration:
 */
class datacite__nameidentifier_formatter extends ChadoFieldFormatter {

  // The default label for this field.
  public static $default_label = 'Contact Identifier';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('datacite__nameidentifier');

  // The list of default settings for this formatter.
  public static $default_settings = array(
    'setting1' => 'default_value',
  );

   /**
    * @see ChadoFieldFormatter::settingsForm()
    *
    **/

  public function settingsForm($view_mode, $form, &$form_state) {

  }

    /**
    * @see ChadoFieldFormatter::View()
    *
    **/

  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {

    // Get the settings
    $settings = $display['settings'];
  }

    /**
    * @see ChadoFieldFormatter::settingsSummary()
    *
    **/

  public function settingsSummary($view_mode) {
    return '';
  }

}