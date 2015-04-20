<?php
/**
 * @file
 * ctl_training.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ctl_training_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access all course reports'.
  $permissions['access all course reports'] = array(
    'name' => 'access all course reports',
    'roles' => array(
      'Staff' => 'Staff',
      'Trainer' => 'Trainer',
      'administrator' => 'administrator',
    ),
    'module' => 'course',
  );

  // Exported permission: 'access course'.
  $permissions['access course'] = array(
    'name' => 'access course',
    'roles' => array(
      'Staff' => 'Staff',
      'Trainee' => 'Trainee',
      'Trainer' => 'Trainer',
      'administrator' => 'administrator',
    ),
    'module' => 'course',
  );

  // Exported permission: 'access course administration area'.
  $permissions['access course administration area'] = array(
    'name' => 'access course administration area',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'course',
  );

  // Exported permission: 'access quiz'.
  $permissions['access quiz'] = array(
    'name' => 'access quiz',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'administer course'.
  $permissions['administer course'] = array(
    'name' => 'administer course',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'course',
  );

  // Exported permission: 'administer course enrollment types'.
  $permissions['administer course enrollment types'] = array(
    'name' => 'administer course enrollment types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'course',
  );

  // Exported permission: 'administer privatemsg settings'.
  $permissions['administer privatemsg settings'] = array(
    'name' => 'administer privatemsg settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'administer quiz configuration'.
  $permissions['administer quiz configuration'] = array(
    'name' => 'administer quiz configuration',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'allow disabling privatemsg'.
  $permissions['allow disabling privatemsg'] = array(
    'name' => 'allow disabling privatemsg',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'create course content'.
  $permissions['create course content'] = array(
    'name' => 'create course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create lesson content'.
  $permissions['create lesson content'] = array(
    'name' => 'create lesson content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create multichoice content'.
  $permissions['create multichoice content'] = array(
    'name' => 'create multichoice content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create quiz content'.
  $permissions['create quiz content'] = array(
    'name' => 'create quiz content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create reading content'.
  $permissions['create reading content'] = array(
    'name' => 'create reading content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any course content'.
  $permissions['delete any course content'] = array(
    'name' => 'delete any course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any lesson content'.
  $permissions['delete any lesson content'] = array(
    'name' => 'delete any lesson content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any multichoice content'.
  $permissions['delete any multichoice content'] = array(
    'name' => 'delete any multichoice content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz content'.
  $permissions['delete any quiz content'] = array(
    'name' => 'delete any quiz content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz results'.
  $permissions['delete any quiz results'] = array(
    'name' => 'delete any quiz results',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'delete any reading content'.
  $permissions['delete any reading content'] = array(
    'name' => 'delete any reading content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own course content'.
  $permissions['delete own course content'] = array(
    'name' => 'delete own course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own lesson content'.
  $permissions['delete own lesson content'] = array(
    'name' => 'delete own lesson content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own multichoice content'.
  $permissions['delete own multichoice content'] = array(
    'name' => 'delete own multichoice content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own quiz content'.
  $permissions['delete own quiz content'] = array(
    'name' => 'delete own quiz content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own reading content'.
  $permissions['delete own reading content'] = array(
    'name' => 'delete own reading content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete privatemsg'.
  $permissions['delete privatemsg'] = array(
    'name' => 'delete privatemsg',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'delete results for own quiz'.
  $permissions['delete results for own quiz'] = array(
    'name' => 'delete results for own quiz',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'edit any course content'.
  $permissions['edit any course content'] = array(
    'name' => 'edit any course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any lesson content'.
  $permissions['edit any lesson content'] = array(
    'name' => 'edit any lesson content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any multichoice content'.
  $permissions['edit any multichoice content'] = array(
    'name' => 'edit any multichoice content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any quiz content'.
  $permissions['edit any quiz content'] = array(
    'name' => 'edit any quiz content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any reading content'.
  $permissions['edit any reading content'] = array(
    'name' => 'edit any reading content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own course content'.
  $permissions['edit own course content'] = array(
    'name' => 'edit own course content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own lesson content'.
  $permissions['edit own lesson content'] = array(
    'name' => 'edit own lesson content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own multichoice content'.
  $permissions['edit own multichoice content'] = array(
    'name' => 'edit own multichoice content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own quiz content'.
  $permissions['edit own quiz content'] = array(
    'name' => 'edit own quiz content',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own reading content'.
  $permissions['edit own reading content'] = array(
    'name' => 'edit own reading content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit question titles'.
  $permissions['edit question titles'] = array(
    'name' => 'edit question titles',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'manual quiz revisioning'.
  $permissions['manual quiz revisioning'] = array(
    'name' => 'manual quiz revisioning',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'read all private messages'.
  $permissions['read all private messages'] = array(
    'name' => 'read all private messages',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'read privatemsg'.
  $permissions['read privatemsg'] = array(
    'name' => 'read privatemsg',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'reply only privatemsg'.
  $permissions['reply only privatemsg'] = array(
    'name' => 'reply only privatemsg',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'score any quiz'.
  $permissions['score any quiz'] = array(
    'name' => 'score any quiz',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'score own quiz'.
  $permissions['score own quiz'] = array(
    'name' => 'score own quiz',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'score taken quiz answer'.
  $permissions['score taken quiz answer'] = array(
    'name' => 'score taken quiz answer',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'select text format for privatemsg'.
  $permissions['select text format for privatemsg'] = array(
    'name' => 'select text format for privatemsg',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'use tokens in privatemsg'.
  $permissions['use tokens in privatemsg'] = array(
    'name' => 'use tokens in privatemsg',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'view any quiz question correct response'.
  $permissions['view any quiz question correct response'] = array(
    'name' => 'view any quiz question correct response',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'view any quiz results'.
  $permissions['view any quiz results'] = array(
    'name' => 'view any quiz results',
    'roles' => array(
      'Staff' => 'Staff',
      'Trainer' => 'Trainer',
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view own quiz results'.
  $permissions['view own quiz results'] = array(
    'name' => 'view own quiz results',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view quiz question outside of a quiz'.
  $permissions['view quiz question outside of a quiz'] = array(
    'name' => 'view quiz question outside of a quiz',
    'roles' => array(),
    'module' => 'quiz',
  );

  // Exported permission: 'view results for own quiz'.
  $permissions['view results for own quiz'] = array(
    'name' => 'view results for own quiz',
    'roles' => array(
      'Staff' => 'Staff',
      'administrator' => 'administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'write privatemsg'.
  $permissions['write privatemsg'] = array(
    'name' => 'write privatemsg',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  return $permissions;
}
