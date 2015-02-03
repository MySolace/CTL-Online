<?php
/**
 * @file
 * ctl_application.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ctl_application_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ctl_application_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ctl_application_node_info() {
  $items = array(
    'application' => array(
      'name' => t('Application'),
      'base' => 'node_content',
      'description' => t('This is the CTL Volunteer Application.'),
      'has_title' => '1',
      'title_label' => t('Email'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_video_default_presets().
 */
function ctl_application_video_default_presets() {
  $items = array(
    'Default' => array(
      'name' => 'Default',
      'description' => '',
      'settings' => array(
        'video_extension' => 'ogv',
        'video_codec' => 'libtheora',
        'video_preset' => '',
        'video_quality' => 2,
        'video_speed' => 3,
        'wxh' => '720x480',
        'video_aspectmode' => 'pad',
        'video_upscale' => 0,
        'audio_codec' => 'vorbis',
        'audio_quality' => 3,
        'deinterlace' => 'detect',
        'max_frame_rate' => '',
        'frame_rate' => '',
        'keyframe_interval' => '',
        'video_bitrate' => '',
        'bitrate_cap' => '',
        'buffer_size' => '',
        'one_pass' => 1,
        'skip_video' => 0,
        'pixel_format' => '',
        'h264_profile' => '',
        'audio_bitrate' => 96,
        'audio_channels' => 2,
        'audio_sample_rate' => '',
        'skip_audio' => 0,
        'video_watermark_enabled' => 0,
        'video_watermark_fid' => 0,
        'video_watermark_x' => 5,
        'video_watermark_y' => 5,
        'video_watermark_width' => '',
        'video_watermark_height' => '',
        'video_watermark_origin' => 'content',
        'autolevels' => 0,
        'deblock' => 0,
        'denoise' => '',
        'clip_start' => '',
        'clip_length' => '',
      ),
    ),
  );
  return $items;
}
