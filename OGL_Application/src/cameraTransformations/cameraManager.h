#pragma once
#include<vector>
#include<string>
#include<fpcamera.h>
#include<PrintHelper.h>

namespace fpcameraNS {

	static unsigned FLYING_CAMERA_INDEX = 1;
	static unsigned GROUND_CAMERA_INDEX = 0;
	static unsigned PANORAMIC_CAMERA_INDEX = 2;


	/* CAMERA MANAGER */
	class CameraManager {
		friend class Transformation;
		//APPROFONDIRE CHIAMATE A FUNZIONI VIRTUALI E CASTING DI PUNTATORI!
		static std::vector<Transformation*> cameraList;
		static unsigned activeCamIndex;
		static printHelperNS::PrintHelper ph;
	public:
		

		static  const Transformation& getActiveCamera() { return *cameraList[activeCamIndex]; }
		static  Transformation& getActiveCameraLH() { return *cameraList[activeCamIndex]; }//LH leftHand
		static const Transformation* getActiveCameraPT() { return cameraList[activeCamIndex]; }
		static void update() {
			(*cameraList[activeCamIndex]).update();
		}

		static void I() { cameraList[activeCamIndex]->switchPrintInfos(); }
		static void switchCamera();
		static void resetAll() {
			for (int i = 0; i < cameraList.size(); i++)
			{
				cameraList[i]->resetAll();
				cameraList[i]->BOsetCamera();
			}

		}

		static void save();

		static void load(const string&);

		static void setActiveCameraIndex(int activeCameraIndex);

		//
		static void switchPrintInfos() {

			for (int i = 0; i < cameraList.size(); i++)
				cameraList[0]->switchPrintInfos();

		}

		static void pushNewCamera(Transformation*);

		static void changeCameraMovementSpeed(int i)
		{
			cameraList[activeCamIndex]->changeTranslationSpeed(i);
		}

		static string getActiveCameraType()
		{
			return cameraList[activeCamIndex]->getCameraType();
		}

	};






}