#include<activeCharacterManager.h>

namespace activeObjectManagerNS
{

	vector<collectorNS::ActiveObject*>  ActiveCharacterManager::list;

	void ActiveCharacterManager::add(collectorNS::ActiveObject* p)
	{
		list.push_back(p);
	}

	vector<string> ActiveCharacterManager::getACID()
	{
		vector<string> acnames;

		for (int i = 0; i < list.size(); i++)
			acnames.push_back(list[i]->collectorID);


		return acnames;
	}




}