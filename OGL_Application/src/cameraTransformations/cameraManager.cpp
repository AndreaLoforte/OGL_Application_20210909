#include<cameraManager.h>
#include<PrintHelper.h>
#include<userInterface.h>
#include<cameraLoader.h>
namespace fpcameraNS {


	unsigned CameraManager::activeCamIndex = 1;
	std::vector<Transformation*> CameraManager::cameraList;
	printHelperNS::PrintHelper CameraManager::ph{ "cameraManager" };






	void CameraManager::save() 
	{
		
		std::ofstream out(logNS::Logger::PROJECTDIR + saveloadNS::CAMERASAVINGFILE);
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
		}
		else
		{
			activeCamIndex = 0;
		}

	}

	

	void CameraManager::load(const std::string& projectFilename) {

		
		auto lambda_autoInit = [&]()
		{
			cameraList.push_back(new GroundCamera());
			cameraList.push_back(new FlyingCamera());
			cameraList.push_back(new PanoramicCamera());

			for (int i = 0; i < 3; i++)
			{
				cameraList[i]->camForGLBcoords[0] = 0;
				cameraList[i]->camForGLBcoords[1] = -50;
				cameraList[i]->camForGLBcoords[2] = -100;

				if (cameraList[i]->getCameraType() == FLYINGCAMERA ||
					cameraList[i]->getCameraType() == PANORAMICCAMERA)
				{
					cameraList[i]->camOrientation = mymathlibNS::Quaternion::getQuaternionfromXAngle(20);
				}
			}
		};

		
	
		std::string dir(logNS::Logger::PROJECTDIR + saveloadNS::CAMERASAVINGFILE);
		std::ifstream in(dir);
		saveloadNS::CameraSavings fh(in);


		if (!fh.FileIsEmpty)
		{
			cameraList.clear();

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
		{
			lambda_autoInit();
		}
			
	}



}