#include<string>
#include<objectCollector.h>
#include<applicationDerivedObject.h>
#include<cameraManager.h>
#include<collectorLoader.h>
#include<activeObjectCollector.h>
namespace collectorNS {

	int ApplicationObjectCollector::collectorCounter;
	const std::string ApplicationObjectCollector::COLLECTOR_TYPE{ "APPLICATIONCOLLECTOR" };
	const string SEPARATOR = "_";


	/*this constructor should be called only when loading an instance, so we can restore 
	the original collNumber*/
	ApplicationObjectCollector::ApplicationObjectCollector(const std::string collName, const unsigned collNumber, AOcontainer* coll) :
		externalContainer(true),
		Pcontainer(coll),
		collectorNumber(collNumber),
		collectorName(collName),
		collectorID(collectorName + SEPARATOR + std::to_string(collNumber))
	{
		collectorCounter = collNumber + 1;
	}

	ApplicationObjectCollector::ApplicationObjectCollector(const std::string collName, AOcontainer* coll) :
		externalContainer(true),
		Pcontainer(coll),
		collectorNumber(ApplicationObjectCollector::collectorCounter),
		collectorName(collName),
		collectorID(collectorName + SEPARATOR + std::to_string(ApplicationObjectCollector::collectorCounter))
	{
		ApplicationObjectCollector::collectorCounter++;
	}


	ApplicationObjectCollector::ApplicationObjectCollector(const std::string collName, const unsigned collNumber) :
		externalContainer(false),
		Pcontainer(&ownContainer),
		collectorNumber(collNumber),
		collectorName(collName),
		collectorID(collectorName + SEPARATOR + std::to_string(collNumber))
	{
		collectorCounter = collNumber + 1;
	}


	ApplicationObjectCollector::ApplicationObjectCollector(const std::string collName) :
		externalContainer(false),
		Pcontainer(&ownContainer),
		collectorNumber(ApplicationObjectCollector::collectorCounter),
		collectorName(collName),
		collectorID(collectorName + SEPARATOR + std::to_string(ApplicationObjectCollector::collectorCounter))
	{
		ApplicationObjectCollector::collectorCounter++;
	}








	


	void ApplicationObjectCollector::canSleep(bool v)
	{
		isOn = !v;
		//newColl->getSubObject(j)->AOcanSleep(collectorData.AOobjects[j].isOn);
		for (int i = 0; i < Pcontainer->size(); i++)
		{
			Pcontainer->at(i)->AOcanSleep(v);
		}
	}



	ApplicationObjectCollector* ApplicationObjectCollector::getCopy() {

		ApplicationObjectCollector * newcoll = this;
		return newcoll;
	}

	


	ApplicationObjectCollector::~ApplicationObjectCollector()
	{
		//deallocazione della memoria occupata da collector
		for (int i = 0; i < Pcontainer->size(); i++)
			delete Pcontainer->at(i);
		collectorCounter--;
	}

	//////////////////////////////////////////////////////////////////
	//METODI

	void ApplicationObjectCollector::OCcreateObject()
	{
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOcreateObject();
	}

	void ApplicationObjectCollector::OCsetParameters()
	{
		for (int i = 0; i < Pcontainer->size(); i++)
		{
			Pcontainer->at(i)->setParameters();
			Pcontainer->at(i)->AOsetShaders();
		}
	}

	void ApplicationObjectCollector::OCreset()
	{
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOreset();
	}

	void ApplicationObjectCollector::OCupdate(const float & duration)
	{
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOupdate(duration);
	}

	void ApplicationObjectCollector::OCrender()
	{
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOrender();
	}


	void ApplicationObjectCollector::OCinsertObject(myobjectNS::ApplicationObject* obj)
	{
		Pcontainer->push_back(obj);
		Pcontainer->back()->AOcreateObject();
		Pcontainer->back()->setParameters();
		
	}

	
	void ApplicationObjectCollector::OCsave(std::string& s)
	{
		
		saveloadNS::CollectorSaver::save(this, s);

	}


	ApplicationObjectCollector* ApplicationObjectCollector::OCgetNewInstance() {

		ApplicationObjectCollector* coll
		(new ApplicationObjectCollector
		(collectorName,ApplicationObjectCollector::collectorCounter,new AOcontainer));

		for (int i = 0; i < Pcontainer->size(); i++)
			coll->Pcontainer->push_back(Pcontainer->at(i)->getNewInstance());

		return coll;
	}

	ApplicationObjectCollector* ApplicationObjectCollector::OCloadInstance(const unsigned& collNumber) 
	{

		ApplicationObjectCollector* coll
		(new ApplicationObjectCollector(collectorName, collNumber, new AOcontainer));

		for (int i = 0; i < Pcontainer->size(); i++)
			coll->Pcontainer->push_back(Pcontainer->at(i)->getNewInstance());

		return coll;
	}

	ActiveObjectCollector* ApplicationObjectCollector::OCloadActiveObject(const unsigned& collNumber)
	{

		ActiveObjectCollector* coll
		(new ActiveObjectCollector(ApplicationObjectCollector::collectorName, collNumber, new AOcontainer));

		for (int i = 0; i < Pcontainer->size(); i++)
			coll->Pcontainer->push_back(Pcontainer->at(i)->getNewInstance());

		return coll;
	}



	myobjectNS::ApplicationObject* ApplicationObjectCollector::getSubObject(int i)
	{

		return Pcontainer->at(i);
	}

	void  ApplicationObjectCollector::deleteAtPos(const int& i)
	{
		vector<myobjectNS::ApplicationObject*>::iterator it = Pcontainer->begin();
		
		Pcontainer->erase(it + i);
		
	}

	//DI DEFAULT SETTIAMO IL NOME DEL COLLETTORE AL NOME DEL PRIMO OGGETTO CONTENUTO
	std::string ApplicationObjectCollector::getCollectorName() {
		return Pcontainer->at(0)->AOobjectName;
	}

	
	/*create collector from an ApplicationObject*/
	ApplicationObjectCollector* ApplicationObjectCollector::getCollector(myobjectNS::ApplicationObject* obj)
	{

		collectorNS::ApplicationObjectCollector * coll = 
			new collectorNS::ApplicationObjectCollector
			(obj->AOobjectName,
				new collectorNS::AOcontainer);

		coll->Pcontainer->push_back(obj->getNewInstance());
		//coll->setCollectorName();
		return coll;
	}


	void ApplicationObjectCollector::AOtr(const int& shiftX = 0,const int& shiftY = 0, const int& shiftZ = 0) {
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOtr(shiftX, shiftY, shiftZ);
	}



	void ApplicationObjectCollector::AOtrX(int sign) {
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOtrX(sign);
	}
	void ApplicationObjectCollector::AOtrY(int sign) {
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOtrY(sign);
	}
	void ApplicationObjectCollector::AOtrZ(int sign) {
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOtrZ(sign);
	}
	void ApplicationObjectCollector::AOrotX(int sign) {
		/*sempre specificare f per float!*/

		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOrotX(sign);

	}
	void ApplicationObjectCollector::AOrotY(int sign) {
		//AOorientation[1] += sign * AOrot[0];
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOrotY(sign);

	}
	void ApplicationObjectCollector::AOrotZ(int sign) {
		//AOorientation[2] += sign * AOrot[0];
		for (int i = 0; i < Pcontainer->size(); i++)
			Pcontainer->at(i)->AOrotZ(sign);
	}



}