#include <applicationObjectManager.h>
#include<vmath.h>
#include<printHelper.h>
#include<app.h>
#include<physics.h>
#include<assets.h>
#include<extern_definitions.h>
#include<gun.h>
#include<activeobjectloader.h>
#include<collectorLoader.h>
#include<set>
#include<fstream>
using namespace std;

namespace myobjectNS
{



	void ApplicationObjectManager::save(std::string projectName) {

		for (int i = 0; i < ApplicationCollectorList.size(); i++)
			ApplicationCollectorList[i]->OCsave(logNS::Logger::PROJECTDIR);

		
	}




	bool ApplicationObjectManager::loadActiveObjects(string filename) {

		string savings = logNS::Logger::PROJECTDIR + saveloadNS::ACTIVEOBJECTSAVINGFILE;
		ifstream in(savings);
		saveloadNS::ActiveObjectLoader fh(in);

		if (!fh.FileIsEmpty)
		{
			vector<saveloadNS::ActiveObjectDataStructure>* LoadedCollectors = fh.getCollectors();

			if (in.is_open())
			{
				//CHIUDO E RIAPRO IL FILE PER RIPOSIZIONARE IL CURSORE A ZERO
				in.close();
				in.open(savings);

				for (int i = 0; i < LoadedCollectors->size(); i++)
				{

					saveloadNS::ActiveObjectDataStructure collectorData = LoadedCollectors->at(i);

					//carico direttamente i collettori : in base al collectorsID carico un tipo diverso di collettore
					collectorNS::ActiveObject* newColl = static_cast<collectorNS::ActiveObject*>
						(AssetNS::Assets::getNewCollector(collectorData.collectorName));

					for (int j = 0; j < newColl->getSize(); j++)
					{
						//newColl->collector ritorna in ogni caso il collettore della classe padre ApplicationObjectCollector
						//bisogna fetchare il collettore corretto usando il polimorfismo!
						newColl->setActivityGround(collectorData.activityGroundID);
						newColl->setCollectorName(collectorData.collectorName);
						newColl->setCollectorNumber(collectorData.collectorNumber);
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




	bool ApplicationObjectManager::loadCollectors(string projectName) {

		ApplicationCollectorList.clear();

		ifstream in(logNS::Logger::PROJECTDIR + saveloadNS::COLLECTORSAVINGFILE);
		saveloadNS::CollectorLoader fh(in);

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
						AssetNS::Assets::getNewCollector(collectorData.collectorsName);

					for (int j = 0; j < newColl->getSize(); j++)
					{
						//newColl->collector ritorna in ogni caso il collettore della classe padre ApplicationObjectCollector
						//bisogna fetchare il collettore corretto usando il polimorfismo!
						newColl->setCollectorID(collectorData.collectorsName,collectorData.collectorNumber);
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





}