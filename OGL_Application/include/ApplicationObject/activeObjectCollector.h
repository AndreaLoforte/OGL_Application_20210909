#pragma once
#include<fstream>
#include<objectCollector.h>


namespace myobjectNS {
	class GroundSurfaceOC;
}

using namespace std;
namespace collectorNS {

	class ActiveObjectCollector : public ApplicationObjectCollector {
	public:
		ActiveObjectCollector(const std::string collName, AOcontainer* c) :
			ApplicationObjectCollector(collName, c),
			activeObjectID(collName) {}

		ActiveObjectCollector(const std::string collName,const unsigned& collNumber, AOcontainer* c) :
			activeObjectID(collName),
			ApplicationObjectCollector(collName, collNumber,c) {}

		virtual ~ActiveObjectCollector() override;
		const std::string activeObjectID;
		int healt = 100;
		bool isAlive = true;
		virtual int getHealt() { return healt; }
		virtual void setHealt(int c) { healt += c; }
		const bool& damage(const int& i = 10);

		virtual void setActivityGround(myobjectNS::GroundSurfaceOC* sb) {}
		virtual void setActivityGround(const string&) {}
		virtual myobjectNS::GroundSurfaceOC* getActivityGround() { return NULL; }
		virtual string getCollectorName() override { return collectorName; }
		virtual ActiveObjectCollector* OCloadActiveObject(const unsigned& collNumber);
		void OCsave(std::string& out) override;
	};



}