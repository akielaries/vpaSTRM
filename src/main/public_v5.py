"""
similar to previous versions of our stream implementations 
this time we are not using threading, creating a function to 
parse our cameras to assign URL extensions based off of, and 
render our stream using the index.html template scene in /tempaltes

The biggest issue with this is latency and buffering issues.
"""

from flask import Flask, render_template, Response
# import the necessary packages
from flask import Response, Flask, render_template
import threading
import multiprocessing
import argparse
import datetime, time
import imutils
import cv2


app = Flask(__name__)

output_frame = None
t_lock = threading.Lock()

def parse_cams(id):
    cameras = ['rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2',
               'rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2']

    return cameras[int(id)]

def stream_feed(cam_id, frame_count):
    global output_frame, t_lock

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

@app.route('/video_feed/<string:id>/', methods=["GET"])
def video_feed(id):
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(generate(id),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/', methods=["GET"])
def index():
    return render_template('index.html')

def main():
    cam_id = 0
    frame_count = output_frame
    """
    initialize the output frame and a lock used to ensure thread-safe
    exchanges of the output frames (useful when multiple browsers/tabs are viewing the stream)
    """
    ap = argparse.ArgumentParser()

    ap.add_argument("-c", "--cam_id", type=int,
        help="# of cams we want to stream/display")
    ap.add_argument("-f", "--frame_count", type=int, default=32, 
        help="# of frames used to construct the background model")

    kwargs = vars(ap.parse_args())

    #thread_o = threading.Thread(target=stream_feed, args=(args["frame_count"],))
    thread_o = threading.Thread(target=stream_feed, kwargs={'cam_id':cam_id,'frame_count':frame_count})
    #thread_t = threading.Thread(target=)


    thread_o.daemon = True
    thread_o.start()

    app.run(host= '0.0.0.0',debug=True, threaded=True)


if __name__ == '__main__':
    main()

