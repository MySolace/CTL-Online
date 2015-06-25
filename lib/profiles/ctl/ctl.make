; CTL custom modules and themes
api = 2
core = 7.x

includes[] = drupal-org.make

; CTL
projects[ctl_features][type] = "module"
projects[ctl_features][subdir] = "ctl"
projects[ctl_features][download][type] = local
projects[ctl_features][download][source] = './lib/modules/ctl_features'

; Lesson
projects[lesson][type] = "module"
projects[lesson][subdir] = "ctl"
projects[lesson][download][type] = local
projects[lesson][download][source] = './lib/modules/lesson'

; Example Conversations
projects[example_conversation][type] = "module"
projects[example_conversation][subdir] = "ctl"
projects[example_conversation][download][type] = local
projects[example_conversation][download][source] = './lib/modules/example_conversation'

; CTL Theme
projects[ctl_theme][type] = "theme"
projects[ctl_theme][subdir] = "ctl"
projects[ctl_theme][download][type] = local
projects[ctl_theme][download][source] = './lib/themes/ctl_theme'

projects[schedule_recurring][type] = "module"
projects[schedule_recurring][subdir] = "ctl"
projects[schedule_recurring][download][type] = local
projects[schedule_recurring][download][source] = './lib/modules/schedule_recurring'
