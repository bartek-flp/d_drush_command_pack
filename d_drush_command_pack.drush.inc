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

  $commands['delete-node-alias'] = [
    'description' => 'Delete an node alias',
    'aliases' => ['dna'],
    'arguments' => [
      'source' => 'Delete by source',
      'alias' => 'Delete by alias',
    ],
    'options' => [
      'name' => 'Name of source or alias',
    ],
    'examples' => [
      'drush dna source /node/1' => 'Delete an alias by source path',
      'drush dna alias /path-alias-name' => 'Delete an alias by alias path name',
    ],
  ];

  return $commands;
}

/**
 * Drush command logic for rebuilding file cache.
 *
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

/**
 * Drush command logic for deleting aliases
 *
 */
function drush_d_drush_command_pack_delete_node_alias($arg = NULL, $opt = NULL) {
  $tokens = ['@arg' => $arg, '@opt' => $opt];

  switch ($arg) {
    case 'alias':
    case 'source':
      $condition = [$arg => $opt];
      \Drupal::service('path.alias_storage')
        ->delete($condition);
      drush_print(dt('Alias @opt deleted', $tokens));
      break;

    default:
      drush_print(dt('Wrong argument and options. Example use: drush dna source /node/1'));
  }
}
