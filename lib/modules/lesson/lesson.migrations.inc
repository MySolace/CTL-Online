<?php

function lesson_update_7105() {
  if (module_exists('course_lesson')) {
    $res = db_select('audio_progress', 'a')
      ->fields('a', array('nid', 'uid', 'progress'))
      ->execute()
      ->fetchAll();

    foreach ($res as $row) {
      if (substr_count($row->progress, 'f') > 0) {
        $account = user_load($row->uid);
        if ($object = course_get_course_object('course_lesson', 'lesson', $row->nid, $account)) {
          $object->getFulfillment()->setComplete()->save();
        }
      }
    }
  }


  db_query("UPDATE audio_progress SET progress='1' WHERE progress LIKE '%f%'");
  db_query("UPDATE audio_progress SET progress='0' WHERE progress != '1'");

  db_change_field('audio_progress', 'progress', 'progress', array(
    'type' => 'float',
    'not null' => TRUE,
    'default' => 0,
  ));
}
