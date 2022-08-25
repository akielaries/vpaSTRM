# Introduction
WIP repo on using opencv with python to utilize the 
Annke l51dm IP turret camera as a tool to monitor the 
DISCOVER test site, specifically the Terrestrial Robots. 
Also cpp example providing basic feed.


# Dependencies
- Assumes you are using some type of linux-based (or OSX)environment.

**fetch updates**
```
$ sudo apt-get update
```

**py 2&3 support**
```
sudo apt-get install python-dev python-numpy
sudo apt-get install python3-dev python3-numpy
```

**pip3 for easy installation of some python modules**
```
$ sudo apt-get -y install python3-pip
```

**For GTK GUI features**
```
$ sudo apt-get install libgtk-3-dev
```
bulk install our python dependencies using pip
**datetime, openCV, Flask, imutils**
```
$ pip3 install datetime opencv-python flask imutils
```

# Build this project
```
$ git clone git@github.com:DiscoverCCRI/ip_cam.git &&
cd ip_cam/src &&
python3 test_stream_v1.py

Enter IP of your local machine into a browser and your RTSP stream should be present.
```

# Issues
Issues I ran into when installing on Raspian on RPI 4
  - When installing imutils there might be some errors, to fix I installed
  these packages and fixed some various issues with numpy
```
pip3 install opencv-python
sudo apt-get install libcblas-dev
sudo apt-get install libhdf5-dev
sudo apt-get install libhdf5-serial-dev
sudo apt-get install libatlas-base-dev
sudo apt-get install libjasper-dev 
sudo apt-get install libqtgui4 
```
  - Issues with numpy on my local machine with bad versions. To fix:
```
$ pip3 install -U numpy
```
