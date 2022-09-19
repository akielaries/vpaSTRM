import ffmpeg


stream = ffmpeg.input("rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2", ss=0)
file = stream.output("test_stream.mp4")
test = file.run(capture_stdout=True, capture_stderr=True)



