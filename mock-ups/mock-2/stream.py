"""
similar to previous versions of our stream implementations 
this time we are not using threading, creating a function to 
parse our cameras to assign URL extensions based off of, and 
render our stream using the index.html template scene in /tempaltes
The biggest issue with this is latency and buffering issues.

This version uses a class to take care of threading using the generated 
cam id from parse_cams in conjunction with generate()
"""

from flask import Flask, render_template, Response
from thread import CameraStream
import cv2

# initialize a flask object
app = Flask(__name__)

def parse_cams(id):
    """
    function for parsing our cam ids. declared as a list
    declare capture object and pass in the full rtsp cmd and 
    confirm capture is opened 
    RTSP format for l51dm cameras :
        - rtsp://user:pass@IPADDRESS:554/channel
            * 554 = default RTSP port
    """
    cameras = ['rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2',
               'rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2']

    return cameras[int(id)]


def generate(cam_id):
    """
    generate():
        - enter a loop where we will encode the cameras stream as 
        jpg files
        - yield our output frames in byte formate 
    
    issues: 
        - video(or rather continuous photo) stream is rather choppy
        not sure if any improvements could be made in here
    """
    cam_num = parse_cams(cam_id)
    cap = CameraStream(cam_num).start()
    """Video streaming generator function."""
    while cap:
        frame = cap.read()
        convert = cv2.imencode('.jpg', frame)[1].tobytes()
        # concate frame one by one and show result
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + convert + b'\r\n') 



@app.route('/video_feed/<string:id>/', methods=["GET"])
def video_feed(id):

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
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(generate(id),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/', methods=["GET"])
def index():
    """
    index():
        - return the template store in templates/index.html
    ** "routes" are essentially URLs of our application (i.e. 192.168.1.176)
    """
    return render_template('index.html')


def main():
    app.run(host='0.0.0.0', threaded=True)

if __name__ == '__main__':
    main()

