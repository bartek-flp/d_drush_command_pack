<?php

/**
 * Implements hook_drush_command().
 */
function d_drush_command_pack_drush_command() {

  $commands['rebuild-aggregate-file'] = [
    'description' => 'Rebuild aggregate css/js files',
    'aliases' => ['raf'],
    'arguments' => [
      'js' => 'Rebuild aggregate js files only',
      'css' => 'Rebuild aggregate css files only',
    ],
    'examples' => [
      'drush raf' => 'Rebuild aggregate css/js files',
      'drush raf js' => 'Rebuild aggregate js files',
      'drush raf css' => 'Rebuild aggregate css files',
    ],
  ];

  return $commands;
}

/**
 * Drush command logic.
 * drush_[MODULE_NAME]_[COMMAND_NAME]().
 */
function drush_d_drush_command_pack_rebuild_aggregate_file($arg = NULL) {
  $tokens = ['@arg' => $arg];
  switch ($arg) {
    case 'js':
      \Drupal::service("asset.js.collection_optimizer")->deleteAll();
      _drupal_flush_css_js();
      drush_print(dt('Rebuild aggregate @arg files.', $tokens));
      break;
    case 'css':
      \Drupal::service("asset.css.collection_optimizer")->deleteAll();
      _drupal_flush_css_js();
      drush_print(dt('Rebuild aggregate @arg files.', $tokens));
      break;
    case '':
      \Drupal::service("asset.css.collection_optimizer")->deleteAll();
      \Drupal::service("asset.js.collection_optimizer")->deleteAll();
      _drupal_flush_css_js();
      drush_print(dt('Rebuild aggregate js/css files.'));
      break;
    default:
      drush_print(dt('Wrong argument. Possible arguments: js, css or use command without argument.'));
  }
}
