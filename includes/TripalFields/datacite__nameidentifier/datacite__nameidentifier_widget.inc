<?php
/**
 * @class
 * Purpose:
 *
 * Allowing edit?
 * Data:
 * Assumptions:
 */
class datacite__nameidentifier_widget extends ChadoFieldWidget {

  // The default label for this field.
  public static $default_label = 'Contact Identifier';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('datacite__nameidentifier');


 /**
  * @see ChadoFieldWidget::form()
  *
  **/

  public function form(&$widget, &$form, &$form_state, $langcode, $items, $delta, $element) {
    parent::form($widget, $form, $form_state, $langcode, $items, $delta, $element);

    $field_name = $this->field['field_name'];
    $base_table = 'db';
    $field_table = 'dbxref';
    $schema = chado_get_schema($field_table);
    //dpm($schema);
    $pkey = $schema['primary key'][0];
    $fkey_lcolumn = key($schema['foreign keys'][$base_table]['columns']);

    $fkey_rcolumn = $schema['foreign keys'][$base_table]['columns'][$fkey_lcolumn];
    // Get the field defaults
    $record_id = '';
    $fk_value = $element['#entity'] ? $element['#entity']->chado_record_id : '';
    // Set some empty defaults
    $accession = '';
    $db_id = '';
    $dbxref_id = '';


    // If the field already has a value then it will come through the $items
    // array. This happens when editing an existing record.
    // @todo what is the third thing here trying to do? $items[$delta]['value'] is an array...
    if (count($items) > 0 and array_key_exists($delta, $items) and strlen($items[$delta]['value'] > 0)) {
      /**
       * values we expect here:
       *  - accession
       *  - database (name)
       *  - urlprefix
       *  - url
       *  - db_id
       */
      //$fk_value = $items[$delta]['value']['contact_id'];
      //$record_id = $items[$delta]['value']['contact_dbxref_id'];
      //$contact_id = $items[$delta]['value']['contact_id'];

      // Other useful values
      $accession = $items[$delta]['value']['accession'];
      $db_id = $items[$delta]['value']['db_id'];
      $dbxref_id = $items[$delta]['value']['dbxref_id'];
    }

    // Check $form_state['values'] to see if an AJAX call set the values.
    if (array_key_exists('values', $form_state) AND array_key_exists($field_name, $form_state['values'])) {
      $accession    = $form_state['values'][$field_name]['und'][$delta]['accession'];
      $db_id        = $form_state['values'][$field_name]['und'][$delta]['db_id'];
      $dbxref_id    = $form_state['values'][$field_name]['und'][$delta]['dbxref_id'];
    }

    // We have all the values we need, so we can build the form.
    $widget['value'] = [
      '#type' => 'value',
      '#value' => array_key_exists($delta, $items) ? $items[$delta]['value'] : '',
    ];

    // Evaluates to 'chado-dbxref__dbxref_id'
    /* $widget['chado-' . $field_table . '__' . $pkey] = [
      '#type' => 'value',
      '#default_value' => $fk_value,
    ]; */

    // Evaluates to 'chado-dbxref__db_id
    $widget['chado-' . $field_table . '__' . $fkey_lcolumn] = [
      '#type' => 'value',
      '#default_value' => $fk_value,
      // Disable for now since it doesn't work
      '#disabled' => TRUE,
    ];

    $widget['dbxref_id'] = [
      '#type' => 'value',
      '#default_value' => $dbxref_id,
    ];
    
    $options = chado_get_db_select_options();
    $widget['db_id'] = [
      '#type' => 'select',
      '#title' => t('Database'),
      '#options' => $options,
      '#required' => $element['#required'],
      '#prefix' => t('These fields are currently disabled as the functionality does not exist yet. Please manually enter values in the database (dbxref followed by dbxref_contact).'),
      '#default_value' => $db_id,
      '#ajax' => [
        'callback' => "datacite__nameidentifier_widget_form_ajax_callback",
        'wrapper' => "$field_name-dbxref--db-id-$delta",
        'effect' => 'fade',
        'method' => 'replace',
      ],
      // Disable for now since it doesn't work
      '#disabled' => TRUE,
    ];

    $schema = chado_get_schema('dbxref');
    $widget['accession'] = [
      '#type' => 'textfield',
      '#title' => t('Accession'),
      '#default_value' => $accession,
      '#required' => $element['#required'],
      '#maxlength' => array_key_exists('length', $schema['fields']['accession']) ? $schema['fields']['accession']['length'] : 255,
      '#size' => 15,
      // Disable for now since it doesn't work
      '#disabled' => TRUE,
    ];
  }

  /**
  * @see ChadoFieldWidget::validate()
  *
  **/
  public function validate($element, $form, &$form_state, $langcode, $delta) {
    $field_name = $this->field['field_name'];
    $base_table = 'db';
    $field_table = 'dbxref';

    $schema = chado_get_schema($field_table);
    $lfkey_field = key($schema['foreign keys'][$base_table]['columns']);
    // Get the database id from the form state
    $db_id = $form_state['values'][$field_name]['und'][$delta]['db_id'];
    //error_log("db_id for " . $delta . ": " . $db_id . "\n", 3, "/tmp/php_debug.log");
    $accession = $form_state['values'][$field_name]['und'][$delta]['accession'];
    // If no database is selected, we should set the field for deletion.
    if ($db_id == 0) {
      $form_state['values'][$field_name]['und'][$delta]['chado-contact_dbxref__contact_dbxref_id'] = '';
      $form_state['values'][$field_name]['und'][$delta]['chado-contact_dbxref__contact_id'] = '';

      $form_state['values'][$field_name]['und'][$delta]['accession'] = '';
      $form_state['values'][$field_name]['und'][$delta]['db_id'] = '';
    }
    else {
      $form_state['values'][$field_name]['und'][$delta]['value'] = 'cannot be empty';
      $form_state['values'][$field_name]['und'][$delta]['chado-dbxref__accession'] = $accession;
      $form_state['values'][$field_name]['und'][$delta]['chado-dbxref__db_id'] = $db_id;
    }
  }

  /**
  * @see ChadoFieldWidget::submit()
  *
  **/
  public function submit($form, &$form_state, $entity_type, $entity, $langcode, $delta) {
    /* $field_name = $this->field['field_name'];
    //$field_table = $this->instance['settings']['chado_table'];
    $field_table = 'contact_dbxref';

    $dbxref_id = $form_state['values'][$field_name]['und'][$delta]['dbxref_id'];
    $db_id = $form_state['values'][$field_name]['und'][$delta]['db_id'];
    $accession = $form_state['values'][$field_name]['und'][$delta]['accession'];
    //error_log($dbxref_id . "=" . $db_id . ": " . $accession . "\n", 3, "/tmp/php_debug.log");
    //dpm($form_state);
    if ($db_id and $dbxref_id) {
      // Update within the dbxref table
      $dbxref = chado_insert_dbxref([
        'db_id' => $db_id,
        'accession' => $accession,
      ]);
      // Update within the contact_dbxref table
      $values_ins = array(
        'contact_id' => $form_state['values'][$field_name]['und'][$delta]['chado-contact_dbxref__contact_id'],
        'dbxref_id' => $dbxref->dbxref_id,
        'is_current' => '1',
      );
      //dpm($values);
      $contact_dbxref = chado_insert_record(
        'contact_dbxref',
        $values_ins,
      );
      $form_state['values'][$field_name]['und'][$delta]['chado-' . $field_table . '__dbxref_id'] = $dbxref->dbxref_id;
      $form_state['values'][$field_name]['und'][$delta]['accession'] = $accession;
      $form_state['values'][$field_name]['und'][$delta]['urlprefix'] = '';
      $form_state['values'][$field_name]['und'][$delta]['url'] = '';
    } */
  }

}

/**
 * An ajax callback for the dbxref widget
 */
function datacite__nameidentifier_widget_form_ajax_callback($form, $form_state) {
  // Get the triggering element
  $form_element_name = $form_state['triggering_element']['#name'];
  preg_match('/(.+?)\[(.+?)\]\[(.+?)\]/', $form_element_name, $matches);
  $field = $matches[1];
  $lang = $matches[2];
  $delta = $matches[3];

  // Return the widget that triggered the AJAX call
  if (isset($form[$field][$lang][$delta])) {
    return $form[$field][$lang][$delta];
  }
  // Alternatively, return the default value widget for the widget setting form
  else {
    return $form['instance']['default_value_widget'][$field];
  }
}