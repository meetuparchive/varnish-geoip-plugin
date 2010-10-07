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


AC_MSG_CHECKING([GeoIP City Data])
if test -z "$GEOIP_CITY_DATA"
then
    for f in /usr/share/GeoIP /usr/local/share/GeoIP
    do
        if test -e "$f/GeoLiteCity.dat"
        then
            GEOIP_CITY_DATA="$fGeoLiteCity.dat"
        fi
    done

    for f in /usr/share/GeoIP /usr/local/share/GeoIP
    do
        if test -e "$f/GeoIPCity.dat"
        then
            GEOIP_CITY_DATA="$fGeoIPCity.dat"
        fi
    done

    if test -z "$GEOIP_CITY_DATA"
    then
        AC_MSG_ERROR([not found], [1])
    else
        AC_MSG_RESULT([yes])
    fi
else
    if test -e "$GEOIP_CITY_DATA"
    then
        AC_MSG_RESULT([yes])
    else
        AC_MSG_ERROR([not found], [1])
    fi
fi

AC_SUBST([GEOIP_CITY_DATA], ["$GEOIP_CITY_DATA"])

AC_CONFIG_FILES([Makefile src/Makefile vcl/Makefile test/Makefile])
AC_OUTPUT
