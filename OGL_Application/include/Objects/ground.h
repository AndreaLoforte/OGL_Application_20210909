#pragma once

#include<array>
#include<vector>
#include<applicationObjectManager.h>
#include<userInterface.h>
#include<core.h>
#include<applicationDerivedObject.h>
#include<utility>

namespace aiNS {
	class myfirstIA;
}


namespace myobjectNS {

	struct SurfaceBoundaries
	{
		myobjectNS::ApplicationObject* p;
		SurfaceBoundaries(myobjectNS::ApplicationObject * p_):p(p_){}
		array<float, 3> size;

		void boundaryLinesEq();

		array<float, 3> getRandomPointInSurface(aiNS::myfirstIA* brain);
		

	};


	class Ground {
	public:
		typedef std::map<string, SurfaceBoundaries*>::iterator GroudMapIterator;
		/*groundID , ground*/
		static std::map<string, SurfaceBoundaries*> groundMap;
		static std::vector<SurfaceBoundaries> grounds;
		static GroudMapIterator groundMapIT;

		static void addBoundaries(std::vector<std::array<float, 3>> surf_vertices){}		
		static void addSurface(collectorNS::ApplicationObjectCollector* c);
		static void addSurface(myobjectNS::ApplicationObject* c);
		static vector<string> getGroundList();
		static SurfaceBoundaries* getGround(const string&);

	};





	class GroundSurface :public ObjectPlane, public BaseObject {
		string objectName = "Surface";
		static unsigned instanceCounter;
		unsigned instanceNumber;

		vector<array<float, 3>> vertices;

	public:
		GroundSurface(std::string sh_prog_name, GLfloat l = 100) :
			ObjectPlane(sh_prog_name, 100, 0, 100),
			BaseObject(sh_prog_name)
		{

			CollisionFinitePlane::size[0] = l;
			CollisionFinitePlane::size[1] = 0;
			CollisionFinitePlane::size[2] = l;

			instanceNumber = instanceCounter++;
			body->RBobjectName = objectName;
			
			Ground::addSurface(this);
		}



		void clean() {}
		void render(const fpcameraNS::Transformation&) override;
		void renderSurface();
		void renderCollisionPrimitive();
		void update(const float&) override;
		void setColor(float, float, float, float);
		void create()override;
		void AOsetShaders() override { setShaders(); }
		void setRigidBodyParameters();
		void setParameters()override;
		GroundSurface* getNewInstance()override {
			GroundSurface* s(new GroundSurface("groundSurface"));
			return s;
		}
		int getCollisorID() override { return AOCollisorID; }



	};




}