(function ($) {
  Drupal.behaviors.ctlThemeForms = {
    attach: function (context, settings) {
      $('input:not([type="hidden"]').not('.vbo-select,.vbo-table-select-all').each(function () {
        if ($(this).siblings('label').size() == 0) {
          var id = $(this).attr('id');
          $(this).after($('<label for="' + id + '">'));
        }
      });
    }
  };
})(jQuery);