// Adjusts the sticky table header placement based on how admin_menu handles it.
Drupal.ctlThemeTableHeaderOffset = function () {
  var $nav = jQuery(".navbar-fixed-top");
  var height = $nav.outerHeight();
  // In IE, Shadow filter adds some extra height, so we need to remove it from
  // the returned height.
  if ($nav.css("filter") && $nav.css("filter").match(/DXImageTransform\.Microsoft\.Shadow/)) {
    height -= $nav.get(0).filters.item("DXImageTransform.Microsoft.Shadow").strength;
  }

  if (Drupal.admin) {
    height += Drupal.admin.height();
  }

  return height;
};
