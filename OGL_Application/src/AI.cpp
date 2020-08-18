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
	






	/*funzione che imposta la velocità del nemico in modo che segua il main character.
	attenzione : in questa funzione non stiamo aggiornando AOposition ! 
	aggiorniamo direttamente la rigid body position! */
	void myfirstIA::follow(myobjectNS::ApplicationObject* obj, myobjectNS::ApplicationObject* target, const float& distance)
	{
		//if(!AIon || !seekAndDestroy()) return;
		//static float i = 0.0;
		//static const int M = 10;

		///*mymathlibNS::Quaternion orientation;
		//static const mymathlibNS::Quaternion orientation_offset(mymathlibNS::Quaternion::getQuaternionfromYAngle(90.0));
		//orientation = mymathlibNS::Quaternion::getProduct(orientation_offset, pc.getPlayer()->getOrientation());*/

		///*deve guardare nella direzione dell'oggetto seguito 
		//non nella stessa direzione dell'oggetto seguito*/

		///*mymathlibNS::Quaternion moving_offset(mymathlibNS::Quaternion::getQuaternionfromXAngle(i++ / M));
		//orientation = mymathlibNS::Quaternion::getProduct(moving_offset, orientation);
		//obj->setOrientation(orientation);*/

		//std::array<float, 3> targetpos = target->getPosition();

		////prendo la posizione del corpo rigido
		//Vector3  enemypos{ obj->getRB()->position };
		////la uso per settare la posizione AOposition che passerò poi a gun come firespot
		//obj->setPosition(conversionLibNS::conversionLibrary::cycloneVec3TostdArray(enemypos));
		//std::array<float, 3> distance_v
		//{ targetpos[0] - enemypos[0] ,
		//	targetpos[1] - enemypos[1] ,
		//	targetpos[2] - enemypos[2]
		//};

		///*myobjectNS::PrintHelper::mapNewString("IA", "enemy-target distance : " +
		//	logNS::Logger::stdarray3ToString(distance_v));*/
		//
		//	obj->getRB()->velocity =
		//	Vector3(
		//		distance_v[0] / distance,
		//		distance_v[1] / distance,
		//		distance_v[2] / distance);

		//	if (obj->getRB()->velocity == Vector3(0.0, 0.0, 0.0))
		//		;

	}


	const bool& myfirstIA::seekAndDestroy()
	{
		return target->isAlive;
	}


	void myfirstIA::follow(collectorNS::ActiveObject* obj,collectorNS::ActiveObject* target)
	{
		//if (!target) return;
		if (!target||!AIon || !obj->isOn || !UserInterface::AIon) return;

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
		{
			moveRandomly();
		}
	}

	void myfirstIA::moveRandomly()
	{
		if (activityArea == NULL || myobjectNS::Ground::grounds.size() == 0)
		{
			return;
		}

		deltaMovement = nextPosition - currentPosition;

		if (deltaMovement.magnitude() <=20.0)
		{
			nextPosition = conversionLibNS::conversionLibrary::stdArrayToCycloneVec3(activityArea->getRandomPointInSurface(this));
		}
	

		Vector3 vel = deltaMovement;
		vel.normalise();

		vel *= 10;


		myRB->velocity = vel;

	}


	void myfirstIA::moveInsideBoundaries()
	{	
		

		static std::uniform_int_distribution<int> distribution{ -1000, 1000 };
		static auto random = std::bind(distribution, generator);

		if (deltaMovement.magnitude() <= 5)
		{
			randomDestination[0] = random();
			randomDestination[1] = 0.0;
			randomDestination[2] = random();
		
		}

			deltaMovement[0] = randomDestination[0] - currentPosition[0];
			deltaMovement[1] = 0.0;
			deltaMovement[2] = randomDestination[2] - currentPosition[2];

			Vector3 vel = deltaMovement;
			vel.normalise();

			vel *= 50;

			vel.y = myRB->velocity.y;
	

			myRB->velocity = vel;
		
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