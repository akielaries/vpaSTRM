# Introduction
Welcome to v0.0.1 of vpaSTRM! So far it is very simple and limited but 
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

# Dependencies
```
# Run updates
$ sudo apt-get update -y

# install libav related libs, comes with FFMPEG (what this project heavily relies on)
$ sudo apt-get install ffmpeg
```

# Install + Run
```
# Clone the repo
$ git clone git@github.com:akielaries/vpaSTRM.git
$ cd vpaSTRM

# Run the test examples found in cv-tests/input to verify install
$ ./vpaSTRM.sm cv-data/input/small_bunny_1080p_60fps.mp4
```
Enter the vpaSTRM folder and run the software against and length video file and expect
a surplus of PGM (Portable Gray Map) image files. v0.0.1 has limited functionality but
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

# Installing Dependencies
> :warning: **Please view [DEPENDENCIES.md](https://github.com/akielaries/rgaSTRM/blob/main/docs/DEPENDENCIES.md)**
