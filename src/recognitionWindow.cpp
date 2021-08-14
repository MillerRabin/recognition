#include <opencv2/opencv.hpp>
#include <http/http.h>


using namespace cv;

int main() {		
	HttpRequest req;
	HttpResponse res = req.request({"https://raintech.su"});
    	
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