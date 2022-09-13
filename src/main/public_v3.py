"""
Messy but working Python program using RTSP protocol to stream video
from the l51dm Annke turret IP Cam using openCV and displaying it on 
a simple webpage using Flask.
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
thr_lock = threading.Lock()
 
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
    global output_frame, thr_lock

    frame = parse_cams(cam_id)
    capture = cv2.VideoCapture(frame)
    # variables for streaming to window on local machine
    # window = "top"
    # cv2.namedWindow(window, cv2.WINDOW_NORMAL)
    # cv2.resizeWindow(window, 720, 720)

    if capture.isOpened():
        while True:
            ret, frame = capture.read()
            # depending on how cam is mounted, adjust this line
                # for this instance we flip the camera vertically
            #stream = cv2.flip(frame, 0)
            # stream to stdout
            #cv2.imshow(stream)
            #time.sleep(0.02)
            if frame.shape:
                frame = cv2.resize(frame, (640,360))
            #frame = imutils.resize(frame, width=620)    
                with thr_lock:
                    output_frame = frame.copy()
            
            else:
                continue 

        key = cv2.waitKey(1)
        if key == ord('q'):
            capture.release()
            cv2.destroyAllWindows()
            exit(1)
    else:
        print('ERR:     COULD NOT OPEN STREAM')
    
    return cam_id, frame_count

"""
generate():
    - enter a loop where we will encode the cameras stream as 
    jpg files
    - yield our output frames in byte formate 
issues: 
    - video(or rather continuous photo) stream is rather choppy
    not sure if any improvements could be made in here
"""
def generate(cam_id):
    # grab global references to the output frame and lock variables
    global output_frame, thr_lock
    
    #stream = parse_cams(cam_id)

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
        #yield(b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + 
        #    bytearray(encoded_img) + b'\r\n')
        # concate frame one by one and show result
        yield (b'--frame\r\n' 
            b'Content-Type: image/jpeg\r\n\r\n' + encoded_img + b'\r\n')

    return cam_id, output_frame

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
    # return the response generated along with the specific media
    # type (mime type)
    return Response(generate(id),
        mimetype = 'multipart/x-mixed-replace; boundary=frame')


"""
index():
    - return the template store in templates/index.html

** "routes" are essentially URLs of our application (i.e. 192.168.1.176)
"""
@app.route('/', methods=["GET"])
def index():
    # return the rendered template
    return render_template("index.html")


"""
- check to see if this is the main thread of execution
- pass in our arguments to get our applicatoin running
    * creation of argument parser var, pass in frame count and host,
    return
"""
#if __name__ == '__main__':
def main():
    cam_id = 0
    # frame_count = output_frame
    frame_count = 0
    # construct the argument parser and parse command line arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-c", "--cam_id", type=int, 
        help="# of cams we want to stream/display")
    ap.add_argument("-f", "--frame-count", type=int, default=32,
        help="# of frames used to construct the background model")
   
    # kwargs for multiple arguments
    kargs = vars(ap.parse_args())
    #args = vars(ap.parse_args())
    
    thr_arg = threading.Thread(target=stream_feed, kwargs={'cam_id':cam_id,'frame_count':frame_count})
    
    #   thr_arg = threading.Thread(target=generate, args=(args["cam_id"],))
    #thr_arg = threading.Thread(target=stream_feed, kwargs=(args{'cam_id':cam_id,'frame_count':frame_count}))
    
    thr_arg.daemon = True
    thr_arg.start()
    
    # start the flask app passing in host, not requiring execution of program
    # as new edits arise, instead refresh page 
    #app.run(host=args["ip"], port=args["port"], debug=True,
    #    threaded=True, use_reloader=False)

    app.run(host= '0.0.0.0',debug=True, threaded=True)


if __name__ == '__main__':
    # run main
    main()


