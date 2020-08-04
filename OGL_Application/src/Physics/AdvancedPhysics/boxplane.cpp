#include<AdvancedPhysics/collide_fine_advanced.h>


namespace rtcdNS {

	static inline real transformToAxis(
		const CollisionBox &box,
		const Vector3 &axis
	)
	{
		return
			box.halfSize.x * real_abs(axis * box.getAxis(0)) +
			box.halfSize.y * real_abs(axis * box.getAxis(1)) +
			box.halfSize.z * real_abs(axis * box.getAxis(2));
	}


	bool AdvancedIntersectionTest::boxAndFinitePlane(
		const CollisionBox &box,
		const advancedPhysicsNS::CollisionFinitePlane &plane)
	{
		// Work out the projected radius of the box onto the plane direction
		real projectedRadius = transformToAxis(box, plane.normal);

		// Work out how far the box is from the origin
		real boxDistance =
			plane.normal *
			box.getAxis(3) -
			projectedRadius;

		Vector3 bCenter = box.getAxis(3);
		Vector3 pCenter = plane.getAxis(3);
		Vector3 bRelCenter = plane.getTransform().transformInverse(bCenter);

		if (std::fabs(std::fabs(bRelCenter.x) - box.halfSize[0]) > plane.size[0]||
			/*std::fabs(bRelCenter.y - box.halfSize[1]) > plane.size[1]/2 ||*/
			std::fabs(std::fabs(bRelCenter.z) - box.halfSize[2]) > plane.size[2] )
			return false;

		// Check for the intersection
		return boxDistance <= plane.offsetNorm;
	}



	////////////////////////////////////////////

	unsigned AdvancedCollisionDetector::boxAndFinitePlane(
		CollisionBox &box,
		advancedPhysicsNS::CollisionFinitePlane &plane,
		CollisionData *data)
	{
		// Make sure we have contacts
		if (data->contactsLeft <= 0) return 0;

		// Check for intersection
		if (!AdvancedIntersectionTest::boxAndFinitePlane(box, plane))
		{
			return 0;
		}

		// We have an intersection, so find the intersection points. We can make
		// do with only checking vertices. If the box is resting on a plane
		// or on an edge, it will be reported as four or two contact points.

		// Go through each combination of + and - for each half-size
		static real mults[8][3] = { {1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},
								   {1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1} };

		Contact* contact = data->contacts;
		unsigned contactsUsed = 0;
		for (unsigned i = 0; i < 8; i++) 
		{

			// Calculate the position of each vertex
			Vector3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
			vertexPos.componentProductUpdate(box.halfSize);
			vertexPos = box.getTransform().transform(vertexPos);

			// Calculate the distance from the plane
			real vertexDistance = vertexPos * plane.normal;

			// Compare this to the plane's distance
			if (vertexDistance <= plane.offsetNorm)
			{
				// Create the contact data.

				// The contact point is halfway between the vertex and the
				// plane - we multiply the direction by half the separation
				// distance and add the vertex location.
				contact->contactPoint = plane.normal;
				contact->contactPoint *= (vertexDistance - plane.offsetNorm);
				contact->contactPoint += vertexPos;
				contact->contactNormal = plane.normal;
				
				contact->penetration = plane.offsetNorm - vertexDistance;

				// Write the appropriate data
				contact->setBodyData(box.body, plane.body,
					data->friction, data->restitution);

				// Move onto the next contact
				contact++;
				contactsUsed++;
				if (contactsUsed == (unsigned)data->contactsLeft) return contactsUsed;
			}
		}

		data->addContacts(contactsUsed);
		return contactsUsed;
	}



}