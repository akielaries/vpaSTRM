# Introduction
WIP repo aiming to stream feeds from RTSP based IP
cameras. Previously implemented in Python, this 
version aims to improve performance and usability 
and will be primarily focused on implementations in
C and C++. The goal is to use FFMPEG in conjunction
with OpenCV. The use of Python will be made useful 
again for potential cases of statistical analysis, 
machine learning, and other ideas involving data
visualization. 

End result will include a functioning package allowing users to utilize 
this application in whatever way they see fit. This project heavily encourages
contributors to suggest and make changes to this, what I aim to be, open source 
project. 
contributors to suggest and make changes to this, what I aim to be an, open source 
project. Developers implementing their own solution to a similar problem are also
heavily encouraged to contribute or use parts of this project for their own
implementations!


> :warning: *This repo is forked and detached from [here](https://github.com/DiscoverCCRI/ip_cam) and serves
as a "new version" also developed by [me](https://github.com/akielaries), building off of the application
used for the DiscoverCCRI research study. This project welcomes contributors!*
---


# Ideas
- think of different py libs to implement GUI, PyQt, Tkinter, etc
- maybe implement my own, if going for speed and effeciency lets write it in C!
- modularize what ever the final result is for the demo into something usable
for an application. 
- if we are using C, research how to a C-based GUI can talk with our existing python
implementations.
- research using GTK with C
- Research using curses (terminal-based GUI)
- hash out the issues with buffering on our test cams
- instead of FFMPEG try with GStreamer

# Dependencies

### OpenCV
Can be quite a process to install and also requires dependencies in itself
so I will offer two methods of installation, I was able to get the lib 
working using the method below. 

> :warning: GStreamer can be used in place of FFMPEG, which will be enable by
default.

```
# install dependencies
$ sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev python3-dev python3-numpy libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-dev python3-pip python3-numpy

# FFMPEG 
sudo apt-get -y install \
  autoconf \
  automake \
  build-essential \
  cmake \
  git-core \
  libass-dev \
  libfreetype6-dev \
  libgnutls28-dev \
  libsdl2-dev \
  libtool \
  libva-dev \
  libvdpau-dev \
  libvorbis-dev \
  libxcb1-dev \
  libxcb-shm0-dev \
  libxcb-xfixes0-dev \
  meson \
  ninja-build \
  pkg-config \
  texinfo \
  wget \
  yasm \
  zlib1g-dev
  
# GStreamer
sudo apt-get -y install \
  libgstreamer1.0-dev \
  libgstreamer-plugins-base1.0-dev \
  libgstreamer-plugins-bad1.0-dev \
  gstreamer1.0-plugins-base \
  gstreamer1.0-plugins-good \
  gstreamer1.0-plugins-bad \
  gstreamer1.0-plugins-ugly \
  gstreamer1.0-libav \
  gstreamer1.0-tools \
  gstreamer1.0-x \
  gstreamer1.0-alsa \
  gstreamer1.0-gl \
  gstreamer1.0-gtk3 \
  gstreamer1.0-qt5 \
  gstreamer1.0-pulseaudio
  
$ sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
$ sudo apt-get install gstreamer1.0-plugins
$ sudo apt-get install gstreamer1.0-gl

# Clone the repository
$ git clone git@github.com:opencv/opencv.git

$ cd opencv

# create build dir and enter
$ mkdir build && cd build

# Configure
$ cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/include \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D BUILD_EXAMPLES=OFF \
-D INSTALL_PYTHON_EXAMPLES=OFF \
-D INSTALL_C_EXAMPLES=OFF \
-D PYTHON_EXECUTABLE=$(which python2) \
-D BUILD_opencv_python2=OFF \
-D PYTHON3_EXECUTABLE=$(which python3) \
-D PYTHON3_INCLUDE_DIR=$(python3 -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())") \
-D PYTHON3_PACKAGES_PATH=$(python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())") \
-D WITH_GSTREAMER=ON \
-D WITH_FFMPEG=ON \
-D HAVE_FFMPEG=ON \
-D WITH_GTK=ON \
-D BUILD_SHARED_LIBS=OFF \
-D BUILD_TIFF=ON \
 ..

cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D BUILD_EXAMPLES=OFF \
-D INSTALL_PYTHON_EXAMPLES=OFF \
-D INSTALL_C_EXAMPLES=OFF \
-D PYTHON_EXECUTABLE=$(which python2) \
-D BUILD_opencv_python2=OFF \
-D PYTHON3_EXECUTABLE=$(which python3) \
-D PYTHON3_INCLUDE_DIR=$(python3 -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())") \
-D PYTHON3_PACKAGES_PATH=$(python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())") \
 ..


# Build (spread load accross 4 core, use appropriately)
$ make-j4
```

Check your opencv2 files are in /usr/include and not
/usr/local/include. If they are stored in the latter, simply run 
```
sudo mv -r /usr/local/include/opencv4/opencv2/ /usr/include/
```
