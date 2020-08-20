#pragma once
#include<fstream>
#include<objectCollector.h>
//#include<string>

namespace myobjectNS {
	class GroundSurfaceOC;
}

using namespace std;
namespace collectorNS {

	class ActiveObject : public ApplicationObjectCollector {
	public:
		ActiveObject(const std::string collName, AOcontainer* c) :ApplicationObjectCollector(collName, c) {}
		std::string activeObjectID;
		int healt = 100;
		bool isAlive = true;
		virtual int getHealt() { return healt; }
		virtual void setHealt(int c) { healt += c; }
		const bool& damage(const int& i = 10);



		virtual void setActivityGround(myobjectNS::GroundSurfaceOC* sb) {}
		virtual void setActivityGround(const string&) {}
		virtual myobjectNS::GroundSurfaceOC* getActivityGround() { return NULL; }
		
		
		
		void OCsave(std::string& out) override;
	};



}