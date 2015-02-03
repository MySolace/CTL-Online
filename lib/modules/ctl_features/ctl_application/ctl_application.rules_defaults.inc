<?php
/**
 * @file
 * ctl_application.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ctl_application_default_rules_configuration() {
  $items = array();
  $items['rules_under_18'] = entity_import('rules_config', '{ "rules_under_18" : {
      "LABEL" : "Under 18",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "data_is" : {
            "data" : [ "account:field-birthdate" ],
            "op" : "\\u003C",
            "value" : "-18 years"
          }
        }
      ],
      "DO" : [
        { "user_block" : { "account" : [ "account" ] } },
        { "drupal_message" : {
            "message" : "Unfortunately, we do not accept volunteers under the age of 18. We have your information, though, and will get in touch when you turn 18!",
            "type" : "error"
          }
        }
      ]
    }
  }');
  $items['rules_update_under_18s'] = entity_import('rules_config', '{ "rules_update_under_18s" : {
      "LABEL" : "Update Under 18s",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "views_bulk_operations", "rules" ],
      "ON" : { "cron" : [] },
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "users_over_18|default" },
            "PROVIDE" : { "entity_list" : { "users" : "Users" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "Current User" },
            "DO" : [
              { "user_unblock" : { "account" : [ "user" ] } },
              { "mail" : {
                  "to" : "[user:mail]",
                  "subject" : "Apply to be a Crisis Text Line volunteer.",
                  "message" : "It looks like you\\u0027re now old enough to apply to be a Crisis Text Line volunteer. Head on over to http:\\/\\/online.crisistextline.org\\/apply to apply now!",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
