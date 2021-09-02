# i5k Custom Fields

This module is designed to provide a number of custom fields for various content types on Tripal i5k websites.

Currently, the following fields are provided:
 - [ ] Parent publication for gene/mRNA
   - On gene and mRNA pages, any publications tied to the originating analysis will be shown.
 - [ ] Polypeptide Annotations
   - On mRNA pages, related polypeptide annotations will be shown.

# Installation
1. Enable this module like any other Drupal module, either:
    ```shell
    drush pm-enable i5k_custom_fields
    ```
    or visit the Modules page of your Drupal site and enable from there.
2. Navigate to `admin/structure/bio_data` (In the menu: Structure > Tripal Content Types)
3. For each content type that may have new fields, perform the following:
    a. Click 'Manage Fields'
    b. At the top of the Manage Fields page, click "+ Check for new fields". Tripal will work its magic and find any fields added by this module.
    c. Click on the 'Manage Display' tab at the top.
    d. The new fields should be listed on this page. Use the UI to drag the fields to where you want them to appear in your page.