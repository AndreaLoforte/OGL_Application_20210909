#include<AI.h>
#include<playerCharacter.h>
#include<gun.h>
#include<contacts.h>
#include<applicationObjectManager.h>
#include<mymathlib.h>
#include<app.h>
#include<random>
#include<functional>
#include<userInterface.h>
#include<conversionLIB.h>
#include<ground.h>
namespace aiNS {

	
	using namespace textRendererNS;


	myobjectNS::PlayerCharacterOC * AI::target;// = myobjectNS::PlayerCharacterOC::getPlayer()
	printHelperNS::PrintHelper AI::ph{ "AI" };
	





	/*FUNZIONE UTILIZZATA DALLA FUNZIONE moverandomly()*/
	array<float, 3> myfirstIA::getRandomPointInSurface(aiNS::myfirstIA* brain)
	{
		myobjectNS::ApplicationObject* surface = activityArea->getBody();
		array<float, 3> direction_v1{ surface->AOvertices[0][0] - surface->AOposition[0], surface->AOvertices[0][1] - surface->AOposition[1], surface->AOvertices[0][2] - surface->AOposition[2] };
		array<float, 3> direction_v2{ surface->AOvertices[1][0] - surface->AOposition[0], surface->AOvertices[1][1] - surface->AOposition[1], surface->AOvertices[1][2] - surface->AOposition[2] };
		array<float, 3> direction_v3{ surface->AOvertices[2][0] - surface->AOposition[0], surface->AOvertices[2][1] - surface->AOposition[1], surface->AOvertices[2][2] - surface->AOposition[2] };
		array<float, 3> direction_v4{ surface->AOvertices[3][0] - surface->AOposition[0], surface->AOvertices[3][1] - surface->AOposition[1], surface->AOvertices[3][2] - surface->AOposition[2] };


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

		randomPoint = mymathlibNS::stdLibHelper::array3fSum(randomPoint, surface->AOposition);


		return (randomPoint);
	}

	const bool& myfirstIA::seekAndDestroy()
	{
		return target->isAlive;
	}


	void myfirstIA::follow(collectorNS::ActiveObject* obj,collectorNS::ActiveObject* target)
	{
		//if (!target) return;
		bool target_is_set = target;
		if (!target_is_set ||!AIon || !obj->isOn) return;

		std::array<float, 3> targetpos = target->getBody()->getPosition();

		//prendo la posizione del corpo rigido
		currentPosition = myRB->position;
		//la uso per settare la posizione AOposition che passerò poi a gun come firespot
		mybody->setPosition(conversionLibNS::conversionLibrary::cycloneVec3TostdArray(currentPosition));
		std::array<float, 3> distance_v 
		{ 
			targetpos[0] - currentPosition[0] ,
			targetpos[1] - currentPosition[1] ,
			targetpos[2] - currentPosition[2]
		};

		targetDistanceNorm = mymathlibNS::stdLibHelper::norm(distance_v);
		/*if the target is not inside the sight region => move randomly */
		if (!target->isOn || !target->isAlive || targetDistanceNorm > activationDistance)
			moveRandomly();
		/*else move towards the target*/
		else
		{
			Vector3 vel;
			vel.x = distance_v[0];
			/*vel.y = distance_v[1];*/ /*da non modificare per non avere levitazione antigravitazionale*/
			vel.z = distance_v[2];
			vel.normalise();

			vel *= 10;


			myRB->velocity.x = vel.x;
			myRB->velocity.z = vel.z;
		}

	}

	void myfirstIA::moveRandomly()
	{
		if (activityArea == NULL || myobjectNS::Ground::groundMap.size() == 0)
		{
			return;
		}

		deltaMovement = nextPosition - currentPosition;

		if (deltaMovement.magnitude() <=20.0)
		{
			nextPosition = conversionLibNS::conversionLibrary::stdArrayToCycloneVec3(getRandomPointInSurface(this));
		}
	

		Vector3 vel = deltaMovement;
		vel.normalise();

		vel *= 10;


		myRB->velocity = vel;

	}



	void myfirstIA::moveInsideBoundaries()
	{
		


	}









	void myfirstIA::setTarget(collectorNS::ActiveObject* t) 
	{ 
		target = dynamic_cast<myobjectNS::PlayerCharacterOC*>(t); 
		AIon = true;

		
		
	}


	void myfirstIA::update()
	{
		seekAndDest = target->isAlive;	
	}

	void myfirstIA::shoot(
		const std::array<float, 3>& mypos, 
		const std::array<float, 3>& targetpos, 
		const unsigned& repFreq,
		myobjectNS::OCGun& gun) 
	{
		/*if (!AIon ) return;

		static int i = 0;

		if (++i >= 1000/repFreq)
		{
			gun.shootAt(mypos, targetpos);
			i = 0;
		}*/
	}


	void myfirstIA::shoot(
		collectorNS::ActiveObject* obj,
		collectorNS::ActiveObject* target,
		const unsigned& repFreq,
		myobjectNS::OCGun& gun)
	{
		if (!AIon || !obj->isOn || !target->isOn || !target->isAlive || !UserInterface::AIon) return;

		if (targetDistanceNorm > activationDistance)
			return;

		if (++gunTimer >= gunRepFreq / repFreq)
		{
			std::array<float, 3> targetPos = target->getBody()->getPosition();
			std::array<float, 3> error{ rand() % 10, rand() % 10, rand() % 10 };
			std::array<float, 3>
				targetPosWithError{
				targetPos[0] + error[0],
				targetPos[1] + error[1],
				targetPos[2] + error[2] };

			gun.shootAt(obj->getBody()->getPosition(), targetPosWithError);
			gunTimer = 0;
			gunRepFreq = rand() % 2000;
		}


	}


	/*funzionce che aggiorna lo stato di salute del nemico se viene colpito da un proiettile*/
	void AI::updateHealt(const Contact* contactArray, const unsigned& contactCounter)
	{
		using namespace myobjectNS;
		

		for (int i = 0; i < myphysicsNS::CollisorePolimorfo::frameContactCounter; i++)
		{
			Contact contact = contactArray[i];

			size_t obj_index;

			auto lambda_updateEnemyHealt = [&]
			{
				collectorNS::ActiveObject * obj = 
					static_cast<collectorNS::ActiveObject*>
					(ApplicationObjectManager::getObjectByRBID(contact.body[obj_index]->RBobjectID));

				if(!obj->damage())
				{
					ApplicationObjectManager::kill(obj->collectorID);
					ph.eraseButtonByID(obj->collectorID);
					return;
				}

				ph.mapNewString(obj->collectorID, obj->collectorID + "  healt : " + std::to_string(obj->getHealt()));
				return;
			};


			if (contact.body[0]->RBobjectName == "enemy" && contact.body[1]->RBobjectName == "projectile")
			{
				obj_index = 0;
				lambda_updateEnemyHealt();
			}
			if (contact.body[0]->RBobjectName == "projectile" && contact.body[1]->RBobjectName == "enemy")
			{
				obj_index = 1;
				lambda_updateEnemyHealt();
			}
			if (contact.body[0]->RBobjectName == "playercharacter" && contact.body[1]->RBobjectName == "projectile")
			{
				obj_index = 0;
				lambda_updateEnemyHealt();
			
			}
			if (contact.body[0]->RBobjectName == "projectile" && contact.body[1]->RBobjectName == "playercharacter")
			{
				obj_index = 1;
				lambda_updateEnemyHealt();
			
			}

		}




	}

}