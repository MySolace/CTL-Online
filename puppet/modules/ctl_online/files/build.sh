#!/bin/sh

WEB_ROOT='/var/www/online.crisistextline.org/html/current'
DATA_ROOT='/data'
LIB_DIR=$DATA_ROOT/lib
MAKEFILE=build-ctl.make

# Build our local Drupal site's directory.
cd $DATA_ROOT
drush make --prepare-install --no-gitinfofile "$MAKEFILE" "$WEB_ROOT"

# Install our local Drupal site.
cd $WEB_ROOT
drush site-install ctl --db-url=mysql://root@localhost/ctl --site-name="CTL Online" --yes

# TODO
# - try adding the usage of `--writable`.  i.e.:
# drush site-install ctl --writable --db-url=mysql://root@localhost/ctl --site-name="CTL Online" --yes

# FileField Nginx Progress provides support for upload progress bars
# for servers configured in a certain way.
drush pm-disable filefield_nginx_progress --yes

# Coder checks Drupal code against coding standards and best practices.
drush pm-download coder-7.x-2.x-dev

# Coder Tough Love goes further and is more opinionated than Coder.
drush pm-download coder_tough_love

# Devel is a suite of tools for assisting development.
drush pm-download devel

# Reroute Email reroutes outgoing emails to a configurable email address.
drush pm-download reroute_email

drush pm-enable coder coder_tough_love devel reroute_email --yes

# https://www.drupal.org/node/498140#comment-2978658
drush php-eval 'node_access_rebuild();'

# http://dropbucket.org/node/216
# http://stackoverflow.com/questions/4990172/how-to-append-several-lines-of-text-in-a-file-using-a-shell-script/4990185#4990185
cat <<EOF >> ${WEB_ROOT}/sites/default/settings.php

// Have PHP complain about everything.
// http://php.net/manual/en/errorfunc.constants.php#103504
error_reporting(~0);

// Show errors on WSOD pages.
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

# Settings defined here in the \`\$conf\` array will override
# similar settings in the \`variable\` database table.

// Show all messages on the screen.
// We use \`2\` instead of ERROR_REPORTING_DISPLAY_ALL
// since error.inc would not yet be loaded.
\$conf['error_level'] = 2;

// Set file paths.
\$conf['file_public_path']    = 'sites/default/files';
\$conf['file_private_path']   = '/var/www/online.crisistextline.org/html/private';
\$conf['file_temporary_path'] = '/tmp';

// Caching during development only slows us down.
\$conf['block_cache']      = FALSE;
\$conf['cache']            = FALSE;
\$conf['page_compression'] = FALSE;
\$conf['preprocess_css']   = FALSE;
\$conf['preprocess_js']    = FALSE;

// Show theme rendering info in HTML output.
\$conf['theme_debug'] = TRUE;

// Delete the Mandrill API key.
// http://192.168.7.7/admin/config/services/mandrill
\$conf['mandrill_api_key'] = '';

// Delete the iFlyChat API key.
// http://192.168.7.7/admin/config/drupalchat/configuration
\$conf['drupalchat_external_api_key'] = '';

// Change the mailer to Drupal's default mailer.
// http://192.168.7.7/admin/config/system/mailsystem
\$conf['mail_system'] = array(
  'default-system' => 'DefaultMailSystem',
  'mandrill_test'  => 'DefaultMailSystem',
);

// We don't want any live emails going out.
// http://192.168.7.7/admin/config/development/reroute_email
\$conf['reroute_email_address']        = '';
\$conf['reroute_email_enable']         = TRUE;
\$conf['reroute_email_enable_message'] = TRUE;

EOF

service php-fpm restart

rm -rf $WEB_ROOT/profiles/ctl/modules/ctl
ln -s $LIB_DIR/modules/ $WEB_ROOT/profiles/ctl/modules/ctl

rm -rf $WEB_ROOT/profiles/ctl/themes/ctl
ln -s $LIB_DIR/themes/ $WEB_ROOT/profiles/ctl/themes/ctl
