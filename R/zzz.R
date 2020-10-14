.onLoad <- function(libname, pkgname) {
  # Loading the package is required to register the C++ callables.
  # We Import it so this should always work.
  requireNamespace("rcctz", quietly = TRUE)
}
