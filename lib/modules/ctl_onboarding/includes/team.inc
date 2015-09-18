<?php

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'ctl_onboarding') . '/includes/helper.inc';


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
      else {
        // TODO
        // - figure out how to specilly handle the "filled to capacity"
        //   case if at all
      }
    }

    // TODO
    // - when the time is right account for more different statuses

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
        _ctl_onboarding_set_user_role($uid, CTL_ONBOARDING_ROLE_TRAINEE);

        // Assign the cohort number to the user.
        $user = user_load($uid);
        $user->field_cohort[LANGUAGE_NONE][0]['value'] = $cohort_id;
        user_save($user);

        _ctl_onboarding_add_group_user($node->nid, $user);
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


/**
 * Assigns a trainer to a team and makes them the group admin.
 * @param  int $uid    The user ID for the trainer to assign.
 */
function _ctl_onboarding_set_team_trainer($trainer_uid) {
  // Add the trainer to group.
  $trainer_user = user_load($trainer_uid);
  _ctl_onboarding_add_group_user($node->nid, $trainer_user);

  // OG_ADMINISTRATOR_ROLE
  // user_role_load_by_name() ?

  // og_roles()

  og_role_grant('node', $nid, $trainer_uid, $rid);

  // function og_group($group_type, $gid, $values = array(), $save_created = TRUE) {
  // function og_role_grant($group_type, $gid, $uid, $rid) {

  // og_group('node', $nid, array(
  //   'entity type'     => 'user',
  //   'entity'          => $user,
  //   'membership type' => OG_MEMBERSHIP_TYPE_DEFAULT,
  // ));


  // // Get all the member uids of the group.
  // $uids = og_get_group_members_properties($node, array(), 'members', 'node');

  // OG_ADMINISTRATOR_ROLE

  // og_get_user_roles()
  // og_role_grant()
  // og_role_revoke()

  // og_role_load()

  // og_get_groups_by_user()
  // og_get_entity_groups()

  // og_ungroup()
  // og_group()

  // make the trainer the group admin

  // update the group members' "Trainer" field

}


/**
 * Ensures that a user has only a one role out of a set of related roles.
 * @param int    $uid          The user ID.
 * @param string $role_name    The name of the role to set.
 */
function _ctl_onboarding_set_user_role($uid, $role_name) {
  // Remove all the roles we don't want the user to have.
  $role_names = array(
    CTL_ONBOARDING_ROLE_ACCEPTED,
    CTL_ONBOARDING_ROLE_INVITED,
    CTL_ONBOARDING_ROLE_DEFERRED,
    CTL_ONBOARDING_ROLE_DECLINED,
    CTL_ONBOARDING_ROLE_TRAINEE,
  );
  foreach ($role_names as $k => $v) {
    if ($v === $role_name) {
      unset($role_names[$k]);
      break;
    }
  }
  _ctl_onboarding_remove_user_roles($uid, $role_names);
  // Assign the user the role we want them to have.
  _ctl_onboarding_add_user_roles($uid, array($role_name));
}
