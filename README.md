# Introduction
WIP repo on using opencv with python to utilize the 
Annke l51dm IP turret camera as a tool to monitor the 
DISCOVER test site, specifically the Terrestrial Robots. 
Also 1 cpp example with basic feed.


# Dependencies
- Assumes you are using some type of linux-based (or OSX)environment.

**fetch updates**
```
$ sudo apt-get update
```

**py 2&3 support**
```
$ sudo apt-get install python-dev python-numpy &&
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
**datetime lib**
```
$ pip3 install datetime
```
**openCV**
```
$ pip3 install opencv-python
```

**Flask** 
```
$ pip3 install flask
```

**imutils**
```
$ pip3 install imutils
```

# Build this project
```
$ git clone git@github.com:DiscoverCCRI/ip_cam.git &&
cd ip_cam/src &&
python3 test_stream_v1.py
```
