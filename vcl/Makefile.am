varnishpluginsdir = $(libdir)/varnish/plugins
varnishplugins_DATA = geoip_plugin.vcl

CLEANFILES = $(varnishplugins_DATA)
EXTRA_DIST = geoip_plugin.vcl.in

do_subst = sed -e 's,[@]varnishpluginsdir[@],$(varnishpluginsdir),g'

geoip_plugin.vcl: geoip_plugin.vcl.in Makefile
	$(do_subst) < $(srcdir)/geoip_plugin.vcl.in > geoip_plugin.vcl