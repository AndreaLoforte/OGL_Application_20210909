#ifndef APPOBJECT_H
#define APPOBJECT_H

#include<gl3w.h>
#include<string.h>
#include<fpcamera.h>
#include<vector>
#include<array>
#include<objectCollector.h>

class RigidBody;


namespace myobjectNS{


	class ApplicationObject {
		
	protected:
	public:
		/*dice a quale collettore appartiene questo oggetto*/
		std::string AOcollectorOwnershipID = "none";
		int AOCollisorID = 100;
		int AOinstanceNumber = 0;
		std::string AOinstanceID;
		int stride = 3.0;
		std::array<float, 3> AOshift{ 3.0,0.0,0.0 }, AOrot{ 3.0,0.0,0.0 };
		std::vector<float> AOsize;
		mymathlibNS::Quaternion AOorientation{ 1.0,0.0,0.0,0.0 };//quaternione unitario
		std::array<float, 3> AOposition;
		vmath::vec4 AOcolor{ 0.5,0.5,0.5,0.5 };
	

		bool readyToDraw = false;//parametro settato a true se ci sono tutte le condizioni per renderizzare l'ogetto (ad esempio sono stati compilati correttamente gli shaders)
		bool AOisOn = true;
	
		ApplicationObject(std::string objName = "ApplicationObject");
		ApplicationObject(ApplicationObject*);
		
		std::string AOobjectClass{ "GenericApplicationObject" };
		virtual int getCollisorID() { return AOCollisorID; }//elemento che permette al collisore di distinguere il tipo di oggetto
		void AOrender();
		virtual void render(const fpcameraNS::Transformation&) {}
		void AOreset() { this->reset(); }
		virtual void reset() {};
		void AOcreateObject() { this->create(); }
		virtual void create() {};
		virtual void AOsetShaders() {};
		void AOupdate(const float& duration);
		virtual void update(const float& duration) {}
		virtual void updatePhysics(const float& duration){}
		virtual void setParameters() {}
		void virtual AOtrX(int sign) ;
		void virtual AOtrY(int sign) ;
		void virtual AOtrZ(int sign) ;
		void virtual AOrotX(int sign) ;
		void virtual AOrotY(int sign);
		void virtual AOrotZ(int sign);
		void AOtr(const int& shiftX, const int& shiftY, const int& shiftZ);
		std::string AOprintInfos();
		virtual std::string showParameters() { return "No Infos to shows for this object"; }
		void AOgetNewInstance() { this->getNewInstance(); }
		virtual ApplicationObject* getNewInstance();
		//virtual collectorNS::ApplicationObjectCollector* getCollector();
		std::string AOgetInstanceID();
		virtual std::string getRBObjectID() { return "RigidBodyID undefined"; }
		std::string AOobjectName;
		vmath::mat4 AOTrMatrix = vmath::mat4::identity();
		void save(std::ofstream&);
		virtual void specializedSave(std::ofstream&){}
		virtual ApplicationObject* load(std::ifstream&, std::size_t, std::size_t);
		void setPosition(std::array<float, 3> pos) { AOposition = pos; }
		void setPosition(const GLfloat arr[3]) { AOposition[0] = arr[0]; AOposition[1] = arr[1]; AOposition[2] = arr[2]; }
		const std::array<float, 3>& getPosition() { return AOposition; }
		void setOrientation(mymathlibNS::Quaternion q) { AOorientation = q; }
		const mymathlibNS::Quaternion& getOrientation() { return AOorientation; }
		virtual void setColor(const vmath::vec4& col)
		{
			AOcolor[0] = col[0];
			AOcolor[1] = col[1];
			AOcolor[2] = col[2];
			AOcolor[3] = col[3];

		}
		virtual void changeColor(const std::vector<float>& col)
		{
			AOcolor[0] = col[0];
			AOcolor[1] = col[1];
			AOcolor[2] = col[2];
			AOcolor[3] = col[3];
		}
		virtual void setSize(const std::vector<float>& sz)
		{
			AOsize = sz;
		}
		virtual void makesound(){}
		/*funzione da sovrascrivere nelle final classes*/
		virtual int getHealt() { return -1; }
		virtual void setHealt(const int&){}
		virtual void switchPhysics(const bool v){}
		virtual RigidBody* getRB();
		void AOcanSleep(const bool v)
		{
			AOisOn = !v;
			DOcanSleep(v);
		}
		
		virtual void DOcanSleep(const bool&){}


		virtual void setCollectorOwnership(const std::string s)
		{
			AOcollectorOwnershipID = s;
		}

		
	};






}


#endif
