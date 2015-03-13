
node default {
    include ::php
    include ::nginx
    include ::mysql::server
    include ::php

    include drush

    exec { 'drush-reqs-root':
        command => '/usr/bin/drush dl make_local-7.x-1.1',
        require => File['symlink drush'],
        creates => '/root/.drush/make_local'
    }

    exec { 'drush-reqs-vagrant':
        command => '/usr/bin/drush dl make_local-7.x-1.1',
        require => File['symlink drush'],
        creates => '/home/vagrant/.drush/make_local',
        user    => 'vagrant'
    }

    package { 'git':
        ensure => latest
    }

    file { 'webroot':
        path => '/var/www/online.crisistextline.org',
        ensure => directory,
        require => Package['nginx']
    }

    file { 'build-script':
        path   => '/home/vagrant/build.sh',
        source => 'puppet:///modules/ctl-online/build.sh'
    }
        
    exec { 'build':
        require => File['build-script'],
        command => '/bin/sh /home/vagrant/build.sh',
        creates => '/var/www/online.crisistextline.org/current'
    }
}
