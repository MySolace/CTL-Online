<?php

function _ctl_onboarding_setup_teams($cohort_id) {
  // Gather the registrants for the cohort.
  $query = db_select('ctl_onboarding_registrant', 'r');
  $query->addField('r', 'uid');
  $query->addField('r', 'slot_code');
  $query->addField('r', 'status');
  $result = $query
    ->condition('r.cohort_id', $cohort_id)
    ->execute()
    ->fetchAll();

  if (empty($result)) {
    return;
  }

  // From the registrats' info we can determine what teams need to be created.




  // find if teams exist

  // if they do delete them

  // create new teams


  $node = _ctl_onboarding_create_team_node($cohort_id, $slot_code);

  dsm($node);


  // $user = user_load(3);

  // // http://zbozien.co.uk/blog/2015/02/28/drupal-add-user-to-og-group-and-delete-from-group-membership/

  // // Add the user to the group.
  // og_group('node', $node->nid, array(
  //   'entity type'     => 'user',
  //   'entity'          => $user,
  //   'membership type' => OG_MEMBERSHIP_TYPE_DEFAULT,
  // ));



  // calculate user/team number balance

  // shuffle users

  // distribute users into teams

  foreach ($result as $registrant) {
    $status = intval($registrant->status);
    // TODO
    // - handle more statuses
    if ($status === CTL_ONBOARDING_STATUS_ACCEPTED) {
      // dsm($registrant->uid);

      // add user to team
    }
  }

  // foreach ($slots as $key => $slot_code) {
  //   if ($slot_code) {
  //     // $query = db_select('ctl_onboarding_slot', 'r');
  //     // $query->addField('r', 'cohort_id');
  //     // $query->addField('r', 'slot_code');
  //     // $query->addField('r', 'num_trainers');
  //     // $query->addField('r', 'num_registrants');
  //     // $result = $query
  //     //   ->condition('s.cohort_id', $cohort_id)
  //     //   ->condition('s.slot_code', $slot_code)
  //     //   ->execute()
  //     //   ->fetchAll();
  //   }
  // }
}


function _ctl_onboarding_create_team_node($cohort_id, $slot_code) {
  $node           = new stdClass();
  $node->type     = 'training_team';
  $node->language = LANGUAGE_NONE;

  node_object_prepare($node);

  $node->title = "Training Team:  Cohort $cohort_id - Slot $slot_code";

  $team_description = 'Training Team';
  $node->body[$node->language][0]['value']   = $team_description;
  $node->body[$node->language][0]['summary'] = text_summary($team_description);
  $node->body[$node->language][0]['format']  = 'full_html';

  $node->comment = COMMENT_NODE_HIDDEN;
  $node->created = time();
  $node->path    = array('alias' => "training-team/$cohort_id/$slot_code");
  $node->promote = NODE_NOT_PROMOTED;
  $node->status  = NODE_PUBLISHED;
  $node->sticky  = NODE_NOT_STICKY;

  // Make the superuser is the author of our node.
  $node->uid = 1;

  node_save($node);

  return $node;
}
