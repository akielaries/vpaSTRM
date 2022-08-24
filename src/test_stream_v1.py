""":
Messy but working Python program using RTSP protocol to stream video
from the l51dm Annke turret IP Cam using openCV and displaying it on 
a simple webpage using Flask.

- first declare the window this video output will be displayed on
and enable it to be resized (used for displaying to stdout)
- declare an output frame object and ensure using threads safely 
- initialize flask object

- declare capture object and pass in the full rtsp cmd
- confirm capture is opened 

def index():

def stream():
- original orientation of camera if placed on flat side down, displays
upside down, used cv2.flip to flip cam vertically
- 

def generate():

def video_feed():

current issues: 
- when flipping orientation of camera output, must also flip the timestamp 

"""

# import the necessary packages
from flask import Response, Flask, render_template
import threading
import argparse 
import datetime, time
import imutils
import cv2

# initialize the output frame and a lock used to ensure thread-safe
# exchanges of the output frames (useful when multiple browsers/tabs are viewing the stream)
output_frame = None
thr_lock = threading.Lock()
 
# initialize a flask object
app = Flask(__name__)
 
capture_obj = "rtsp://admin:password123@192.168.1.176:554/2"
capture = cv2.VideoCapture(capture_obj)
# time.sleep(2.0)

@app.route("/")
def index():
    # return the rendered template
    return render_template("index.html")

def stream(frame_count):
    global output_frame, thr_lock
    # variables for streaming to window on local
    # window = "top"
    # cv2.namedWindow(window, cv2.WINDOW_NORMAL)
    # cv2.resizeWindow(window, 720, 720)

    if capture.isOpened():
        while True:
            ret, frame = capture.read()
            # cv2.namedWindow(('IP camera DEMO'), cv2.WINDOW_AUTOSIZE)
            # depending on how cam is mounted, adjust this line
                # for this instance we flip the camera vertically
            stream = cv2.flip(frame, 0)
            # stream to stdout
            # cv2.imshow(window, stream)
        
            if frame.shape:
                frame = cv2.resize(stream, (640,360))
                with thr_lock:
                    output_frame = frame.copy()
            else:
                continue 
        else:
            print('camera open failed')

def generate():
    # grab global references to the output frame and lock variables
    global output_frame, thr_lock
 
    # loop over frames from the output stream
    while True:
        # wait until the lock is acquired
        with thr_lock:
            # check if the output frame is available, otherwise skip
            # the iteration of the loop
            if output_frame is None:
                continue
 
            # encode the frame in JPEG format
            (flag, encoded_img) = cv2.imencode(".jpg", output_frame)
 
            # ensure the frame was successfully encoded
            if not flag:
                continue
 
        # yield the output frame in the byte format
        yield(b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + 
            bytearray(encoded_img) + b'\r\n')

"""
Route this method to *url*/video_feed
"""
@app.route("/video_feed")
def video_feed():
    # return the response generated along with the specific media
    # type (mime type)
    return Response(generate(),
        mimetype = "multipart/x-mixed-replace; boundary=frame")
"""
check to see if this is the main thread of execution
pass 
"""
if __name__ == '__main__':
    # construct the argument parser and parse command line arguments
    ap = argparse.ArgumentParser()
    """
    #ap.add_argument("-i", "--ip", type=str, required=False, default='192.168.1.176',
        #help="ip address of the device")
    ap.add_argument("-o", "--port", type=int, required=False, default=8000, 
        help="ephemeral port number of the server (1024 to 65535)")
    """
    ap.add_argument("-f", "--frame-count", type=int, default=32,
        help="# of frames used to construct the background model")
   
    args = vars(ap.parse_args())
    
    thr_arg = threading.Thread(target=stream, args=(args["frame_count"],))
    thr_arg.daemon = True
    thr_arg.start()
    
    # start the flask app
    #app.run(host=args["ip"], port=args["port"], debug=True,
    #    threaded=True, use_reloader=False)
    app.run(host= '0.0.0.0',debug=True)

# release the video stream pointer
capture.release()
cv2.destroyAllWindows()


