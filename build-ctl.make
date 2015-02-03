api = 2
core = 7.x

; Include drupal core
includes[] = drupal-org-core.make

; CTL profile
projects[ctl][type] = profile
projects[ctl][download][type] = local
projects[ctl][download][source] = "./lib/profiles/ctl"
