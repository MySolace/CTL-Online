#!/bin/sh

WEB_ROOT='/var/www/online.crisistextline.org/current'
DATA_ROOT='/data'
LIB_DIR=$DATA_ROOT/lib

MAKEFILE=build-ctl.make

cd $DATA_ROOT
drush make --prepare-install --no-gitinfofile --no-cache "$MAKEFILE" "$WEB_ROOT"

cd $WEB_ROOT
drush site-install ctl -y --db-url=mysql://root@localhost/ctl --site-name="CTL Online"

rm -rf $WEB_ROOT/profiles/ctl/modules/ctl
ln -s $LIB_DIR/modules/ $WEB_ROOT/profiles/ctl/modules/ctl

rm -rf $WEB_ROOT/profiles/ctl/themes/ctl
ln -s $LIB_DIR/themes/ $WEB_ROOT/profiles/ctl/themes/ctl
