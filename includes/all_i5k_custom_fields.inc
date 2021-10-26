<?php
/**
 * This is where all of the custom fields will be initially loaded from.
 * The two functions below are generic and based on the module name. Within,
 * we have to reference all of the custom fields via their
 * [field_name].fields.inc file. 
 * 
 * Only this file should be included in the main .module file.
 * 
 * Each function is expected to call the 
 * [field_name]_bundle_fields_info()
 * and
 * [field_name]_bundle_instances_info()
 * functions, with a slight modification - The arguments passed
 * will now include the arrays that are expected from these functions
 * as pointers.
 * For example,
 * field_name_bundle_fields_info($entity_type, $bundle) {}
 * would become
 * field_name_bundle_fields_info($entity_type, $bundle, &$fields) {}
 */
// Include the necessary field files
include('local__parent_analysis_pub.inc');
include('analysis_contact.fields.inc');
include('analysis_author.fields.inc');

function i5k_custom_fields_bundle_fields_info($entity_type, $bundle) {
    $fields = array();

    // Parent Analysis Publication
    local__parent_analysis_pub_bundle_fields_info($entity_type, $bundle, $fields);
    
    // Analysis Contact
    analysis_contact_bundle_fields_info($entity_type, $bundle, $fields);

    // Analysis Author
    analysis_author_bundle_fields_info($entity_type, $bundle, $fields);

    return $fields;
}

function i5k_custom_fields_bundle_instances_info($entity_type, $bundle) {
    $instances = array();

    // Parent Analysis Publication
    //include('local__parent_analysis_pub.inc');
    local__parent_analysis_pub_bundle_instances_info($entity_type,$bundle, $instances);

    // Analysis Contact
    //include('analysis_contact.fields.inc');
    analysis_contact_bundle_instances_info($entity_type, $bundle, $instances);

    // Analysis Author
    analysis_author_bundle_instances_info($entity_type, $bundle, $instances);

    return $instances;
}