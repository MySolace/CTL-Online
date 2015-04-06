# Overview

This is the internal counselor application/scheduling/management system, built in Drupal 7.

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

Sit back and wait while drush builds the Drupal install.

# Using locally

Once the build is done, head to 192.168.7.7 in your browser of choice.
You can log into the admin account via 192.168.7.7/user/login, using the password as supplied in output of the bash script you ran above.

# Enjoy

Enjoy!
