# Overview

This the internal counselor application/scheduling/management system, built in Drupal 7.

# Starting up

In order to get started, you'll need to run the following commands once you've cloned the repo:

```
git submodule update --init
vagrant up
```

# In the VM

Once the Vagrant box has fully provisioned, you will need to do the following:

```
vagrant ssh
```

Once you are in the box:

```
sudo su
sh /home/vagrant/build.sh
```

Sit back and wait while drush builds the Drupal install

# Enjoy

Enjoy!
