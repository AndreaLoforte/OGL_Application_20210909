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

namespace myobjectNS
{



	void ApplicationObjectManager::save(std::string fileName) {

		static std::ofstream out(logNS::Logger::STOREDDATADIR + fileName);
		static string s = logNS::Logger::STOREDDATADIR + fileName;

		for (int i = 0; i < ApplicationCollectorList.size(); i++)
			//ApplicationCollectorList[i]->OCsave(out);
			ApplicationCollectorList[i]->OCsave(s);

	}




	bool ApplicationObjectManager::loadActiveObjects(string filename) {

		//ApplicationCollectorList.clear();

		filename += "ActiveObject";
		ifstream in(logNS::Logger::STOREDDATADIR + filename);
		saveloadNS::ActiveObjectLoader fh(in);

		if (!fh.FileIsEmpty)
		{
			vector<saveloadNS::ActiveObjectDataStructure>* LoadedCollectors = fh.getCollectors();

			if (in.is_open())
			{
				//CHIUDO E RIAPRO IL FILE PER RIPOSIZIONARE IL CURSORE A ZERO
				in.close();
				in.open(logNS::Logger::STOREDDATADIR + App::projectDataFileName);

				for (int i = 0; i < LoadedCollectors->size(); i++)
				{

					saveloadNS::ActiveObjectDataStructure collectorData = LoadedCollectors->at(i);

					//carico direttamente i collettori : in base al collectorsID carico un tipo diverso di collettore
					collectorNS::ActiveObject* newColl = static_cast<collectorNS::ActiveObject*>
						(AssetNS::Assets::getNewCollector(collectorData.collectorsID));

					for (int j = 0; j < newColl->getSize(); j++)
					{
						//newColl->collector ritorna in ogni caso il collettore della classe padre ApplicationObjectCollector
						//bisogna fetchare il collettore corretto usando il polimorfismo!
						newColl->setActivityGround(collectorData.activityGroundID);
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




	bool ApplicationObjectManager::loadCollectors(string filename) {

		ApplicationCollectorList.clear();

		ifstream in(logNS::Logger::STOREDDATADIR + filename);
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