#pragma once
#include<vector>
#include<activeobjectCollector.h>
#include<activeObjectManager.h>
#include<map>
using namespace std;

namespace activeObjectManagerNS
{


	class ActiveObjectManager
	{
	public:
		static vector<collectorNS::ActiveObjectCollector*> activeObjectlist;

		static void add(collectorNS::ActiveObjectCollector* p);
		static vector<string> getACID();
		static bool loadActiveObjects(string filename);
		static bool del(collectorNS::ActiveObjectCollector*);
	};




}