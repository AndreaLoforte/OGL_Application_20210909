#include<cameraManager.h>
#include<PrintHelper.h>
#include<userInterface.h>
namespace fpcameraNS {


	unsigned CameraManager::activeCamIndex = 0;
	std::string CameraManager::projectDataFileName;
	std::vector<Transformation*> CameraManager::cameraList;
	textRendererNS::PrintHelper CameraManager::ph{ "cameraManager" };



	void CameraManager::save() 
	{
		std::ofstream out(logNS::Logger::STOREDDATADIR + "camera");
		for (int i = 0; i < cameraList.size(); i++)
			cameraList[i]->save(out);

	}


	void CameraManager::pushNewCamera(Transformation* t) 
	{
		cameraList.push_back(t);
	}

	void CameraManager::switchCamera() {
		if (cameraList.size() - 1 > activeCamIndex)
		{
			activeCamIndex++;
			CameraManager::ph.mapNewString("CAMERAID", fpcameraNS::CameraManager::getActiveCamera().cameraID);
		}
		else
		{
			activeCamIndex = 0;
			CameraManager::ph.mapNewString("CAMERAID", fpcameraNS::CameraManager::getActiveCamera().cameraID);
		}

	}

	static const std::string TAG_OBJECT_CAMERA{ "Camera" };

	void CameraManager::load() {

		auto lambda_autoInit = [&]()
		{
			ph.mapNewString("CAMERALOADWARNING", "there are no camera savings : default camera loaded");
			cameraList.push_back(new GroundCamera());
			cameraList.push_back(new FlyingCamera());
			cameraList.push_back(new PanoramicCamera());
		};

		
		std::string dir(logNS::Logger::STOREDDATADIR + TAG_OBJECT_CAMERA);
		std::ifstream in(dir);
		saveloadNS::CameraSavings fh(in);


		if (!fh.FileIsEmpty)
		{
			vector<saveloadNS::CameraDataStructure>* loadedCameras =
				fh.getCameras();

			if (loadedCameras->size() != 0)
			{
				for (int i = 0; i < loadedCameras->size(); i++)
				{
					saveloadNS::CameraDataStructure cameraData = loadedCameras->at(i);
					Transformation * loadedT;
					if (cameraData.CameraID == GROUNDCAMERA)
						loadedT = new GroundCamera();
					else if (cameraData.CameraID == FLYINGCAMERA)
						loadedT = new FlyingCamera();
					else if (cameraData.CameraID == PANORAMICCAMERA)
						loadedT = new PanoramicCamera();
					else
						loadedT = new GroundCamera(); /*groundCamera is the default*/


					loadedT->cameraID = cameraData.CameraID;
					loadedT->camForGLBcoords[0] = cameraData.GlobalCoords[0];
					loadedT->camForGLBcoords[1] = cameraData.GlobalCoords[1];
					loadedT->camForGLBcoords[2] = cameraData.GlobalCoords[2];
					loadedT->camOrientation = cameraData.orientation;
					//loadedT->prev_M = cameraData.prev_Mat;
					//loadedT->reverse_prev_x_rot = cameraData.reversePrevXrotMat;

					loadedT->BOsetCamera();
					cameraList.push_back(loadedT);

				}
			}
			else
				lambda_autoInit();

		}
		else
			lambda_autoInit();



		CameraManager::ph.eraseFromMap("CAMERALOADWARNING");
		CameraManager::ph.mapNewString("CAMERAID", getActiveCamera().cameraID);

	}



}