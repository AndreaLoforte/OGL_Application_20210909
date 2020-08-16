#ifndef IA_H
#define IA_H

#include<core.h>
#include<fpcamera.h>
#include<body.h>
#include<applicationDerivedObject.h>
#include<random>
#include<functional>
#include<PrintHelper.h>
namespace myobjectNS {
	class PlayerCharacterOC;
	class OCGun;
}

class Contact;

namespace aiNS {



	class AI {
		static printHelperNS::PrintHelper ph;
	public:
		static void updateHealt(const Contact* contactArray, const unsigned& contactCounter);
		static myobjectNS::PlayerCharacterOC * target;



	};



	class myfirstIA {
	public:
		
		/*flag AI activity for a active object*/
		bool AIon = false;
		
		myobjectNS::PlayerCharacterOC* target;
		std::array<float, 3> targetDistance;
		float targetDistanceNorm;
		const float activationDistance = 1000;
		bool seekAndDest = true;
		/*IA cache all the relevant pointers of the
		controlled object*/
		collectorNS::ActiveObject* myself;
		myobjectNS::ApplicationObject* mybody;
		RigidBody *myRB;
		Vector3 myposition;

		std::default_random_engine generator;
		Vector3 randomDestination{ 0.0,0.0,0.0 };
		Vector3 deltaMovement{ 0.0,0.0,0.0 };
		std::uniform_int_distribution<int> distribution{ -100,100 };

		std::_Binder<std::_Unforced,
			std::uniform_int_distribution<int>&, 
			std::default_random_engine&> 
			random = std::bind(distribution, generator);

		int gunTimer = 0;
		int gunRepFreq = 100;
	public:	
		myfirstIA(collectorNS::ActiveObject* I):myself(I)
		{
			mybody = myself->getBody();
			myRB = mybody->getRB();
			myposition = myRB->position;
		}

		/*funzione che impone all'oggetto passato di seguire il mainCharacter*/
		void follow(myobjectNS::ApplicationObject*, myobjectNS::ApplicationObject*, const float& distance);
		void follow(collectorNS::ActiveObject* obj, collectorNS::ActiveObject* target);
		/*spotfire, spotTarget, gun*/
		void shoot(const std::array<float,3>&, const std::array<float, 3>&,const unsigned&,myobjectNS::OCGun&);
		void shoot(collectorNS::ActiveObject*, collectorNS::ActiveObject*,  const unsigned&, myobjectNS::OCGun&);
		void setTarget(collectorNS::ActiveObject* t);
		void update();
		const bool& seekAndDestroy();
		void moveRandomly();
		void moveInsideBoundaries();
	};


	

	class HealtManager {

	public:
		

	};
	






}




#endif