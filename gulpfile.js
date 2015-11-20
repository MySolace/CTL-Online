var elixir = require('laravel-elixir');

require('laravel-elixir-bower-io');
// require('laravel-elixir-postcss');

elixir.config.production = true;

elixir.config.assetsPath = 'lib/themes/ctl';
elixir.config.publicPath = 'lib/themes/ctl';
elixir.config.sourcemaps = false;
elixir.config.css.sass.pluginOptions.includePaths = [
  'bower_components/bootstrap-sass-official/assets/stylesheets',
  'bower_components/fontawesome/scss',
  'bower_components/normalize-css'
];

// Output line numbers during development for debugging.
if (!elixir.production) {
  elixir.config.css.sass.pluginOptions.sourceComments = 'map';
}

elixir(function (mix) {
  mix.Bower();
  mix.copy('bower_components/fontawesome/fonts', elixir.config.publicPath + '/fonts');
  mix.copy('bower_components/bootstrap-sass-official/assets/fonts/bootstrap', elixir.config.publicPath + '/fonts/bootstrap');
  // http://danielstrunk.me/blog/2015/03/11/one-cool-trick-to-sassify/
  mix.copy('bower_components/normalize-css/normalize.css', 'bower_components/normalize-css/_normalize.scss');
  mix.sass('ctl.scss');
});
