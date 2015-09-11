<style>
  .certificate {
    position: relative;
  }
  .graduate-name {
    font-size:  300%;
    left:       17%;
    position:   absolute;
    text-align: center;
    top:        38%;
    width:      69%;
  }
  .graduation-date {
    font-size:  300%;
    left:       57%;
    position:   absolute;
    text-align: center;
    top:        64%;
    width:      37%;
  }
</style>
<div class="certificate">
  <span><?php print theme('image', array('path' => $certificate_image)); ?></span>
  <span class="graduate-name"><?php print $graduate_name; ?></span>
  <span class="graduation-date"><?php print $graduation_date; ?></span>
</div>
