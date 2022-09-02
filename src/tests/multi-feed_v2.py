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

# define window variables and size allowing for resizing when program runs
window1 = "window1"
window2 = "window2"
cv2.namedWindow(window1, cv2.WINDOW_NORMAL)
cv2.namedWindow(window2, cv2.WINDOW_NORMAL)
cv2.resizeWindow(window1, 720, 720)
cv2.resizeWindow(window2, 720, 720)

src1 = cv2.VideoCapture('rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2')
src2 = cv2.VideoCapture('rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2')

def capture():
    while True:
        ret1, frame1 = src1.read()
        ret2, frame2 = src2.read()

        if (ret1):
            cv2.imshow(window1, frame1)
    
        if (ret2):
            cv2.imshow(window2, frame2)
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break


    src1.release()
    src3.release()
    cv2.destroyAllWindows()

def main():
    capture()

if __name__ == "__main__":
    main()

