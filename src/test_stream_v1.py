"""
Messy but working Python program using RTSP protocol to stream video
from the l51dm Annke turret IP Cam using openCV and displaying it on 
a simple webpage using Flask.
"""
# import the necessary packages
from flask import Response, Flask, render_template
import threading
import argparse 
import datetime, time
import imutils
import cv2
"""
initialize the output frame and a lock used to ensure thread-safe
exchanges of the output frames (useful when multiple browsers/tabs are viewing the stream)
"""
output_frame = None
thr_lock = threading.Lock()
 
# initialize a flask object
app = Flask(__name__)

"""
declare capture object and pass in the full rtsp cmd and 
confirm capture is opened 

RTSP format for l51dm cameras :
    - rtsp://user:pass@IPADDRESS:554/channel
        * 554 = default RTSP port
"""
capture_obj = "rtsp://admin:password123@192.168.1.176:554/2"
capture = cv2.VideoCapture(capture_obj)

"""
index():
    - return the template store in templates/index.html

** "routes" are essentially URLs of our application (i.e. 192.168.1.176)
"""
@app.route("/")
def index():
    # return the rendered template
    return render_template("../templates/index.html")

"""
stream_feed():
    - set output and thread lock variables and read in the frames
    - set a stream var = to our openCV's flip method for correct orientation
    - resize our streams window in the webpage 


"""
def stream_feed(frame_count):
    global output_frame, thr_lock
    # variables for streaming to window on local machine
    # window = "top"
    # cv2.namedWindow(window, cv2.WINDOW_NORMAL)
    # cv2.resizeWindow(window, 720, 720)

    if capture.isOpened():
        while True:
            ret, frame = capture.read()
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

"""
generate():
    - enter a loop where we will encode the cameras stream as 
    jpg files
    - yield our output frames in byte formate 
issues: 
    - video(or rather continuous photo) stream is rather choppy
    not sure if any improvements could be made in here
"""
def generate():
    # grab global references to the output frame and lock variables
    global output_frame, thr_lock
 
    # loop over frames from the output stream
    while True:
        # wait until the lock is acquired
        with thr_lock:
            # check if the output frame is available
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
video_feed():
    - returns streaming response
    - returns the images to be displayed to the web page
    - browsers support multipart responses allowing for a continuous
    stream of pictures appearing as video
    - route this method to *url*/cam_1 using @app.route
    - would want to modify/duplicate for display of multiple cameras
    or potentially create another script for each camera using this as a
    template
issues : 
    - when visiting the url, loads infinitely
"""
@app.route("/cam1")
def video_feed():
    # return the response generated along with the specific media
    # type (mime type)
    return Response(generate(),
        mimetype = "multipart/x-mixed-replace; boundary=frame")

"""
- check to see if this is the main thread of execution
- pass in our arguments to get our applicatoin running
    * creation of argument parser var, pass in frame count and host,
    return
"""
if __name__ == '__main__':
    # construct the argument parser and parse command line arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-f", "--frame-count", type=int, default=32,
        help="# of frames used to construct the background model")
   
    args = vars(ap.parse_args())
    
    thr_arg = threading.Thread(target=stream_feed, args=(args["frame_count"],))
    thr_arg.daemon = True
    thr_arg.start()
    
    # start the flask app passing in host, not requiring execution of program
    # as new edits arise, instead refresh page 
    #app.run(host=args["ip"], port=args["port"], debug=True,
    #    threaded=True, use_reloader=False)
    app.run(host= '0.0.0.0',debug=True)

# release the video stream pointer
capture.release()
cv2.destroyAllWindows()


