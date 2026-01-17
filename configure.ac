dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.54)

dnl Name your plug-in here
m4_define([plugin_name], [gimp-deskew-plugin])

dnl These three define the plug-in version number
m4_define([plugin_major_version], [1])
m4_define([plugin_minor_version], [1])
m4_define([plugin_micro_version], [0])

m4_define([plugin_version],
          [plugin_major_version.plugin_minor_version.plugin_micro_version])

AC_INIT([plugin_name], [plugin_version])

AC_DEFINE(PLUGIN_NAME, PACKAGE_NAME, [Deskew])
dnl AC_DEFINE(PLUGIN_VERSION, PACKAGE_VERSION, [2.2.0])

dnl AC_DEFINE(PLUGIN_MAJOR_VERSION, plugin_major_version, [2])
dnl AC_DEFINE(PLUGIN_MINOR_VERSION, plugin_minor_version, [2])
dnl AC_DEFINE(PLUGIN_MICRO_VERSION, plugin_micro_version, [0])

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS(config.h)

AM_INIT_AUTOMAKE([no-define subdir-objects])

AC_PROG_CC
AC_PROG_CXX


ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

AM_MAINTAINER_MODE


dnl Use -Wall if we have gcc.
changequote(,)dnl
if test "x$GCC" = "xyes"; then
  case " $CFLAGS " in
  *[\ \	]-Wall[\ \	]*) ;;
  *) CFLAGS="$CFLAGS -Wall" ;;
  esac
fi
changequote([,])dnl


GIMP_REQUIRED_VERSION=3.0.0

PKG_CHECK_MODULES(GIMP,
  gimp-3.0 >= $GIMP_REQUIRED_VERSION gimpui-3.0 >= $GIMP_REQUIRED_VERSION)

AC_SUBST(GIMP_CFLAGS)
AC_SUBST(GIMP_LIBS)

GIMP_LIBDIR=`$PKG_CONFIG --variable=gimplibdir gimp-3.0`
AC_SUBST(GIMP_LIBDIR)


dnl i18n stuff

GETTEXT_PACKAGE=gimp30-deskew-plugin
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE",
				    [The gettext translation domain.])

dnl Add the languages which your application supports here.
dnl ALL_LINGUAS="az de fr sk sv zh_TW"
ALL_LINGUAS="es ru"

AC_PROG_INTLTOOL
AM_GLIB_GNU_GETTEXT

AC_CHECK_FUNCS(bind_textdomain_codeset)

LOCALEDIR="${datadir}/locale"
if test "$DATADIRNAME" = "lib"; then
   LOCALEDIR="$libdir/locale"
fi
AC_SUBST(LOCALEDIR)

DATADIR="${datadir}/plugin_name"
AC_SUBST(DATADIR)


AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
help/Makefile
help/en/Makefile
help/es/Makefile
help/images/Makefile
])

AC_OUTPUT
