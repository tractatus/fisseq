#include <Rcpp.h>
using namespace Rcpp;

// OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

#include <libics.h>
#include "libics_sensor.h"
#include "libics_test.h"
#include "libics_intern.h"

#include <unistd.h>
#include <string>
#include <stdint.h>

using namespace std;


// take number image type number (from cv::Mat.type()), get OpenCV's enum string.
string getImgTypes(int imgTypeInt)
{
  int numImgTypes = 35; // 7 base types, with five channel options each (none or C1, ..., C4)

  int enum_ints[] =       {Ics_unknown,  Ics_uint8,  Ics_sint8,  Ics_uint16,  Ics_sint16,
                           Ics_uint32,  Ics_sint32,  Ics_real32,  Ics_real64,  Ics_complex32,
                           Ics_complex64};

  string enum_strings[] = {"Ics_unknown",  "Ics_uint8: unsigned char",  "Ics_sint8: signed char",  "Ics_uint16: unsigned short",  "Ics_sint16: signed short",
                           "Ics_uint32: unsigned int",  "Ics_sint32: signed int",  "Ics_real32: float",  "Ics_real64: double",  "Ics_complex32: float, float ",
                           "Ics_complex64: double, double"};

  for(int i=0; i<numImgTypes; i++)
  {
    if(imgTypeInt == enum_ints[i]) return enum_strings[i];
  }
  return "unknown image type";
}

RcppExport SEXP readICS(SEXP input, SEXP verbose) {
  BEGIN_RCPP
  Rcpp::RNGScope __rngScope;

  Rcpp::CharacterVector f(input);
  std::string ff(f[0]);
  //convert to C char version
  const char *filenameChar = ff.c_str();

  int VERBOSE = Rcpp::as<int>(verbose);

  ICS* ip;
  Ics_DataType dt;
  int ndims;
  size_t dims[ICS_MAXDIM];
  size_t strides[ICS_MAXDIM];
  size_t bufsize;
  void* buf;
  Ics_Error retval;
  char filename[ICS_MAXPATHLEN];
  int elemsize;
  int ii;
  size_t tmp;
  char errormessage[2048];

  int barWidth = 70;
  float progress = 0.0;

///Users/danielfurth/Downloads/fisseq_test.ics
  retval = IcsOpen (&ip, filenameChar, "r");
  if (retval != IcsErr_Ok)
    /* Flag error condition */ ;



  IcsGetLayout (ip, &dt, &ndims, dims);

  if(VERBOSE){
    Rcpp::Rcout << "Data type: " << getImgTypes(dt) << std::endl;
  }

  bufsize = IcsGetDataSize (ip);
  buf = malloc (bufsize);
  if (buf == NULL){
    Rcpp::Rcout << "====== ERROR ======" << std::endl;
  }
    /* Flag error condition*/ ;
  retval = IcsGetData (ip, buf, bufsize);
  if (retval != IcsErr_Ok){
    Rcpp::Rcout << "====== ERROR ======" << std::endl;
  }
    if(VERBOSE){ Rcpp::Rcout << "====== Image read ======" << std::endl;}

    int p;
    Ics_Format Format;
    int Sign;
    size_t Bits;
    char* s;

    IcsGetPropsDataType (ip->Imel.DataType, &Format, &Sign, &Bits);

    p = ip->Dimensions;
    int elements = 1;
    for (ii=0; ii<p; ii++)
      elements = elements*(unsigned long) ip->Dim[ii].Size;

    std::vector<uint16_t> b(elements);
    for(int j=0;j<elements;j++){
      b[j] = ((uint16_t *)buf)[j];
    }

    std::vector< float > histoCount;
    std::vector<float> rangeR;
    for(int col=0; col< (int)ip->Dim[4].Size;col++){
    //loop through z-stacks
   for(int k=0; k< (int)ip->Dim[2].Size;k++){



    Mat MatrixName = Mat((int)ip->Dim[1].Size, (int)ip->Dim[0].Size, CV_16U);

    for(int i=0; i< (int)ip->Dim[1].Size;i++){
      for(int j=0;j<(int)ip->Dim[0].Size;j++){
        MatrixName.at<ushort>(i,j) = (int)b[i*(int)ip->Dim[0].Size + j + k*((int)ip->Dim[0].Size*(int)ip->Dim[1].Size) + col*((int)ip->Dim[0].Size*(int)ip->Dim[1].Size*(int)ip->Dim[2].Size) ];
      }
    }

    double hmin, hmax;
    minMaxLoc(MatrixName, &hmin, &hmax);
    //Rcpp::Rcout <<  "Max, Min: " << hmin << " | " << hmax << std::endl;

    int histSize = 2048;
    float range[] = {hmin, hmax};
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;

    Mat hist;
    calcHist( &MatrixName, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);


    //Mat canvas = Mat::zeros(200, histSize, CV_8UC1);

    for (int j = 0; j < histSize-1; j++){
      histoCount.push_back(hist.at<float>(j));
    }

    /* MatrixName.convertTo(MatrixName,CV_8UC1,255.0/(200-0));
    imshow("test", MatrixName);
    waitKey(0);
    destroyWindow("test"); */
    rangeR.push_back(range[0]);
    rangeR.push_back(range[1]);
   }
   if(VERBOSE){Rcpp::Rcout << "  [";
     int pos = barWidth * progress;
     for (int w = 0; w < barWidth; ++w) {
       if (w < pos) Rcpp::Rcout << "=";
       else if (w == pos) Rcpp::Rcout << ">";
       else Rcpp::Rcout << " ";
     }
     Rcpp::Rcout << "] " << int(progress * 100.0) << "% \r" << std::cout.flush();//cout.flush();
     R_FlushConsole();
     R_ProcessEvents();
     R_CheckUserInterrupt();
     progress += (float)1/((int)ip->Dim[4].Size-1);
   }
    }

    if(VERBOSE){
  IcsPrintIcs(ip);
    }

  retval = IcsClose (ip);
  if (retval != IcsErr_Ok){}
    /* Flag error condition*/ ;


  return List::create(
    _["histo"] = histoCount,
    _["range"] = rangeR
  );
  END_RCPP
}
