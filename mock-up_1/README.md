# mock-up v1

### To run
> :warning: This assumes are connected to the NAU VPN and
have necessary dependencies installed (openCV-python, Flask)

```
git clone git@github.com:DiscoverCCRI/ip_cam.git
cd /mock-up_1
python3 stream.py
```

In this test I found some resources on threading and using a 
class, offloaded operations onto the thread.py file and generation
and encoding operation onto the stream.py file. Of course is still 
buffers and this time seems to be entirely limited by computational 
resources. Some commone error codes we see when running this:
```
[hevc @ 0x7f76ec02aec0] The cu_qp_delta -47 is outside the valid range [-26, 25].
[hevc @ 0x7f76f4044f40] Could not find ref with POC 5
```
These codes have been the biggest hinderence and are due to encoding issues
possibly specific to FFMPEG. Will try getting around this with using 
Gstreamer with OpenCV instead of the FFMPEG dependency.

when building openCV from src 

```
# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip

# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip

# Create build directory
mkdir -p build && cd build

# Configure
cmake  ../opencv-4.x -DWITH_GSTREAMER=ON

# Build
cmake --build .
```

![example](https://github.com/DiscoverCCRI/ip_cam/blob/main/imgs/mockup-1.1.png)
