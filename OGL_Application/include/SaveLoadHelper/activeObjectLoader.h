#pragma once
#include<collectorLoader.h>
#include<activeObjectCollector.h>
#include<saver.h>
using namespace std;
namespace saveloadNS {


	const string ACTIVEOBJECTSAVINGFILE = "activeObject";

	class ActiveObjectDataStructure {
	public:
		string collectorName;
		unsigned collectorNumber;
		string activityGroundID;
		size_t pos_start = 0, pos_end = 0;
		bool isOn;
		vector<AODataStructure> AOobjects;
	};



	class ActiveObjectLoader : public FileHelper {

		/*must be static otherwise is clearead (because initialized)
		after class constructor call()*/
		static vector<ActiveObjectDataStructure> collectors;

	public:
		ActiveObjectLoader(ifstream& in) :
			FileHelper(in, 
				{
		/*can't pass as a vector because it is
		initialized after the call to FileHelper constructor*/
			COLLECTORTAG,
			COLLECTORENDTAG,
			COLLECTORNUMBER,
			OBJECTNAMETAG,
			AOPOSITIONTAG,
			AOORIENTATIONTAG,
			AOTRMATRIXTAG,
			AOCOLORTAG,
			DOSIZETAG,
			AOISONFLAGTAG,
			COLLECTORISONTAG,
			ACTIVITYGROUNDID,
				},
				this) {}
		

		virtual unsigned getTotalLines() { return totalLines; }
		virtual unsigned& getTotalChars() { return totalChars; }

		FileMap getCollectorsMap() { return TAGLIST.at(COLLECTORTAG); }

		vector<ActiveObjectDataStructure>* getCollectors() { return &collectors; }

	
		/*il metodo loadCollectors.. legge dalle mappe
		e porta i dati da formato stringa al loro vero
		formato per poi inserirle nelle data structure*/
		void loadMapsIntoDataStructure() ;
		
		static const string
			COLLECTORTAG,
			COLLECTORENDTAG,
			COLLECTORNUMBER,
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


	class ActiveObjectSaver : dataSaver
	{
		
	public:
		static ofstream out;
		bool savingSessionIsOpen = false;
		static void save(collectorNS::ActiveObject* coll, std::string& filename);
	};



}