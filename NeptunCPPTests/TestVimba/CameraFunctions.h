void WaitForCamera(int numberOfCameras)
{
	if (PvCameraCount() < 2)
	{
		if (numberOfCameras == 1)
			printf("Waiting for a camera\n");
		else
			printf("Waiting for %d cameras\n", numberOfCameras);
		while (PvCameraCount() < 2)
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}



bool CameraGet(int numberOfCameras, tPvHandle &cameraHandle1, tPvHandle &cameraHandle2)
{

	tPvUint32 count, connected;
	tPvCameraInfoEx list[10];
	tPvErr error;

	//regardless if connected > 1, we only set UID of first camera in list
	count = PvCameraListEx(list, numberOfCameras, &connected, sizeof(tPvCameraInfoEx));
	if (count > 0)
	{
		/*GCamera.UID = list.UniqueId;*/
		for (unsigned int i = 0; i < count; i++)
		{
			printf("Detected camera %s\n", list[i].SerialNumber);
			// Open the camera.
			tPvAccessFlags err = static_cast<tPvAccessFlags>(list[i].PermittedAccess);
			if (i == 0)
				error = PvCameraOpen(list[i].UniqueId, ePvAccessMaster, &cameraHandle1);
			else
				error = PvCameraOpen(list[i].UniqueId, ePvAccessMaster, &cameraHandle2);

			if (error == ePvErrSuccess)
				printf("Camera Handle aquired successfully\n");
			else
			{
				printf("Camera Handle not aquired\n");
				return false;
			}

		}
		return true;




	}
	else
	{
		printf("CameraGet: Failed to find a cameras\n");
		return false;
	}
}