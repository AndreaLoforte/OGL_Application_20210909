#pragma once
#include<fileMap.h>
#include<saver.h>
#include<objectCollector.h>
using namespace std;
namespace saveloadNS {

	const string COLLECTORSAVINGFILE = "collectors";

	/*Application Object Data container :
		from here loaded data will be poured into
		real Application Object*/
	class AODataStructure {
	public:
		string ObjectName;
		unsigned instanceNumber;
		vmath::mat4 AOTrMatrix;
		std::array<float, 3> AOposition;
		float AOscale;
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

		/*must be static otherwise is clearead (because initialized)
		after class constructor call()*/
		static vector<CollectorDataStructure> collectors;

	public:
		CollectorLoader(ifstream& in) :
			FileHelper(in, {
			COLLECTORTAG,
			COLLECTORENDTAG,
			COLLECTORISONTAG,
			COLLECTORNUMBER,
			OBJECTNAMETAG,
			AOPOSITIONTAG,
			AOSCALE,
			AOORIENTATIONTAG,
			AOTRMATRIXTAG,
			AOINSTANCENUMBERTAG,
			AOCOLORTAG,
			DOSIZETAG,
			AOISONFLAGTAG
				},this) {}
		//bool FileIsEmpty = false;
		virtual unsigned getTotalLines() { return totalLines; }
		virtual unsigned& getTotalChars() { return totalChars; }

		FileMap getCollectorsMap() { return TAGLIST.at(COLLECTORTAG); }

		vector<CollectorDataStructure>* getCollectors() { return &collectors; }

		/*il metodo loadCollectors.. legge dalle mappe
		e porta i dati da formato stringa al loro vero
		formato per poi inserirle nelle data structure*/
		void loadMapsIntoDataStructure() ;


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
			AOSCALE,
			AOCOLORTAG,
			DOSIZETAG,
			AOISONFLAGTAG;

	};



	class CollectorSaver : dataSaver
	{
	public:
	
		static ofstream out;
		static	void save(collectorNS::ApplicationObjectCollector* coll, std::string& projectName);
	};



}