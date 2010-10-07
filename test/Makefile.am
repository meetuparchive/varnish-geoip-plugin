check_PROGRAMS = test-geoip-plugin
noinst_PROGRAMS = test-geoip-plugin

EXTRA_PROGRAMS = test-geoip-plugin

LDADD = $(top_builddir)/src/libgeoip_plugin.la
AM_CFLAGS = -DSRCDIR=\"$(top_srcdir)\"

test_geoip_plugin_SOURCES = test_geoip_plugin.c

EXTRA_DIST = test_cases.txt
TESTS = test-geoip-plugin