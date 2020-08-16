#pragma once
#include<applicationDerivedObject.h>
#include<baseObject.h>
#include<vector>
#include<fpcamera.h>


namespace myobjectNS {


	class Polygon : public ApplicationObject, public BaseObject{
	public:
		Polygon(const string& s):BaseObject(s),ApplicationObject(s)
		{
			AOobjectName = s;
		}
		std::vector<float> vertices;
		void create();
		void render(const fpcameraNS::Transformation& cam) override;
		void renderPolygon();
		void renderCollisionPrimitive();
		void update(const float& duration);
		void setRigidBodyParameters();
		void setParameters();
		Polygon* getNewInstance() 
		{
			Polygon* f(new Polygon("polygon"));
			return f;
		}
	};



}