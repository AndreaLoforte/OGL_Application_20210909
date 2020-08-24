#ifndef OBJECTCOLLECTOR_H
#define OBJECTCOLLECTOR_H

#include<vector>
#include<string>

using namespace std;

namespace myobjectNS {
	class ApplicationObject;
	class ObjectPlane;
	class ObjectSphere;
	class ObjectBox;
	class SurfaceBoundaries;

}

namespace collectorNS{

	typedef std::vector<myobjectNS::ApplicationObject*> AOcontainer;
	class ActiveObject;

	///////////////////////////////////////APPLICATIONOBJECT COLLECTOR///////////////////////////////////////

	/*uso il collettore come una interfaccia :
	concretamente gli oggetti risiederanno nel vettore
	puntato da Pcollector, che viene passato 
	dall'istanza del collettore creata.
	In questo modo ho una buona flessibilità nel senso che
	per esempio dato l'oggetto OCEnemy contenente l'oggetto
	Gun e altri oggetti semplici.Sia OCEnemy che Gun sono collettori, ma io voglio che
	i proiettili di gun vengano messi nello stesso contenitore di OCEnemy
	=> creo in OCEnemy il contenitore e lo passo a Gun in modo che
	venga inizializzato il puntatore del collettore, in questo modo
	Gun mette i proiettili nello stesso contenitore dove vengono messi
	gli altri oggetti di OCEnemy */
class ApplicationObjectCollector {
public:
	/*flag per sapere se stiamo usando
	il contenitore interno o esterno*/
	bool externalContainer = false;
	/*contenitore se non vogliamo
	usarne uno esterno*/
	AOcontainer ownContainer;
	/*puntatore a contenitore
	passato dall'esterno */
	AOcontainer* Pcontainer;

public:
	/*dice a quale collettore appartiene questo collettore*/
	std::string collectorOwnership{ "none" };
	static const std::string COLLECTOR_TYPE;
	static int collectorCounter;
	const std::string collectorName;
	const std::string collectorID;
	const unsigned collectorNumber;
	bool isOn = false;
	
	
	/*when loading stored collectors we want to restore the original collector number*/
	ApplicationObjectCollector(const std::string collName,const unsigned collNumber, AOcontainer* coll);
	ApplicationObjectCollector(const std::string collName,  AOcontainer* coll);
	ApplicationObjectCollector(const std::string collName, const unsigned collNumber);
	//ApplicationObjectCollector(const std::string collName,  AOcontainer* coll);
	ApplicationObjectCollector(const std::string s);
	ApplicationObjectCollector()  = delete;

	virtual ~ApplicationObjectCollector();

	//////////////////////METODI
	virtual myobjectNS::ApplicationObject* getSubObject(int i);
	virtual unsigned getSize() { return Pcontainer->size(); }
	//virtual void OCsave(std::ofstream& out);
	virtual void OCsave(std::string& s);
	virtual ApplicationObjectCollector* OCgetNewInstance();
	virtual void OCcreateObject();
	virtual void OCsetParameters();
	virtual void setParameters() {}
	virtual void OCreset();
	virtual void OCupdate(const float&);
	virtual void OCrender();
	virtual void OCinsertObject(myobjectNS::ApplicationObject*);
	virtual std::string getCollectorID() { return collectorID; }
	virtual std::string getCollectorType()const { return COLLECTOR_TYPE; }
	virtual ApplicationObjectCollector* getCopy();
	virtual std::string getCollectorName();
	virtual ApplicationObjectCollector* OCloadInstance(const unsigned& collNumber);
	virtual ActiveObject* OCloadActiveObject(const unsigned& collNumber);
	virtual void  deleteAtPos(const int&);
	static ApplicationObjectCollector* getCollector(myobjectNS::ApplicationObject*);
	virtual void canSleep(bool);
	/*getBody returns the body (not the rigid body!) of this ApplicationObjectCollector*/
	virtual myobjectNS::ApplicationObject* getBody() { return Pcontainer->at(0); }
	void virtual AOtrX(int sign);
	void virtual AOtrY(int sign);
	void virtual AOtrZ(int sign);
	void virtual AOrotX(int sign);
	void virtual AOrotY(int sign);
	void virtual AOrotZ(int sign);
	void AOtr(const int& shiftX, const int& shiftY, const int& shiftZ);
	
	virtual std::string getInfos() 
	{
		return "generic collector";
	}

	virtual void setCollectorOwnership(const std::string s)
	{
		collectorOwnership = s;
	}
	
};






}




#endif 