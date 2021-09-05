#pragma once
#include<fstream>
#include<string>
#include<vector>
#include<set>
using namespace  std;
namespace saveloadNS {

	class dataSaver
	{
	public:
		static set<ofstream*> ofstreamList;
	
		unsigned savingSessionID;
		static bool sessionWasClosed;
		
		void clearFile(const string& filefullpath);

		static void openSavingSession()
		{
			for (set<ofstream*>::iterator it = ofstreamList.begin();
				it != ofstreamList.end();
				it++)
			{
				if(*it)
					(*it)->clear();
			}

		}

		static void closeSavingSession()
		{
			for (set<ofstream*>::iterator it = ofstreamList.begin();
				it != ofstreamList.end();
				it++)
			{
				(*it)->close();
			}
				
		}

		
	};

}