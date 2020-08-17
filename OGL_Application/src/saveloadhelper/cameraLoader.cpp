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


	void CameraSavings::loadCameraMapsIntoDataStructure()
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

	

	/*funzione che in lettura dal FileMap dell'intero file
	distribuisce su tutte le mappe dei parametri,
	i relativi valori*/
	void CameraSavings::setAllCameraMap()
	{

		for (int i = 0; i < totalLines; i++)
		{
			//LOAD CAMERA TAG AND CAMERA END TAG
			if (fileMap.getLine(i).find(CAMERATAG) != string::npos)
			{
				//inserisco in mappa la linea successiva al tag
				CameraMap.insert(fileMap.getLine(i), fileMap.getPos(i));
			}
			if (fileMap.getLine(i).find(ENDCAMERATAG) != string::npos)
			{
				//inserisco in mappa la linea successiva al tag
				CameraDelimitersMap.insert(fileMap.getLine(i), fileMap.getPos(i));
			}


			//LOAD CAMERA ID
			if (fileMap.getLine(i) == CAMERAID)
			{
				/*inserisco sempre la riga successiva al tag*/
				CameraIDMap.insert(fileMap.getLine(i + 1), fileMap.getPos(i + 1));
			}

			//LOAD GLOBAL COORDINATES
			if (fileMap.getLine(i) == CAMERAGLBCOORDS)
			{
				CameraGLBCoordsMap.insert(fileMap.getLine(i + 1), fileMap.getPos(i + 1));
			}

			//LOAD ORIENTATION
			if (fileMap.getLine(i) == CAMERAORIENTATION)
			{
				CameraOrientationMap.insert(fileMap.getLine(i + 1), fileMap.getPos(i + 1));
			}


			//LOAD MATRIX 1
			if (fileMap.getLine(i) == CAMERAMATRIX1)
			{
				//la matrice è distribuita su 4 righe
				CameraPrevMatrixMap.insert(fileMap.getLine(i + 1), fileMap.getPos(i + 1));
				CameraPrevMatrixMap.insert(fileMap.getLine(i + 2), fileMap.getPos(i + 2));
				CameraPrevMatrixMap.insert(fileMap.getLine(i + 3), fileMap.getPos(i + 3));
				CameraPrevMatrixMap.insert(fileMap.getLine(i + 4), fileMap.getPos(i + 4));

			}

			//LOAD MATRIX2 
			if (fileMap.getLine(i) == CAMERAMATRIX2)
			{
				
				//la matrice è distribuita su 4 righe
				CameraInversePrevXRotMat.insert(fileMap.getLine(i + 1), fileMap.getPos(i + 1));
				CameraInversePrevXRotMat.insert(fileMap.getLine(i + 2), fileMap.getPos(i + 2));
				CameraInversePrevXRotMat.insert(fileMap.getLine(i + 3), fileMap.getPos(i + 3));
				CameraInversePrevXRotMat.insert(fileMap.getLine(i + 4), fileMap.getPos(i + 4));

			}

			

		}



	}
	


	//CameraSavings::CameraSavings(ifstream& in)
	//{

	//	
	//	if (in.is_open())
	//	{
	//		in.seekg(0);
	//		while (!in.eof() && (std::fpos_t/*casting is needed to avoid ambiguous operator !=*/)in.tellg()>=0)
	//		{
	//			getline(in, s);
	//			std::fpos_t cursor_pos = in.tellg();
	//			size_t lineLength = s.length();
	//			std::fpos_t line_beg = cursor_pos - lineLength - 2; //2 extra char "\n"
	//			fileMap.insert(s, line_beg);
	//			in.seekg(cursor_pos + lineLength);
	//		}

	//		totalLines = fileMap.getSize();

	//		countChar();
	//		if (totalChars == 0)
	//		{
	//			FileIsEmpty = true;
	//			return;
	//		}


	//		countChar();
	//		
	//		setAllCameraMap();
	//		
	//		loadCameraMapsIntoDataStructure();

	//	}


	//}



	CameraSavings::CameraSavings(ifstream& in)
	{

		std::size_t cursorpos = 0;
		if (in.is_open())
		{
			in.seekg(cursorpos);
			while (!in.eof())
			{
				getline(in, s);
				//in.seekg(0)
				
				size_t lineLength = s.length();
				cursorpos += lineLength+2;//2 extra char "\n"
				std::size_t line_beg = cursorpos - lineLength - 2; //2 extra char "\n"
				fileMap.insert(s, line_beg);
				//in.seekg(cursorpos + lineLength);
			}

			totalLines = fileMap.getSize();

			
			if (fileMap.getCharNumber() == 0)
			{
				FileIsEmpty = true;
				return;
			}

			setAllCameraMap();

			loadCameraMapsIntoDataStructure();

		}


	}




}