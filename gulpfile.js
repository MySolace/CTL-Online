var gulp       = require('gulp'),;
var sass       = require('gulp-ruby-sass');
var autoprefix = require('gulp-autoprefixer');
var notify     = require("gulp-notify");
var bower      = require('gulp-bower');

var config = {
  themeBase:'./lib/themes/ctl_theme',
  bowerDir: './bower_components',
  source:   'ctl.scss'
};

gulp.task('bower', function () {
  return bower().pipe(gulp.dest(config.bowerDir))
});

gulp.task('icons', function () {
  return gulp.src(config.bowerDir + '/fontawesome/fonts/**.*')
    .pipe(gulp.dest(config.themeBase + '/fonts'));
});

gulp.task('css', function () {
  return gulp.src(config.themeBase + '/sass/' + config.source)
    .pipe(sass({
      style: 'compressed',
      loadPath: [
        './resources/sass',
        config.bowerDir + '/bootstrap-sass-official/assets/stylesheets',
        config.bowerDir + '/fontawesome/scss',
      ]
    })
    .on("error", notify.onError(function (error) {
      return "Error: " + error.message;
    })))
    .pipe(autoprefix('last 2 version'))
    .pipe(gulp.dest(config.themeBase + '/css'));
});

// Rerun the task when a file changes
gulp.task('watch', function () {
  gulp.watch(config.sassPath + '/**/*.scss', ['css']);
});

gulp.task('default', ['bower', 'icons', 'css']);
