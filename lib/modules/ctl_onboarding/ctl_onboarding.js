// TODO
// color coding brainstorming:
// - no color:  0 trainers
// - solid green:  > 0 trainers
// - translucent green:  change in number of trainers


(function ($) {
  Drupal.behaviors.ctlOnboardingAdmin = {
    attach: function (context, settings) {
      $('.form-item-ctl-onboarding-slot-codes-2 .form-type-select select', context).bind('change', function () {
        $this = $(this);
        num_trainers = this.value;
        if (num_trainers > 0) {
          $this.parent().addClass('changing-num-trainers');
        }
      });
    }
  };
})(window.jQuery);
