import cv2
import time


cam = cv2.VideoCapture(0)
cam.set(3,800)
cam.set(4,480)

while True:
    time.sleep(0.2)
    ret, image = cam.read()
    if ret:
        cv2.imwrite('/var/www/html/image.jpg',image)
        #cv2.imshow('Target',image)
        #cv2.waitKey(0)
	
cam.release()
cv2.destroyAllWindows()
