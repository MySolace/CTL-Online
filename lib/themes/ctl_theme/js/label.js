(function ($) {
  Drupal.behaviors.lesson = {
    attach: function (context, settings) {
      $('input').each(function () {
        if ($(this).siblings('label').size() == 0) {
          var id = $(this).attr('id');
          $(this).after($('<label for="' + id + '">'));
        }
      });
    }
  };
})(jQuery);