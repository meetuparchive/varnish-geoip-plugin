#include <GeoIP.h>
#include <GeoIPCity.h>

#ifndef GEOIP_DATABASE_LOCATION
#define GEOIP_DATABASE_LOCATION "/usr/local/meetup/conf/GeoIPCity.dat"
#endif

static GeoIP *gi = NULL;

GeoIPRecord*
get_geoip_record(const char* ip) {
  if (gi == NULL) {
    gi = GeoIP_open(GEOIP_DATABASE_LOCATION, GEOIP_MEMORY_CACHE);
  }
  if (gi == NULL) {
    fprintf(stderr, "Couldn't open GeoIP database at "
            "GEOIP_DATABASE_LOCATION");
            
  }
  else {
    return GeoIP_record_by_addr(gi, ip);
  }
  return NULL;
}
