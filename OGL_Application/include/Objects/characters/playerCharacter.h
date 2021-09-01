#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<AI.h>
#include<gun.h>
#include<activeObjectCollector.h>


namespace myobjectNS {

	
	class PlayerCharacter final :public ObjectSphere, public ShaderObject{
		GLuint VAO, VBO;
		static int instanceCounter;
		static constexpr GLuint N = 100, M = 50;
		GLfloat sphere[M][N][4];
		static constexpr GLfloat theta_stride = 360 / N;
		static constexpr GLfloat phi_stride = 360 / M;
		

	public:
		/*ogni oggetto che creo ha un puntatore 
		all'oggetto principale (in realtà vorrei 
		non poter creare altri player)*/
		static PlayerCharacter* main;
		static bool mainIsSet;
		std::array<float, 3> lookat;

		PlayerCharacter(std::string sh_prog_name = "playercharacter") :
			ObjectSphere(sh_prog_name),
			ShaderObject(sh_prog_name,"characters/playercharacter/") {
			AOcolor[0] = 1.0;
			AOcolor[0] = .5;
			AOcolor[0] = .5;
			AOcolor[0] = 1.0;
			main = this;
			mainIsSet = true;
			
		}
		/*PlayerCharacter(){}*/


		~PlayerCharacter() {}
		void clean() {}
		void update(const float&) override;
		const std::array<float, 3>& getPosition() { return main->AOposition; }
		void create()override;
		//void specializedSave(std::ofstream&)override;
		void render(const fpcameraNS::Transformation&) override;
		void setRigidBodyParameters();
		void reset() override;
		void OSsetParameters() override;

		PlayerCharacter* getNewInstance();

	
		void setParameters() override;
		PlayerCharacter * getPlayer();


		void cameraTransformation(myobjectNS::ApplicationObject* obj);
		/*void shoot();

		void changeFirepower(const double& yscroll);*/

	

	};

/////////////////////////////////////////////////////////////
	///////////////////////////////

	class PlayerCharacterOC final :public collectorNS::ActiveObject {
		
		collectorNS::AOcontainer playerContainer;
		OCGun gun{&playerContainer};
		PlayerCharacter pc;

	public:
		/*ogni oggetto che creo ha un puntatore
		all'oggetto principale (in realtà vorrei
		non poter creare altri player)*/
		static PlayerCharacterOC* main;
		static bool mainIsSet;

		PlayerCharacterOC() :
			ActiveObject("playercharacter", &playerContainer)
		{
			main = this;
			mainIsSet = true;
			//InputsNS::Controls::setPlayer(this);
			playerContainer.push_back(&pc);
			
			healt = 1000;
			
		}
		~PlayerCharacterOC() override;

		const std::array<float, 3>& getPosition() { return pc.main->getPosition(); }

		PlayerCharacterOC* OCgetNewInstance() override;
		static PlayerCharacterOC* getPlayer();

		void shoot();

		void changeFirepower(const double& yscroll);

		ApplicationObject* getBody() { return &pc; }
		ActiveObject* OCloadActiveObject(const unsigned& collNumber) override
		{	
			InputsNS::Controls::setPlayer(main);
			return main;
		}

	};







}//NS
#endif
