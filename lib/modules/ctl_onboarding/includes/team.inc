<?php

function _ctl_onboarding_create_teams($cohort_id) {

  // find if teams exist

  // if they do delete them

  // create new teams

  $query = db_select('ctl_onboarding_registrant', 'r');
  $query->addField('r', 'uid');
  $query->addField('r', 'slot_code');
  $query->addField('r', 'status');
  $result = $query
    ->condition('r.cohort_id', $cohort_id)
    ->execute()
    ->fetchAll();

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
  //     // $query->addField('r', 'max_trainers');
  //     // $query->addField('r', 'num_registrants');
  //     // $result = $query
  //     //   ->condition('s.cohort_id', $cohort_id)
  //     //   ->condition('s.slot_code', $slot_code)
  //     //   ->execute()
  //     //   ->fetchAll();
  //   }
  // }

  return;








  $team_description = 'Training Team';

  $node           = new stdClass();
  $node->type     = 'training_team';
  $node->language = LANGUAGE_NONE;

  node_object_prepare($node);

  $node->title = "Training Team - $cohort_id";

  $node->body[$node->language][0]['value']   = $team_description;
  $node->body[$node->language][0]['summary'] = text_summary($team_description);
  $node->body[$node->language][0]['format']  = 'full_html';

  $node->status  = NODE_PUBLISHED;
  $node->promote = NODE_NOT_PROMOTED;
  $node->sticky  = NODE_NOT_STICKY;
  $node->comment = COMMENT_NODE_HIDDEN;

  // Make the superuser the author of our node.
  $node->uid = 1;

  $node->created = time();

  $path       = "training-team/$cohort_id/";
  $node->path = array('alias' => $path);

  node_save($node);

  dsm($node);





  // // http://knackforge.com/blog/vishnu/programmatically-create-node-drupal-7

  // $complaint_body = 'Your node complaint body text';

  // $node = new stdClass();
  // $node->type = 'training_team';
  // $node->language = LANGUAGE_NONE;
  // node_object_prepare($node);

  // $node->title = 'Your node title';

  // $node->body[$node->language][0]['value']   = $complaint_body;
  // $node->body[$node->language][0]['summary'] = text_summary($complaint_body);
  // $node->body[$node->language][0]['format']  = 'full_html';

  // $node->status  = NODE_PUBLISHED;
  // $node->promote = NODE_NOT_PROMOTED;
  // $node->sticky  = NODE_NOT_STICKY;
  // $node->comment = COMMENT_NODE_HIDDEN;

  // // Add author of the node
  // $node->uid = 1;

  // // Set created date
  // $node->date    = 'complaint_post_date';
  // $node->created = strtotime('complaint_post_date');

  // $path       = 'content/mytest-' . date('YmdHis');
  // $node->path = array('alias' => $path);

  // node_save($node);


  // $node->field_complaint_address[LANGUAGE_NONE][0]['value'] = 'This is custom cck filed to get complaint address';




  // $node = node_load(2);

  // $user = user_load(3);

  // // http://zbozien.co.uk/blog/2015/02/28/drupal-add-user-to-og-group-and-delete-from-group-membership/

  // // Add the user to the group.
  // og_group('node', $node->nid, array(
  //   'entity type'     => 'user',
  //   'entity'          => $user,
  //   'membership type' => OG_MEMBERSHIP_TYPE_DEFAULT,
  // ));
}
