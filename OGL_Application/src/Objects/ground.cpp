#include<ground.h>
#include<conversionLIB.h> 
#include<random>
#include<functional>
#include<AI.h>

namespace myobjectNS {

	std::vector<SurfaceBoundaries> Ground::grounds;

	void SurfaceBoundaries::boundaryLinesEq()
	{}


	array<float, 3> SurfaceBoundaries::getRandomPointInSurface(aiNS::myfirstIA* brain)
	{
	
		array<float, 3> direction_v1{ p->AOvertices[0][0] - p->AOposition[0],p->AOvertices[0][1] - p->AOposition[1], p->AOvertices[0][2] - p->AOposition[2] };
		array<float, 3> direction_v2{ p->AOvertices[1][0]- p->AOposition[0], p->AOvertices[1][1] - p->AOposition[1], p->AOvertices[1][2] - p->AOposition[2] };
		array<float, 3> direction_v3{ p->AOvertices[2][0]- p->AOposition[0], p->AOvertices[2][1] - p->AOposition[1], p->AOvertices[2][2] - p->AOposition[2] };
		array<float, 3> direction_v4{ p->AOvertices[3][0]- p->AOposition[0], p->AOvertices[3][1] - p->AOposition[1], p->AOvertices[3][2] - p->AOposition[2] };

		
		float a = brain->random(), b = brain->random(), c = brain->random(), d = brain->random();

		float total_norm = std::abs(a) + std::abs(b) + std::abs(c) + std::abs(d);
		float c1 = a / total_norm, c2 = b / total_norm, c3 = c / total_norm, c4 = d / total_norm;

		direction_v1 =  mymathlibNS::stdLibHelper::array3fProd1s(direction_v1,c1);
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
		
		vector<float> size = c->getBody()->AOsize;
		array<float, 3> pos = c->getBody()->AOposition;

		SurfaceBoundaries s(c->getBody());
		

		grounds.push_back(s);
	}


	void Ground::checkWithBoundaries(Vector3& pos, Vector3& vel)
	{
		/*Vector3 movement = pos + vel;
		if (grounds.size() == 0) return;
		if (movement.x > grounds[0].vertices[0].x || movement.x < grounds[0].vertices[3].x)
			vel.x = 0;
		if (movement.y > grounds[0].vertices[0].z || movement.y < grounds[0].vertices[3].z)
			vel.z = 0;*/

	}



}