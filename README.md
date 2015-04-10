# Overview

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

Sit back and wait while drush builds the Drupal install.

## Using locally

Once the build is done, head to 192.168.7.7 in your browser of choice.
You can log into the admin account via 192.168.7.7/user/login, using the password as supplied in output of the bash script you ran above.

# Front-End

This install uses our own CTL theme, a subtheme of [Adminimal](https://www.drupal.org/project/adminimal_theme).
Lauren Smith designed [the template](https://github.com/smithln/ctl), which is included as a subtheme at /lib/themes/ctl_theme/lib. To get started:

```
cd lib/themes/ctl_theme
npm install
gulp
```

This will compile the SASS into /lib/themes/ctl_theme/css, where it can then be used by the Drupal custom theming system.
Stem files with imports back to Lauren's submoduled repository are provided, which we can build off of for actual implementation in the site.

# Enjoy

Enjoy!
