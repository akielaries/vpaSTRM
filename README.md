# Introduction
WIP repo aiming to stream feeds from RTSP based IP
cameras. Previously implemented in Python, this 
version aims to improve performance and usability 
and will be primarily focused on implementations in
C, and C++ for computer vision related tasks. 

The goal is to wrap certain functionaities of FFMPEG, in conjunction 
with OpenCV + friendly UI to manipulate video files in various ways.

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

# Installing Dependencies
> :warning: **Please view [DEPENDENCIES.md](https://github.com/akielaries/rgaSTRM/blob/main/docs/DEPENDENCIES.md)**
