#include<AdvancedPhysics/advancedCD.h>
#include<AdvancedPhysics/collide_fine_advanced.h>
#include<sound.h>
#include<physics.h>
namespace rtcdNS {

	


	int getDistanceFromFinitePlane(const advancedPhysicsNS::CollisionFinitePlane& plane, const CollisionSphere& sphere);




	unsigned AdvancedCollisionDetector::sphereAndFinitePlane(
		CollisionSphere &sphere,
		advancedPhysicsNS::CollisionFinitePlane &plane,
		CollisionData *data)
	{

		if (data->contactsLeft <= 0) return 0;


		Vector3 sphere_curr_pos = sphere.getAxis(3);// Cache the sphere position
		Vector3 sphere_prev_pos = sphere.getPrevPosition();
		Vector3 sphere_mov = sphere_curr_pos - sphere_prev_pos;
		Vector3 planeNormal = plane.normal;

		float sphere_curr_distance = sphere_curr_pos.scalarProduct(planeNormal) - plane.offsetNorm;///positiva se la sfera sta sopra al piano
		float ABSsphere_new_distance = std::fabs(sphere_curr_distance);


		float sphere_prev_distance = sphere.getPrevPosition().scalarProduct(planeNormal) - plane.offsetNorm;
		float ABSsphere_prev_distance = std::fabs(sphere_prev_distance);

		float sphere_mov_along_plane_normal = sphere_mov.scalarProduct(planeNormal);//spostamento sfera lungo la normale : positivo se concorde, negativo se discorde
		float ABS_sphere_mov_along_plane_normal = std::fabs(sphere_mov_along_plane_normal);
		bool sphereWasAbove, sphereIsAbove, moveTowardsPlane, hasTunneled = false;


		auto lambda_addContact = [&]()
		{
			/*la penetration indica di quanto si sono compenetrati i corpi se non considero la risoluzione*/
			real penetration;
			//penetration dev'essere sempre positivo
			if (hasTunneled)
				penetration = std::fabs(sphere.radius + ABSsphere_new_distance);
			else
				penetration = std::fabs(sphere.radius - ABSsphere_new_distance);

			Contact* contact = data->contacts;
			if (sphereWasAbove)
				contact->contactNormal = planeNormal;
			else
				contact->contactNormal = planeNormal * -1;

			contact->penetration = penetration;
			contact->contactPoint = sphere_curr_pos - plane.normal * sphere_curr_distance;
			contact->setBodyData(sphere.body, plane.body,
				data->friction, data->restitution);

			data->addContacts(1);
			//dal momento che abbiamo individuato un contatto, la curr_position dev'essere corretta alla posizione del contatto
			sphere_curr_pos = contact->contactPoint;

			return 1;

		};

		/*dopo l'urto la posizione della sfera viene settata alla posizione del contatto.
		a tale posizione ovviamente la distanza dal piano è nulla, ma nella computazione si ottiene un piccolo errore che può essere positivo o negativo.
		Se l'errore prende segno opposto a quello della precedente distanza dal piano interpretiamo il cambio di segno della distanza come un tunnel e quindi come collisione.
		Ma in questo caso il cambio di segno è dovuto all'errore, per questo motivo è necessario ammettere un coefficiente epsilon di scostamento dallo zero assoluto
		entro il quale non dichiariamo una nuova collisione.*/
		static const float epsilon = 0.00001;

		if (sphere_curr_distance > 0)
			sphereIsAbove = true;
		else
			sphereIsAbove = false;

		if (sphere_prev_distance > epsilon)
			sphereWasAbove = true;
		if (sphere_prev_distance > -epsilon && sphere_prev_distance < epsilon)
			sphereWasAbove = sphereIsAbove;
		if (sphere_prev_distance < -epsilon)
			sphereWasAbove = false;

		if (sphereIsAbove && !sphereWasAbove || !sphereIsAbove &&sphereWasAbove)
			hasTunneled = true;
		else
			hasTunneled = false;


		if (sphere_mov_along_plane_normal > 0 && sphereWasAbove)
		{
			moveTowardsPlane = false;
			return 0;
		}
		if (sphere_mov_along_plane_normal < 0 && sphereWasAbove == false)
		{
			moveTowardsPlane = false;
			return 0;
		}

		if (sphere_mov_along_plane_normal >= 0 && sphereWasAbove == false)
		{
			moveTowardsPlane = true;
			float t = std::fabs(ABSsphere_prev_distance - sphere.radius) / ABS_sphere_mov_along_plane_normal;
			if (t >= 0 && t <= 1)
			{
				if (getDistanceFromFinitePlane(plane, sphere) == 1)
				{
					lambda_addContact();
					return 1;
				}
				else return 0;


			}
			return 0;
		}
		if (sphere_mov_along_plane_normal < 0 && sphereWasAbove == true)
		{
			moveTowardsPlane = true;
			float t = std::fabs(ABSsphere_prev_distance - sphere.radius) / ABS_sphere_mov_along_plane_normal;
			if (t >= 0 && t <= 1)
			{
				if (getDistanceFromFinitePlane(plane, sphere) == 1)
				{
					lambda_addContact();
					return 1;
				}
				else
					return 0;


			}
			return 0;
		}

	}




	int getDistanceFromFinitePlane(const advancedPhysicsNS::CollisionFinitePlane& plane, const CollisionSphere& sphere)
	{


		Vector3 sphereCentre = sphere.getAxis(3);
		Vector3 planeCentre = plane.offset;

		/*trovo le coordinate della sfera relative al piano trasformato:
		in questo modo potrò considerare il piano come se non fosse stato trasformato.*/
		Vector3 sphereRelCentre = plane.getTransform().transformInverse(sphereCentre);

		if ((std::fabs(sphereRelCentre.x) - sphere.radius <= plane.size[0]) &&
			std::fabs(sphereRelCentre.z) - sphere.radius <= plane.size[2])
			return 1;

		else
			return 0;


	}




	//testing collision of moving sphere with static Infinite plane
	unsigned AdvancedCollisionDetector::sphereAndInfinitePlane(
		CollisionSphere &sphere,
		CollisionPlane &plane,
		CollisionData *data)
	{
		if (data->contactsLeft <= 0) return 0;


		Vector3 sphere_curr_pos = sphere.getAxis(3);// Cache the sphere position
		Vector3 sphere_prev_pos = sphere.getPrevPosition();
		Vector3 sphere_mov = sphere_curr_pos - sphere_prev_pos;
		Vector3 planeNormal = plane.direction;

		float sphere_curr_distance = sphere_curr_pos.scalarProduct(planeNormal) - plane.offset;///positiva se la sfera sta sopra al piano
		float ABSsphere_new_distance = std::fabs(sphere_curr_distance);


		float sphere_prev_distance = sphere.getPrevPosition().scalarProduct(planeNormal) - plane.offset;
		float ABSsphere_prev_distance = std::fabs(sphere_prev_distance);

		float sphere_mov_along_plane_normal = sphere_mov.scalarProduct(planeNormal);//spostamento sfera lungo la normale : positivo se concorde, negativo se discorde
		float ABS_sphere_mov_along_plane_normal = std::fabs(sphere_mov_along_plane_normal);
		bool sphereWasAbove, sphereIsAbove, moveTowardsPlane, hasTunneled = false;


		auto lambda_addContact = [&]()
		{
			real penetration;
			//penetration dev'essere sempre positivo
			if (hasTunneled)
				penetration = std::fabs(sphere.radius + ABSsphere_new_distance);
			else
				penetration = std::fabs(sphere.radius - ABSsphere_new_distance);

			Contact* contact = data->contacts;
			if (sphereWasAbove)
				contact->contactNormal = planeNormal;
			else
				contact->contactNormal = planeNormal * -1;

			contact->penetration = penetration;
			contact->contactPoint = sphere_curr_pos - plane.direction * sphere_curr_distance;
			contact->setBodyData(sphere.body, NULL,
				data->friction, data->restitution);

			data->addContacts(1);

			//dal momento che abbiamo individuato un contatto, la curr_position dev'essere corretta alla posizione del contatto
			sphere_curr_pos = contact->contactPoint;

			return 1;

		};

		/*dopo l'urto la posizione della sfera viene settata alla posizione del contatto.
		a tale posizione ovviamente la distanza dal piano è nulla, ma nella computazione si ottiene un piccolo errore che può essere positivo o negativo.
		Se l'errore prende segno opposto a quello della precedente distanza dal piano interpretiamo il cambio di segno della distanza come un tunnel e quindi come collisione.
		Ma in questo caso il cambio di segno è dovuto all'errore, per questo motivo è necessario ammettere un coefficiente epsilon di scostamento dallo zero assoluto
		entro il quale non dichiariamo una nuova collisione.*/
		static const float epsilon = 0.00001;

		if (sphere_curr_distance > 0)
			sphereIsAbove = true;
		else
			sphereIsAbove = false;

		if (sphere_prev_distance > epsilon)
			sphereWasAbove = true;
		if (sphere_prev_distance > -epsilon && sphere_prev_distance < epsilon)
			sphereWasAbove = sphereIsAbove;
		if (sphere_prev_distance < -epsilon)
			sphereWasAbove = false;

		if (sphereIsAbove && !sphereWasAbove || !sphereIsAbove &&sphereWasAbove)
			hasTunneled = true;
		else
			hasTunneled = false;


		if (sphere_mov_along_plane_normal > 0 && sphereWasAbove)
		{
			moveTowardsPlane = false;
			return 0;
		}
		if (sphere_mov_along_plane_normal < 0 && sphereWasAbove == false)
		{
			moveTowardsPlane = false;
			return 0;
		}

		if (sphere_mov_along_plane_normal >= 0 && sphereWasAbove == false)
		{
			moveTowardsPlane = true;
			float t = std::fabs(ABSsphere_prev_distance - sphere.radius) / ABS_sphere_mov_along_plane_normal;
			if (t >= 0 && t <= 1)
			{
				lambda_addContact();
				return 1;
			}
			return 0;
		}
		if (sphere_mov_along_plane_normal < 0 && sphereWasAbove == true)
		{
			moveTowardsPlane = true;
			float t = std::fabs(ABSsphere_prev_distance - sphere.radius) / ABS_sphere_mov_along_plane_normal;
			if (t >= 0 && t <= 1)
			{
				lambda_addContact();
				return 1;

			}
			return 0;
		}

	}




}