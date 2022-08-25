# very elementary Dockerfile running this project
# FROM python:3.9.2
FROM --platform=linux/arm/v7 python:3.9.2

# install updates and core dependencies for our projects dependencies
RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get -y install apt-utils
RUN apt-get -y install libc-dev
RUN apt-get -y install build-essential
RUN apt install -y cmake g++ wget unzip

# install base python img
RUN apt-get install -y python3-dev python3-distutils python3-pip python3-apt gfortran gcc 
RUN pip3 install --upgrade pip

# copy script we are running


# install dependencies
# GTK GUI features
RUN apt-get install -y libgtk-3-dev

# numpy
# RUN pip3 install numpy
# RUN apt-get install -y python3-numpy
RUN pip3 install numpy==1.7

# install datetime
RUN pip3 install datetime 

# openCV for all camera interfacing features
# download the pkg
#RUN wget -O ~/opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
#RUN cd ~/ && unzip ~/opencv.zip

# creat build dir 
#RUN mkdir -p ~/build 
# configure and build
#RUN cd ~/build && cmake ../opencv-4.x && cmake --build .

RUN pip3 -v install opencv-python

# flask for displaying on the webpage
RUN pip3 install flask

# imutils for img proc funcs, manipulation of our feeds dimensions
RUN pip3 install imutils

# execute .py program
# CMD ["python3", "../src/test_stream_v1.py"]
CMD python3 ../src/test_stream_v1.py

