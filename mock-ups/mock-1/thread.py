from threading import Thread, Lock
import cv2


class CameraStream(object):
    """
    class where all threading responsibilties are offloaded to
    here we will take in parsed camera ids from stream.py and
    initiate captures based on the corresponding ids and start
    our thread lock
    """
    def __init__(self, cam_id):
        self.stream = cv2.VideoCapture(cam_id)
        (self.grabbed, self.frame) = self.stream.read()
        self.started = False
        self.read_lock = Lock()
    
    def start(self):
    """
    start our thread if not already started
    """
        if self.started:
            print("already started!!")
            return None
        self.started = True
        self.thread = Thread(target=self.update, args=())
        self.thread.start()
        return self

    def update(self):
    """ 
    update our frames
    """
        while self.started:
            (grabbed, frame) = self.stream.read()
            self.read_lock.acquire()
            self.grabbed, self.frame = grabbed, frame
            self.read_lock.release()

    def read(self):
    """
    return our frames 
    """
        self.read_lock.acquire()
        frame = self.frame.copy()
        self.read_lock.release()
        return frame

    """
    join our frames
    """
    def stop(self):
        self.started = False
        self.thread.join()

    """
    exit our threads and release the stream
    """
    def __exit__(self, exc_type, exc_value, traceback):
        self.stream.release()

