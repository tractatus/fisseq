FISSEQ with R
==============

`fisseq` is a powerful minimal R package for in situ sequencing microscopic images. It interfaces C++ image processing tools with higher level bioinformatics, statistical and visualization tools from R. It is designed to work well on an ordinary laptop with limited RAM (~8 GB), as well as a large server or cluster.

### Current dependencies

| library        | purpose           | language  | size  |
| ------------- |:-------------:| -----:| ----------: |
| OpenCV 3.0      | image processing | C++ | 267 MB |
| libics 1.5.2      | reading and writing Flow Cytometry format |  C   |   468.7 kB |
| FFTW3 | Fourier transform for deconvolution      |    C++ | 4.1 MB |


### Installation instructions

Since this is a developing version no static binaries are compiled and hence the user first needs to compile the C/C++ libraries from source (this makes updating considerably easy until all core features are in place and have been tested. By that time we'll compile binaries and the whole package will be as easy to install as any package on CRAN).

Begin by compiling OpenCV (depending on if you have core libraries for rreading writing TIFF/PNG etc installed or not this could eithe rtake 20 minutes of several hours).
####Mac OSX

#####Install OpenCV 3.0:

make sure you have XCode with command line tools installed (otherwise install it from the Appstore).
Check if you have homebrew by opening the Terminal app and enter:
```
which brew
```
If it responds "brew not found" you do not have homebrew installed, install it by typing:
```
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

With homebrew install OpenCV 3.0:
```
brew install https://raw.githubusercontent.com/Homebrew/homebrew-science/d154fff3192ab13bb69b0b7cb5b297a947a565e2/opencv3.rb
brew pin opencv3
```



#####Install libics:
Type the following into the terminal.

```
curl -L  https://sourceforge.net/projects/libics/files/libics/libics-1.5.2.tar.gz > libics-1.5.2.tar.gz
tar zxf glibics-1.5.2.tar.gz
cd libics-1.5.2
./configure
make
sudo make install
```

#####Install FFTW3:
Type the following into the terminal.

```
curl -O http://www.fftw.org/fftw-3.3.4.tar.gz
tar zxf fftw-3.3.4.tar.gz
cd fftw-3.3.4
./configure --enable-shared --enable-threads
make
sudo make install
```

####On Linux:
```
sudo apt-get install libopencv-dev
sudo apt-get install fftw3 fftw3-dev pkg-config
```

####Install the fisseq R package from R:
 
Open up R and type the following:
```R
if (!require(devtools)) {
  install.packages("devtools")
}
devtools::install_github("tractatus/fisseq")
```


### How to update to the latest version:

Open up R and first remove the fisseq package:
```R
#Uninstall anything still remaining of old wholebrain R package.
 remove.packages('fisseq')
#importantly quit R before reinstalling the wholebrian package.
 quit()
```

Open up R again and install the package again:
```R
#check if devtools is installed by trying to load it. 
#if not then install devtools.
#Devtools is needed to install packages from Github.
if (!require(devtools)) { install.packages("devtools") }
#intall wholebrain from Github. 
#devtools:: calls the command install_github directly from devtools.
# "::" calls functions directly without loading entire library. 
 devtools::install_github("tractatus/fisseq")
 library(wholebrain)
```





