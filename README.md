# Overview

[![Greenkeeper badge](https://badges.greenkeeper.io/MySolace/CTL-Online.svg)](https://greenkeeper.io/)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/238101e1a0f24f86938b7ec777d53853)](https://www.codacy.com/app/MySolace/CTL-Online?utm_source=github.com&utm_medium=referral&utm_content=MySolace/CTL-Online&utm_campaign=badger)

This is the internal counselor application/scheduling/management system, built in Drupal 7.

# Starting up

In order to get started, you'll need to run the following commands once you've cloned the repo:

```
git submodule update --init
vagrant up
```

## In the VM

Once the Vagrant box has fully provisioned, you will need to do the following:

```
vagrant ssh
```

Once you are in the box:

```
sudo su
sh /home/vagrant/build.sh
```

Sit back and wait while drush builds the Drupal install. You might also need to edit the nginx config to set sendmail off, at /etc/nginx/nginx.conf. We are working to set this off automatically -> see /puppet/manifests/site.pp of the base repo.

## Using locally

Once the build is done, head to 192.168.7.7 in your browser of choice.
You can log into the admin account via 192.168.7.7/user/login, using the password as supplied in output of the bash script you ran above.

# Front-End

This install uses our own CTL theme, a subtheme of [Adminimal](https://www.drupal.org/project/adminimal_theme).
Lauren Smith designed [the template](https://github.com/smithln/ctl), which is included as a subtheme at /lib/themes/ctl_theme/lib. To get started, exit out of the vagrant box and cd back to the base repo directory, then:

```
npm install
gulp
```

This will compile the SASS into /lib/themes/ctl_theme/css, where it can then be used by the Drupal custom theming system.
Stem files with imports back to Lauren's submoduled repository are provided, which we can build off of for actual implementation in the site.

If you've already provisioned the Vagrant box a while ago and are seeing funky things happen after updating to the latest commit, clearing cache and restarting PHP-FPM will likely solve 99% of your problems:

```
vagrant ssh
cd /var/www/online.crisistextline.org/html/current
drush cc all
sudo service php-fpm restart
```

# Enjoy

Enjoy!
