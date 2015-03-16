class ctl_online::fw_post {
    firewall { '999 drop all':
        proto   => 'all',
        action  => 'drop',
        before  => undef,
    }
}
