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

window = "top"
cv2.namedWindow(window, cv2.WINDOW_NORMAL)
cv2.resizeWindow(window, 720, 720)

# ip cam #1 local environment IP
#capture_obj = cv2.VideoCapture('rtsp://admin:password123@192.168.1.177:554/2')
capture_obj = cv2.VideoCapture('rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2')
# ip cam #1 test-site IP
#capture_obj = cv2.VideoCapture('rtsp://admin:password123@10.55.34.251:554/2')
#capture_obj = cv2.VideoCapture('rtsp://admin:password123@10.55.34.46:554/2')


def capture():
    if capture_obj.isOpened():
        # ret; bool val returns true if fram is available
        # frame; img arr vector 
        ret, frame = capture_obj.read()
    else:
        ret = False
    while ret:
        ret, frame = capture_obj.read()
        # depending on how cam is mounted, adjust this line
            # for this instance we flip the camera vertically
        stream = cv2.flip(frame, 0);
        
        # cv2.imshow("Capturing", frame)
        cv2.imshow(window, stream)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    capture_obj.release()
    cv2.destroyAllWindows()

def main():
    capture()

if __name__ == "__main__":
    main()

