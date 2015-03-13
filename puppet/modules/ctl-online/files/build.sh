#!/bin/sh

WEB_ROOT='/var/www/online.crisistextline.org/current'
DATA_ROOT='/data'
LIB_DIR=$DATA_ROOT/lib

MAKEFILE=$DATA_ROOT/build-ctl.make


drush make --prepare-install --no-gitinfofile --no-cache "$MAKEFILE" "$WEB_ROOT"

cd $WEB_ROOT
drush site-install ctl -y --db-url=mysql://root@localhost/ctl --site-name="CTL Online"

#rm -rf $WEB_ROOT/ctl/modules/ctl
#ln -s $LIB_DIR/modules/ /var/www/online.crisi
