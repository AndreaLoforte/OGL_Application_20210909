#include<ground.h>
#include<conversionLIB.h> 
#include<random>
#include<functional>
#include<AI.h>

namespace myobjectNS {

	std::map<string, GroundSurfaceOC*> Ground::groundMap;
	Ground::GroudMapIterator  Ground::groundMapIT;


	GroundSurfaceOC::GroundSurfaceOC(const string& collName):
	ApplicationObjectCollector(collName, ApplicationObjectCollector::collectorCounter++,&ground)
	{
		ground.push_back(&gs);
		//Ground::addSurface(this);
	}

	GroundSurfaceOC::GroundSurfaceOC(const string& collName, const unsigned& collNumber):
		ApplicationObjectCollector(collName, collNumber, &ground)
	{
		ground.push_back(&gs);
		//Ground::addSurface(this);
	}


	GroundSurfaceOC* GroundSurfaceOC::OCgetNewInstance()
	{
		GroundSurfaceOC* coll{ new GroundSurfaceOC("groundSurface") };
		Ground::addSurface(this);
		return coll;

	}

	GroundSurfaceOC* GroundSurfaceOC::OCloadInstance(const unsigned& collNumber)
	{
		GroundSurfaceOC* coll{ new GroundSurfaceOC("groundSurface", collNumber) };
		Ground::addSurface(coll);
		return coll;

	}


	void GroundSurfaceOC::OCcreateObject()
	{
		//Ground::addSurface(this);
		gs.create();
	}



	void Ground::addSurface(GroundSurfaceOC* c)
	{
		groundMap.emplace( c->collectorID, c );
	}


	void Ground::addSurface(myobjectNS::ApplicationObject* ao){}



	vector<string> Ground::getGroundList()
	{
		vector<string> groundList;
		

		for(Ground::groundMapIT = groundMap.begin(); groundMapIT != groundMap.end(); groundMapIT++)
		{
			groundList.push_back(groundMapIT->first);
		}

		return groundList;

	}

	GroundSurfaceOC* Ground::getGround(const string& gID)
	{
		groundMapIT = groundMap.find(gID);
		//const SurfaceBoundaries* sur{ groundMapIT->second };
		if (groundMapIT != groundMap.end())
			return groundMapIT->second;
		else
			return NULL;
	}

}