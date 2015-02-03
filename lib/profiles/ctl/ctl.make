; CTL custom modules and themes
api = 2
core = 7.x

includes[] = drupal-org.make

; CTL
projects[ctl_features][type] = "module"
projects[ctl_features][subdir] = "ctl"
projects[ctl_features][download][type] = local
projects[ctl_features][download][source] = './lib/modules/ctl_features'

; CTL Online
projects[ctl_online][type] = "module"
projects[ctl_features][subdir] = "ctl"
projects[ctl_online][download][type] = local
projects[ctl_online][download][source] = './lib/modules/ctl_online'
