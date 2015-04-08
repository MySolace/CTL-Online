#!/bin/sh

WEB_ROOT='/var/www/online.crisistextline.org/current'
DATA_ROOT='/data'
LIB_DIR=$DATA_ROOT/lib

MAKEFILE=build-ctl.make

cd $DATA_ROOT
drush make --prepare-install --no-gitinfofile "$MAKEFILE" "$WEB_ROOT"

cd $WEB_ROOT
drush site-install ctl -y --db-url=mysql://root@localhost/ctl --site-name="CTL Online"
drush dis filefield_nginx_progress -y
drush dl reroute_email
drush en reroute_email -y
echo "\$conf['reroute_email_enable'] = 1;" >> sites/default/settings.php

rm -rf $WEB_ROOT/profiles/ctl/modules/ctl
ln -s $LIB_DIR/modules/ $WEB_ROOT/profiles/ctl/modules/ctl

rm -rf $WEB_ROOT/profiles/ctl/themes/ctl
ln -s $LIB_DIR/themes/ $WEB_ROOT/profiles/ctl/themes/ctl
