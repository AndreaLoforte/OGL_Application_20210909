#ifndef PROJECTILE
#define PROJECTILE

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<assert.h>
#include<physics.h>
#include<mymathlib.h>

namespace myobjectNS{

  class Projectile final :public ObjectSphere, public BaseObject{
	  friend class myphysicsNS::CollisorePolimorfo;
	  friend class Gun;
	  GLuint VAO;
	  vmath::mat4 tr_m;
	  GLfloat position[3]{ 0.0,0.0,0.0 };
	  mymathlibNS::Quaternion orientation;
	  GLfloat direction[3] ;
	  GLfloat velocity[3]{ 0.0,0.0,0.0 };
	  GLfloat vel_module = 0.0;
	  /*shift della posizione di partenza del proiettile.
		evita la collisione del proiettile col corpo che lo spara*/
	  std::array<float, 3> fireSpotShift;
	  /*il modulo dello shift dev'essere tale da portare
	  il corpo del proiettile fuori dal corpo del corpo che spara (somma dei raggi)*/
	  const float fireSpotShiftModule = 0;
 public:
	 Projectile(std::string sh_prog_name = "projectile", std::array<float, 3> fireSpot = { 0.0,0.0,0.0 }) :
		 ObjectSphere(sh_prog_name),
		 BaseObject(sh_prog_name)
	 {
		 radius = 2.0;
		 AOposition = fireSpot;
		 vel_module = 10;
		 AOCollisorID = 0;//sphere
	 }
	 ~Projectile() {}
   void clean(){}
   void update(const float&);
   void create() override;
   void OSsetParameters() override { setRigidBodyParameters(); }
   void render();
   void render(const fpcameraNS::Transformation& cam) override;
   void setRigidBodyParameters();
  // void shot(const fpcameraNS::Transformation*);
   void shoot(const std::array<float, 3>&,const std::array<float, 3>&);
   void setVelModule(const float& vm) { vel_module = vm; }
   void resetAll() {
	   setRigidBodyParameters();
   }

   Projectile* getNewInstance() override {

	   Projectile*p(new Projectile("projectile"));
	   return p;
   }

  int getCollisorID() override { return AOCollisorID; }
   
 };







}//NS
#endif
