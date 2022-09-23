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
Can be quite a process to install so I will offer two methods of installation,
I was able to get the dependency working using method 1. I 

> :warning: GStreamer can be used in place of FFMPEG which will be enable by
default

#### Method 1
```
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
-D BUILD_TIFF=ON ..

# Build (spread load accross 4 core, use appropriately)
$ make-j4
```

```
# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
# Create build directory
mkdir -p build && cd build
# Configure
cmake ../opencv-4.x -D BUILD_TIFF=ON
# Build 
cmake --build.
# Make (spread load accross all cores)
make -j4
```

Check your opencv2 files are in /usr/include and not
/usr/local/include. If they are stored in the latter, simply run 
```
sudo mv -r /usr/local/include/opencv4/opencv2/ /usr/include/
```
