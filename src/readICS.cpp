#include <Rcpp.h>
using namespace Rcpp;

#include <libics.h>

RcppExport SEXP readICS(SEXP input, SEXP outputfolder, SEXP outname, SEXP kernel, SEXP display,  SEXP outputfile, SEXP writetoconsole) {
  BEGIN_RCPP
  Rcpp::RNGScope __rngScope;

  ICS* ip;
  Ics_DataType dt;
  int ndims;
  size_t dims[ICS_MAXDIM];
  size_t bufsize;
  void* buf;
  Ics_Error retval;

  retval = IcsOpen (&ip, "file.ics", "r");
  if (retval != IcsErr_Ok)
  /* Flag error condition */ ;

  IcsGetLayout (ip, &dt, &ndims, dims);
  bufsize = IcsGetDataSize (ip);
  buf = malloc (bufsize);
  if (buf == NULL)
  /* Flag error condition*/ ;
  retval = IcsGetData (ip, buf, bufsize);
  if (retval != IcsErr_Ok)
  /* Flag error condition */ ;

/*
 * There are some other functions available to get
 * more info on the image in the .ics file.
 */

  retval = IcsClose (ip);
  if (retval != IcsErr_Ok)
  /* Flag error condition*/ ;
  END_RCPP
}
