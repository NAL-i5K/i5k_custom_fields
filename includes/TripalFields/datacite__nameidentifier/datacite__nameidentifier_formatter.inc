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
    // Test for data
    if ( !$items[0]['value'] == '') {
      $delta = 0;
      while(array_key_exists($delta,$items)) {
        $urlprefix = $items[$delta]['value']['urlprefix'];
        $url = $items[$delta]['value']['url'];
        // Craft the final URL
        $final_url = preg_replace('/\{accession\}/', $items[$delta]['value']['accession'], $urlprefix, -1, $acc_count);

        $element[$delta] = [
          '#type' => 'markup',
          '#markup' => l($items[$delta]['value']['database'] .
                        ': ' . $items[$delta]['value']['accession']    ,$final_url),
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