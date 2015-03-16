class ctl_online {
    Firewall {
        before  => Class['ctl_online::fw_post'],
        require => Class['ctl_online::fw_pre'],
    }

    class { ['ctl_online::fw_pre', 'ctl_online::fw_post']: }

    class { 'firewall': }
}
