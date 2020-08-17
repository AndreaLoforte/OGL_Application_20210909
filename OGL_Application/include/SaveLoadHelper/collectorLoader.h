#pragma once
#include<fileMap.h>


using namespace std;
namespace saveloadNS {

	/*Application Object Data container :
		from here loaded data will be poured into
		real Application Object*/
	class AODataStructure {
	public:
		string ObjectName;
		unsigned instanceNumber;
		vmath::mat4 AOTrMatrix;
		std::array<float, 3> AOposition;
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







	




	class CollectorLoader : public FileHelper {

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
		CollectorLoader(ifstream& in);
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
			AOISONFLAGTAG,
			ACTIVITYGROUNDID;
	};




}