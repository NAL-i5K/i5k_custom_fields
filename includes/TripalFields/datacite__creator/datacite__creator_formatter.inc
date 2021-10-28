<?php
/**
 * @class
 * Purpose:
 *
 * Display:
 * Configuration:
 */
class datacite__creator_formatter extends ChadoFieldFormatter {

  // The default label for this field.
  public static $default_label = 'Analysis Authors';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('datacite__creator');

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
    // Test for data
    if ( !$items[0]['value'] == '') {
      $delta = 0;
      while(array_key_exists($delta,$items)) {
        $element[$delta] = [
          '#type' => 'markup',
          '#markup' => l($items[$delta]['value']['schema__name'],'/contact/' . $items[$delta]['value']['entity_id']),
        ];
        $delta++; 
      }
    }
  }

    /**
    * @see ChadoFieldFormatter::settingsSummary()
    *
    **/

  public function settingsSummary($view_mode) {
    return '';
  }

}