#ifndef ASSETS_H
#define ASSETS_H


//#include<applicationObject.h>//circular dependence

#include<objectCollector.h>
#include<vector>
#include<map>
namespace myobjectNS {

		class ApplicationObject;
}

namespace AssetNS {


	

	class Assets {
	public:
		static std::vector< collectorNS::ApplicationObjectCollector*> assetsList;
		static std::map<std::string, int> assetIndex;//mappa nome colletore VS indice in assetList
		static std::vector<myobjectNS::ApplicationObject*> assetAOList;
		static std::map<std::string, int > assetAOindex;//mappa nome ApplicatioObject VS indice in assetAOList

		Assets() {
			init();
		}
		static void init();
		static std::vector< collectorNS::ApplicationObjectCollector*>* getAssetList() { return &assetsList; }
		static std::vector<myobjectNS::ApplicationObject*>* getAssetAOList() { return &assetAOList; }
		static std::map<std::string, int >* getAssetAOIndex() { return &assetAOindex; }
		static std::map<std::string, int >* getAssetIndex() { return &assetIndex; }
		static std::map<std::string, int>::iterator  getAssetMapBeg() { return assetIndex.begin(); }
		static std::map<std::string, int>::iterator  getAssetMapEnd() { return assetIndex.end(); }
		static std::multimap<std::string, int>::iterator getAssetMapID(std::string assetName) { return assetIndex.find(assetName); }
		static int mapSize;
		static myobjectNS::ApplicationObject* getNewObject(std::string);
		static collectorNS::ApplicationObjectCollector* getNewCollector(std::string);
		static myobjectNS::ApplicationObject* getNewObject(int index);
		static collectorNS::ApplicationObjectCollector* getNewCollector(int index);

	};


}


#endif