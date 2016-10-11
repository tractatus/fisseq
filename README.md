FISSEQ with R
==============

`fisseq` is a powerful minimal R package that interfaces C++ image processing tools with higher level bioinformatics, statistical and visualization tools from R.

### Current dependencies

| library        | purpose           | language  | size  |
| ------------- |:-------------:| -----:| ----------: |
| OpenCV 3.0      | image processing | C++ | 300 Mb |
| libics 1.5.2      | reading and writing Flow Cytometry format      |   30 Mb |
| FFTW3 | Fourier transform for deconvolution      |    C++ | 3 Mb |


### Installation instructions

Since this is a developing version no static binaries are compiled and hence the user first needs to compile the C/C++ libraries from source (this makes updating considerably easy until all core features are in place and have been tested. By that time we'll compile binaries and the whole package will be as easy to install as any package on CRAN).

Begin by compiling OpenCV (depending on if you have core libraries for rreading writing TIFF/PNG etc installed or not this could eithe rtake 20 minutes of several hours):

### How to update to the latest version:






