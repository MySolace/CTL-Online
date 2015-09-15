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

  // TODO
  // - perhaps augment $slots instead of using $slot_infos
  $slot_infos = array();

  // TODO
  // - there may be some optimizations if we use array references more

  // From the registrats' info we can determine what teams need to be created.
  foreach ($registrants as &$registrant) {
    $slot_code = $registrant->slot_code;

    // Setup time slot info if it doesn't exist yet.
    if (!isset($slot_infos[$slot_code])) {
      foreach ($slots as $slot) {
        if ($slot->slot_code === $slot_code) {
          break;
        }
      }

      // Determine how trainees should be spread across teams.
      $num_trainers          = $slot->num_trainers;
      $num_registrants       = $slot->num_registrants;
      $max_trainees_per_team = intval(ceil($num_registrants / $num_trainers));

      $slot_infos[$slot_code] = array(
        'num_trainers'          => $num_trainers,
        'max_trainees_per_team' => $max_trainees_per_team,
        'cur_team'              => 0,
        'teams'                 => array(array()),
      );
    }

    $info     = $slot_infos[$slot_code];
    $cur_team = $info['teams'][$info['cur_team']];

    // If the current team is full then form a new one if possible.
    // TODO
    // - for the future make sure team creation factors in registrant
    //   statuses (e.g. no team needs to be formed if all its potential
    //   members are ineligible for whatever reason)
    if (count($cur_team) >= $info['max_trainees_per_team']) {
      if (count($info['teams']) < $info['num_trainers']) {
        $info['teams'][]  = array();
        $info['cur_team'] = count($info['teams']) - 1;
        $cur_team         = $info['teams'][$info['cur_team']];
      }
    }

    // TODO
    // - when the time is right account for different statuses

    // Add the accepted user to the team.
    $status = intval($registrant->status);

    if ($status === CTL_ONBOARDING_STATUS_ACCEPTED) {
      $cur_team[]         = $registrant->uid;
      $registrant->status = CTL_ONBOARDING_STATUS_ASSIGNED;
    }

    $info['teams'][$info['cur_team']] = $cur_team;
    $slot_infos[$slot_code]           = $info;
  }

  // Create the new organic groups.
  foreach ($slot_infos as $slot_code => $slot_info) {
    // TODO
    // - do this
    // Delete previously existing teams.  This ensures that team
    // rosters are up to date with what registrants we have.

    // Create the organic groups for the teams.
    $teams = $slot_info['teams'];
    foreach ($teams as $k => $team) {
      $node = _ctl_onboarding_create_team_node($cohort_id, $slot_code, $k + 1);
      foreach ($team as $uid) {
        _ctl_onboarding_add_team_member($node->nid, $uid);
      }
    }
  }
}


function _ctl_onboarding_create_team_node($cohort_id, $slot_code, $team_number) {
  $node           = new stdClass();
  $node->type     = 'training_team';
  $node->language = LANGUAGE_NONE;

  node_object_prepare($node);

  $node->title = "Training Team - Cohort: $cohort_id, Slot: $slot_code, Team: $team_number";

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
