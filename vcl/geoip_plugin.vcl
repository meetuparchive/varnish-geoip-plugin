C{
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GeoIPCity.h>

static const char* (*get_geoip_record)(char *ip) = NULL;

// simple enough to copy instead of resolving it at runtime
void GeoIPRecord_delete(GeoIPRecord *gir) 
{
  free(gir->region);
  free(gir->city);
  free(gir->postal_code);
  free(gir);
}

__attribute__((constructor))
void load_module()
{
  const char* plugin_name = "/usr/local/lib/varnish/plugins/geoip_plugin.so";
  void *handle = NULL;
	
  handle = dlopen(plugin_name, RTLD_NOW);
  if (handle != NULL) {
    get_geoip_record = dlsym(handle, "get_geoip_record");
    if (get_geoip_record == NULL) {
      fprintf( stderr, "\nError: Could not load "
               "GeoIP plugin:\n%s\n\n", dlerror() );
    }
    else {
      printf("GeoIP plugin loaded.\n");
    }
  }
  else {
    fprintf(stderr, "\nError: Could not load"
            " GeoIP plugin:\n%s\n\n", dlerror());
  }
}
}C

sub geocode_and_lookup {
    C{
      GeoIPRecord *gir;
      char city[100];
      char latlong[50];

      gir = (GeoIPRecord *)get_geoip_record(VRT_IP_string(sp, VRT_r_client_ip(sp)));
      if (gir != NULL) {
        snprintf(city, 100, "%s, %s, %s, %s",
                 gir->city ? gir->city : "",
                 gir->region ? gir->region: "",
                 gir->country_code ? gir->country_code : "",
                 gir->postal_code ? gir->postal_code : "");
        snprintf(latlong, 100, "%f,%f", gir->latitude, gir->longitude);

        VRT_SetHdr(sp, HDR_REQ, "\020X-GeoIP-LatLong:", latlong, vrt_magic_string_end);
        VRT_SetHdr(sp, HDR_REQ, "\015X-GeoIP-City:", city, vrt_magic_string_end);
        GeoIPRecord_delete(gir);
      }
      else {
        VRT_SetHdr(sp, HDR_REQ, "\024X-GeoIP-Unavailable:", "1", vrt_magic_string_end);
      }
    }C

    return(lookup);
}
