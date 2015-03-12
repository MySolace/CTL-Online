node default {
    include ::php
    include ::nginx
    include ::mysql::server
    include ::php
    include drush

    package { 'git':
        ensure => latest
    }

    file { 'webroot':
        path => '/var/www/online.crisistextline.org',
        ensure => directory,
        require => Package['nginx']
    }

    file { 'webroot-link':
        path => '/var/www/online.crisistextline.org/current',
        ensure => link,
        target => '/home/vagrant/ctl-online',
        require => File['webroot']
    }

    file { 'build-script':
        path   => '/home/vagrant/build.sh',
        source => 'puppet:///modules/ctl-online/build.sh'
    }
        
    exec { 'build':
        require => File['build-script'],
        command => '/bin/sh /home/vagrant/build.sh',
        creates => '/var/www/online.crisistextline.org/current/sites/default/settings.php'
    }
}
