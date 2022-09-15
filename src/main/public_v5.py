"""
similar to previous versions of our stream implementations 
this time we are using threading, creating a function to 
parse our cameras to assign URL extensions based off of, and 
render our stream using the index.html template scene in /tempaltes

The biggest issue with this is latency and buffering issues.
"""
# import the necessary packages
from flask import Response, Flask, render_template
import threading
import multiprocessing
import argparse
import datetime, time
import imutils
import cv2

"""
initialize the output frame and a lock used to ensure thread-safe
exchanges of the output frames (useful when multiple browsers/tabs are viewing the stream)
"""
output_frame = None
t_lock = threading.Lock()
 
# initialize a flask object
app = Flask(__name__)

"""
method for parsing our cam ids. declared as a list
declare capture object and pass in the full rtsp cmd and 
confirm capture is opened 
RTSP format for l51dm cameras :
    - rtsp://user:pass@IPADDRESS:554/channel
        * 554 = default RTSP port
"""
def parse_cams(id):
    cameras = ['rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2',
               'rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2']

    return cameras[int(id)]
    print(id)

"""
stream_feed():
    - set output and thread lock variables and read in the frames
    - set a stream var = to our openCV's flip method for correct orientation
    - resize our streams window in the webpage 
<----- LEAVE OFF HERE  ----->
    - rethink this method especially. other non-threaded version works fine 
    without this. perhaps morph stream_feed into a resize function since we 
    do not need to display anything using the OpenCV windows, only the HTML
    webpage we are creating for localhost. 
    - maybe pass a camera object into here and return the new resized frame
    OVERALL THINK OF A NEW WAY TO USE THIS 
<----- PICK UP HERE  ----->
    - will want to remove the code that displays our feeds in an 
    openCV window
    - rethink generate() and stream_feed() to communicate off eachother
    
    generate() - should do all of our streaming work. 
"""
def stream_feed(cam_id, frame_count):
    global output_frame, t_lock

    # tuple, may need to do index of cam_id
    cam = parse_cams(cam_id)
    capture =  cv2.VideoCapture(cam)
    
    if capture.isOpened():
        while True:
            ret_val, frame = capture.read()
            frame = imutils.resize(frame, 720)
            with t_lock:
                output_frame = frame.copy()
        
    return cam_id, output_frame

"""
generate():
    - enter a loop where we will encode the cameras stream as 
    jpg files
    - yield our output frames in byte formate 
issues: 
    - video(or rather continuous photo) stream is rather choppy
    not sure if any improvements could be made in here

<----LEAVE OFF HERE---->
"""
def generate(cam_id):
    global output_frame, t_lock
    cam = parse_cams(cam_id)
    capture =  cv2.VideoCapture(cam)

    while True:
        with t_lock:
            # Capture frame-by-frame
            success, frame = capture.read()  # read the camera frame
            if not success:
                break
            
            elif output_frame is None:
                continue

            else:
                ret, buffer = cv2.imencode('.jpg', output_frame)
                #(flag, buffer) = cv2.imencode(".jpg", output_frame)
                #convert_to_bytes = cv2.imencode('.jpg', output_frame)[1].tobytes()
                convert_to_bytes = buffer.tobytes()
                # flag = buffer.tobytes()
                # flag = buffer.tobytes()
                # concat frame one by one and show result
                yield (b'--frame\r\n'
                    b'Content-Type: image/jpeg\r\n\r\n' + convert_to_bytes + b'\r\n')

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
@app.route('/video_feed/<string:id>/', methods=["GET"])
def video_feed(id):
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(generate(id),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

"""
index():
    - return the template store in templates/index.html
** "routes" are essentially URLs of our application (i.e. 192.168.1.176)
"""
@app.route('/', methods=["GET"])
def index():
    return render_template('index.html')

"""
- check to see if this is the main thread of execution
- pass in our arguments to get our applicatoin running
    * creation of argument parser var, pass in frame count and host,
    return
"""
def main():
    cam_id = [0, 1]
    frame_count = 0

    """
    initialize the output frame and a lock used to ensure thread-safe
    exchanges of the output frames (useful when multiple browsers/tabs are viewing the stream)
    """
    ap = argparse.ArgumentParser()

    ap.add_argument("-c", "--cam_id", type=int,
        help="# of cams we want to stream/display")
    ap.add_argument("-f", "--frame_count", type=int, default=32, 
        help="# of frames used to construct the background model")

    print(frame_count)

    kwargs = vars(ap.parse_args())
    print(kwargs)

    #thread_o = threading.Thread(target=stream_feed, args=(args["frame_count"],))
    thread_o = threading.Thread(target=stream_feed, kwargs={'cam_id':cam_id[0],'frame_count':frame_count})
    thread_t = threading.Thread(target=stream_feed, kwargs={'cam_id':cam_id[1],'frame_count':frame_count})
    #thread_t = threading.Thread(target=)


    thread_o.daemon = True
    thread_t.daemon = True
    thread_o.start()
    thread_t.start()
    # clone application and try specifying different port for different stream
    # location
    app.run(host= '0.0.0.0',debug=True, threaded=True)
    print(kwargs)
    print(frame_count)

if __name__ == '__main__':
    # run main
    main()


