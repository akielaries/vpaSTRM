"""
similar to previous versions of our stream implementations 
this time we are not using threading, creating a function to 
parse our cameras to assign URL extensions based off of, and 
render our stream using the index.html template scene in /tempaltes
The biggest issue with this is latency and buffering issues.
"""

from flask import Flask, render_template, Response
from ray.util.multiprocessing import Pool
import cv2

# for regular flask app
app = Flask(__name__)
# for flask app proxied to public URL generated w/ ngrok

def parse_cams(id):
    cameras = ['rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2',
               'rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2']

    return cameras[int(id)]

def gen_frames(cam_id):

    cam = parse_cams(cam_id)
    capture =  cv2.VideoCapture(cam)

    while True:
        # for cap in caps:
        # # Capture frame-by-frame
        success, frame = capture.read()  # read the camera frame
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                # concat frame one by one and show result
                b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')


@app.route('/video_feed/<string:id>/', methods=["GET"])
def video_feed(id):

    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen_frames(id),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/', methods=["GET"])
def index():
    return render_template('index.html')


def main():
    app.run()

if __name__ == '__main__':
    main()
