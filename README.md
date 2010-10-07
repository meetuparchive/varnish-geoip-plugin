# Geocoding Incoming Requests

This package contains the source for a little library used through inline C
in Varnish for converting IPs to "Lat,Long" or "City, Region, Country" to
be used for custom hashes, backends, translation, etc. 

It uses, and relies on the MaxMind GeoIP library available from:

   [http://www.maxmind.com/app/c](http://www.maxmind.com/app/c)

The site includes instructions on how to build the GeoIP library, which must
be installed prior to using the library and inline C.

# Building

To build the plugin, be sure the GeoIP library is installed and use the 
following:

    $ ./configure
    $ make
    $ make check
    $ sudo make install

The `configure` script will attempt to find GeoIP, and will also attempt
to find the GeoIP City database which is also required. The `configure`
script will search for either the paid version 'GeoIPCity.dat' or the 
Lite version 'GeoLiteCity.dat' in a few standard locations. If your 
database is not found, you can tell the `configure` script exactly where to
find it by doing:

    $ GEOIP_CITY_DATA=/path/to/data ./configure

`make install` will install the plugin and it's required files into 
`$(prefix)/lib/varnish/plugins` where `$(prefix)` is customizable by
passing `--prefix=/usr/local` to `configure`

# Making use of the library

If you follow the above steps, and everything goes smoothly, you should 
end up with `geoip_plugin.vcl` in `$(prefix)/lib/varnish/plugins` which
can be included in your VCL file like so:

    include "$(prefix)/lib/varnish/plugins/geoip_plugin.vcl";

Including `geoip_plugin.vcl` will define a new sub in your VCL file that
must be used, called `geocode_and_lookup` which can be called in the VCL
like so:

    call geocode_and_lookup;

This sub will attempt to geocode the client's IP address and if 
successful, define 2 headers `X-GeoIP-LatLong` and `X-GeoIP-City`. If 
geocoding cannot be done, the header `X-GeoIP-Unavailable` will be set 
to '1'.

The format of the headers is as follows:

    X-GeoIP-LatLong: -12.900919,10.200939
    X-GeoIP-City: Brooklyn, NY, US, 11219

In the case of X-GeoIP-LatLong, an empty string, will be substituted if
the information is unavailable.

`geocode_and_lookup` finishes with `return(lookup)`, as the name
indicates, therefore is only valid in places where calling `lookup` is
appropriate.

Note: Varnish will fail to load your VCL if you include the plugin, but
do not make use of it. If you do not make a call to `geocode_and_lookup`
do not use the `include` line.

When the loaded VCL makes use of `geoip_plugin.vcl` you should see 
"GeoIP plugin loaded." upon starting varnishd.