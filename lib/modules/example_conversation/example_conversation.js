(function ($) {
  Drupal.behaviors.exampleConversation = {
    attach: function (context, settings) {

      var pluses = new Feedback($('.webform-component--pluses textarea'), 'Pluses', settings.example_conversation.min_pluses);
      var wishes = new Feedback($('.webform-component--wishes textarea'), 'Wishes', settings.example_conversation.min_wishes);

      var submit = $('<button>').text('Submit').click(function () {
        var $self = $(this);
        if (pluses.validate() && wishes.validate()) {
          var $form = $('.webform-client-form');
          $.post($form.attr('action'), $form.serialize(), function () {
            $wrapper.prepend($('<div class="message message-info">').text('Thanks! We got your submission.'));
            pluses.adminFeedback(settings.example_conversation.pluses);
            wishes.adminFeedback(settings.example_conversation.wishes);
            $self.remove();
          });
        } else {
          alert('Please fill out all pluses and wishes.');
        }
      });

      var $wrapper = $('<div class="plus-wish-wrap">').append(pluses.getContent(), wishes.getContent(), submit);
      $('.node-example-conversation .content').after($wrapper);
    }
  }


  var Feedback = function ($populate, name, numInputFields) {
    if (!numInputFields) {
      numInputFields = 5;
    }

    this.$populate = $populate;
    this.title = name;

    this.$content = $('<div>').addClass('plus-wish');
    this.$content.append($('<h3>').text(this.title));

    for (var i = 0; i < numInputFields; i++) {
      this.$content.append(this.$inputFormGroup.clone(true, true));
    }

    this.$inputs = this.$content.find('input');

    var self = this;
    this.$inputs.bind('keyup', function () {
      self.$populate.val('');
      var text = '';
      self.$inputs.each(function () {
        text += '- ' + $(this).val() + "\n";
      });

      self.$populate.val(text);
    });
  };

  Feedback.prototype.$inputFormGroup = $('<div>').addClass('form-group').append($('<input type="text">'));

  Feedback.prototype.getInput = function () {
    return this.$inputFormGroup.clone();
  };

  Feedback.prototype.getContent = function () {
    return this.$content;
  };

  Feedback.prototype.validate = function () {
    var returnBool = true;
    this.$inputs.each(function () {
      if ($(this).val() == '') {
        $(this).parent().addClass('error');
        returnBool = false;
      }
    });

    return returnBool;
  };

  Feedback.prototype.adminFeedback = function (items) {
    this.$content.find('.form-group').remove();
    this.$content.find('h3').text('Here are some ' + this.title + ' from us.');

    var $ul = $('<ul>');
    $.each(items, function (idx, item) {
      $ul.append($('<li>').text(item));
    });

    this.$content.append($ul);
  };

})(jQuery);
