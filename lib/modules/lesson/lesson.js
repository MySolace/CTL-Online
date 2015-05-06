(function ($) {
  Drupal.behaviors.lesson = {
    attach: function (context, settings) {
      var $loading = $('<div>').css({
        position: 'fixed',
        left: '0px',
        top: '0px',
        width: '100%',
        height: '100%',
        zIndex: '9999',
        textAlign: 'center',
        paddingTop: '25%',
        fontSize: '3em',
        background: 'rgba(0,0,0,.75)',
        color: 'white'
      }).text('Loading...').appendTo('body');

      // Passing these into the init method doesn't
      // seem to work.
      $.deck.defaults.keys = {
        next: [],
        previous: []
      };

      $('.slide div').each(function () {
        $(this).html(marked($(this).html(), {breaks: true}));
        var bubbleClass = 'c-speech-bubbles--teen';
        var labelClass = 'texter__name--user';
        var label = 'Texter';

        $(this).find('p').each(function () {
          if ($(this).html()[0] == '[') {
            $(this).wrap($('<div>').addClass('c-speech-bubbles ' + bubbleClass));
            $(this).parent().after($('<span class="texter__name ' + labelClass + '">' + label + '</span>'));
            $text = $(this).html();
            $(this).html($text.substring(1, $text.length - 1));

            bubbleClass = 'c-speech-bubbles--ctl';
            labelClass = 'texter__name--ctl';
            label = 'Crisis Counselor';
          }
        })
      });

      $.deck('section', {
        hashPrefix: '',
      });
      $.deck('enableScale');

      var manager, transcript;
      $('audio').bind('loadedmetadata', function () {
        var len = $(this).attr('duration');
        manager = new SegmentManager(len, settings.lesson_progress, $(this));
        transcript = new Transcript($('.transcript').text(), len);
      });

      $('audio').bind('canplaythrough', function () {
        setTimeout(function () {
          $loading.hide();
        }, 1000);
      });

      $('audio').bind('seeked', function () {
        transcript.update($(this).attr('currentTime'));
      });

      $('audio').bind('timeupdate', function () {
        var t = $(this).attr('currentTime');
        transcript.update(t);
      });

      $('audio').bind('play', function () {
        manager.start();
      });

      $('audio').bind('pause', function () {
        manager.stop();
      });

      $('audio').bind('ended', function () {
        manager.stop();
      });

      var lastProgress = null;

      setInterval(function () {
        var t = $('audio').attr('currentTime');

        manager.update();

        var progress = manager.toString();

        if (progress !== lastProgress) {
          $.post('/node/' + settings.nid + '/audio_progress', {progress: progress});
          lastProgress = progress;
        }
      }, 5000);

      window.onbeforeunload = function () {
        manager.stop();
        $.ajax({
          type: 'POST',
          url: '/node/' + settings.nid + '/audio_progress',
          data: {progress: manager.toString()},
          async: false,
        });
      }
    }
  }
})(jQuery);

var Transcript = function (text, maxlen) {
  this.$div = jQuery('<div class="caption">');
  jQuery('.transcript').before(this.$div);

  this.times = {};
  this.end = maxlen;
  this.currentTime = -1;

  var text = text.split('\n');
  for (var i = 0; i < text.length; i++) {
    var t = text[i].substring(0, text[i].indexOf(' ')).split(':');
    t = parseInt(t[0]) * 60 + parseInt(t[1]);

    this.times[t] = text[i].substr(text[i].indexOf(' ') + 1);
  }

  this.times[0] = '[1]';
};

Transcript.prototype.update = function (timestamp) {
  timestamp = parseInt(timestamp);
  if (this.currentTime == timestamp) {
    return;
  }

  this.currentTime = timestamp;

  var t, slide;
  for (var i in this.times) {
    if (i <= timestamp) {
      t = this.times[i];
      if (t[0] == '[') {
        var num = t.substring(t.indexOf('[')+1, t.indexOf(']'));
        slide = num-1;
      } else if (t[0] == '<') {
        var command = t.substring(t.indexOf('<') + 1, t.indexOf('>'));
        if (command == 'pause' && !this.hasPaused[i] && !jQuery('audio')[0].paused) {
          jQuery('audio')[0].pause();
          this.hasPaused[i] = true;
        } else {

        }
      } else {
        this.$div.text(this.times[i]);
      }
    } else {
      break;
    }
  }

  jQuery.deck('go', slide);
};

Transcript.prototype.hasPaused = [];

var SEGMENTS = 50;

var SegmentManager = function (length, progress, $obj) {
  this.length = Math.floor(length);
  this.progress = parseFloat(progress);
  this.$audio = $obj;

  $obj.attr('currentTime', progress * this.length);
};

SegmentManager.prototype.start = function() {
  this.lastStart = new Date().getTime();
};

SegmentManager.prototype.stop = function () {
  if (!this.lastStart) {
    return;
  } else {
    var now = new Date().getTime();
    var diff = now - this.lastStart;

    this.progress = this.progress + (diff / 1000 / this.length);
    this.lastStart = null;
  }
};

SegmentManager.prototype.update = function () {
  if (!this.$audio.attr('paused')) {
    this.stop();
    this.lastStart = new Date().getTime();
  }
};

SegmentManager.prototype.toString = function () {
  return this.progress;
};
