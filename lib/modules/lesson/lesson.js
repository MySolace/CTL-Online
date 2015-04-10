(function ($) {
  Drupal.behaviors.lesson = {
    attach: function (context, settings) {
      // Passing these into the init method doesn't
      // seem to work.
      $.deck.defaults.keys = {
        next: [],
        previous: []
      };

      $.deck('section', {
        hashPrefix: '',
      });
      $.deck('enableScale');


      var manager = null;
      $('audio').on('loadeddata', function () {
        console.log($(this).prop('duration'));
        manager = new SegmentManager($(this).prop('duration'), settings.lesson_progress, $(this));
      });

      $('audio').on('pause waiting seeking', function () {
        console.log('pause and such');
      });

      $('audio').on('timeupdate', function (e) {
        var t = $(this).prop('currentTime');

        manager.updateSegment(t);
      });

      var lastProgress = null;

      setInterval(function () {
        var progress = manager.toString();

        if (progress !== lastProgress) {
          $.post('/node/' + settings.nid + '/audio_progress', {progress: progress});
          lastProgress = progress;
        }
      }, 5000);
    }
  }
})(jQuery);


var SEGMENTS = 50;

var SegmentManager = function (length, progress, $obj) {
  this.segments = {};
  length = Math.floor(length);

  var temp = parseInt(progress, 16).toString(2);

  var segmentLength = length / SEGMENTS;
  this.currentSegment = 0;
  var somethingComplete = false;

  for (var i = 0; i < SEGMENTS; i++) {
    var l = Math.round(segmentLength * i);
    this.segments[l] = new Segment(l, l+1);

    if (temp[i] == 1) {
      this.segments[l].complete = true;
      somethingComplete = true;
    } else if (this.currentSegment == 0) {
      this.currentSegment = l;
    }
  }

  // If we're still at 0 but something has been listened to, then
  // that means everything has been listened to.
  if (this.currentSegment == 0 && somethingComplete) {
    this.currentSegment = Math.round(segmentLength * (SEGMENTS-1));
  }

  $obj.prop('currentTime', this.currentSegment);
};

SegmentManager.prototype.getSegments = function () {
  return this.segments;
};

SegmentManager.prototype.updateSegment = function (t) {
  if (t >= this.segments[this.currentSegment].max || t <= this.segments[this.currentSegment].min) {
    for (var i in this.segments) {
      if (t < this.segments[i].max && t > this.segments[i].min) {
        this.currentSegment = i;
        break;
      }
    }
  }

  this.segments[this.currentSegment].track(t);
};

SegmentManager.prototype.toString = function () {
  var binary = '';
  for (var i in this.segments) {
    binary = ((this.segments[i].complete) ? 1 : 0) + binary;
  }

  return parseInt(binary, 2).toString(16);
};

var Segment = function (start, end) {
  this.min = start;
  this.max = end;

  this.localMin = 1e100;
  this.localMax = -1;

  this.complete = false;
};

Segment.prototype.track = function (time) {
  if (this.complete) {
    return;
  }

  time = Math.round(time);

  if (time > this.localMax) {
    this.localMax = time;
  } else if (time < this.localMin) {
    this.localMin = time;
  }

  if (this.localMin <= this.min && this.localMax >= this.max) {
    this.complete = true;
  }
};
