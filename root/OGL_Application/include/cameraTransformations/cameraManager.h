#pragma once
#include<vector>
#include<string>
#include<text.h>
#include<fpcamera.h>


namespace fpcameraNS {

	/* CAMERA MANAGER */
	class CameraManager {
		static std::string cameraSavingsFilename;
		static std::string cameraSavingsDirectory;
		friend class Transformation;
		//APPROFONDIRE CHIAMATE A FUNZIONI VIRTUALI E CASTING DI PUNTATORI!
		static std::vector<Transformation*> cameraList;
		static unsigned activeCamIndex;
		static std::string projectDataFileName;
		static textRendererNS::PrintHelper ph;
	public:
		CameraManager(std::string projectdatafilename) {
			projectDataFileName = projectdatafilename;


		}

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

		static void setActiveCameraIndex(int activeCameraIndex) {
			activeCamIndex = activeCameraIndex;
		}

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

	};






}