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



bool CameraGet(int numberOfCameras, tPvHandle cameraHandle)
{

	tPvUint32 count, connected;
	tPvCameraInfoEx list[10];

	//regardless if connected > 1, we only set UID of first camera in list
	count = PvCameraListEx(list, numberOfCameras, &connected, sizeof(tPvCameraInfoEx));
	if (count > 0)
	{
		/*GCamera.UID = list.UniqueId;*/
		printf("%d\n", count);
		for (unsigned int i = 0; i < count; i++)
		{
			printf("Got camera %s\n", list[i].SerialNumber);
			if (list[i].PermittedAccess == ePvAccessMaster)
			{
				// Open the camera.
				if (PvCameraOpen(list[i].UniqueId, ePvAccessMaster, &cameraHandle) == ePvErrSuccess)
					printf("Camera Handle aquired successfully");
				
			}
		}
		return true;


		

	}
	else
	{
		printf("CameraGet: Failed to find a camera\n");
		return false;
	}
	//tPvUint32 count, connected;
	//unsigned long numCamera;
	//tPvCameraInfoEx list[10];

	////regardless if connected > 1, we only set UID of first camera in list
	//count = PvCameraListEx(list, numberOfCameras, &connected, sizeof(tPvCameraInfoEx));
	//if (count > 0	)
	//{
	//	/*unsigned long UID = *list.UniqueId;*/
	//	printf("The following cameras were found:\n");
	//	//for (int i = 1; i <= connected;i ++)
	//	//	printf("%s", list[i].SerialNumber);
	//	return true;
	//}
	//else
	//{
	//	printf("CameraGet: Failed to find a camera\n");
	//	return false;
	//}
}