// Generated by cpp11: do not edit by hand
// clang-format off


#include "cpp11/declarations.hpp"

// code.cpp
void fun();
extern "C" SEXP _rcctzuser_fun() {
  BEGIN_CPP11
    fun();
    return R_NilValue;
  END_CPP11
}

extern "C" {
/* .Call calls */
extern SEXP _rcctzuser_fun();

static const R_CallMethodDef CallEntries[] = {
    {"_rcctzuser_fun", (DL_FUNC) &_rcctzuser_fun, 0},
    {NULL, NULL, 0}
};
}

extern "C" void R_init_rcctzuser(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
