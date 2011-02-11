varnishpluginsdir = $(prefix)/plugins

varnishplugins_LTLIBRARIES = libgeoip_plugin.la

libgeoip_plugin_la_LDFLAGS = -shared -fPIC -lGeoIP
libgeoip_plugin_la_SOURCES = geoip_plugin.c

libgeoip_plugin_la_CFLAGS = -DGEOIP_CITY_DATA=\"@GEOIP_CITY_DATA@\"
