#ifndef GUN_H
#define GUN_H
#include<fpcamera.h>
#include<projectile.h>
#include<viewfinder.h>
#include<applicationObject.h>
#include<inputs.h>
#include<physics.h>
#include<objectCollector.h>
#include<sound.h>
namespace myobjectNS{


	

	class Gun {
	public:
		friend class myphysicsNS::CollisorePolimorfo;
		friend class InputsNS::Controls;
		unsigned int projcounter{ 0 };
		unsigned velmodule = 1000;
		bool trigger = false;
		/*oltre questo numero di proiettili,
		eliminiamo uno vecchio per crearne uno nuovo*/
		static constexpr unsigned MAXNUMEXISTINGPROJ{ 10 };


	 const bool&  getTrigger() { return trigger; }
     void clean(){}
	 void create() ;
     void update(const float &) ;
	 void render(const fpcameraNS::Transformation& cam);
	 void invokeSetTextures();
     void invokeSetShaders();
     void invokeSetRigidBodyParameters(const fpcameraNS::Transformation*);
	 void invokeSetPosition();

	 /*funzione che spara,  data un fireSpot 
	 e la posizione	del bersaglio */
     void shotAt(const std::array<float,3>&,const std::array<float,3>&);
	 //void OCload(std::ifstream& in, std::size_t start_from, std::size_t stop_at) override;
	 void shootTowards(const std::array<float,3>&,const std::array<float,3>&);
	 void OCcreateObject() ;
	 void OCrender();
	void OCsetParameters() ;
	//void OCsave(std::ofstream& out) ;
	
	 Gun* getNewInstance()  {
		 Gun* g(new Gun);
		 return g; 
	 }
	
	 void spawnProjectile(myobjectNS::ApplicationObject* obj) 
	 {
		 //if (projcounter >= MAXNUMEXISTINGPROJ)
			// /*prima di eliminare dovrei assicurarmi 
			// che si tratti di un proiettile e non di viewfinder*/
			// Pcontainer->erase(Pcontainer->begin());
		 //Pcontainer->push_back(obj);
		 //Pcontainer->back()->AOcreateObject();
		 //Pcontainer->back()->setParameters();
		 //projcounter++;
	 }

	 


	 void changeFirepower(double mouseYscroll) {
		 if (velmodule + mouseYscroll * 70 > 0)
			 velmodule += mouseYscroll * 70;
		 else
			 velmodule = 0;
	 }

};


	//////////////////////////////////////////////////////////////

class OCGun : public collectorNS::ApplicationObjectCollector {
public:
	friend class myphysicsNS::CollisorePolimorfo;
	friend class InputsNS::Controls;
	unsigned int projcounter{ 0 };
	unsigned velmodule = 500;
	bool trigger = false;
	/*oltre questo numero di proiettili,
	eliminiamo uno vecchio per crearne uno nuovo*/
	static constexpr unsigned MAXNUMEXISTINGPROJ{ 10 };
	Gun gun;
	ViewFinder vw;
	
	collectorNS::AOcontainer::iterator gunObjectsIT;

	//default constructor : utilizzo il container di default ownContainer
	OCGun():ApplicationObjectCollector("Gun")
	{
		char c('_');
		collectorID = "GUN";
		collectorID.push_back(c);
		collectorID.append(std::to_string(collectorNumber));
		//ownContainer.push_back(myobjectNS::ViewFinder().getNewInstance());
		collectorName = "Gun";
	}

	OCGun(collectorNS::AOcontainer* coll) :
		ApplicationObjectCollector("Gun",coll)
	{}

	OCGun(std::string objName, collectorNS::AOcontainer* coll) :
		collectorNS::ApplicationObjectCollector(objName,coll)
	{}


	const bool&  getTrigger() { return trigger; }
	void clean() {}
	void create();
	void render(const fpcameraNS::Transformation& cam);
	void invokeSetRigidBodyParameters(const fpcameraNS::Transformation*);

	/*funzione che spara,  data un fireSpot
	e la posizione	del bersaglio */
	void shootAt(const std::array<float, 3>&, const std::array<float, 3>&);
	
	//void OCload(std::ifstream& in, std::size_t start_from, std::size_t stop_at) override;
	void shootTowards(const std::array<float, 3>&, const std::array<float, 3>&);
	void OCcreateObject() override;
	void OCrender() override;
	void OCsetParameters() override;
	//void OCsave(std::ofstream& out) override;
	void OCsave(std::string& filename) override;
	std::string getCollectorName() override {
		return "Gun";
	}
	OCGun* OCgetNewInstance() override {
		OCGun* g = new OCGun(new collectorNS::AOcontainer);
		return g;
	}

	void OCinsertObject(myobjectNS::ApplicationObject* obj) override;

	void changeFirepower(double mouseYscroll) {
		if (velmodule + mouseYscroll * 70 > 0)
			velmodule += mouseYscroll * 70;
		else
			velmodule = 0;
	}


	void setCollectorName() { collectorName = "Gun"; }



};







}



#endif