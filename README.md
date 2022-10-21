# Introduction
Welcome to v1.x of vpaSTRM! So far it is very simple and limited but 
stay tuned for more!
Previously a streaming applicatoin implemented in Python for streaming 
RTSP based IP cameras, this version aims to start from the ground up 
improving performance + usability and will be primarily focused on 
implementations in C, C++, and other languages close to the hardware.

There a multiple branches in this repository. The stable one being v1.x,
an will be updated on a rolling basis that will include some minor changes 
and feature improvements as well as large changes including brand new features,
new funcionality and of course more fun algorithms to play with :). 

```
v1.x : stable, updated on volatile basis. 
v1.0.0 : stable, archived release. Major versions will have their own branch. 
v1.x-dev : development branch, updated frequently, often left in broken state. 
```

The goal is to wrap certain functionaities of FFMPEG, OpenCV + friendly UI 
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


# Clean Up
For now I recommend running this in the root directory of this package. This allows for easier cleanup
if using this straight from the source. See below on some various ways to cleanup your files after running!

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
welcomes all suggestions. vpaSTRM uses the K & R Stroustrup variant for code
indentation style. 

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
