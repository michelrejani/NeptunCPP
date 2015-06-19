#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <PvAPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <PvApi.h>
#include <thread>

using namespace cv;
using namespace std;

static int width = 320;
static int height = 240;

#include "CameraFunctions.h"
int main() {
	
	tPvErr errCode;

	// initialize the PvAPI
	if ((errCode = PvInitialize()) != ePvErrSuccess)
	{
		printf("PvInitialize err: %u\n", errCode);
	}
	else
	{
		WaitForCamera(2);

		int NumberOfCameras = PvCameraCount();
		printf("Number of cameras detected = %d \n", NumberOfCameras);

		tPvHandle cameras[2];

		CameraGet(2, &cameras);

		tPvHandle Camera = cameras[0];
		tPvFrame FrameAllocation{};
		tPvFrame *Frame = &FrameAllocation;

		Mat imageBuffer = cv::Mat(cv::Size(width, height), CV_8UC3);

		unsigned long bufferSize = sizeof(Mat) * width * height;
		unsigned long unusedBuffer = 0;
		unsigned long unusedBufferLength = 1;

		Frame->ImageBuffer = &imageBuffer;
		Frame->ImageBufferSize = bufferSize;
		Frame->AncillaryBuffer = &unusedBuffer;
		Frame->AncillaryBufferSize = unusedBufferLength;

		//start driver stream
		PvCaptureStart(Camera);
		//queue frame
		PvCaptureQueueFrame(Camera, Frame, NULL);
		//set frame triggers to be generated internally
		PvAttrEnumSet(Camera, "FrameStartTriggerMode", "Freerun");
		//set camera to receive continuous number of frame triggers
		PvAttrEnumSet(Camera, "AcquisitionMode", "Continuous");
		//start camera receiving frame triggers
		PvCommandRun(Camera, "AcquisitionStart");
		do {
			//wait for frame to return to host
			printf("first\n");
			PvCaptureWaitForFrameDone(Camera, Frame, PVINFINITE);
			imshow("cam", imageBuffer);
			printf("here\n");
			PvCaptureQueueFrame(Camera, Frame, NULL);
		} while (true);


		
		// uninitialize PvAPI
		PvUnInitialize();
	}




	//VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

	//if (!stream1.isOpened()) { //check if video device has been initialised
	//	cout << "cannot open camera";
	//}

	////unconditional loop
	//while (true) {
	//	Mat cameraFrame;
	//	stream1.read(cameraFrame);
	//	imshow("cam", cameraFrame);
	//	if (waitKey(30) >= 0)
	//		break;
	//}
	return 0;
}