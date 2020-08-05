#ifndef APPLICATIONDERIVEDOBJ_H
#define APPLICATIONDERIVEDOBJ_H


#include<applicationObject.h>
//#include<collide_fine.h>
#include<AdvancedPhysics/collide_fine_advanced.h>
//#include<physics.h>

namespace collectorNS {
	class ObjectPlaneCollector;
	class ObjectPlaneCollector;
	class ObjectBoxCollector;
}

class RigidBody;

namespace myobjectNS 
{

	static const std::string classSphere{ "Sphere" };

	static const std::string classPlane{ "Plane" };

	static const std::string classBox{ "Box" };


	constexpr int HALFSPACECOLLISORID = -1;/*TBD*/
	constexpr int PLANECOLLISORID = -3;/*TBD*/
	constexpr int FINITEPLANECOLLISORID = 3;
	constexpr int SPHERECOLLISORID = 0;
	constexpr int BOXCOLLISORID = 2;
	constexpr int AABBCOLLISORID = 2.1;/*TBD*/

	class ObjectSphere : public ApplicationObject, public CollisionSphere {
	protected:
		float DOradius = 5.0;
		static unsigned instanceCounter;
		unsigned instanceNumber;
	public:
		ObjectSphere(ObjectSphere*);
		ObjectSphere(std::string s = classSphere);
		int getCollisorID() override { AOCollisorID = SPHERECOLLISORID; return AOCollisorID; }
		std::string showParameters() override;
		ObjectSphere* getNewInstance()override;
		void render(const fpcameraNS::Transformation& cam) override { FinalRender(cam); }
		void OScreate() { create(); }
		virtual void create(){}
		virtual void OSsetParameters(){}
		virtual void FinalRender(const fpcameraNS::Transformation& cam){}
		//collectorNS::ObjectSphereCollector* getCollector() override;
		void specializedSave(std::ofstream&) override;
		std::string getRBObjectID() override { return body->RBobjectID;}
		virtual void changeRadius(float Rad) 
		{ 
			DOradius = Rad; 
			radius = DOradius;
			create();
		}
		void setSize(const std::vector<float>& sz) override
		{
			changeRadius(sz[0]);
		}

		void switchPhysics(const bool v) override { body->setAwake(v); }
		RigidBody * getRB()override;
		void DOcanSleep(const bool& v) override
		{
			body->canSleep = v;

		}

		void updatePhysics(const float& duration) override
		{
			body->integrate(duration);
			calculateInternals();
		}

	};

	


	class ObjectPlane : public ApplicationObject, public advancedPhysicsNS::CollisionFinitePlane {
	protected:
		static unsigned instanceCounter;
		unsigned instanceNumber;
	public:
		ObjectPlane(ObjectPlane*, const size_t& L1, const size_t& L2, const size_t& L3);
		ObjectPlane(const std::string& s,const size_t&L1, const size_t& L2, const size_t& L3);
		int getCollisorID() override { AOCollisorID = FINITEPLANECOLLISORID; return AOCollisorID; }
		std::string showParameters()override;
		vmath::vec4 planeNormal{ 0.0,1.0,0.0,1.0 };
		void create()override{}
		ObjectPlane* getNewInstance()override;
		std::string getRBObjectID() override { return body->RBobjectID; }
		//collectorNS::ObjectPlaneCollector* getCollector() override;
		void render(const fpcameraNS::Transformation& cam) override {}
		void specializedSave(std::ofstream&) override;

		/*chiamata a runtime per modificare size*/
		void changeDimensions(const GLfloat& w, const GLfloat& h) 
		{
			/*L1 = w;
			L2 = h;*/
			CollisionFinitePlane::size[0] = w;
			CollisionFinitePlane::size[1] = 0;
			CollisionFinitePlane::size[2] = h;

			create();
		}

		/*chiamata da application manager in loading*/
		void setSize(const std::vector<float>& sz) override
		{
			size[0] = sz[0];
			size[1] = sz[1];
			size[2] = sz[2];
			
		}

		void switchPhysics(const bool v) override { body->setAwake(v); }
		RigidBody * getRB()override;
		void DOcanSleep(const bool& v) override
		{
			body->canSleep = v;
		}
		void updatePhysics(const float& duration) override
		{
			body->integrate(duration);
			calculateInternals();
		}

	};




	class ObjectBox : public ApplicationObject, public CollisionBox {
	protected:
		GLfloat L1 = 10, L2 = 10, L3 = 10;
		static unsigned instanceCounter;
		unsigned instanceNumber;
	public:
		ObjectBox(ObjectBox*, const float& l1, const float& l2, const float& l3);
		ObjectBox(const std::string& s,const float& l1,const float& l2, const float& l3);
		int getCollisorID() override { AOCollisorID = BOXCOLLISORID; return AOCollisorID; }
		std::string getRBObjectID() override { return body->RBobjectID; }
		std::string showParameters()override;
		void setParameters() override;
		static void editBoxSize(const GLfloat&, const GLfloat& , const GLfloat&);
		ObjectBox* getNewInstance()override;
		//collectorNS::ObjectBoxCollector* getCollector() override;
		void specializedSave(std::ofstream&) override;
		//void setParameters() override{}
		void changeDimensions(const GLfloat& w, const GLfloat& h, const GLfloat& d)
		{
			L1 = w;
			L2 = h;
			L3 = d;
			halfSize[0] = L1/2;
			halfSize[1] = L2/2;
			halfSize[2] = L3/2;
			create();
		}

		void switchPhysics(const bool v) override { body->setAwake(v); }
		void DOcanSleep(const bool& v) override
		{
			body->canSleep = v;
			body->isAwake = !v;			
		}
		RigidBody * getRB()override;
		
		void updatePhysics(const float& duration) override
		{
			body->integrate(duration);
			calculateInternals();
		}

	};



	class ObjectAABB : public ApplicationObject, public advancedPhysicsNS::CollisionAABB {
	protected:
		GLfloat L1 = 10, L2 = 10, L3 = 10;
		static unsigned instanceCounter;
		unsigned instanceNumber;
	public:
		ObjectAABB(ObjectBox*, const float& l1, const float& l2, const float& l3);
		ObjectAABB(const std::string& s, const float& l1, const float& l2, const float& l3);
		int getCollisorID() override { AOCollisorID = AABBCOLLISORID; return AOCollisorID; }
		std::string getRBObjectID() override { return body->RBobjectID; }
		std::string showParameters()override;
		void setParameters() override;
		ObjectAABB* getNewInstance()override;
		
		void specializedSave(std::ofstream&) override;
		void changeDimensions(const GLfloat& w, const GLfloat& h, const GLfloat& d)
		{
			L1 = w;
			L2 = h;
			L3 = d;
			create();
		}
		void setSize(const std::vector<float>& sz) override
		{
			changeDimensions(sz[0], sz[1], sz[2]);
		}

		void switchPhysics(const bool v) override { body->setAwake(v); }
		void DOcanSleep(const bool& v) override
		{
			body->canSleep = v;

		}
		RigidBody * getRB()override;


		void updatePhysics(const float& duration) override
		{
			body->integrate(duration);
			calculateInternals();
		}

	};






}











#endif