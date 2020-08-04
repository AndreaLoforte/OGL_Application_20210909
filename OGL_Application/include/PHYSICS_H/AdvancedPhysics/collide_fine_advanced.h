#ifndef COLLIDEFINEADVANCED_H
#define COLLIDEFINEADVANCED_H
#include<collide_fine.h>

namespace advancedPhysicsNS {


	/*Implementazione di piano di dimenzioni finite.
	Questo piano è CollisionPrimitive*/
	class CollisionFinitePlane : public CollisionPrimitive
	{

	public:
		CollisionFinitePlane() = delete;
		CollisionFinitePlane(std::string s,size_t L1, size_t L2, size_t L3) :CollisionPrimitive(s)
		{
			size[0] = L1;
			size[1] = L2;
			size[2] = L3;
		}

		Vector3 normal;

		/**
		 * The distance of the plane from the origin.
		 */
		real offsetNorm;
		Vector3 offset;

		std::array<float, 3> size;
	};


	class CollisionAABB : public CollisionPrimitive
	{
	public:
		CollisionAABB(const std::string& s, const float& L1, const float& L2, const float& L3) :CollisionPrimitive(s)
		{
			halfSize[0] = L1;
			halfSize[1] = L2;
			halfSize[2] = L3;
		}
		/**
		 * Holds the half-sizes of the box along each of its local axes.
		 */
		Vector3 halfSize;
		Vector3 min, max;
	};


}





#endif