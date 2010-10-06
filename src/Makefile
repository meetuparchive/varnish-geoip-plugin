LDLIBS=-lGeoIP

geoip_plugin.so:	geoip_plugin.c
	gcc -shared -fPIC $< -o $@ $(LDLIBS)

test:	geoip_plugin_test.c geoip_plugin.so
	gcc $< -o geoip_plugin_test -ldl $(LDLIBS)
	LD_LIBRARY_PATH=$$PWD ./geoip_plugin_test

clean:
	rm -f geoip_plugin.so geoip_plugin_test
