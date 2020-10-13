#include <cpp11.hpp>
#include <rcctz.h>

[[cpp11::register]]
cpp11::doubles fun() {
  cctz::civil_second cs = cctz::civil_second(2020, 1, 5, 1, 1, 1);

  cctz::time_zone tz;
  const char* c_tz = "America/New_York";

  if (!rcctz::tz_load(c_tz, &tz)) {
    cpp11::stop("Failed to load time zone.");
  }

  cctz::time_zone::civil_lookup cl = rcctz::lookup_civil(cs, tz);

  cpp11::writable::doubles out(1);

  switch (cl.kind) {
  case cctz::time_zone::civil_lookup::UNIQUE: {
    out[0] = cl.trans.time_since_epoch().count();
  }
  case cctz::time_zone::civil_lookup::SKIPPED: {
    // In a DST gap, this time does not exist
    out[0] = NA_REAL;
  }
  case cctz::time_zone::civil_lookup::REPEATED: {
    // Ambiguous time due to DST fallback, choose the pre-fallback time?
    out[0] = cl.pre.time_since_epoch().count();
  }
  }

  out.attr("class") = {"POSIXct", "POSIXt"};
  out.attr("tzone") = c_tz;

  return out;
}
