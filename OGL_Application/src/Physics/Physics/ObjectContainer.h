//#ifndef MYPHYSICS_H
//#define MYPHYSICS_H
//#include<collide_fine.h>
//#include<applicationObject.h>
//#include<applicationDerivedObject.h>
//
//
//namespace myphysicsNS {
//
//	
//
//
//	class CollisorePolimorfo {
//		
//		//friend class myobjectNS::Surface;
//
//	public:
//		static CollisionData cdata;
//		const static unsigned maxContacts = 256;
//		Contact contacts[maxContacts];
//		CollisionDetector cdetector;//mi serve solo per inizializare gli attributi statici.
//		static ContactResolver resolver;
//	
//		CollisorePolimorfo(){
//			cdata.friction = (real).3;
//			cdata.restitution = (real)0.8;
//			cdata.tolerance = (real)0.2;
//			cdata.contactArray = contacts;
//			cdata.contacts = cdata.contactArray;
//		}
//
//		static void CPinvokeCollisionDetector(myobjectNS::ApplicationObject* v1, myobjectNS::ApplicationObject*v2);
//
//		static void generateContacts();
//
//
//		static void update(float duration) {
//			// Perform the contact generation
//			generateContacts();
//
//			// Resolve detected contacts
//			resolver.resolveContacts(
//				getCollisionData()->contactArray,
//				getCollisionData()->contactCount, duration);
//			
//			cdata.reset(maxContacts);
//		}
//
//
//		static CollisionData* getCollisionData() { return &cdata; }
//
//	};
//
//
//
//	struct CollisionObjectContainer {
//
//		CollisionObjectContainer() {}
//
//		CollisionObjectContainer(std::vector<myobjectNS::ApplicationObject*> objVec)
//		{
//			container = objVec;
//		}
//
//		CollisionObjectContainer(myobjectNS::ApplicationObject* objVec)
//		{
//			container.push_back(objVec);
//		}
//
//		virtual myobjectNS::ApplicationObject* getSubObject(int i);
//		virtual unsigned getSize() { return container.size(); }
//
//		std::vector<myobjectNS::ApplicationObject*> container;
//	};
//
//
//	struct CollisionPlaneContainer : CollisionObjectContainer {
//
//
//		CollisionPlaneContainer() {}
//
//		CollisionPlaneContainer(std::vector<myobjectNS::ObjectPlane*> objVec)
//		{
//			container = objVec;
//		}
//
//		CollisionPlaneContainer(myobjectNS::ObjectPlane* objVec)
//		{
//			container.push_back(objVec);
//		}
//
//		myobjectNS::ObjectPlane* getSubObject(int i)override;
//		unsigned getSize() override { return container.size(); }
//		std::vector<myobjectNS::ObjectPlane*> container;
//	};
//
//
//
//
//	struct CollisionSphereContainer : CollisionObjectContainer {
//
//
//		CollisionSphereContainer() {}
//
//		CollisionSphereContainer(std::vector<myobjectNS::ObjectSphere*> objVec)
//		{
//			container = objVec;
//		}
//
//		CollisionSphereContainer(myobjectNS::ObjectSphere* objVec)
//		{
//			container.push_back(objVec);
//		}
//
//		myobjectNS::ObjectSphere* getSubObject(int i)override;
//		unsigned getSize() override { return container.size(); }
//		std::vector<myobjectNS::ObjectSphere*> container;
//	};
//
//
//
//	struct CollisionBoxContainer : CollisionObjectContainer {
//
//
//		CollisionBoxContainer() {}
//
//		CollisionBoxContainer(std::vector<myobjectNS::ObjectBox*> objVec)
//		{
//			container = objVec;
//		}
//
//		CollisionBoxContainer(myobjectNS::ObjectBox* objVec)
//		{
//			container.push_back(objVec);
//		}
//
//		myobjectNS::ObjectBox* getSubObject(int i) override;
//		unsigned getSize() override { return container.size(); }
//		std::vector<myobjectNS::ObjectBox*> container;
//	};
//
//
//
//
//
//	
//
//
//
//}
//
//
//
//
//#endif