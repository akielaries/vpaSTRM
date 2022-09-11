"""
Implementation of our previous programs using threading!
"""


# Import OpenCV and threading packages
import cv2
import threading

# Define class for the camera thread.
class CamThread(threading.Thread):

    def __init__(self, previewname, camid):
        threading.Thread.__init__(self)
        self.previewname = previewname
        self.camid = camid

    def run(self):
        print("Starting " + self.previewname)
        previewcam(self.previewname, self.camid)

# Function to preview the camera.
def previewcam(previewname, camid):
    cv2.namedWindow(previewname)
    cam = cv2.VideoCapture(camid)
    if cam.isOpened():
        rval, frame = cam.read()
    else:
        rval = False

    while rval:
        cv2.imshow(previewname, frame)
        rval, frame = cam.read()
        key = cv2.waitKey(20)
        if key == 27:  # Press ESC to exit/close each window.
            break
    cv2.destroyWindow(previewname)

threadLock = threading.Lock()
threads = []
# Create different threads for each video stream, then start it.
thread1 = CamThread("Test Site Cam2", 'rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2')
thread2 = CamThread("Test Site Cam3", 'rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2')

thread1.start()
thread2.start()
#thread3.start()

threads.append(thread1)
threads.append(thread2)

for t in threads:
    t.join()
print("EXITING MAIN THREAD")




