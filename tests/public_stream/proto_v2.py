from flask import Response, Flask, render_template
import threading
import multiprocessing
import argparse
import datetime, time
import imutils
import cv2

output_frame = None
thr_lock = threading.Lock()

app = Flask(__name__)

def parse_cams(id):
    cameras = ['rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2',
               'rtsp://admin:password123@disc-cam3.iot.nau.edu:554/2']

    return cameras[int(id)]


def stream_feed(cam_id, frame_count):
    global output_frame, thr_lock

    stream = parse_cams(cam_id)
    capture = cv2.VideoCapture(stream)
    # variables for streaming to window on local machine
    # window = "top"
    # cv2.namedWindow(window, cv2.WINDOW_NORMAL)
    # cv2.resizeWindow(window, 720, 720)

    while True:
        if capture.isOpened():
            ret, frame = capture.read()
            # depending on how cam is mounted, adjust this line
                # for this instance we flip the camera vertically
            #stream = cv2.flip(frame, 0)
            # stream to stdout
            cv2.imshow(stream)
            #time.sleep(0.02)
            if frame.shape:
                #frame = cv2.resize(stream, (640,360))
                frame = imutils.resize(frame, width=620)
                #cv2.imshow(stream)
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
          
    print(stream)
    return cam_id, frame_count


def generate(cam_id):
    # grab global references to the output frame and lock variables
    global output_frame, thr_lock

    stream = parse_cams(cam_id)

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
    return cam_id

@app.route('/video_feed/<string:id>/', methods=["GET"])
def video_feed(id):
    # return the response generated along with the specific media
    # type (mime type)
    return Response(generate(id),
        mimetype = 'multipart/x-mixed-replace; boundary=frame')



def main():
    cam_id = 0 
    frame_count = 0
    # construct the argument parser and parse command line arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-c", "--cam_id", type=int, 
        help="# of cams we want to stream/display")
    ap.add_argument("-f", "--frame-count", type=int, default=32,
        help="# of frames used to construct the background model")
  
    # kwargs for multiple arguments
    kargs = vars(ap.parse_args())
    # OG
    thr_arg = threading.Thread(target=stream_feed, args=(args["frame_count"],))
    #thr_arg = threading.Thread(target=stream_feed, kwargs=(["cam_id"],["frame_count"],))
    # thr_arg = threading.Thread(target=stream_feed, kwargs={'cam_id':cam_id,'frame_count':frame_count})
    #thr_arg = threading.Thread(target=stream_feed, kwargs=(args{'cam_id':cam_id,'frame_count':frame_count}))

    #thread1 = th
    #thr_arg = threading.Thread(target=stream_feed, args=(["cam_id"],["frame_count"],))
    #data_dict = {'cam_id':cam_id, 'frame_count':frame_count}
    #thr_arg = threading.Thread(target=stream_feed, kwargs=params)
    thr_arg.daemon = True
    thr_arg.start()

    # start the flask app passing in host, not requiring execution of program
    # as new edits arise, instead refresh page 
    #app.run(host=args["ip"], port=args["port"], debug=True,
    #    threaded=True, use_reloader=False)
    #data_dict = {'cam_id':cam_id, 'frame_count':frame_count}
    #thr1 = threading.Thread(target=stream_feed, kwargs=my_dict)

    # app.run(host= '0.0.0.0',debug=True, threaded=True)


if __name__ == '__main__':
    # run main
    main()





