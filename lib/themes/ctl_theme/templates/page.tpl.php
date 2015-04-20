<?php
/**
* @file
* Main page template.
*/
?>
<!--id="branding"-->
<nav class="navbar navbar-default navbar-fixed-top">
    <div class="container">
        <a class="navbar-brand" href="/">CTL ONLINE</a>
        <?php if ($page['site_nav']): ?>
            <?php print render($page['site_nav']); ?>
        <?php endif; ?>
    </div>
</nav>

<?php /*
<div class="container">
    <?php print $breadcrumb; ?>
</div>
*/ ?>

<div id="navigation">
    <div class="container">
        <?php if ($secondary_local_tasks): ?>
            <div class="tabs-secondary clearfix"><ul class="tabs secondary"><?php print render($secondary_local_tasks); ?></ul></div>
        <?php endif; ?>
    </div>
</div>

<div id="page">
    <div class="container">
        <?php print render($title_prefix); ?>

        <?php if (isset($page['content_before'])): ?>
                <div id="content-before">
                        <?php print render($page['content_before']); ?>
                </div>
        <?php endif; ?>
        <?php if ($title): ?>
                <h1 class="page-title"><?php print $title; ?></h1>
        <?php endif; ?>

        <?php print render($title_suffix); ?>

        <div class="node-nav">
            <?php if ($primary_local_tasks): ?>
                <?php print render($primary_local_tasks); ?>
            <?php endif; ?>
        </div>

        <div id="content" class="clearfix">
                <div class="element-invisible"><a id="main-content"></a></div>

        <?php if ($messages): ?>
                <div id="console" class="clearfix"><?php print $messages; ?></div>
        <?php endif; ?>

        <?php if ($page['help']): ?>
                <div id="help">
                        <?php print render($page['help']); ?>
                </div>
        <?php endif; ?>

        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

  <div id="content-wrapper">

    <?php if (isset($page['sidebar_left'])): ?>
      <div id="sidebar-left">
        <?php print render($page['sidebar_left']); ?>
      </div>
    <?php endif; ?>

    <div id="main-content">
            <?php print render($page['content']); ?>
          </div>

    <?php if (isset($page['sidebar_right'])): ?>
      <div id="sidebar-right">
        <?php print render($page['sidebar_right']); ?>
      </div>
    <?php endif; ?>

        </div>

        <?php if (isset($page['content_after'])): ?>
                <div id="content-after">
                        <?php print render($page['content_after']); ?>
                </div>
        <?php endif; ?>

        </div>

        <div id="footer">
                <?php print $feed_icons; ?>
        </div>
    </div>
</div>
