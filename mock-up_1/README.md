# mock-up v1
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


