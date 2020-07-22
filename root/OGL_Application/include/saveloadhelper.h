#ifndef SAVELOADHELPER
#define SAVELOADHELPER
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<vmath.h>
#include<array>
#include<mymathlib.h>
using namespace std;
namespace saveloadNS {

	
	void stringToFloatVec(string s, vector<float>& vec);
	vmath::mat4 stringToMat4(string m);
	std::array<float, 3> stringToVec3(string s);

	/*it's a Map to hold together the string content
	of the file, with information of the cursor position
	for each row (cursor position depends on number of chars in the line)*/
	class FileMap {
	public:
		/*collect each line of the file*/
		vector<string> fileLines;
		/*for each line, collect the 
		respective cursor position*/
		vector<std::fpos_t> filePos;
		unsigned size = 0;
		unsigned charnumber = 0;
		void insert(string s, size_t pos);

		/*get the i-th line in the file*/
		string getLine(unsigned i);
		/*get the cursor position at line i*/
		size_t getPos(unsigned i);
		/*get the map size*/
		unsigned& getSize();
		unsigned& getCharNumber()
		{
			for (int i = 0; i < fileLines.size(); i++)
				charnumber += fileLines[i].length();
			return charnumber;
		}
		/*funzione che ritorna tutte le stringhe della 
		mappa contenute dentro il range specificato*/
		vector<string> getContentInRange(size_t, size_t);

		void popLastElement();
	};


	/*Application Object Data container :
	from here loaded data will be poured into 
	real Application Object*/
	class AODataStructure {
	public:
		string ObjectName;
		unsigned instanceNumber;
		vmath::mat4 AOTrMatrix;
		std::array<float,3> AOposition;
		std::vector<float> AOsize;
		vmath::vec4 AOcolor;
		mymathlibNS::Quaternion AOorientation;
		bool isOn;
		string getStructureID()
		{
			return ObjectName;
		}
	
	};

	
	


	class CollectorDataStructure {
	public:
		string collectorsID;
		size_t pos_start = 0, pos_end = 0;
		bool isOn;
		vector<AODataStructure> AOobjects;
	};


	class CameraDataStructure
	{
	public:
		string CameraID;
		float GlobalCoords[3];
		mymathlibNS::Quaternion orientation;
		vmath::mat4 prev_Mat;
		vmath::mat4 reversePrevXrotMat;
	};




	class FileHelper {};




	class CollectorSavings : public FileHelper {

		/*fileMap , maps the entire file*/
		FileMap fileMap;
		string s;
		unsigned totalLines = 0;
		unsigned totalChars = 0;

		/*following map are specific for
		object or parameters inside object*/
		FileMap collectorsMap;
		FileMap collectorsDelimitersMap;
		FileMap ObjectsMap;
		FileMap AOpositionMap;
		FileMap AOorientationMap;
		FileMap AOTrMatrixMap;
		FileMap AOcolorMap;
		FileMap DOsizeMap;
		FileMap AOisonFlagMap;
		FileMap OCisOnMap;



		vector<CollectorDataStructure> collectors;

	public:
		CollectorSavings(ifstream& in);
		bool FileIsEmpty = false;
		virtual unsigned getTotalLines() { return totalLines; }
		virtual unsigned& getTotalChars() { return totalChars; }

		FileMap getCollectorsMap() { return collectorsMap; }

		vector<CollectorDataStructure>* getCollectors() { return &collectors; }

		/*il metodo setAllCollectorsMap carica tutte
		le mappe dei collettori in modo tale che ogni
		oggetto/parametro di un collettore abbia la sua mappa*/
		void setAllCollectorsMap();

		/*il metodo loadCollectors.. legge dalle mappe
		e porta i dati da formato stringa al loro vero
		formato per poi inserirle nelle data structure*/
		void loadCollectorMapsIntoDataStructure();

		static const string
			COLLECTORTAG,
			COLLECTORENDTAG,
			COLLECTORISONTAG,
			OBJECTNAMETAG,
			AOPOSITIONTAG,
			AOORIENTATIONTAG,
			AOTRMATRIXTAG,
			AOINSTANCENUMBERTAG,
			AOCOLORTAG,
			DOSIZETAG,
			AOISONFLAGTAG;
	};












	class CameraSavings : public FileHelper{

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
		unsigned getTotalLines()  { return fileMap.fileLines.size(); }
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




#endif