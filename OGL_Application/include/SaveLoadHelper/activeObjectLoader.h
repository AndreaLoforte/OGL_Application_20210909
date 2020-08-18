#pragma once
#pragma once
#include<collectorLoader.h>

using namespace std;
namespace saveloadNS {


	class ActiveObjectDataStructure {
	public:
		string collectorsID;
		string activityGroundID;
		size_t pos_start = 0, pos_end = 0;
		bool isOn;
		vector<AODataStructure> AOobjects;
	};



	class ActiveObjectLoader : public FileHelper {

		vector<ActiveObjectDataStructure> collectors;

	public:
		ActiveObjectLoader(ifstream& in);
		bool FileIsEmpty = false;
		virtual unsigned getTotalLines() { return totalLines; }
		virtual unsigned& getTotalChars() { return totalChars; }

		FileMap getCollectorsMap() { return TAGLIST.at(STARTDELIMITER);/* collectorsMap;*/ }

		vector<ActiveObjectDataStructure>* getCollectors() { return &collectors; }

	
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
			AOISONFLAGTAG,
			ACTIVITYGROUNDID;


		const string STARTDELIMITER = "ACTIVEOBJECT_";
		const string ENDDELIMITER = "--------ACTIVEOBJECTEND--------";

		map<string,FileMap> TAGLIST
		{
			{STARTDELIMITER,					FileMap("collectorsMap")},
			{ENDDELIMITER,				FileMap("collectorsDelimitersMap")},
			{"AOobjectName",					FileMap("ObjectsMap")},
			{"AOposition",						FileMap("AOpositionMap")}	 ,
			{"AOorientation",					FileMap("AOorientationMap")},
			{"AOTrMatrix",						FileMap("AOTrMatrixMap")}	,			  
			{"AOcolor",							FileMap("AOcolorMap")}	 ,
			{"DOsize",							FileMap("DOsizeMap")}	 ,
			{"AOisOnFlag",						FileMap("AOisonFlagMap")}	 ,
			{"OCisOnFlag",						FileMap("OCisOnMap")}	 ,
			{"ACTIVE_OBJECT_ACTIVITYGROUND_ID", FileMap("ActivityGroundMap")},
		};


	};




}