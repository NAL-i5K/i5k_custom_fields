<?php
/**
 * @class
 * Purpose:
 *
 * Allowing edit?
 * Data:
 * Assumptions:
 */
class datacite__creator_widget extends ChadoFieldWidget {

  // The default label for this field.
  public static $default_label = 'Analysis Authors';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('datacite__creator');


 /**
  * @see ChadoFieldWidget::form()
  *
  **/

  public function form(&$widget, &$form, &$form_state, $langcode, $items, $delta, $element) {
    parent::form($widget, $form, $form_state, $langcode, $items, $delta, $element);

    $field_name = $this->field['field_name'];
    $base_table = 'analysis';
    $field_table = 'analysis_author';
    $schema = chado_get_schema($field_table);

    $pkey = $schema['primary key'][0];
    $fkey_lcolumn = key($schema['foreign keys'][$base_table]['columns']);
    //    $fkey_lcolumn = key($schema['foreign keys']['protocol']['columns']);

    $fkey_rcolumn = $schema['foreign keys'][$base_table]['columns'][$fkey_lcolumn];

    // Get the field defaults
    $record_id = '';
    $fk_value = (array_key_exists('#entity', $element) and $element['#entity']) ? $element['#entity']->chado_record_id : NULL;
    $contact_id = '';
    $name = '';

    $name_term = 'schema__name';

    // If the field already has a value then it will come through the $items
    // array.  This happens when editing an existing record.
    echo "got here<br />";
    dpm($items);
    if (count($items) > 0 and array_key_exists($delta, $items) and strlen($items[$delta]['value'] > 0)) {
      echo "Delta: " . $delta . "<br />";
      $name = array_key_exists($name_term, $items[$delta]['value']) ? $items[$delta]['value'][$name_term] : $name;
      /*
      $fk_value = tripal_get_field_item_keyval($items, $delta, 'chado-' . $field_table . '__' . $fkey_lcolumn, $fk_value);
      $record_id = tripal_get_field_item_keyval($items, $delta, 'chado-' . $field_table . '__' . $pkey, $record_id);
      $contact_id = tripal_get_field_item_keyval($items, $delta, 'chado-' . $field_table . '__contact_id', $contact_id);
      */
      // Manually do these I guess
      $fk_value = $items[$delta]['value']['analysis_id'];
      $record_id = $items[$delta]['value']['analysis_author_id'];
      $author_id = $items[$delta]['value']['author_id'];
    }

    // Check $form_state['values'] to see if an AJAX call set the values.
    if (array_key_exists('values', $form_state) and
      array_key_exists($field_name, $form_state['values'])) {
      $name = $form_state['values'][$field_name]['und'][$delta]['name'];
    }

    $schema = chado_get_schema('contact');

    $widget['value'] = [
      '#type' => 'value',
      '#value' => array_key_exists($delta, $items) ? $items[$delta]['value'] : '',
    ];

    $widget['chado-' . $field_table . '__' . $pkey] = [
      '#type' => 'value',
      '#default_value' => $record_id,
    ];
    $widget['chado-' . $field_table . '__' . $fkey_lcolumn] = [
      '#type' => 'value',
      '#default_value' => $fk_value,
    ];
    $widget['chado-' . $field_table . '__author_id'] = [
      '#type' => 'value',
      '#default_value' => $author_id,
    ];

    $widget['name'] = [
      '#type' => 'textfield',
      '#title' => t('Author(s)'),
      '#default_value' => $name,
      '#autocomplete_path' => 'admin/tripal/storage/chado/auto_name/contact',
      '#maxlength' => 100000,
    ];
  }

  /**
  * @see ChadoFieldWidget::validate()
  *
  **/
  public function validate($element, $form, &$form_state, $langcode, $delta) {
  }

   /**
  * @see ChadoFieldWidget::submit()
  *
  **/
  public function submit($form, &$form_state, $entity_type, $entity, $langcode, $delta) {
  }

}