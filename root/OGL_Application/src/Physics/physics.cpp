#include<physics.h>
#include<applicationObjectManager.h>
#include<objectCollector.h>
#include<sound.h>



namespace myphysicsNS {


	unsigned CollisorePolimorfo::frameContactCounter = 0;
	CollisionData CollisorePolimorfo::cdata;
	ContactResolver CollisorePolimorfo::resolver;
	std::vector<myobjectNS::ApplicationObject*> CollisorePolimorfo::CPobjectslist;
	

	void CollisorePolimorfo::generateContacts() {

		typedef  myobjectNS::ApplicationObjectManager AOManager;
		
		CPobjectslist.clear();
		/*metto tutti gli oggetti in una lista lineare*/
		for (int i = 0; i < myobjectNS::ApplicationObjectManager::ApplicationCollectorList.size(); i++)
		{
				
			for (int j = 0; j < myobjectNS::ApplicationObjectManager::ApplicationCollectorList[i]->getSize(); j++)
			{
				CPobjectslist.push_back(myobjectNS::ApplicationObjectManager::ApplicationCollectorList[i]->getSubObject(j));
			}
				
		}
	
		/*invoco il collision detector su ogni coppia*/
		for (int i = 0; i < CPobjectslist.size(); i++)
			for (int j = i + 1; j < CPobjectslist.size(); j++)
				CPinvokeCollisionDetector(CPobjectslist[i], CPobjectslist[j]);
			

	}





	void CollisorePolimorfo::CPinvokeCollisionDetector(myobjectNS::ApplicationObject* o1, myobjectNS::ApplicationObject* o2) {
		/*0 => SFERA  
		  1 => HALF SPACE
		  2 => BOX 
		  3 => TRUE PLANE*/
		int CollisorID1 = o1->getCollisorID();
		int CollisorID2 = o2->getCollisorID();
		myobjectNS::ObjectSphere *sphere1, *sphere2;
		myobjectNS::ObjectPlane *plane1, *plane2;
		myobjectNS::ObjectBox *box1, *box2;
		
		//Poichè non sappiamo a priori come avverranno le chiamate a questa funzione dobbiamo considerare
		//tutte le possibili casistiche per chiamare il collision detector nell'ordine corretto

		/*SFERA - SFERA*/
		if (CollisorID1 == 0 && CollisorID2 == 0) {
			sphere1 = dynamic_cast<myobjectNS::ObjectSphere*> (o1);
			sphere2 = dynamic_cast<myobjectNS::ObjectSphere*> (o2);
			if (sphere1->AOcollectorOwnershipID == sphere2->AOcollectorOwnershipID) return;
			CollisionDetector::ACD.sphereAndSphere(*sphere1, *sphere2, &cdata);
		}

		/* DISATTIVATO */
		if (CollisorID1 == 0 && CollisorID2 == 1) {
			sphere1 = dynamic_cast<myobjectNS::ObjectSphere*> (o1);
			plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o2);
			/*tutti i piani adesso vengono costruiti come collisionFinitePlane. Necessario creare nuovi oggetti per halfSpace e infinite Plane*/
			//bool collide = CollisionDetector::sphereAndHalfSpace(*sphere1, *plane1, &cdata);
		}

		/*SFERA - PIANO FINITO*/
		{
			if (CollisorID1 == 0 && CollisorID2 == 3) {
				sphere1 = dynamic_cast<myobjectNS::ObjectSphere*> (o1);
				plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o2);
				CollisionDetector::ACD.sphereAndFinitePlane(*sphere1, *plane1, &cdata);
			}
			if (CollisorID1 == 3 && CollisorID2 == 0) {
				sphere1 = dynamic_cast<myobjectNS::ObjectSphere*> (o2);
				plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o1);
				CollisionDetector::ACD.sphereAndFinitePlane(*sphere1, *plane1, &cdata);
			}
		}

		/*BOX - PIANO FINITO*/
		{
			if (CollisorID1 == 3 && CollisorID2 == 2)
			{
				box1 = dynamic_cast<myobjectNS::ObjectBox*> (o2);
				plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o1);
				CollisionDetector::ACD.boxAndFinitePlane(*box1, *plane1, &cdata);
			}
			if (CollisorID1 == 2 && CollisorID2 == 3) {
				plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o1);
				box1 = dynamic_cast<myobjectNS::ObjectBox*> (o2);
				CollisionDetector::ACD.boxAndFinitePlane(*box1, *plane1, &cdata);
			}
		}




		/*BOX - SFERA*/
		{
			if (CollisorID1 == 0 && CollisorID2 == 2) 
			{
				sphere1 = dynamic_cast<myobjectNS::ObjectSphere*> (o1);
				box1 = dynamic_cast<myobjectNS::ObjectBox*> (o2);
				//CollisionDetector::ACD.BoxAndSphere(*box1, *sphere1, &cdata);
				CollisionDetector::boxAndSphere(*box1, *sphere1, &cdata);
			}
			if (CollisorID1 == 2 && CollisorID2 == 0) {
				box1 = dynamic_cast<myobjectNS::ObjectBox*> (o1);
				sphere1 = dynamic_cast<myobjectNS::ObjectSphere*> (o2);
				//CollisionDetector::ACD.BoxAndSphere(*box1, *sphere1, &cdata);
				CollisionDetector::boxAndSphere(*box1, *sphere1, &cdata);
			}
		}

		{//BOX - HALF SPACE---DISATTIVATO
			if (CollisorID1 == 1 && CollisorID2 == 2) {
				plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o1);
				box1 = dynamic_cast<myobjectNS::ObjectBox*> (o2);
				//CollisionDetector::boxAndHalfSpace(*box1, *plane1, &cdata);
			}
			if (CollisorID1 == 2 && CollisorID2 == 1) {
				box1 = dynamic_cast<myobjectNS::ObjectBox*> (o1);
				plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o2);
				//CollisionDetector::boxAndHalfSpace(*box1, *plane1, &cdata);
			}

		}
		
		//SFERA - HALF SPACE
		if (CollisorID1 == 1 && CollisorID2 == 0)
		{
			plane1 = dynamic_cast<myobjectNS::ObjectPlane*> (o1);
			sphere1 = dynamic_cast<myobjectNS::ObjectSphere*> (o2);
			//CollisionDetector::sphereAndHalfSpace(*sphere1, *plane1, &cdata);
		}

		
		//BOX-BOX
		if (CollisorID1 == 2 && CollisorID2 == 2) {
			box1 = dynamic_cast<myobjectNS::ObjectBox*> (o1);
			box2 = dynamic_cast<myobjectNS::ObjectBox*> (o2);
			CollisionDetector::boxAndBox(*box1, *box2, &cdata);
		}
		




	}





}