#include<AdvancedPhysics/collide_fine_advanced.h>


namespace rtcdNS {




	unsigned AdvancedCollisionDetector::sphereAndSphere(
		const CollisionSphere &one,
		const CollisionSphere &two,
		CollisionData *data
	)
	{
		
		

		// Make sure we have contacts
		if (data->contactsLeft <= 0) return 0;

		Vector3 s1pos = one.getAxis(3), s2pos = two.getAxis(3);
		Vector3 s2prevpos = two.getPrevPosition(), s1prevpos = one.getPrevPosition();
		Vector3 s2mov = s2pos - s2prevpos, s1mov = s1pos - s1prevpos;
		float t;


		if (AdvancedIntersectionTest::TestMovingSphereSphere(one, two, s1pos, s2pos, s1prevpos, s2prevpos, s1mov, s2mov, t) == 1)
		{
			// We manually create the normal, because we have the
			// size to hand.
			
			Vector3 s1coll_pos = s1prevpos + s1mov * t;
			Vector3 s2coll_pos = s2prevpos + s2mov * t;

			/*distanza all'istante della collisione dovrebbe essere pari
			alla somma dei due raggi*/
			Vector3 s1s2CenterDistance = s2coll_pos - s1coll_pos;
			/*lo spostamento residuo dopo la collisione per determinare la penetrazione*/
			Vector3 s1mov2 = s1pos - s1coll_pos, s2mov2 = s2pos - s2coll_pos;
			/*spostamento relativo di s2 rispetto a s1 dopo la collisione*/
			Vector3 s2relmov = s2mov2-  s1mov2  ;
			/*normale di contatto va da s1 a s2*/
			Vector3 normal = s1s2CenterDistance*-1;
			normal.normalise();

			Contact* contact = data->contacts;
			contact->contactNormal = normal;
			contact->contactPoint = s1coll_pos + normal * one.radius;
			/*penetrazione totale = 
			penetrazione data dal movimento di s1 + 
			penetrazione data dal movimento di s2 */
			contact->penetration = s2relmov.scalarProduct(normal);
			contact->setBodyData(one.body, two.body,
				data->friction, data->restitution);

			data->addContacts(1);
			return 1;
		}
	}

	unsigned AdvancedIntersectionTest::TestMovingSphereSphere(
		const CollisionSphere &s0,
		const CollisionSphere &s1,
		const Vector3& Pos0,
		const Vector3& Pos1,
		const Vector3& prevPos0,
		const Vector3& prevPos1,
		const Vector3& v0,
		const Vector3& v1,
		float &collisionTime)
	{

		/*
		-le posizioni attuali delle sfere sono interpretate come posizioni future
		(infatti qui siamo dopo l'integrazione, ma prima del rendering quindi
		questa posizione è "tentativa" e sarà corretta nel contact resolution
		se viene individuata una collisione	durante il movimento.
		-Le posizioni precedenti sono pensate come attuali.
		-Le differenze tra posizioni attuali e precedenti dà il movimento
		delle sfere in questo frame : bisogna verificare che i movimenti
		non si intersechino*/

		Vector3 currentSpheresCenterDistance = Pos1 - Pos0;
		Vector3 prevSpheresCentersdistance = prevPos1 - prevPos0; // Vector between sphere centers
		Vector3 v = v1 - v0; // Relative motion of s1 with respect to stationary s0
		float r = s1.radius + s0.radius; // Sum of sphere radii
		float CurrentSpaceBetweenSpheres = prevSpheresCentersdistance.scalarProduct(currentSpheresCenterDistance) - r * r;
		float prevSpaceBetweenSpheres = prevSpheresCentersdistance.scalarProduct(prevSpheresCentersdistance) - r * r;
		
		if (prevSpaceBetweenSpheres < 0.0f) {
			// Spheres initially overlapping so exit directly
			collisionTime = 0.0f;
			return 1;
		}

		/*a : modulo quadro del moto relativo tra le sfere*/
		float a = v.scalarProduct(v);
		static constexpr float EPSILON = 0.00001;

		/* il moto relativo è nullo => le sfere sono ferme rispetto l'una rispetto all'altra*/
		if (a < EPSILON) return 0;

		/*le sfere sono in avvicinamento solo se
		il verso dello spostamento di 1 rispetto a 0
		è opposto alla distanza di 1 rispetto a 2*/
		float b = v.scalarProduct(prevSpheresCentersdistance);
		if (b >= 0.0f) return 0;

		/*calcolo il delta dell'equazionone di intersezione delle sfere*/
		float d = b * b - a * prevSpaceBetweenSpheres;
		if (d < 0.0f) return 0; // No real-valued root, spheres do not intersect
		collisionTime = (-b - std::sqrt(d)) / a;
		if (collisionTime <= 1)
			return 1;
		else
			return 0;


	}



}