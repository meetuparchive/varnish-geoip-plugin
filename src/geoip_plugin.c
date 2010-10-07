#include <stdio.h>
#include <config.h>


#ifdef HAVE_GEOIP_H
#include <GeoIP.h>
#endif

#ifdef HAVE_GEOIPCITY_H
#include <GeoIPCity.h>
#endif

#ifndef GEOIP_CITY_DATA
#define GEOIP_CITY_DATA "/usr/share/GeoIP/GeoIPCity.dat"
#endif

static GeoIP *gi = NULL;

GeoIPRecord*
get_geoip_record(const char* ip) {
  if (gi == NULL) {
    gi = GeoIP_open(GEOIP_CITY_DATA, GEOIP_MEMORY_CACHE);
  }
  if (gi == NULL) {
    fprintf(stderr, "Couldn't open GeoIP database at "
            "GEOIP_CITY_DATA");
            
  }
  else {
    return GeoIP_record_by_addr(gi, ip);
  }
  return NULL;
}
