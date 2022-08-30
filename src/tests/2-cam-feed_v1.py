"""
Messy but working Python program using RTSP protocol to stream video
from the l51dm Annke turret IP Cam using openCV. 

- first declare the window this video output will be displayed on
and enable it to be resized. 
- declare capture object and pass in the full rtsp cmd
- confirm capture is opened 
- original orientation of camera if placed on flat side down, displays
upside down, used cv2.flip to flip cam vertically
- 

current issues: 
- when flipping orientation of camera output, must also flip the timestamp 

"""

import cv2
import os
import time
import threading

#window = "top"
#cv2.namedWindow(window, cv2.WINDOW_NORMAL)
#cv2.resizeWindow(window, 720, 720)


#os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "rtsp_transport;udp"

# ip cam #1 local environment IP
#src_url1 = 'rtsp://admin:password123@192.168.1.176:554/2'
# ip cam #2 local env IP
#src_url2 = 'rtsp://admin:password123@192.168.1.124:554/2'

# ip cam #1 test-site IP
#capture_obj = cv2.VideoCapture('rtsp://admin:password123@10.55.34.251:554/2')
#capture_obj = cv2.VideoCapture('rtsp://admin:password123@10.55.34.46:554/2')

def parse_cams(id):
    
    #cams = ['rtsp://admin:password123@192.168.1.176:554/2', 
    #        'rtsp://admin:password123@192.168.1.124:554/2']
    cams = ['rtsp://username:password@192.168.1.176:554/admin=username_password123=password_channel=channel_number_stream=0.sdp',
    'rtsp://username:password@192.168.1.124:554/admin=username_password123=password_channel=channel_number_stream=0.sdp']

    return cams[int(id)]

def capture(cam_id):
    # camera object
    cam = parse_cams(cam_id)
    capture_obj = cv2.VideoCapture(cam)
    


    while True:
        # ret; bool val returns true if fram is available
        # frame; img arr vector 
        ret, frame = capture_obj.read()
        small_frame = cv2.resize(frame, (0, 0), fx=.50,fy=.50)
        small_frame = cv2.flip(small_frame, 0)

        # depending on how cam is mounted, adjust this line
            # for this instance we flip the camera vertically
        #stream = cv2.flip(frame, 0);
        
        # cv2.imshow("Capturing", frame)
        cv2.imshow("camera", small_frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    capture_obj.release()
    cv2.destroyAllWindows()

"""
def main():
    capture(src_url1)
    capture(src_url2)
"""

#if __name__ == '__main__':

