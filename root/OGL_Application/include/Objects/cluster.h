#pragma once

#include<objectCollector.h>


namespace myobjectNS {


	class Cluster {
	public:

		std::vector<collectorNS::ApplicationObjectCollector*> group;

	};

	

	//class ObjectPointer{
	//public:

	//	collectorNS::ApplicationObjectCollector* pointer;


	//};


	//class Cluster {
	//	size_t counter = 0;
	//	size_t size;
	//public:
	//	Cluster() 
	//	{ 
	//		counter = 0; 
	//		size = 5;
	//		group = new ObjectPointer[size];
	//	}
	//	ObjectPointer* group;
	//	ObjectPointer* const beg{ group };
	//	ObjectPointer* backup;

	//	void push_back(collectorNS::ApplicationObjectCollector* obj);
	//	void Backup();
	//	void Restore();
	//	void AllocateSpace();
	//	ObjectPointer* begin() { return beg; }
	//	ObjectPointer* end() { return beg+counter; }
	//	size_t getSize() { return counter; }

	//	ObjectPointer& getPointer(const size_t& i) { return *(beg + i); }
	//};

	

}//NS
