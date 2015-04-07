(function ($) {
  Drupal.behaviors.scheduleRecurringTableSelect = {
    attach: function (context, settings) {
      $('.tableselect tr').click(function () {
        $(this).find('input').click();
      });

      $('.tableselect tr input').click(function (e) {
        e.stopPropagation();
      });
    }
  };
})(jQuery);

