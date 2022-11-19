![Version](https://img.shields.io/github/v/release/akielaries/vpaSTRM?color=%23BF40BF)
![Build](https://github.com/akielaries/vpaSTRM/actions/workflows/build.yml/badge.svg)

# Introduction
Welcome to v1.0.2 of vpaSTRM! It is fair to say the tool is in a beta 
stage as it is very simple and limited but stay tuned for more! 
Previously a streaming application implemented in Python for viewing 
RTSP based IP cameras, this version aims to start from the ground up 
improving performance + usability and will be primarily focused on 
implementations in C, C++, and other languages close to the hardware.

There are multiple branches in this repository. The stable one being v1.x, 
and will be updated on a rolling basis that will include some minor changes 
and feature improvements as well as large changes including brand new features, 
new functionality and of course more fun algorithms to play with :).

> :warning: *For this version the biggest implementation was the use of some command line
arguments including flags. For this piece of the software and this specific version
I had only implemented the `-d` flag for decoding videos into picture frames. For
this specific functionality I highly recommend that you only pass in a valid video 
file as I have not implemented a failsafe for invalid arguments for this flag. 
v1.1.3 will hopefully provide a more clear solution for parsing command line arguments
along with some new functionalities.*

```
v1.x : stable, most recent release, updated on a volatile basis. 
v1.x-dev : development branch, updated frequently, often left in broken state. 
```

The goal is to wrap certain functionalities of FFMPEG, OpenCV + friendly UI 
to manipulate video files in various ways.

> :warning: *This repo is forked and detached from [here](https://github.com/DiscoverCCRI/ip_cam) and serves
as a "new version" also developed by [me](https://github.com/akielaries), building off of an application
built for the DiscoverCCRI research study. This project welcomes contributors!!*
---

# Functionality
- specify video file 
  - so far only .mp4 has been tested
  - mov,mp4,m4a,3gp,3g2,mj2 + more will be functional 
- decode algorithm parses the passed in h264/265 video into series of frames  
- decoded packets are saved to .pgm (Portable Gray Map) to size of 2MB

NOTE: this algorithm is 'dynamic' in a way and uses this formula:
```
r = f(d)

r = result output of frames
f = Frames Per Second (FPS) of video file
d = duration of video file must be an integer as partial frames won't be counted
```

# Dependencies
```
# Run updates
$ sudo apt-get update -y

# install libavcodec, decode/encode video and audio
$ sudo apt-get install -y libavcodec-dev

# install libavformat
$ sudo apt-get install -y libavformat-dev

# OR install all libav related libs, comes with FFMPEG (what this project heavily relies on)
$ sudo apt-get install ffmpeg
```

# Install + Run
```
# Clone the repo
$ git clone git@github.com:akielaries/vpaSTRM.git
$ cd vpaSTRM

# Run the test examples found in cv-tests/input to verify install
$ ./vpaSTRM.sh -d cv-data/input/small_bunny_1080p_60fps.mp4
```
Enter the vpaSTRM folder and run the software against video files of any length and expect
a surplus of PGM (Portable Gray Map) image files. v1.x has limited functionality but
future versions will build off of this version as it serves as the "core."

vpaSTRM can also be ran in a Docker container although this is primarily for testing 
purposes when pushing changes upstream. 
```
# build the image
$ docker build -t vpastrm .
# view images
$ docker images
# run the container
$ docker run -d vpastrm
# view containers
$ docker ps
```

# Clean Up
For now I recommend running this in the root directory of this package. This allows for easier clean up
if using this straight from the source. See below on some various ways to clean up your files after running!

```
# remove all generated files when compiling and running
$ make clean-all

# remove all log files
$ make clean-logs

# remove all generated image files
$ make clean-imgs

# remove bins + images
$ make clean
```

# Contribute
Checkout some of the documentation located in docs/ on how to submit a pull 
request, what it should contain, etc. All contributors are welcome and I hope 
this project is easily digestible. This project could use students, 
industry-based individuals, with knowledge of computer vision, 
systems/low-level programming, knowledge and passion for image processing 
related algorithms, codecs, + more! This project has no limitations and 
welcomes all suggestions. Please view the documentation for examples of
the coding style adopted for this project. 


# Ideas
Some cases of python for quick and dirty prototyping for basic
functionalities before implementing in C. Future cases of
statistical analysis, machine learning, and other ideas involving 
data visualization will be explored (scikit-learn, pandas, PyQT, numpy, 
etc). **Long Term focus is reliability, efficiency, and of course speed 
(maybe ease of use too).**

End result will include a functioning package allowing users to utilize 
this application in whatever way they see fit. This project heavily encourages
contributors to suggest and make changes to this, what I aim to be an, open source 
project. Developers implementing their own solution to a similar problem are also
heavily encouraged to contribute or use parts of this project for their own
implementations!

- Py libs for GUI implementation: PyQt, Tkinter, etc
- C libs for GUI implementation: GTK, Ncurses
- Optional functionalities using GStreamer

# Acknowledgments
* FFMPEG

