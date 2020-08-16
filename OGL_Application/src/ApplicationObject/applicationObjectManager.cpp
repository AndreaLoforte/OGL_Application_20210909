#include <applicationObjectManager.h>
#include<vmath.h>
#include<printHelper.h>
#include<app.h>
#include<physics.h>
#include<assets.h>
#include<extern_definitions.h>
#include<gun.h>
#include<saveloadhelper.h>


namespace myobjectNS
{
	using namespace std;
	using namespace textRendererNS;

	printHelperNS::PrintHelper ApplicationObjectManager::ph{ "ApplicationObjectManager" };


///std::vector< collectorNS::ApplicationObjectCollector*> ApplicationObjectManager::AssetCollectorList;
	std::vector< collectorNS::ApplicationObjectCollector*> ApplicationObjectManager::ApplicationCollectorList;
unsigned ApplicationObjectManager::editableObjIndex  = 0;
std::map< std::string, std::pair<int,int>> ApplicationObjectManager::objectListIndexMap;
std::map< std::string, std::pair<int, int>> ApplicationObjectManager::objectListRBIDMap;
std::map< std::string, int> ApplicationObjectManager::collectorIDMap;



void ApplicationObjectManager::setupObjectsParameters()
{
	for (int i = 0; i < ApplicationCollectorList.size(); i++)
		ApplicationCollectorList[i]->OCcreateObject();

	for (int i = 0; i < ApplicationCollectorList.size(); i++)
		ApplicationCollectorList[i]->OCsetParameters();

}




bool ApplicationObjectManager::loadData(string filename) {

	ApplicationCollectorList.clear();

	ifstream in(logNS::Logger::STOREDDATADIR + filename);
	saveloadNS::CollectorSavings fh(in);
	
	if (!fh.FileIsEmpty)
	{
		vector<saveloadNS::CollectorDataStructure>* LoadedCollectors = fh.getCollectors();

		if (in.is_open())
		{
			//CHIUDO E RIAPRO IL FILE PER RIPOSIZIONARE IL CURSORE A ZERO
			in.close();
			in.open(logNS::Logger::STOREDDATADIR + App::projectDataFileName);

			for (int i = 0; i < LoadedCollectors->size(); i++)
			{

				saveloadNS::CollectorDataStructure collectorData = LoadedCollectors->at(i);

				//carico direttamente i collettori : in base al collectorsID carico un tipo diverso di collettore
				collectorNS::ApplicationObjectCollector* newColl =
					AssetNS::Assets::getNewCollector(collectorData.collectorsID);

				for (int j = 0; j < newColl->getSize(); j++)
				{
					//newColl->collector ritorna in ogni caso il collettore della classe padre ApplicationObjectCollector
					//bisogna fetchare il collettore corretto usando il polimorfismo!
					newColl->setCollectorName(collectorData.collectorsID);
					newColl->canSleep(!collectorData.isOn);
					newColl->getSubObject(j)->setPosition(collectorData.AOobjects[j].AOposition);
					//newColl->getSubObject(j)->AOTrMatrix = collectorData.AOobjects[j].AOTrMatrix;
					newColl->getSubObject(j)->setOrientation(collectorData.AOobjects[j].AOorientation);
					newColl->getSubObject(j)->setColor(collectorData.AOobjects[j].AOcolor);
					newColl->getSubObject(j)->setSize(collectorData.AOobjects[j].AOsize);

				}

				ApplicationCollectorList.push_back(newColl);

			}//for

			initObjectMaps();

			return true;
		}
		else {
			return false;
		}

	}
}




collectorNS::ApplicationObjectCollector * ApplicationObjectManager::getEditableCollector()
{	
	return ApplicationCollectorList[editableObjIndex];
}
std::string ApplicationObjectManager::getEditableObjectName() {
	if (ApplicationCollectorList.size() == 0)
		return "NO OBJECT TO MOVE";
	return ApplicationCollectorList[editableObjIndex]->getCollectorID();
}
void ApplicationObjectManager::nextObject() {
	
	if (editableObjIndex < ApplicationCollectorList.size()-1)
		++editableObjIndex;
	else
		editableObjIndex = 0;

}
void ApplicationObjectManager::prevObject() {
	if (editableObjIndex > 0)
		--editableObjIndex;
	else
		editableObjIndex = ApplicationCollectorList.size()-1;

}


bool ApplicationObjectManager::setEditableObject(const string& s)
{
	std::map< std::string, int>::iterator it = collectorIDMap.find(s);
	if (it == collectorIDMap.end()) return false;
	else
	{
		editableObjIndex = it->second;

		return true;
	}

}







/*funzione che - passato AOobjectName ritorna indice collettore e
indice posizione nel collettore*/
std::pair<int,int> ApplicationObjectManager::getObjectListIndexByAOobjectName(std::string s) {
try {
		return objectListIndexMap.at(s);//usare sempre at per le mappe altrimenti inserisce oggetti non esistenti
	}
	catch (...) {
		logNS::Logger::writeLog("ApplicationObject.h : getObjectListIndex(objName) couldn't find the specified object objName");
		return std::pair<int,int>({ -1,-1 });
	}
}

std::pair<int, int> ApplicationObjectManager::getObjectListIndexByRBobjectID(std::string s) {
	try {
		return objectListRBIDMap.at(s);//usare sempre at per le mappe altrimenti inserisce oggetti non esistenti
	}
	catch (...) {
		logNS::Logger::writeLog("ApplicationObject.h : getObjectListIndex(objName) couldn't find the specified object objName");
		return std::pair<int, int>({ -1,-1 });
	}
}






/*funzione che passato l'ID di un oggetto avente corpo rigido
lo elimina (viene richiamata dall'AI quando è stato eliminato un nemico)*/
void ApplicationObjectManager::kill(const string& RBobjectID)
{
	int collPos = collectorIDMap.at(RBobjectID);
	ApplicationCollectorList.erase(ApplicationCollectorList.begin() + collPos);

}

void ApplicationObjectManager::kill(const collectorNS::ActiveObject* obj){}

collectorNS::ApplicationObjectCollector* 
ApplicationObjectManager::getObjectByRBID(std::string RBobjectID)
{
	pair<int, int> objPos = 
		getObjectListIndexByRBobjectID(RBobjectID);

	if (objPos.first == -1 || objPos.second == -1) return NULL;
			return ApplicationCollectorList[objPos.first];
}

/*this method returns the collector specified via argument by its collectorID*/
collectorNS::ApplicationObjectCollector* ApplicationObjectManager::getObjectByCollectorID(const std::string& collectorID)
{
	std::map< std::string, int>::iterator it = collectorIDMap.find(collectorID);
	if (it != collectorIDMap.end())
		return ApplicationCollectorList[it->second];
	else
		return NULL;
}

std::string ApplicationObjectManager::printEditableObjectInfos()
{
	return ApplicationCollectorList[editableObjIndex]->getInfos();
		
}

void ApplicationObjectManager::initObjectMaps() {
	
	objectListIndexMap.clear();
	objectListRBIDMap.clear();
	collectorIDMap.clear();

	for (int i = 0; i < ApplicationCollectorList.size(); i++)
	{
		for (int j = 0; j < ApplicationCollectorList[i]->getSize(); j++)
		{
			std::string AOobjID = ApplicationCollectorList[i]->getSubObject(j)->AOobjectName;
			std::string RBobjID = ApplicationCollectorList[i]->getSubObject(j)->getRBObjectID();
			
			objectListIndexMap.insert({ AOobjID, std::pair<int, int> { i,j } });
			objectListRBIDMap.insert({ RBobjID, std::pair<int, int> { i,j } });
			
		}

		std::string collID = ApplicationCollectorList[i]->getCollectorID();
		collectorIDMap.insert({ collID,i });
	}
}


void ApplicationObjectManager::save(std::string fileName) {
	
	static std::ofstream out(logNS::Logger::STOREDDATADIR + fileName);

	for (int i = 0; i < ApplicationCollectorList.size(); i++)
		ApplicationCollectorList[i]->OCsave(out);
		
}


void ApplicationObjectManager::initObjectAssetList() {}


void ApplicationObjectManager::createNewObject(int N) {
	
	collectorNS::ApplicationObjectCollector * newcoll = AssetNS::Assets::getNewCollector(N);
	newcoll->OCcreateObject();
	newcoll->OCsetParameters();
	ApplicationCollectorList.push_back(newcoll);
	initObjectMaps();
}

bool ApplicationObjectManager::createNewObject(const string& s) {

	collectorNS::ApplicationObjectCollector * newcoll = AssetNS::Assets::getNewCollector(s);
	if (newcoll == NULL) return false;
	newcoll->OCcreateObject();
	newcoll->OCsetParameters();
	ApplicationCollectorList.push_back(newcoll);
	initObjectMaps();
	return true;
}

void ApplicationObjectManager::deleteObject(const int i) {
	
	if (ApplicationCollectorList.size() > i)
		ApplicationCollectorList.erase(ApplicationCollectorList.begin() + i);

}

bool ApplicationObjectManager::deleteObject(const string& objName) {

	size_t collectorPos;
	std::map< std::string, int>::const_iterator it = collectorIDMap.find(objName);
	if (it != collectorIDMap.end())
	{
		collectorPos = it->second;
		ApplicationCollectorList.erase(ApplicationCollectorList.begin() + collectorPos);
		initObjectMaps();
		return true;
	}
	else
		return false;
		/*ph.mapButtonOnBranch(
			uiNS::UserInterface::getParentButton()->getButtonID(),
			uiNS::UserInterface::getParentButton()->getButtonID(),
			"object does not exist");*/
	
	
}





} // namespace myobjectNS
