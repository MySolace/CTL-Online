var elixir = require('laravel-elixir');

require('laravel-elixir-bower-io');

elixir.config.production = true;

elixir.config.assetsPath = 'lib/themes/ctl_theme';
elixir.config.publicPath = 'lib/themes/ctl_theme';
elixir.config.sourcemaps = false;
elixir.config.css.sass.pluginOptions.includePaths = [
  'bower_components/bootstrap-sass-official/assets/stylesheets',
  'bower_components/fontawesome/scss'
];

// Output line numbers during development for debugging.
if (!elixir.production) {
  elixir.config.css.sass.pluginOptions.sourceComments = 'map';
}

elixir(function (mix) {
  mix.Bower();
  mix.copy('bower_components/fontawesome/fonts', elixir.config.publicPath + '/fonts');
  mix.copy('bower_components/bootstrap-sass-official/assets/fonts/bootstrap', elixir.config.publicPath + '/fonts/bootstrap');
  mix.sass('ctl.scss');
});
