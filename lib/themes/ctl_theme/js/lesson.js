(function ($) {
  Drupal.behaviors.ctlThemeLesson = {
    attach: function () {
      var $b = $('.slide:first-child');
      var $h2 = $b.find('h2');
      var $h3 = $b.find('h3');
      $b.find('.deck-slide-scaler div').append($('<div class="titles">').append($h2, $h3));

      $('.slide:not(:first-child)').each(function () {
        $t = $(this);

        var $div = $t.find('.deck-slide-scaler');

        var $h1 = $t.find('h1');
        var $h2 = $t.find('h2');
        if ($h1.size() > 0 || $h2.size() > 0) {
          if ($div.size() > 0) {
            $t = $div;
            if ($div.find('> div').size() > 0) {
                $t = $div.find('> div');
            }
          }

          $t.prepend($('<div class="titles">').append($h1, $h2));
        }
      });
    }
  };
})(jQuery);
