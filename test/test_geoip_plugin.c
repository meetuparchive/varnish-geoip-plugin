#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <GeoIPCity.h>

GeoIPRecord* get_geoip_record(const char *ip);
 
int main( int argc, char** argv)
{
  const char *symbol_name = "get_geoip_record";
  const char *plugin_name = SRCDIR"/src/libgeoip_plugin.so";

  FILE *f;
  char ip[20];
  char expected_country[10];
  GeoIPRecord *gir = NULL;

  int tests = 0;
  int failures = 0;

  void *handle = NULL;

  // now do other tests.
  f = fopen("test_cases.txt", "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open test_cases.txt\n");
    return 1;
  }

  while (fscanf(f, "%s%s", ip, expected_country) != EOF) {
    tests++;
    fprintf(stderr, "Testing %s's country is %s...", ip, expected_country);
    gir = (GeoIPRecord *)get_geoip_record(ip);
    if (gir) {
      if (strcmp(gir->country_code, expected_country) == 0) {
        fprintf(stderr, "ok\n");
      }
      else {
        fprintf(stderr, "fail\n");
        failures++;
      }
      GeoIPRecord_delete(gir);
    }
    else {
      if (strcmp(expected_country, "Unknown") == 0) {
        fprintf(stderr, "ok\n");
      }
      else {
        fprintf(stderr, "fail\n");
      }
    }
    gir = NULL;
  }

  if (failures > 0) {
    printf("\n\nResults: %d/%d Failed.\n", failures, tests);
    return 1;
  }
  else {
    printf("\n\nResults: %d Successes.\n", tests);
    return 0;
  }
}
