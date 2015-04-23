; Contrib modules, themes and libraries

api = 2
core = 7.x

defaults[projects][subdir] = "contrib"

; Theme
projects[adminimal_theme][version] = "1.20"

; Libraries
libraries[mandrill][download][type] = "get"
libraries[mandrill][download][url] = "https://bitbucket.org/mailchimp/mandrill-api-php/get/1.0.54.zip"
libraries[mandrill][directory_name] = "mandrill"

libraries[twilio][download][type] = "get"
libraries[twilio][download][url] = "https://github.com/twilio/twilio-php/archive/master.zip"
libraries[twilio][directory_name] = "twilio"

; Modules
projects[addressfield][version] = "1.0"
projects[admin_menu][version] = "3.0-rc5"
projects[auto_nodetitle][version] = "1.0"
projects[better_exposed_filters][version] = "3.0"
projects[computed_field][version] = "1.0"
projects[conditional_fields][version] = "3.0-alpha1"
projects[ctools][version] = "1.7"
projects[course][version] = "1.4"
projects[course_relationships][version] = "1.x-dev"
projects[date][version] = "2.8"
projects[editablefields][version] = "1.0-alpha2"
projects[email][version] = "1.3"
projects[email_registration][version] = "1.2"
projects[entity][version] = "1.6"
projects[entityreference][version] = "1.1"
projects[entityreference_prepopulate][version] = "1.5"
projects[features][version] = "2.5"
projects[field_formatter_class][version] = "1.1"
projects[field_formatter_settings][version] = "1.1"
projects[field_group][version] = "1.4"
projects[field_group_ajaxified_multipage][version] = "1.0-beta2"
projects[field_permissions][version] = "1.0-beta2"
projects[filefield_nginx_progress][version] = "2.3"
projects[inline_registration][version] = "1.0"
projects[libraries][version] = "2.2"
projects[mailcontrol][version] = "1.0"
projects[mailsystem][version] = "2.34"
projects[mandrill][version] = "2.1"
projects[module_filter][version] = "2.0"
projects[multipage_jumplist][version] = "1.0-alpha1"
projects[multiple_fields_remove_button][version] = "1.4"
projects[node_limit][version] = "1.0-alpha5"
projects[no_trimmed_preview][version] = "1.0"
projects[privatemsg][version] = "1.4"
projects[quiz][version] = "5.0-alpha9"
projects[realname][version] = "1.2"
projects[redirect][version] = "1.0-rc1"

projects[rules][version] = "2.9"
projects[rules][patch][] = https://www.drupal.org/files/rules-site-property-metadata-fix-1423234-15.patch

projects[rules_conditional][version] = "1.0-beta2"
projects[token][version] = "1.6"
projects[twilio][version] = "1.10"
projects[uuid][version] = "1.0-alpha6"
projects[video][version] = "2.11"
projects[views][version] = "3.10"
projects[views][patch][] = https://www.drupal.org/files/issues/views-data-cache-rebuild-1944674-42.patch
projects[views_bulk_operations][version] = "3.2"
projects[views_field_view][version] = "1.x-dev"
projects[views_fieldsets][version] = "1.3"
projects[views_data_export][version] = "3.0-beta8"
projects[views_role_based_global_text][version] = "1.1"
projects[webform][version] = "4.7"
projects[webform_validation][version] = "1.9"


