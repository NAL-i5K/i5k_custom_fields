<?php
/**
 * @class
 * Purpose:
 *
 * Display:
 * Configuration:
 */
class local__parent_analysis_pub_formatter extends ChadoFieldFormatter {

  // The default label for this field.
  public static $default_label = 'Publication';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('local__parent_analysis_pub');

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
    $field = 'local__parent_analysis_pub';

    // TODO: do this the proper Tripal way. We'll need the Entity ID of the
    //  associated Publication, something that seems somewhat elusive.
    //  At least try not to hardcode the /Publication/ part...

    $element[] = [
      '#type' => 'markup',
      '#markup' => l($items[0]['value']['TPUB:0000039'],'/Publication/' . $items[0]['value']['entity_id']),
    ];
  }

    /**
    * @see ChadoFieldFormatter::settingsSummary()
    *
    **/

  public function settingsSummary($view_mode) {
    return '';
  }

}