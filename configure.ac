AC_PREREQ([2.63])
AC_INIT([geoip_plugin], [0.1], [andrew@meetup.com])
AM_INIT_AUTOMAKE([geoip_plugin], [0.1])
AC_CONFIG_SRCDIR([src/geoip_plugin.c])
AC_CONFIG_HEADERS([src/config.h])

AC_ARG_VAR([GEOIP_CITY_DATA], [location of GeoIP City Data File])

AC_PROG_CC

AM_PROG_LIBTOOL

AC_CHECK_LIB([GeoIP], [GeoIP_open])
AC_CHECK_LIB([dl], [dlsym])

AC_CHECK_HEADERS([stdlib.h stdio.h GeoIP.h GeoIPCity.h])


dnl AC_MSG_CHECKING([GeoIP City Data])
dnl if test -z "$GEOIP_CITY_DATA"
dnl then
dnl     for f in /usr/share/GeoIP /usr/local/share/GeoIP
dnl     do
dnl         if test -e "$f/GeoLiteCity.dat"
dnl         then
dnl             GEOIP_CITY_DATA="$fGeoLiteCity.dat"
dnl         fi
dnl     done

dnl     for f in /usr/share/GeoIP /usr/local/share/GeoIP
dnl     do
dnl         if test -e "$f/GeoIPCity.dat"
dnl         then
dnl             GEOIP_CITY_DATA="$fGeoIPCity.dat"
dnl         fi
dnl     done

dnl     if test -z "$GEOIP_CITY_DATA"
dnl     then
dnl         AC_MSG_ERROR([not found], [1])
dnl     else
dnl         AC_MSG_RESULT([yes])
dnl     fi
dnl else
dnl     if test -e "$GEOIP_CITY_DATA"
dnl     then
dnl         AC_MSG_RESULT([yes])
dnl     else
dnl         AC_MSG_ERROR([not found], [1])
dnl     fi
dnl fi

AC_SUBST([GEOIP_CITY_DATA], ["$GEOIP_CITY_DATA"])

AC_CONFIG_FILES([Makefile src/Makefile vcl/Makefile test/Makefile])
AC_OUTPUT
