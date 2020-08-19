#pragma once

#include<fileMap.h>

using namespace std;
namespace saveloadNS {

	const string CAMERASAVINGFILE = "camera";

	class CameraDataStructure
	{
	public:
		string CameraID;
		float GlobalCoords[3];
		mymathlibNS::Quaternion orientation;
		vmath::mat4 prev_Mat;
		vmath::mat4 reversePrevXrotMat;
	};


	class CameraSavings : public FileHelper {

		/*fileMap , maps the entire file*/
		FileMap fileMap;
		string s = "";

		/*following map are specific for
		object or parameters inside object*/

		FileMap CameraMap;
		FileMap CameraDelimitersMap;
		FileMap CameraGLBCoordsMap;
		FileMap CameraOrientationMap;
		FileMap CameraPrevMatrixMap;
		FileMap CameraInversePrevXRotMat;
		FileMap CameraIDMap;

		vector<CameraDataStructure> cameras;

	public:
		unsigned totalLines = 0;
		unsigned totalChars = 0;


		CameraSavings(ifstream& in);
		bool FileIsEmpty = false;
		unsigned getTotalLines() { return fileMap.fileLines.size(); }
		unsigned& getTotalChars() { return totalChars; }

		vector<CameraDataStructure>* getCameras() { return &cameras; }
		/*il metodo setAllCameraMap carica tutte
		le mappe dei collettori in modo tale che ogni
		oggetto/parametro di un collettore abbia la sua mappa*/

		void setAllCameraMap();
		/*il metodo loadCamera.. legge dalle mappe
		e porta i dati da formato stringa al loro vero
		formato per poi inserirle nelle data structure*/
		void loadCameraMapsIntoDataStructure();

		static const string

			CAMERATAG,
			CAMERAID,
			CAMERAGLBCOORDS,
			CAMERAORIENTATION,
			CAMERAMATRIX1,
			CAMERAMATRIX2,
			ENDCAMERATAG;
	};




}