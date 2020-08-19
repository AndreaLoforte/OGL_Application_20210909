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
		string collectorsName;
		unsigned collectorNumber;
		size_t pos_start = 0, pos_end = 0;
		bool isOn;
		vector<AODataStructure> AOobjects;
	};



	class CollectorLoader : public FileHelper {

		vector<CollectorDataStructure> collectors;

	public:
		CollectorLoader(ifstream& in);
		bool FileIsEmpty = false;
		virtual unsigned getTotalLines() { return totalLines; }
		virtual unsigned& getTotalChars() { return totalChars; }

		FileMap getCollectorsMap() { return TAGLIST.at(COLLECTORTAG); }

		vector<CollectorDataStructure>* getCollectors() { return &collectors; }

		/*il metodo setAllCollectorsMap carica tutte
		le mappe dei collettori in modo tale che ogni
		oggetto/parametro di un collettore abbia la sua mappa*/
		//void loadAllCollectorsMap();

		/*il metodo loadCollectors.. legge dalle mappe
		e porta i dati da formato stringa al loro vero
		formato per poi inserirle nelle data structure*/
		void loadCollectorMapsIntoDataStructure();

		static const string
			COLLECTORTAG,
			COLLECTORENDTAG,
			COLLECTORISONTAG,
			COLLECTORNUMBER,
			OBJECTNAMETAG,
			AOPOSITIONTAG,
			AOORIENTATIONTAG,
			AOTRMATRIXTAG,
			AOINSTANCENUMBERTAG,
			AOCOLORTAG,
			DOSIZETAG,
			AOISONFLAGTAG;

		vector<string> tagList
		{
			COLLECTORTAG,
			COLLECTORENDTAG,
			COLLECTORISONTAG,
			COLLECTORNUMBER,
			OBJECTNAMETAG,
			AOPOSITIONTAG,
			AOORIENTATIONTAG,
			AOTRMATRIXTAG,
			AOINSTANCENUMBERTAG,
			AOCOLORTAG,
			DOSIZETAG,
			AOISONFLAGTAG
		};
	};




}