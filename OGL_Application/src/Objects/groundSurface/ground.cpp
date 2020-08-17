#include<ground.h>
#include<conversionLIB.h> 
#include<random>
#include<functional>
#include<AI.h>

namespace myobjectNS {

	std::vector<SurfaceBoundaries> Ground::grounds;
	std::map<string, SurfaceBoundaries*> Ground::groundMap;
	Ground::GroudMapIterator  Ground::groundMapIT;

	void SurfaceBoundaries::boundaryLinesEq()
	{}


	array<float, 3> SurfaceBoundaries::getRandomPointInSurface(aiNS::myfirstIA* brain)
	{
		
		array<float, 3> direction_v1{ p->AOvertices[0][0] - p->AOposition[0],p->AOvertices[0][1] - p->AOposition[1], p->AOvertices[0][2] - p->AOposition[2] };
		array<float, 3> direction_v2{ p->AOvertices[1][0] - p->AOposition[0], p->AOvertices[1][1] - p->AOposition[1], p->AOvertices[1][2] - p->AOposition[2] };
		array<float, 3> direction_v3{ p->AOvertices[2][0] - p->AOposition[0], p->AOvertices[2][1] - p->AOposition[1], p->AOvertices[2][2] - p->AOposition[2] };
		array<float, 3> direction_v4{ p->AOvertices[3][0] - p->AOposition[0], p->AOvertices[3][1] - p->AOposition[1], p->AOvertices[3][2] - p->AOposition[2] };


		float a = brain->random(), b = brain->random(), c = brain->random(), d = brain->random();

		float total_norm = std::abs(a) + std::abs(b) + std::abs(c) + std::abs(d);
		float c1 = a / total_norm, c2 = b / total_norm, c3 = c / total_norm, c4 = d / total_norm;

		direction_v1 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v1, c1);
		direction_v2 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v2, c2);
		direction_v3 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v3, c3);
		direction_v4 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v4, c4);


		std::array<float, 3> randomPoint;

		randomPoint = mymathlibNS::stdLibHelper::array3fSum(direction_v1, direction_v2);
		randomPoint = mymathlibNS::stdLibHelper::array3fSum(randomPoint, direction_v3);
		randomPoint = mymathlibNS::stdLibHelper::array3fSum(randomPoint, direction_v4);

		randomPoint = mymathlibNS::stdLibHelper::array3fSum(randomPoint, p->AOposition);


		return (randomPoint);
	}



	void Ground::addSurface(collectorNS::ApplicationObjectCollector* c)
	{

	/*	vector<float> size = c->getBody()->AOsize;
		array<float, 3> pos = c->getBody()->AOposition;

		SurfaceBoundaries *s = new SurfaceBoundaries(c->getBody());


		grounds.push_back(*s);*/
	}


	void Ground::addSurface(myobjectNS::ApplicationObject* ao)
	{

		vector<float> size = ao->AOsize;
		array<float, 3> pos = ao->AOposition;

		SurfaceBoundaries* s = new SurfaceBoundaries(ao);


		grounds.push_back(*s);
		groundMap.emplace(ao->getRBObjectID(), s);
	}



	vector<string> Ground::getGroundList()
	{
		vector<string> groundList;

		for (int i = 0; i < grounds.size(); i++)
		{
			groundList.push_back(grounds[i].p->getRBObjectID());
		}

		return groundList;

	}

	SurfaceBoundaries* Ground::getGround(const string& gID)
	{
		groundMapIT = groundMap.find(gID);
		//const SurfaceBoundaries* sur{ groundMapIT->second };
		if (groundMapIT != groundMap.end())
			return groundMapIT->second;
		else
			return NULL;
	}

}