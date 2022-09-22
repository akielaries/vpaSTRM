import ffmpeg

src1 = 'rtsp://admin:password123@disc-cam2.iot.nau.edu:554/2'


stream = ffmpeg.input(src1, ss=0)
file = stream.output("test.png", vframes=1)
testfile = file.run(capture_stdout=True, capture_stderr=True)



