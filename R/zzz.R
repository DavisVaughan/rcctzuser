.onLoad <- function(libname, pkgname) {
  # Required to access C++ callables
  requireNamespace("rcctz", quietly = TRUE)
}
