<?php

function _ctl_onboarding_setup_teams($cohort_id) {
  // Gather the registrants for the cohort.
  $query = db_select('ctl_onboarding_registrant', 'r');
  $query->addField('r', 'uid');
  $query->addField('r', 'slot_code');
  $query->addField('r', 'status');
  $registrants = $query
    ->condition('r.cohort_id', $cohort_id)
    ->execute()
    ->fetchAll();

  if (empty($registrants)) {
    return;
  }

  // Gather the time slots for the cohort.
  $query = db_select('ctl_onboarding_slot', 's');
  $query->addField('s', 'slot_code');
  $query->addField('s', 'num_trainers');
  $query->addField('s', 'num_registrants');
  $slots = $query
    ->condition('s.cohort_id', $cohort_id)
    ->execute()
    ->fetchAll();

  if (empty($slots)) {
    return;
  }

  shuffle($registrants);

  // From the registrats' info we can determine what teams need to be created.
  $slot_info = array();
  foreach ($registrants as $registrant) {
    $slot_code = $registrant->slot_code;

    // Setup time slot info if it doesn't exist yet.
    if (!isset($slot_info[$slot_code])) {
      foreach ($slots as $slot) {
        if ($slot->slot_code === $slot_code) {
          break;
        }
      }

      dsm('$slot');
      dsm($slot);

      // Determine how trainees should be spread across teams.
      $num_trainers          = $slot->num_trainers;
      $num_registrants       = $slot->num_registrants;
      $max_trainees_per_team = intval(ceil($num_registrants / $num_trainers));
      $slot_info[$slot_code] = array(
        'num_trainers'          => $num_trainers,
        'max_trainees_per_team' => $max_trainees_per_team,
        'cur_team'              => 0,
        'teams'                 => array(),
      );
    }

    $info     = $slot_info[$slot_code];
    $cur_team = $info['teams'][$info['cur_team']];
    if (empty($cur_team)) {

    }
    else if (count($cur_team) >= $info['max_trainees_per_team']) {

    }

    // $slot_info[$slot_code]['teams'][$cur_team][trainee];

    // Distribute users into the new teams.

    $status = intval($registrant->status);

    // TODO
    // - when the time is right account for different statuses

    // Add accepted the users to the team.
    if ($status === CTL_ONBOARDING_STATUS_ACCEPTED) {

      // $slot_code = $registrant->slot_code;


    }
  }




  // dsm($slots);

  foreach ($slots as $slot) {
    $slot_code       = $slot->slot_code;


    // calculate user/team number balance





    // Delete previously existing teams.  This ensures that team
    // rosters are up to date with what registrants we have.




    // Create new teams.

    for ($i = 0, $l = count($num_trainers); $i < $l; ++$i) {

      $node = _ctl_onboarding_create_team_node($cohort_id, $slot_code, $i + 1);

      // for () {
      //   _ctl_onboarding_add_team_member($node->nid, $registrant->uid);
      // }

    }


  }
}


function _ctl_onboarding_create_team_node($cohort_id, $slot_code, $team_number) {
  $node           = new stdClass();
  $node->type     = 'training_team';
  $node->language = LANGUAGE_NONE;

  node_object_prepare($node);

  $node->title = "Training Team:  Cohort $cohort_id - Slot $slot_code";

  $team_description = 'Training Team';
  $node->body[LANGUAGE_NONE][0]['value']   = $team_description;
  $node->body[LANGUAGE_NONE][0]['summary'] = text_summary($team_description);
  $node->body[LANGUAGE_NONE][0]['format']  = 'full_html';

  $node->comment = COMMENT_NODE_HIDDEN;
  $node->created = time();
  $node->path    = array('alias' => "training-team/$cohort_id/$slot_code/$team_number");
  $node->promote = NODE_NOT_PROMOTED;
  $node->status  = NODE_PUBLISHED;
  $node->sticky  = NODE_NOT_STICKY;

  // Make the superuser is the author of our node.
  $node->uid = 1;

  node_save($node);

  return $node;
}


function _ctl_onboarding_add_team_member($nid, $uid) {
  $user = user_load($uid);
  og_group('node', $nid, array(
    'entity type'     => 'user',
    'entity'          => $user,
    'membership type' => OG_MEMBERSHIP_TYPE_DEFAULT,
  ));
}
