node default {
    include ::php
    include ::nginx
    include ::mysql::server
    include ctl_online

    include drush

    exec { 'drush-reqs-root':
        command => '/usr/local/bin/drush dl make_local-6.x-1.0',
        require => File['/usr/local/bin/drush'],
        creates => '/usr/share/drush/commands/make_local'
    }

    exec { 'drush-path':
        command => "/bin/echo 'export PATH=\$PATH:/usr/local/bin' > /etc/profile.d/drush-path.sh; source /etc/profile.d/drush-path.sh",
        creates => '/etc/profile.d/drush-path.sh'
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
        source => 'puppet:///modules/ctl_online/build.sh'
    }

    exec { 'build':
        require => File['build-script', '/usr/local/bin/drush'],
        command => '/bin/sh /home/vagrant/build.sh &',
        creates => '/var/www/online.crisistextline.org/current'
    }

    nginx::resource::vhost { 'ctl_online.dev':
      www_root => '/var/www/online.crisistextline.org/current',
      try_files => ['$uri', '$uri/', "/index.php?\$args"],
    }

    nginx::resource::location { "${name}_root":
        ensure          => present,
        vhost           => "ctl_online.dev",
        www_root        => "/var/www/online.crisistextline.org/current/",
        location        => '~ \.php$',
        index_files     => ['index.php'],
        proxy           => undef,
        try_files       => ['$uri', '$uri/', "/index.php?\$args"],
        fastcgi         => "127.0.0.1:9000",
        fastcgi_script  => undef,
        location_cfg_append => {
            fastcgi_connect_timeout => '3m',
            fastcgi_read_timeout    => '3m',
            fastcgi_send_timeout    => '3m'
        }
    }

    # The following isn't working. The closest so far is https://github.com/jfryman/puppet-nginx/blob/master/docs/hiera.md:
    # class { 'nginx::config':
    #    sendfile => 'off',
    # }
    # which only 'redeclares' nginx::config, so currently manually editing puppet/modules/nginx/manifests/config.pp
    #
    #nginx::config { 'sendfile':
    #    sendfile => 'off',
    #}

    firewall { '100 allow ssh':
        port   => [22],
        proto  => tcp,
        action => accept,
    }
    firewall { '100 allow http access':
        port   => [80],
        proto  => tcp,
        action => accept,
    }
}
