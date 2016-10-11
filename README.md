FISSEQ with R
==============

`fisseq` is a powerful minimal R package that interfaces C++ image processing tools with higher level bioinformatics, statistical and visualization tools from R.

### Current dependencies

| library        | purpose           | language  | size  |
| ------------- |:-------------:| -----:|
| OpenCV 3.0      | image processing | C++ |  |
| libics 1.5.2      | reading and writing Flow Cytometry format      |   C | |
| FFTW3 | Fourier transform for deconvolution      |    C++ |


### Installation instructions

Since this is a developing version no static binaries are compiled and henc ethe suer first needs to compile the C/C++ libraries from source (this makes updating considerably easy until all core features are there then we'll compile binaries).

Begin by compiling OpenCV (depending on if you have core libraries for rreading writing TIFF/PNG etc installed or not this could eithe rtake 20 minutes of several hours):








