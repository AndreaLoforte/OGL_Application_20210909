#include<activeObjectmanager.h>
#include<log.h>
#include<activeObjectLoader.h>
#include<assets.h>
#include<applicationObjectManager.h>
#include<userInterface.h>

using namespace myobjectNS;

namespace activeObjectManagerNS
{

	vector<collectorNS::ActiveObject*>  ActiveObjectManager::activeObjectlist;

	void ActiveObjectManager::add(collectorNS::ActiveObject* p)
	{
		activeObjectlist.push_back(p);
	}

	vector<string> ActiveObjectManager::getACID()
	{
		vector<string> acnames;

		for (int i = 0; i < activeObjectlist.size(); i++)
			acnames.push_back(activeObjectlist[i]->collectorID);


		return acnames;
	}


	bool ActiveObjectManager::del(collectorNS::ActiveObject* p)
	{
		vector<collectorNS::ActiveObject*>::iterator it;
		for (it = activeObjectlist.begin(); it != activeObjectlist.end(); it++)
			if ((*it)->collectorID == p->collectorID)
			{

				(*it)->Pcontainer->clear();
				activeObjectlist.erase(it);
				return true;
			}
		return false;
				
	}



	bool ActiveObjectManager::loadActiveObjects(string filename) {

		string savings = logNS::Logger::PROJECTDIR + saveloadNS::ACTIVEOBJECTSAVINGFILE;
		ifstream in(savings);
		saveloadNS::ActiveObjectLoader fh(in);

		try {
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
						collectorNS::ActiveObject* newColl =
							(AssetNS::Assets::loadActiveObject(collectorData.collectorName, collectorData.collectorNumber));

						add(newColl);

						newColl->setActivityGround(collectorData.activityGroundID);

						for (int j = 0; j < newColl->getSize(); j++)
						{
							newColl->canSleep(!collectorData.isOn);
							newColl->getSubObject(j)->setPosition(collectorData.AOobjects[j].AOposition);
							newColl->getSubObject(j)->setOrientation(collectorData.AOobjects[j].AOorientation);
							newColl->getSubObject(j)->setColor(collectorData.AOobjects[j].AOcolor);
							newColl->getSubObject(j)->setSize(collectorData.AOobjects[j].AOsize);

						}

						ApplicationObjectManager::ApplicationCollectorList.push_back(newColl);
						
						
					}//for

					ApplicationObjectManager::initObjectMaps();

					return true;
				}
				else {
					return false;
				}

			}
		}
		catch (const std::exception& ex) {
			
			printHelperNS::PrintHelper ph("activeObjectManager", 0.5, 0.5);
			ph.mapNewString("LOADWARNING", "FAILED TO LOAD DEFAULT PROJECT");
			return false;
		}
	}





}