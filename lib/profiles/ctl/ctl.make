; CTL custom modules and themes
api = 2
core = 7.x

includes[] = drupal-org.make

; CTL
projects[ctl_features][type] = "module"
projects[ctl_features][subdir] = "ctl"
projects[ctl_features][download][type] = local
projects[ctl_features][download][source] = './lib/modules/ctl_features'

; CTL Theme
projects[ctl_theme][type] = "theme"
projects[ctl_theme][subdir] = "ctl"
projects[ctl_theme][download][type] = local
projects[ctl_theme][download][source] = './lib/themes/ctl_theme'
