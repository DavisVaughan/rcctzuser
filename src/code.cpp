#include <cpp11.hpp>
#include <rcctz.h>

[[cpp11::register]]
cpp11::doubles fun(cpp11::strings tzone) {
  rcctz::civil_second cs = rcctz::civil_second(2020, 1, 5, 1, 1, 1);

  rcctz::time_zone tz;
  std::string cpp_tz = rcctz::tz_from_tzone(tzone);

  if (!rcctz::tz_load(cpp_tz, &tz)) {
    cpp11::stop("Failed to load time zone.");
  }

  rcctz::time_zone::civil_lookup cl = tz.lookup(cs);

  cpp11::writable::doubles out(1);

  switch (cl.kind) {
  case rcctz::time_zone::civil_lookup::UNIQUE: {
    out[0] = cl.trans.time_since_epoch().count();
  }
  case rcctz::time_zone::civil_lookup::SKIPPED: {
    // In a DST gap, this time does not exist
    out[0] = NA_REAL;
  }
  case rcctz::time_zone::civil_lookup::REPEATED: {
    // Ambiguous time due to DST fallback, choose the pre-fallback time?
    out[0] = cl.pre.time_since_epoch().count();
  }
  }

  out.attr("class") = {"POSIXct", "POSIXt"};
  out.attr("tzone") = cpp_tz;

  return out;
}
