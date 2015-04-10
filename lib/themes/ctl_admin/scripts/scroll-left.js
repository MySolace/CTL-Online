(function ($) {
    var margin = 32;
    Drupal.behaviors.sidebar_left = {
        attach: function (context, settings) {
            var nav = $('#sidebar-left');
            var navHomeY = nav.offset().top - margin;
            var isFixed = false;
            var $w = $(window);

            $w.scroll(function() {
                var scrollTop = $w.scrollTop();
                var shouldBeFixed = scrollTop > navHomeY && window.innerWidth > 1024;
                if (shouldBeFixed && !isFixed) {
                    nav.css({
                        position: 'fixed',
                        top: margin + 'px',
                        left: nav.offset().left,
                        width: nav.width()
                    });
                    isFixed = true;
                }
                else if (!shouldBeFixed && isFixed)
                {
                    nav.css({
                        position: 'static'
                    });
                    isFixed = false;
                }
            });
            $w.scroll();
        }
    };
})(jQuery);
