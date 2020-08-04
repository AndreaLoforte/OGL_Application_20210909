#ifndef FPCAMERA_H
#define FPCAMERA_H
#include<gl3w.h>
#include<glfw3.h>
#include<vmath.h>
#include<iostream>
#include<fstream>
#include<mymathlib.h>
#include<application.h>
#include<vector>
#include<log.h>
#include<saveloadhelper.h>

//namespace InputsNS{
//    class Controls;
//}

namespace logNS {
	class Logger;
}

namespace fpcameraNS{




 class Transformation {
   // friend InputsNS::Controls;
	public:
	std::string shader_name;
	GLuint camera_index = 0;
	bool printInfos = false;
	std::string cameraID;
	int instanceNumber;
	//LOCAL COORDINATES
    GLfloat xtr,ytr,ztr;
	GLfloat prev_pos[3]{0.0,0.0,0.0 };
	GLfloat prev_rot[3]{ 0.0,0.0,0.0 };
    GLfloat xangle,yangle,zangle;
	GLfloat xrad, yrad, zrad;
	//GLOBAL COORDINATES

	//TERNA SOLIDALE IN LOCAL COORDS
	GLfloat camForLCLcoords[3] = { 0.0,0.0,0.0 };
	//TERNA SOLIDALE IN GLOBAL COORDS
	float camForGLBcoords[3] = { 0.0,0.0,0.0 };
	mymathlibNS::Quaternion camOrientation{1.0,0.0,0.0,0.0};
	//DELTA SPOSTAMENTO (rispetto a sdr solidale camera)
	GLfloat deltaS[3] = { 0.0,0.0,0.0 };
	GLfloat lookat[3] = { 0.0,0.0,-1.0 };
	GLfloat delta_pos[3] = { 0.0,0.0,0.0 };
	GLfloat delta_rot[3] = { 0.0,0.0,0.0 };
	GLfloat x_rot_integral = 0;
	

    GLfloat tr_step = 3.0;
    GLfloat rot_step = 2.0;

	
        
    vmath::mat4 proj_mat;
    vmath::mat4 tr_m;
	vmath::mat4 prev_tr_m;
    vmath::mat4 reverse_prev_tr;
	vmath::mat4 reverse_prev_x_rot;
    vmath::mat4 rot_m ;
    vmath::mat4 M ;
	vmath::mat4 prev_M, inverseM;
    vmath::mat4 reverse_prev_M ;
	

	//MAIN TRANSFORMATION
    vmath::mat4 PM;
  
		//OTHER PARAMETER FOR VIEW SETTING
	  GLfloat perspective_degree, aspectRatio,nearP,farP;
	  static constexpr GLfloat default_pos[3] = {0.0f,-10.0f,-50.0f};
  
  //Transformation(Transformation const &) = delete;
	  
 public:
	 Transformation(std::string sh_name = "unspeciefied Transformation",
		 GLfloat xoff = default_pos[0], GLfloat yoff = default_pos[1], GLfloat zoff = default_pos[2],
		 GLFWwindow* window = Application::window, GLfloat deg = 45.0,
		 GLfloat aspect = Application::aspect, GLfloat nearPlane = .1, GLfloat farPlane = 10000.0) :
		 shader_name(sh_name),
		 perspective_degree(deg),
		 aspectRatio(aspect),
		 nearP(nearPlane),
		 farP(farPlane),
		 PM(vmath::mat4::identity()),
		 tr_m(vmath::mat4::identity()),
		 rot_m(vmath::mat4::identity()),
		 reverse_prev_tr(vmath::mat4::identity()),
		 reverse_prev_x_rot(vmath::mat4::identity()),
		 M(vmath::mat4::identity()),
		 prev_M(vmath::mat4::identity()),
		 prev_tr_m(vmath::mat4::identity()),
		 reverse_prev_M(vmath::mat4::identity())
	 {
		 if (nearP <= 0)
			 std::cerr << "ERROR: NEAR PLANE CANNOT BE <= 0" << std::endl;
		 nearP = .1f;
		 xtr = xoff; ytr = yoff; ztr = zoff;
		 xangle = 0.0; yangle = 0.0; zangle = 0.0;
		 xrad = 0; yrad = 0; zrad = 0;
		 camForGLBcoords[0] = default_pos[0];
		 camForGLBcoords[1] = -default_pos[1];
		 camForGLBcoords[2] = -default_pos[2];
		 lookat[0] = 0.0;
		 lookat[1] = 0.0;
		 lookat[2] =-1.0;

		 proj_mat = vmath::perspective(perspective_degree, aspectRatio, nearP, farP);
		 glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

	 }


    ~Transformation(){}
    
	 bool hasMoved = false;
    //fpCamera member methods for mouse input
	 inline void rotXcw(const GLfloat& xpos) 
	 { 
		 static GLfloat prev_xpos = xpos;
		 static GLfloat delta_xpos;
		 delta_xpos = xpos - prev_xpos;
		 xangle += delta_xpos;
		 prev_xpos = xpos;
		hasMoved = true; 
	 }
	 inline void rotYcw(const GLfloat& ypos) 
	 { 
		 static GLfloat prev_ypos = ypos;
		 static GLfloat delta_ypos;
		 delta_ypos = ypos - prev_ypos;
		 yangle += delta_ypos; 
		 prev_ypos = ypos;
		 hasMoved = true; 
	 }

	 //fpCamera member methods for keyboards input
	 inline void changeTranslationSpeed(int i) 
	 { 
		 if(i>0)
			tr_step *= i * 3; 
		 if (i < 0)
			 tr_step *= 0.333;
	 }
	 inline void moveFw() { ztr += tr_step; hasMoved = true; }
     inline void moveBw(){ ztr -= tr_step; hasMoved = true;}
     inline void moveLt(){ xtr += tr_step; hasMoved = true;}
     inline void moveRt(){ xtr -= tr_step;hasMoved = true;}
     inline void rotXccw(){ xangle -= rot_step;hasMoved = true;}
     inline void rotXcw(){ xangle += rot_step; hasMoved = true;}
     inline void rotYccw(){ yangle -= rot_step; hasMoved = true;}
     inline void rotYcw(){ yangle += rot_step; hasMoved = true;}
     inline void moveUp(){ytr += tr_step; hasMoved = true;}//2
     inline void moveDown(){ ytr -= tr_step; hasMoved = true;}//1
     //inline void moveBy(const float xshift, const float yshift, const float zshift){xtr += xshift; ytr += yshift; ztr += zshift;}
     inline void warn(){std::cerr<<"inputs.cpp::key_callback | pointer to cam not initialized"<<std::endl;}
	 inline void switchPrintInfos() {
		 if (printInfos)
			 printInfos = false;
		 else
			 printInfos = true;
	 }
	 void BOsetCamera() {
		 this->setCamera();
	 };

	 virtual void setCamera(){}
	
	const vmath::mat4& getPlayerCamera()const { return PM; } 
	void computeGlobalCoords();
	void computeGlobalCoordsFromInverseM();
	void updateLookat();
	void update();
	void resetAll();
	void save(std::ofstream&);
	virtual string getCameraType() { return "genericTransformation"; }
	static void load(std::ifstream&);
	/*questo metodo restituisce la trasformazione della camera
	ovvero un oggetto a cui venga data la matrice di trasformazione ritornata da 
	questo metodo, si trova nella esatta posizione della camera.*/
	
	void getCameraTransformation(vmath::mat4& mat) const;
	mymathlibNS::Quaternion getCameraOrientation() const;
	
	/*funzione che ritorna inverso della posizione della camera*/
	std::array<float, 3>  getCamGLBCoords() const;

};

static const std::string FLYINGCAMERA{ "FLYINGCAMERA" };
static const std::string GROUNDCAMERA{ "GROUNDCAMERA" };
static const std::string PANORAMICCAMERA{ "PANORAMICCAMERA" };



/*FLYING CAMERA*/
class FlyingCamera : public Transformation {
public:
	static const std::string camType;//"FLYINGCAMERA"
	static int instanceCounter;

	FlyingCamera() : Transformation() {
		instanceNumber = instanceCounter++;
		cameraID = camType + "_" + std::to_string(instanceNumber);
	}
	void setCamera() override ;
	string getCameraType() override { return camType; }
	
	

};


/*GROUND CAMERA*/
class GroundCamera : public Transformation {
public:
	static const std::string camType;
	static int instanceCounter;
	const int height = -5.0;

	GroundCamera() : Transformation() {
		instanceNumber = instanceCounter++;
		cameraID = camType + "_" + std::to_string(instanceNumber);
	}
	void setCamera() override;
	string getCameraType() override { return camType; }
};


/*PANORAMIC CAMERA*/
class PanoramicCamera : public Transformation {
public:
	static const std::string camType;
	static int instanceCounter;

	PanoramicCamera() : Transformation() {
		instanceNumber = instanceCounter++;
		cameraID = camType + "_" + std::to_string(instanceNumber);
	}
	void setCamera() override ;
	string getCameraType() override { return camType; }
	
	

};


 










}//namespace

#endif
