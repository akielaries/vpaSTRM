from threading import Thread
from flask import Response, Flask, render_template
import argparse
import datetime, time
import imutils
import cv2


app = Flask(__name__)

camlink1 = "rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2"
camlink2 = "rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2"

class VideoStreamWidget(object):
    def __init__(self, link, camname):
        self.capture = cv2.VideoCapture(link)

        # Start the thread to read frames from the video stream
        self.thread = Thread(target=self.update, args=())
        self.thread.daemon = True
        self.thread.start()
        self.camname = camname
        self.link = link
        print(camname)
        print(link)

    def update(self):
        # Read the next frame from the stream in a different thread
        while True:
            if self.capture.isOpened():
                (self.status, self.frame) = self.capture.read()
            #time.sleep(.001)
            time.sleep(.02)

    def show_frame(self):
        """
        Display frames in main program and resize the windows they show in
        """
        frame = imutils.resize(self.frame, width=620)
        cv2.imshow(self.camname, frame)
        key = cv2.waitKey(1)
        if key == ord('q'):
            self.capture.release()
            cv2.destroyAllWindows()
            # implement something like this; to my knowledge no 
            # such function exists
            # self.thread.stop()

            exit(1)

# perhaps include a thread.stop to clean things up
# also look into implementation of the following:
# os.execv(__file__, sys.argv)  
# Run a new iteration of the current script, 
# providing any command line args from the current iteration.



if __name__ == '__main__':
    video_stream_widget = VideoStreamWidget(camlink1, "Cam 2")
    video_stream_widget2 = VideoStreamWidget(camlink2, "Cam 3")
    
    app.run(host= '0.0.0.0',debug=True)
    
    while True:
        try:
            video_stream_widget.show_frame()
            video_stream_widget2.show_frame()
        except AttributeError:
            pass


