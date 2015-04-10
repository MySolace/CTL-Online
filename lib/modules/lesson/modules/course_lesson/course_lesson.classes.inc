<?php

class CourseObjectLesson extends CourseObjectNode {

  function create($node = NULL) {
    $lesson = new stdClass;
    $lesson->auto_created = TRUE;
    $lesson->type = 'lesson';
    parent::create($lesson);
  }

  function getNodeTypes() {
    return array('lesson');
  }

  function isGraded() {
    return TRUE;
  }

  function getCloneAbility() {
    return TRUE;
  }

}
