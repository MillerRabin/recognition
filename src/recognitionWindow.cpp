#include <opencv2/opencv.hpp>
#include <ptz/ptz.h>
#include <credentials.h>

using namespace cv;


int main() {		
	PTZ ptz(CAM_IP);
	Token token = ptz.login(CAM_LOGIN, CAM_PASS);
	ptz.control(token, "Up");
	ptz.control(token, "Stop");
	
	/*VideoCapture cap("rtsp://admin:ifyouwanttohave@192.168.1.32:554/h264Preview_01_main");
	
	if (!cap.isOpened())
		return -1;

	for (;;) {
		Mat frame;
		cap >> frame;
		imshow("WebCam Frame", frame);

		if (waitKey(1) >= 0)
			break;
	}*/
	return 0;
}