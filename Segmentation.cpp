#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

struct MouseParams
{
	Mat img;
	int toleranceValue;
 
public:
	MouseParams(Mat img, int toleranceValue) {
		this->img = img;
		this->toleranceValue = toleranceValue;
	}
};

static void onMouse(int event, int x, int y, int, void *param){

    if (event == EVENT_LBUTTONDOWN){

		MouseParams* mp = (MouseParams*)param;
		Mat src = mp->img;
		int toleranceValue = mp->toleranceValue;
		Scalar tolerance(toleranceValue, toleranceValue, toleranceValue);
		Scalar newVal(0, 255, 255);
		Point selectedPoint(x, y);
		floodFill(src, selectedPoint, newVal, 0, tolerance, tolerance);
		imshow("Input", src);
    }
}

static void onChange(int trackbarPositon, void* param) {
	MouseParams* mp = (MouseParams*)param;
	mp->toleranceValue = trackbarPositon;
}

int main()
{
	std::string imagePath = ".\\rick-and-morty-season-4-image.jpg";
	cv::Mat image;
	image = cv::imread(imagePath);
	int toleranceValue = 1;
	MouseParams* mp = new MouseParams(image, toleranceValue);

	if (image.empty()) {
		cout << "Cannot read image ..." << endl;
		return -1;
	}
	
	namedWindow("Input", WINDOW_NORMAL);
	setMouseCallback("Input", onMouse, mp);
	createTrackbar("Tolerance", "Input", &toleranceValue, 50, onChange, mp);
	imshow("Input", image);
	waitKey(0);

	delete mp;
	return 0;
}
