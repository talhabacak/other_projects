
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
//#include <opencv2\tracking.hpp>	// with Contrib File
#include <iostream>
#include <string>

using namespace std;
using namespace cv;


int main() {
	string path = "siha1.mp4";
	VideoCapture cap(path);
	Mat frame;
	int frameWidth;
	int frameHeight;
	float timer;
	int fps;
	char k;

	if (!cap.isOpened()) {
		cout << "ERROR\n";
		return -1;
	}

	frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
	
	VideoWriter output("siha1-tracker.mp4", VideoWriter::fourcc('X', 'V', 'I', 'D'), 20, Size(frameWidth, frameHeight),true);
	
	Ptr <Tracker> tracker = TrackerMIL::create();	// without Contrib File
	//Ptr <Tracker> tracker = TrackerKCF::create();  // with Contrib File

	cap.read(frame);
	// Select ROI
	Rect trackingBox = selectROI(frame, false);
	tracker->init(frame,trackingBox);

	while (cap.read(frame)) {
		timer = getTickCount();
		if (tracker->update(frame,trackingBox)) {
			rectangle(frame, trackingBox, Scalar(255, 0, 0));
		}
		fps = getTickFrequency() / (getTickCount() - timer);

		putText(frame, to_string(fps), Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.75, (50, 170, 50), 3);
		imshow("Tracker", frame);
		output.write(frame);
		
		k = waitKey(1);
		if (k == 27) {
			break;
		}
		else if (k == 'a' || k == 'A') {
			// Select New ROI
			trackingBox = selectROI(frame, false);
			tracker->init(frame, trackingBox);
		}
	}
	cap.release();
	output.release();
	destroyAllWindows();
}

