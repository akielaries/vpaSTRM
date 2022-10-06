# Introduction
Welcome to v1.0.0 of vpaSTRM! So far it is very simple and limited but 
stay tuned for more!
Previously implemented in Python for streaming RTSP based IP cameras, 
this version aims to start from the ground up improving performance 
and usability and will be primarily focused on implementations in 
C, C++ for computer vision related tasks (openCV C API is outdated). 

The goal is to wrap certain functionaities of FFMPEG, in conjunction 
with OpenCV + friendly UI to manipulate video files in various ways.

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
sudo apt-get install -y libavformat-dev

# OR install all libav related libs, comes with FFMPEG (what this project heavily relies on)
$ sudo apt-get install ffmpeg
```

# Install + Run
```
# Clone the repo
$ git clone git@github.com:akielaries/vpaSTRM.git
$ cd vpaSTRM

# Run the test examples found in cv-tests/input to verify install
$ ./vpaSTRM.sh cv-data/input/small_bunny_1080p_60fps.mp4
```
Enter the vpaSTRM folder and run the software against video file of any length and expect
a surplus of PGM (Portable Gray Map) image files. v1.0.0 has limited functionality but
future versions will build off of this version as it serves as the "core."

# Ideas
Some cases of python for quick and dirty prototyping for basic
functionalities before implementing in C. Future cases of
statistical analysis, machine learning, and other ideas involving 
data visualization will be explored (scikit-learn, pandas, PyQT, numpy, 
etc). **Longterm focus is reliabilty, effeciency, and of course speed 
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
