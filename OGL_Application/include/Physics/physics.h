#ifndef MYPHYSICS_H
#define MYPHYSICS_H
//#include<collide_fine.h>
//#include<applicationObject.h>
#include<applicationDerivedObject.h>

namespace soundNS {
	class soundMap;
}

namespace myphysicsNS {

	


	class CollisorePolimorfo {
		
		friend class soundNS::soundMap;

	public:

		static std::vector<myobjectNS::ApplicationObject*> CPobjectslist;
		static myobjectNS::ApplicationObject*
			CPobjectsArr[2];
		static CollisionData cdata;
		const static unsigned maxContacts = 256;
		Contact contacts[maxContacts];
		CollisionDetector cdetector;//mi serve solo per inizializare gli attributi statici.
		static ContactResolver resolver;
		static unsigned frameContactCounter;
		CollisorePolimorfo(){

			cdata.friction = (real).3;
			cdata.restitution = (real)0.6;
			cdata.tolerance = (real)0.2;
			cdata.contactArray = contacts;
			cdata.contacts = contacts;
		}

		static void CPinvokeCollisionDetector(myobjectNS::ApplicationObject* v1, myobjectNS::ApplicationObject*v2);

		static void generateContacts();


		static void update(float duration) {
			// Perform the contact generation
			generateContacts();



			/*questo contatore di contatti servirà a soundMap.
			non posso passare cdata.contactCount perchè viene resettato
			dopo la risoluzione e quindi risulterebbe sempre nullo*/
			frameContactCounter = cdata.contactCount;


			// Resolve detected contacts
			resolver.resolveContacts(
				getCollisionData()->contactArray,
				getCollisionData()->contactCount, duration);
			

			

			cdata.reset(maxContacts);
		}


		static CollisionData* getCollisionData() { return &cdata; }

	};








}




#endif