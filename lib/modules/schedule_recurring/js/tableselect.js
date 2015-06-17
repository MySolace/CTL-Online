(function ($) {
  Drupal.behaviors.scheduleRecurringTableSelect = {
    attach: function (context, settings) {
      $('.tableselect tr').click(function () {
        $(this).find('input').click();
      });

      $('.tableselect tr input').click(function (e) {
        e.stopPropagation();
      });

      var days = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];

      var $select = $('<select>').append('<option>- Select a day to begin -</option>');

      $.each(days, function (i, val) {
        $select.append('<option value="'+i+'">'+val+'</option>');
      });

      var $showMore = $('<input type="button" value="I can\'t make any of these shifts" class="form-submit">')
        .insertBefore($('#edit-submit'))
        .hide()
        .click(function () {
          var $tr = $('#schedule-recurring-available tr');
          $tr.filter('.day-' + $select.val()).show();
          $(this).hide();
        });

      $select.change(function () {
        var dayClass = '.day-' + $(this).val();

        var $tr = $('#schedule-recurring-available tr').hide();

        if ($tr.filter(dayClass+'.priority').length > 0) {
          $tr.filter(dayClass + '.priority').show();
          if ($tr.filter(dayClass).not('.priority').length > 0) {
            $showMore.show();
          }
        } else {
          $tr.filter(dayClass).show();
        }

        $('#schedule-recurring-available .form-submit[type="submit"]').show();
      });

      $('#schedule-recurring-available')
        .before($select)
        .find('tr').hide().end()
        .find('.form-submit').hide().end();
    }
  };
})(jQuery);

