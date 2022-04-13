# -*- coding: utf-8 -*-
"""
Created on Mon Apr  4 21:51:59 2022

@author: talha
"""
import cv2
import keyboard

tracker = cv2.TrackerMIL_create()   # without Contrib File
#tracker = cv2.TrackerKCF_create()  # with Contrib File
#tracker = cv2.TrackerMOSSE_create()  # with Contrib File

cap = cv2.VideoCapture("siha1.mp4")
ret, frame = cap.read()

frame_height, frame_width = frame.shape[:2]
output = cv2.VideoWriter("siha1-tracker.mp4", 
                         cv2.VideoWriter_fourcc(*'XVID'), 20.0, 
                         (frame_width, frame_height), True)
if not ret:
    print('cannot read the video')
    
### SELECT ROI ###
bbox = cv2.selectROI(frame, False)
ret = tracker.init(frame, bbox)

while True:
    ret, frame = cap.read()
    if not ret:
        print('something went wrong')
        break
    timer = cv2.getTickCount()
    ret, bbox = tracker.update(frame)
    fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)
    if ret:
        p1 = (int(bbox[0]), int(bbox[1]))
        p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
        cv2.rectangle(frame, p1, p2, (255,0,0), 2, 1)
    else:
        cv2.putText(frame, "Tracking failure detected", (100,80), 
                    cv2.FONT_HERSHEY_SIMPLEX, 0.75,(0,0,255),2)
    cv2.putText(frame, "FPS : " + str(int(fps)), (100,25), 
                cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50),2)
    cv2.imshow("Tracking", frame)
    output.write(frame)
    cv2.waitKey(1)
    if keyboard.is_pressed("q") or keyboard.is_pressed("Q"): 
        break
    elif keyboard.is_pressed("a") or keyboard.is_pressed("A"):
        ### SELECT NEW ROI ###
        bbox = cv2.selectROI(frame, False)
        ret2 = tracker.init(frame, bbox)

cap.release()
output.release()
cv2.destroyAllWindows()



