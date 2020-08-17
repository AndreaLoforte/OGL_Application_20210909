#ifndef ENEMY_H
#define ENEMY_H

#include<baseObject.h>
#include<applicationDerivedObject.h>
#include<assert.h>
#include<physics.h>
#include<objectCollector.h>
#include<AI.h>
#include<gun.h>
#include<playerCharacter.h>


namespace myobjectNS {

	class Enemy final :public ObjectSphere, public BaseObject{
		
		friend class myphysicsNS::CollisorePolimorfo;
		friend class OCEnemy;
		GLuint VAO, VBO;
		static int instanceCounter;
		static constexpr GLuint N = 100, M = 50;/* 0.3*puntiSfera;*/
		GLfloat sphere[M][N][4];
		static constexpr GLfloat theta_stride = 360 / N;// 2 * 3.1415926535 / N;
		static constexpr GLfloat phi_stride = 360 / M;// 2 * 3.1415926535 / M;
		const float bodyMass = 1000;
	public:
		Enemy(std::string sh_prog_name) :
			ObjectSphere(sh_prog_name),
			BaseObject(sh_prog_name, "characters/enemy/") {
			AOcolor[0] = 1.0;
			AOcolor[0] = .5;
			AOcolor[0] = .5;
			AOcolor[0] = 1.0;

		}
		~Enemy() {

		}
		void clean() {}
		void update(const float&) override;
		void create()override;
		void render(const fpcameraNS::Transformation&) override;
		void render();
		void setRigidBodyParameters();
		void reset() override {
			setRigidBodyParameters();
		}
		
		void OSsetParameters() override;

		Enemy* getNewInstance() override {
			instanceCounter++;
			Enemy *s(new Enemy("enemy"));
			s->AOinstanceNumber = instanceCounter;
			return s; 
		}
		void setParameters() override { setRigidBodyParameters(); }
		


	};

	//////////////////////////////////////////////////////////////////77


	class EnemyOC final :public collectorNS::ActiveObject {

		friend class myphysicsNS::CollisorePolimorfo;
		/*tutti gli oggetti e i sottooggetti afferenti ad EnemyOC
		vanno nel container enemycoll*/
		collectorNS::AOcontainer enemycoll;
		Enemy enemy{ "enemy" };
		/*brain must be initialized after enemy otherwise
		its constructor will throw exception when using enemy methods*/
		aiNS::myfirstIA brain{ this };
		
		//collettore da costruire passandogli un contenitore
		OCGun gun{ &enemycoll };
		int healt = 100;
		std::array<float, 3> fireSpot;
	public:
		EnemyOC();
		~EnemyOC() {}
		void clean() {}
		void OCupdate(const float&) override;
		void canSleep(bool v) override;
		EnemyOC* OCgetNewInstance() override;
		void setParameters() override;		
		std::string getCollectorName() override { return collectorName; }
		Enemy* getBody() { return &enemy; }
		void setActivityGround(myobjectNS::SurfaceBoundaries* sb)override { brain.activityArea = sb; }
		myobjectNS::SurfaceBoundaries* getActivityGround()override { return brain.activityArea; }
		
	};






}//NS
#endif
