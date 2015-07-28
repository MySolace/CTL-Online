<?php
/**
 * @file
 * application_v2.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function application_v2_default_rules_configuration() {
  $items = array();
  $items['rules_app_v2_submitted'] = entity_import('rules_config', '{ "rules_app_v2_submitted" : {
      "LABEL" : "app v2 submitted",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "appv2" ],
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--application" : { "bundle" : "application" },
        "node_update--application" : { "bundle" : "application" }
      },
      "IF" : [
        { "node_is_published" : { "node" : [ "node" ] } },
        { "data_is" : { "data" : [ "site:current-user:uid" ], "value" : [ "node:author:uid" ] } }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "node:author" ], "roles" : { "value" : { "4" : "4" } } } },
        { "user_remove_role" : {
            "account" : [ "node:author" ],
            "roles" : { "value" : { "3" : "3", "5" : "5" } }
          }
        },
        { "redirect" : { "url" : "apply" } },
        { "mail" : {
            "to" : [ "node:author:mail" ],
            "subject" : "Your Application has been Submitted",
            "message" : "[site:current-user:field-first-name],\\r\\n\\r\\nChris Johnson [12:55 PM]\\r\\nThank you for submitting your application! In order to complete your application, you will need to provide contact information for two references. Please navigate to https:\\/\\/online.crisistextline.org\\/apply and click on the \\u0022Request a reference\\u0022 link to fill in the reference form two times.\\r\\n\\r\\nYour references will receive an automated email asking them to complete a form. You can check back there to see when their forms have been submitted.\\r\\n\\r\\nDates to remember:   \\r\\n-Final applications with references are due August 4th\\r\\n-We\\u2019ll let you know if you were accepted by August 11th\\r\\n-You\\u2019ll begin training on August 18th\\r\\n\\r\\nQuestions? Email us: volunteer@crisistextline.org\\r\\n\\r\\nBest, \\r\\nShannon \\u0026 the Crisis Text Line Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
