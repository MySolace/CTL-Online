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
  $items['ctl_application_no_ssn'] = entity_import('rules_config', '{ "ctl_application_no_ssn" : {
      "LABEL" : "No SSN",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "account:field-has-ssn" ], "value" : "0" } }
      ],
      "DO" : [
        { "user_block" : { "account" : [ "account" ] } },
        { "drupal_message" : {
            "message" : "Unfortunately, we cannot accept volunteers without a us SSN. We need this to execute a proper background check.",
            "type" : "error"
          }
        },
        { "user_remove_role" : {
            "account" : [ "account" ],
            "roles" : { "value" : { "4" : "4", "3" : "3", "5" : "5", "6" : "6", "7" : "7" } }
          }
        }
      ]
    }
  }');
  $items['rules_application_on_save'] = entity_import('rules_config', '{ "rules_application_on_save" : {
      "LABEL" : "Application: redirect on save draft",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--application" : { "bundle" : "application" },
        "node_update--application" : { "bundle" : "application" }
      },
      "IF" : [ { "NOT node_is_published" : { "node" : [ "node" ] } } ],
      "DO" : [ { "redirect" : { "url" : "node\\/[node:nid]\\/edit" } } ]
    }
  }');
  $items['rules_application_on_submit'] = entity_import('rules_config', '{ "rules_application_on_submit" : {
      "LABEL" : "Application: On Submit",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
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
        { "data_set" : { "data" : [ "node:field-status" ], "value" : "1" } },
        { "redirect" : { "url" : "apply" } },
        { "drupal_message" : { "message" : "Your application has been submitted. You can use this page to check the status of your application and request the required references." } },
        { "mail" : {
            "to" : "[node:author:mail]",
            "subject" : "We\\u0027ve received your Crisis Text Line Volunteer Application",
            "message" : "[node:author:field_first_name],\\r\\n\\r\\nYour application has been received!\\r\\n\\r\\nWe will begin to review it once your references submit the forms they\\u0027ve been sent. If you need to, you can log in and send them another request at https:\\/\\/online.crisistextline.org\\/apply\\r\\n\\r\\nGood luck!\\r\\nThe CTL team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_first_draft_save'] = entity_import('rules_config', '{ "rules_first_draft_save" : {
      "LABEL" : "Application: First Draft Save",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--application" : { "bundle" : "application" } },
      "DO" : [
        { "mail" : {
            "to" : "[node:author:mail]",
            "subject" : "Thanks for starting your Crisis Text Line volunteer application",
            "message" : "[node:author:field_first_name],\\r\\n\\r\\nThanks for starting your CTL Volunteer application!\\r\\n\\r\\nYou can access you application at https:\\/\\/online.crisistextline.org\\/apply to complete your application or check your status.\\r\\n\\r\\nThis application also requires two references. You can find the form to request them via the link above.\\r\\n\\r\\nThanks,\\r\\nThe CTL team\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_mark_applied'] = entity_import('rules_config', '{ "rules_mark_applied" : {
      "LABEL" : "Mark Applied",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "views_bulk_operations", "rules" ],
      "ON" : { "cron" : [] },
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "completed_apps|default" },
            "PROVIDE" : { "entity_list" : { "users" : "Users" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "User" },
            "DO" : [
              { "user_remove_role" : { "account" : [ "user" ], "roles" : { "value" : { "5" : "5" } } } },
              { "user_add_role" : { "account" : [ "user" ], "roles" : { "value" : { "7" : "7" } } } },
              { "mail" : {
                  "to" : "[user:mail]",
                  "subject" : "Your Crisis Text Line application is now ready for review",
                  "message" : "[user:field_first_name],\\r\\n\\r\\nWe\\u0027ve received both of your references and will now begin to review your application. Because of the high number of applications we\\u0027re receiving, you\\u0027ll hear from us via email within the next few weeks. Sit tight! You can also check the status at https:\\/\\/online.crisistextline.org\\/apply.\\r\\n\\r\\nThanks,\\r\\nThe CTL Team",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_no_full_commitment'] = entity_import('rules_config', '{ "rules_no_full_commitment" : {
      "LABEL" : "No full commitment",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "list_count_is" : {
            "list" : [ "account:field-user-acceptance" ],
            "op" : "\\u003C",
            "value" : "3"
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[account:mail]",
            "subject" : "Your Crisis Text Line volunteer application",
            "message" : "[account:name],\\r\\n\\r\\nUnfortunately, we require all of our volunteers to have their own computer with a stable internet connection. Additionally, all volunteers must be willing to commit to 1 year of counseling.\\r\\n\\r\\nIf you acquire your own computer and are willing to commit to a year of volunteering, please visit: https:\\/\\/online.crisistextline.org\\/user\\/ and edit your profile indicating these items.\\r\\n\\r\\nThanks,\\r\\nBaylee at Crisis Text Line",
            "language" : [ "" ]
          }
        },
        { "drupal_message" : {
            "message" : "Unfortunately, we require all of our volunteers to have their own computer with a stable internet connection. Additionally, all volunteers must be willing to commit to 1 year of counseling.\\r\\n\\r\\nIf you change your mind, please come back to this site to indicate your new preferences on your account.",
            "type" : "error"
          }
        }
      ]
    }
  }');
  $items['rules_node_list_incomplete_part_2'] = entity_import('rules_config', '{ "rules_node_list_incomplete_part_2" : {
      "LABEL" : "Node list: Incomplete part 2",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "nodes" : { "label" : "Nodes", "type" : "list\\u003Cnode\\u003E" } },
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "nodes" ] },
            "ITEM" : { "node" : "node" },
            "DO" : [
              { "mail" : {
                  "to" : [ "node:author:mail" ],
                  "subject" : "Applications Due Tonight, [node:author:field_first_name] (11:59PM EST)!",
                  "message" : "Just checking in on you [node:author:field_first_name] - we have 10 spots left for the volunteer training. You\\u0027re important to us. Hope you can join!\\r\\n\\r\\nhttps:\\/\\/online.crisistextline.org\\/apply\\r\\n\\r\\nBaylee Greenberg\\r\\nDirector of Operations |  Crisis Text Line\\r\\n",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_node_list_missing_references'] = entity_import('rules_config', '{ "rules_node_list_missing_references" : {
      "LABEL" : "Node list: missing references",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "nodes" : { "label" : "Nodes", "type" : "list\\u003Cnode\\u003E" } },
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "nodes" ] },
            "ITEM" : { "node" : "node" },
            "DO" : [
              { "mail" : {
                  "to" : [ "node:author:mail" ],
                  "subject" : "Applications Due Tonight, [node:author:field_first_name] (11:59PM EST)!",
                  "message" : "Just checking in on you [node:author:field_first_name] - we have 10 spots left for the volunteer training. You\\u0027re important to us. Hope you can join!\\r\\n\\r\\nhttps:\\/\\/online.crisistextline.org\\/apply\\r\\n\\r\\nBaylee Greenberg\\r\\nDirector of Operations |  Crisis Text Line",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_part_1_disable'] = entity_import('rules_config', '{ "rules_part_1_disable" : {
      "LABEL" : "Part 1 disable",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "views_bulk_operations", "rules" ],
      "ON" : { "cron" : [] },
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "users_who_completed_part_2|attachment_2" },
            "PROVIDE" : { "entity_list" : { "users" : "Leads who completed part 1" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "Current user" },
            "DO" : [
              { "user_block" : { "account" : [ "user" ] } },
              { "mail" : {
                  "to" : "[user:mail]",
                  "subject" : "Your CTL Volunteer Application",
                  "message" : "[user:field_first_name],\\r\\n\\r\\nThanks for applying to be a CTL volunteer.\\r\\n\\r\\nUnfortunately, we cannot accept you at this time as you did not indicate that you can meet all the requirements of being a volunteer.\\r\\n\\r\\nIf you can fulfill these three requirements, email support@crisistextline.org:\\r\\n\\r\\n- You have a reliable internet connection\\r\\n- You have a computer than you can reliably use with Chrome or Firefox installed\\r\\n-\\u202fIf accepted, you commit to being a volunteer for one year, completing a weekly 4 hour shift\\r\\n\\r\\nThanks,\\r\\nThe CTL team",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_part_1_promotion'] = entity_import('rules_config', '{ "rules_part_1_promotion" : {
      "LABEL" : "Part 1 promotion",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "views_bulk_operations" ],
      "ON" : { "cron" : [] },
      "IF" : [
        { "data_is" : {
            "data" : [ "site:current-date" ],
            "op" : "\\u003C",
            "value" : 1426652880
          }
        }
      ],
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "users_who_completed_part_2|attachment_1" },
            "PROVIDE" : { "entity_list" : { "users" : "Leads who completed part 1" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "Current user" },
            "DO" : [
              { "user_remove_role" : { "account" : [ "user" ], "roles" : { "value" : { "6" : "6" } } } },
              { "user_add_role" : { "account" : [ "user" ], "roles" : { "value" : { "5" : "5" } } } },
              { "mail" : {
                  "to" : "[user:mail]",
                  "subject" : "Part One of your CTL Volunteer Application has been accepted!",
                  "message" : "[user:field_first_name],\\r\\n\\r\\nCongratulations!\\r\\n\\r\\nYou\\u0027ve been invited to complete Part Two of the volunteer application for Crisis Text Line.\\r\\n\\r\\nPlease set aside at least 1 hour to complete the application. You may also save your progress at any time and return to the application later. Remember - you\\u0027ll will need a webcam or smartphone to record a video of yourself.\\r\\n\\r\\nTo get started, visit: https:\\/\\/online.crisistextline.org\\/apply\\r\\n\\r\\nWe\\u0027re looking forward to reviewing your application!\\r\\nThe CTL team",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_redirect_on_login'] = entity_import('rules_config', '{ "rules_redirect_on_login" : {
      "LABEL" : "Redirect on login",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_login" : [] },
      "DO" : [ { "redirect" : { "url" : "[site:url]", "force" : "0" } } ]
    }
  }');
  $items['rules_reference_received'] = entity_import('rules_config', '{ "rules_reference_received" : {
      "LABEL" : "Reference Received",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--recommendation" : { "bundle" : "recommendation" } },
      "DO" : [
        { "mail" : {
            "to" : [ "node:field-reference:mail" ],
            "subject" : "CTL Reference Received",
            "message" : "[node:field-reference:field-first-name],\\r\\n\\r\\nThis email is to let you know your reference from [node:field_full_name] has been received.\\r\\n\\r\\nThanks,\\r\\nThe CTL team",
            "language" : [ "" ]
          }
        },
        { "redirect" : { "url" : "reference-received" } }
      ]
    }
  }');
  $items['rules_send_email_to_node_list'] = entity_import('rules_config', '{ "rules_send_email_to_node_list" : {
      "LABEL" : "Send email to node list",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "nodes" : { "label" : "Nodes", "type" : "list\\u003Cnode\\u003E" },
        "subject" : { "label" : "Subject", "type" : "text" },
        "message" : { "label" : "Message", "type" : "text" }
      },
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "nodes" ] },
            "ITEM" : { "node" : "node" },
            "DO" : [
              { "mail" : {
                  "to" : [ "node:author:mail" ],
                  "subject" : "Hey [node:author:field_first_name], [subject:value]",
                  "message" : [ "message" ],
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_send_email_to_user_list'] = entity_import('rules_config', '{ "rules_send_email_to_user_list" : {
      "LABEL" : "Send email to user list",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "users" : { "label" : "Users", "type" : "list\\u003Cuser\\u003E" },
        "subject" : { "label" : "Subject", "type" : "text" },
        "message" : { "label" : "Message", "type" : "text" }
      },
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "user" },
            "DO" : [
              { "mail" : {
                  "to" : [ "user:mail" ],
                  "subject" : "Hey [user:field_first_name], [subject:value]",
                  "message" : [ "message" ],
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_under_18'] = entity_import('rules_config', '{ "rules_under_18" : {
      "LABEL" : "Under 18: immediately disable account",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "data_is" : {
            "data" : [ "account:field-birthdate" ],
            "op" : "\\u003E",
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
        },
        { "mail" : {
            "to" : "[account:mail]",
            "subject" : "Volunteering with Crisis Text Line",
            "message" : "[account:name],\\r\\n\\r\\nThanks for your interest in volunteering with Crisis Text Line.\\r\\n\\r\\nUnfortunately, we cannot accept volunteers under the age of 18. We\\u0027ll be sure to reach out after your 18th birthday when you\\u0027re eligible.\\r\\n\\r\\nWarmly,\\r\\nBaylee from Crisis Text Line",
            "language" : [ "" ]
          }
        },
        { "user_remove_role" : {
            "account" : [ "account" ],
            "roles" : { "value" : { "4" : "4", "3" : "3", "5" : "5", "6" : "6", "7" : "7" } }
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
              },
              { "user_add_role" : { "account" : [ "user" ], "roles" : { "value" : { "6" : "6" } } } }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_user_list_haven_t_started_part_2'] = entity_import('rules_config', '{ "rules_user_list_haven_t_started_part_2" : {
      "LABEL" : "User list: Haven\\u0027t started part 2",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "users" : { "label" : "Users", "type" : "list\\u003Cuser\\u003E" } },
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "user" : "user" },
            "DO" : [
              { "mail" : {
                  "to" : [ "user:mail" ],
                  "subject" : "Applications Due Tonight, [user:field_first_name] (11:59PM EST)!",
                  "message" : "Just checking in on you [user:field_first_name] - we have 20 spots left for the volunteer training. You\\u0027re important to us. Hope you can join!\\r\\n\\r\\nhttps:\\/\\/online.crisistextline.org\\/apply\\r\\n\\r\\nBaylee Greenberg\\r\\nDirector of Operations |  Crisis Text Line",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_user_registered'] = entity_import('rules_config', '{ "rules_user_registered" : {
      "LABEL" : "User Registered",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "DO" : [
        { "redirect" : { "url" : "registered" } },
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } }
      ]
    }
  }');
  return $items;
}
