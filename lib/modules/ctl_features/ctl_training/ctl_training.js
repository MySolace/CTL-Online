(function ($) {
  Drupal.behaviors.ctlTraining = {
    attach: function (context, settings) {
      $e = $('.parse-md');

      $e.each(function () {
        $(this).html( marked($(this).html()) );
      });
    }
  }
})(jQuery);
