#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <GeoIPCity.h>
 
int main( int argc, char** argv)
{
  const char* symbol_name = "get_geoip_record";
  const char* plugin_name = "geoip_plugin.so";
  const GeoIPRecord* (*get_geoip_record)(const char* ip) = NULL;
  void *handle = NULL;
	
  handle = dlopen(plugin_name, RTLD_NOW);
  if (handle != NULL) {
    get_geoip_record = dlsym(handle, symbol_name);
    if (get_geoip_record == NULL) {
      fprintf( stderr, "\nError: Could not load GeoIP plugin:\n%s\n\n", dlerror() );
    }
    else {
      int i = 0;
      const char* ips[] = { 
        "195.110.128.11", // enit.it
        "157.166.224.25", // cnn.com
        "212.58.224.138", // bbc.co.uk
        "80.91.37.210", // www.aftenposten.no
        "192.168.0.1", // local IP
        NULL // unknown
      };
      const char* countries[] = {
        "IT",
        "US",
        "GB",
        "NO",
        "Unknown",
        "Unknown"
      }; 

      printf( "GeoIP plugin loaded successfully.\n");
      printf( "Testing IPs:\n" );
      for (i = 0; ; i++) {
        int success = 0;
        GeoIPRecord *gir = (GeoIPRecord *)(*get_geoip_record)(ips[i]);
        if (gir != NULL) {
          success = strcmp(gir->country_code, countries[i]) == 0;
        }
        else {
          success = strcmp(countries[i], "Unknown") == 0;
        }

        printf("%s => %s (%s)\n", ips[i], 
               gir ? gir->country_code : "Unknown", 
               success ? "OK" : "Failed");

        if (gir != NULL) {
          GeoIPRecord_delete(gir);
        }

        if (ips[i] == NULL) {
          break;
        }
      }
    }
  }
  else {
    fprintf( stderr, "\nError: Could not load GeoIP plugin:\n%s\n\n", dlerror() );
  }
  return 0;
}
