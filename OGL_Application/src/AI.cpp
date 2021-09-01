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
		/*i vettori direction_vi sono i vettori dal centro della superficie ai suoi vertici*/
		myobjectNS::ApplicationObject* surface = activityArea->getBody();
		array<float, 3> direction_v1{ surface->AOvertices[0][0] - surface->AOposition[0], surface->AOvertices[0][1] - surface->AOposition[1], surface->AOvertices[0][2] - surface->AOposition[2] };
		array<float, 3> direction_v2{ surface->AOvertices[1][0] - surface->AOposition[0], surface->AOvertices[1][1] - surface->AOposition[1], surface->AOvertices[1][2] - surface->AOposition[2] };
		array<float, 3> direction_v3{ surface->AOvertices[2][0] - surface->AOposition[0], surface->AOvertices[2][1] - surface->AOposition[1], surface->AOvertices[2][2] - surface->AOposition[2] };
		array<float, 3> direction_v4{ surface->AOvertices[3][0] - surface->AOposition[0], surface->AOvertices[3][1] - surface->AOposition[1], surface->AOvertices[3][2] - surface->AOposition[2] };


		float a = brain->random(), b = brain->random(), c = brain->random(), d = brain->random();

		float total_norm = std::abs(a) + std::abs(b) + std::abs(c) + std::abs(d);
		float c1 = a / total_norm, c2 = b / total_norm, c3 = c / total_norm, c4 = d / total_norm;

		/*moltiplico ognuno dei vettori direction_vi per un diverso scalare generato casualmente e contenuto tra zero ed */
		direction_v1 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v1, c1);
		direction_v2 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v2, c2);
		direction_v3 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v3, c3);
		direction_v4 = mymathlibNS::stdLibHelper::array3fProd1s(direction_v4, c4);


		std::array<float, 3> randomPoint;

		/*sommando ognuno dei vettori direction_vi ottengo un vettore direzione casuale 
		ma contenuto nella superficie di movimento del corpo*/
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


	void myfirstIA::follow(collectorNS::ActiveObjectCollector* obj,collectorNS::ActiveObjectCollector* target)
	{
		//if (!target) return;
		bool target_is_set = target;
		if (!target_is_set ||!AIon || !obj->isOn) return;

		//currentPosition è la posizione di enemy
		currentPosition = myRB->position;
		//la uso per settare la posizione AOposition che passerò poi a gun come firespot
		mybody->setPosition(conversionLibNS::conversionLibrary::cycloneVec3TostdArray(currentPosition));


		/*il target è il player*/
		std::array<float, 3> targetpos = target->getBody()->getPosition();

		/*se il target(player) si trova fuori dal perimetro della superficie di pertinenza di enemy,
		tronco le coorinate eccedenti in modo da non andare oltre questo perimetro*/
		moveInsideBoundaries(targetpos);

		/*calcolo il vettore distanza tra la posizione corrente di enemy e la posizione del target( il player)*/
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



	void myfirstIA::moveInsideBoundaries(array<float, 3>& targetPos)
	{
		myobjectNS::ApplicationObject* surface = activityArea->getBody();

		/*inverto la matrice di trasformazione del piano*/
		vmath::mat4 inverse_groundSurfaceTransf_matrix = mymathlibNS::inverseMatrix(activityArea->getBody()->AOTrMatrix);
		/*inverto la trasformazione del piano*/
		vector<array<float, 3>> untrasformed_plane_vertices = mymathlibNS::vmatMatrix::getProduct(surface->AOvertices, inverse_groundSurfaceTransf_matrix);

		/*prendo la posizione target di enemy e gli applico l'antitrasformata così come l'ho applicata sulla superficiee*/
		vector<array<float, 3>> untrasformed_target_pos{ targetPos };
		untrasformed_target_pos = mymathlibNS::vmatMatrix::getProduct(untrasformed_target_pos, inverse_groundSurfaceTransf_matrix);

		/*implementare metodo per verificare che il corpo di enemy */
		/*adesso il piano (rettangolare!) è disposto in modo simmetrico rispetto all'origine
		pertanto posso prendere i valori minimi e massimi delle coordinate dei vertici e confrontarle
		con le coordinate della posizione di enemy*/

		/*trovo coordinate x e z minime*/
		float x_min = min(untrasformed_plane_vertices[0][0], untrasformed_plane_vertices[1][0]);
		x_min = min(x_min, untrasformed_plane_vertices[2][0]);

		float z_min = min(untrasformed_plane_vertices[0][2], untrasformed_plane_vertices[1][2]);
		z_min = min(z_min, untrasformed_plane_vertices[2][2]);

		/*trovo coordinate x e z massime*/
		float x_max = max(untrasformed_plane_vertices[0][0], untrasformed_plane_vertices[1][0]);
		x_max = max(x_max, untrasformed_plane_vertices[2][0]);

		float z_max = max(untrasformed_plane_vertices[0][2], untrasformed_plane_vertices[1][2]);
		z_max = max(z_max, untrasformed_plane_vertices[2][2]);

		/*verifico che la target position di enemy body sia contenuto entro le coordinate min e max*/
		/*se una delle coordinate della target position di enemy è all'esterno della regione contenuta dalle coordinate min e max,
		la sovrascrivo in modo da essere esasttamente uguale alla coordinata min/max consentita */

		if (untrasformed_target_pos.at(0)[0] < x_min) untrasformed_target_pos.at(0)[0] = x_min;
		if (untrasformed_target_pos.at(0)[0] > x_max) untrasformed_target_pos.at(0)[0] = x_max;
		if (untrasformed_target_pos.at(0)[2] < z_min) untrasformed_target_pos.at(0)[2] = z_min;
		if (untrasformed_target_pos.at(0)[2] > z_max) untrasformed_target_pos.at(0)[2] = z_max;

		/*a questo punto ritrasformo il vettore untrasformed_target_pos, per riottenere
		la target_pos confinata dentro la superficie di pertinenza entro la quale si deve muovere enemy*/

		vector<array<float,3>> target_pos_vec = mymathlibNS::vmatMatrix::getProduct(untrasformed_target_pos, activityArea->getBody()->AOTrMatrix);
		targetPos = target_pos_vec.at(0);
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




	void myfirstIA::setTarget(collectorNS::ActiveObjectCollector* t) 
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
		collectorNS::ActiveObjectCollector* obj,
		collectorNS::ActiveObjectCollector* target,
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
				collectorNS::ActiveObjectCollector * obj = 
					static_cast<collectorNS::ActiveObjectCollector*>
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