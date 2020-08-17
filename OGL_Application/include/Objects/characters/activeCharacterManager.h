#pragma once
#include<vector>
#include<activeobjectCollector.h>

using namespace std;

namespace activeObjectManagerNS
{

	class ActiveCharacterManager
	{
	public:
		static vector<collectorNS::ActiveObject*> list;

		static void add(collectorNS::ActiveObject* p);
		static vector<string> getACID();


	};




}