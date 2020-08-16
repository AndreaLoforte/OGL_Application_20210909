#pragma once

#include<array>
#include<vector>
#include<applicationObjectManager.h>
#include<userInterface.h>
#include<core.h>


namespace aiNS {
	class myfirstIA;
}


namespace myobjectNS {


	struct Vertex {

		Vertex(const float& xx,const float& yy, const float& zz):x(xx),y(yy),z(zz){}
		float x;
		float y;
		float z;

		Vertex operator-(Vertex& v)
		{
			Vertex result{ x - v.x,y - v.y,z - v.z };
			return result;
		}
	};


	struct SurfaceBoundaries
	{
		myobjectNS::ApplicationObject* p;
		SurfaceBoundaries(myobjectNS::ApplicationObject * p_):p(p_){}
		array<float, 3> size;

		void boundaryLinesEq();

		array<float, 3> getRandomPointInSurface(aiNS::myfirstIA* brain);
		

	};


	class Ground {
		
		
	public:
		/*each vector contains boundaries for a polygonal surface (since we allows storage for n (non fixed) vertices of
		a polygonal surface, we use a vector of a vector of an array instead of a vector of array of array)*/
		/*boundaries[i] : i-th surface boundaries
		boundaries[i][j] : j-th vertex of i-th surface
		boundaries[i][j][k] : k-th component of j-th vertex of i-th surface*/
		static std::vector<SurfaceBoundaries> grounds;



		static void addBoundaries(std::vector<std::array<float, 3>> surf_vertices){}
		
		static void addSurface(collectorNS::ApplicationObjectCollector* c);


		static void checkWithBoundaries(Vector3& pos,Vector3& vel);

	};



}