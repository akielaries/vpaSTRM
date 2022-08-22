import cv2

capture_obj = cv2.VideoCapture('rtsp://admin:password123@192.168.1.176:554/2')

while True:
    ret, frame = capture_obj.read()
    cv2.imshow("Capturing", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

capture_obj.release()
cv2.destroyAllWindows()

