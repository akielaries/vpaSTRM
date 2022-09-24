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
  

# Clone the repository
$ git clone git@github.com:opencv/opencv.git

$ cd opencv

# create build dir and enter
$ mkdir build && cd build

# Configure
$ cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D BUILD_EXAMPLES=ON \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D INSTALL_C_EXAMPLES=ON \
-D PYTHON_EXECUTABLE=$(which python2) \
-D BUILD_opencv_python2=OFF \
-D PYTHON3_EXECUTABLE=$(which python3) \
-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
-D WITH_GSTREAMER=ON \
-D WITH_FFMPEG=ON \
-D HAVE_FFMPEG=ON \
-D WITH_GTK=ON \
-D WITH_QT=ON \
-D WITH_OPENGL=ON \
-D BUILD_TIFF=ON \
-D BUILD_opencv_apps=OFF \
-D BUILD_SHARED_LIBS=OFF \
-D OPENCV_FFMPEG_SKIP_BUILD_CHECK=ON \
-D ENABLE_PRECOMPILED_HEADERS=OFF \
-D FORCE_VTK=ON \
-D WITH_TBB=ON \
-D WITH_GDAL=ON \
-D WITH_XINE=ON \
-D FFMPEG_LIBDIR="/usr/bin" \
-D FFMPEG_INCLUDE_DIRS="/usr/bin" \
 ..

# Build (use -j flag responsibly)
$ make-j4
```

Check your opencv2 files are in /usr/include and not
/usr/local/include. If they are stored in the latter, simply run 
```
sudo mv -r /usr/local/include/opencv4/opencv2/ /usr/include/
```

