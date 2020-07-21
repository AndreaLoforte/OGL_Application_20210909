#ifndef RTCD_ADVANCEDCD_H
#define RTCD_ADVANCEDCD_H
#include<core.h>

namespace advancedPhysicsNS {
	class CollisionFinitePlane;
}
class CollisionPlane;
class CollisionSphere;
class CollisionBox;
class CollisionData;

typedef Vector3 Point;

namespace rtcdNS {

	

	class AdvancedCollisionDetector {
	public:
		unsigned sphereAndInfinitePlane(
			CollisionSphere &sphere,
			CollisionPlane &plane,
			CollisionData *data);

		unsigned sphereAndFinitePlane(
			CollisionSphere &sphere,
			advancedPhysicsNS::CollisionFinitePlane &plane,
			CollisionData *data);

		unsigned boxAndFinitePlane(
			CollisionBox &box,
			advancedPhysicsNS::CollisionFinitePlane &plane,
			CollisionData *data);

		unsigned sphereAndSphere(
			const CollisionSphere &one,
			const CollisionSphere &two,
			CollisionData *data	);

		unsigned BoxAndSphere(
			const CollisionBox &one,
			const CollisionSphere &two,
			CollisionData *data);

		
	



	};


	class AdvancedIntersectionTest {

	public:
		static bool boxAndFinitePlane(
			const CollisionBox &box,
			const advancedPhysicsNS::CollisionFinitePlane &plane);

		/*test di intersezione richiamato da sphereAndSphere*/
		static unsigned TestMovingSphereSphere(
			const CollisionSphere &s0,
			const CollisionSphere &s1,
			const Vector3&,
			const Vector3&,
			const Vector3&,
			const Vector3&,
			const Vector3&,
			const Vector3&,
			float &collisionTime);

	/*	int IntersectMovingSphereAABB(
			CollisionSphere s,
			Vector3 sphereRelmov,
			AABB b, float &t);

		int IntersectRayAABB(
			Vector3 spherecenter,
			Vector3 sphererelmov,
			AABB a, float &tmin,
			Vector3 &q);*/

	};



}

#endif
