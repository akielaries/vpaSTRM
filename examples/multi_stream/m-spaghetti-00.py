"""
Messy but working Python program using RTSP protocol to stream video
from the l51dm Annke turret IP Cams using openCV. 

- first declare the window this video output will be displayed on
and enable it to be resized. 
- declare capture object and pass in the full rtsp cmd
- confirm capture is opened 
- original orientation of camera if placed on flat side down, displays
upside down, used cv2.flip to flip cam vertically
- 

current issues: 
- when flipping orientation of camera output, must also flip the timestamp 
- issues with latency of course between windows

"""

import cv2
import os
import time
import threading

#os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "rtsp_transport;udp"

# define window variables and size allowing for resizing when program runs
window1 = "window1"
#window2 = "window2"
window3 = "window3"

cv2.namedWindow(window1, cv2.WINDOW_NORMAL)
#cv2.namedWindow(window2, cv2.WINDOW_NORMAL)
cv2.namedWindow(window3, cv2.WINDOW_NORMAL)

cv2.resizeWindow(window1, 720, 720)
cv2.resizeWindow(window3, 720, 720)

# ip cam #1 test-site
src1 = cv2.VideoCapture('rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2')
# ip cam #2 local env IP

# ip cam #2 test-site
#src_url2 = cv2.VideoCapture('rtsp://admin:password123@10.55.34.251:554/2')
# ip cam #3 test-site
src3 = cv2.VideoCapture('rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2')
# ip cam #1 test-site IP
#capture_obj = cv2.VideoCapture('rtsp://admin:password123@10.55.34.251:554/2')
#capture_obj = cv2.VideoCapture('rtsp://admin:password123@10.55.34.46:554/2')

# method for capturing from our IP cameras
def capture():
    frame_num = 20

    if src1.isOpened(): 
        var1 = src1.get(cv2.CAP_PROP_BUFFERSIZE)
        src1.set(cv2.CAP_PROP_BUFFERSIZE, 3)
        src1.set(cv2.CAP_PROP_POS_FRAMES, frame_num)
        # ret; bool val returns true if fram is available
          # frame; img arr vector 
        ret1, frame1 = src1.read()
        # resize frames
        cam_frame1 = cv2.resize(frame1, (0, 0), fx=.50,fy=.50)
    
    else:
        ret1 = False

    if src3.isOpened():
        var3 = src3.get(cv2.CAP_PROP_BUFFERSIZE)
        src3.set(cv2.CAP_PROP_BUFFERSIZE, 3)
        src3.set(cv2.CAP_PROP_POS_FRAMES, frame_num)
        # ret; bool val returns true if fram is available
            # frame; img arr vector 
        ret3, frame3 = src3.read()
        # resize our frames
        cam_frame3 = cv2.resize(frame3, (0, 0), fx=.50,fy=.50)

    else:
        ret3 = False

    while ret1 and ret3:
        # ret; bool val returns true if fram is available
            # frame; img arr vector
        ret1, frame1 = src1.read()
        ret3, frame3 = src3.read()

        # depending on how cam is mounted, adjust this line
            # for this instance we flip the camera vertically
        cam_frame1 = cv2.flip(frame1, 0)
            #cam_frame3 = cv2.flip(frame3, 0)

        # display our feeds in seperate resizable windows
        cv2.imshow(window1, cam_frame1)
        cv2.imshow(window3, frame3)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    src1.release()
    src3.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    capture()

