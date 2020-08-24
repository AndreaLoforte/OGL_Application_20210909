#include<cameraLoader.h>
#include<log.h>

using namespace std;

namespace saveloadNS {


	const string
		CameraSavings::CAMERATAG = "---------------CAMERA-----------------",
		CameraSavings::CAMERAID = "CameraID",
		CameraSavings::CAMERAGLBCOORDS = "GlobalCoordinates",
		CameraSavings::CAMERAORIENTATION = "Orientation",
		CameraSavings::CAMERAMATRIX1 = "PreviousMatrix",
		CameraSavings::CAMERAMATRIX2 = "ReversePreviousXrotationMatrix",
		CameraSavings::ENDCAMERATAG = "--------------ENDCAMERA---------------";


	void CameraSavings::loadMapsIntoDataStructure()
	{

		for (int i = 0; i < CameraMap.getSize(); i++)
		{
			size_t camData_begin = CameraMap.getPos(i);
			size_t camData_end = CameraDelimitersMap.getPos(i);
			CameraDataStructure cameraToLoad;

			//LOADING CAMERA ID
			{
				vector<string> cameraID(CameraIDMap.getContentInRange(CameraMap.getPos(i), CameraDelimitersMap.getPos(i)));
				cameraToLoad.CameraID = cameraID[0];//mi aspetto un vettore monoelemento
			}

			
			//LOADING CAMERA GLOBAL COORDINATES
			{
				vector<string> cameraGLBCoords(CameraGLBCoordsMap.getContentInRange(CameraMap.getPos(i), CameraDelimitersMap.getPos(i)));
				vector<float> cameraGLBCoords_float;
				stringToFloatVec(cameraGLBCoords[0], cameraGLBCoords_float);
				cameraToLoad.GlobalCoords[0] = cameraGLBCoords_float[0];
				cameraToLoad.GlobalCoords[1] = cameraGLBCoords_float[1];
				cameraToLoad.GlobalCoords[2] = cameraGLBCoords_float[2];
			}

			//LOADING CAMERA ORIENTATION COORDINATES
			{
				vector<string> cameraOrientation(CameraOrientationMap.getContentInRange(CameraMap.getPos(i), CameraDelimitersMap.getPos(i)));
				vector<float> cameraOrientation_float;
				/*so che la stringa contenente i valori di orientamento sarà di una sola riga*/
				stringToFloatVec(cameraOrientation[0], cameraOrientation_float);
				cameraToLoad.orientation.w = cameraOrientation_float[0];
				cameraToLoad.orientation.x = cameraOrientation_float[1];
				cameraToLoad.orientation.y = cameraOrientation_float[2];
				cameraToLoad.orientation.z = cameraOrientation_float[3];
			}

			//LOADING CAMERA PREVIOUS MATRIX
			{
				vector<string> cameraPrevMatrix(CameraPrevMatrixMap.getContentInRange(camData_begin, camData_end));
				string concat_matrix_rows = "";
				for (int i = 0; i < cameraPrevMatrix.size(); i++)
					concat_matrix_rows += cameraPrevMatrix[i] + " ";
				cameraToLoad.prev_Mat = stringToMat4(concat_matrix_rows);
			}

			//loading CAMERA INVERSE PREV X ROT MATRIX
			{
				vector<string> CameraInversePrevXRotMat_(CameraInversePrevXRotMat.getContentInRange(camData_begin, camData_end));
				string concat_matrix_rows = "";
				for (int i = 0; i < CameraInversePrevXRotMat_.size(); i++)
					concat_matrix_rows += CameraInversePrevXRotMat_[i] + " ";
				cameraToLoad.reversePrevXrotMat = stringToMat4(concat_matrix_rows);
			}


			cameras.push_back(cameraToLoad);
		}
	}

	
}