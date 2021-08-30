#include<fpcamera.h>
#include<cameraManager.h>
#include<log.h>
#include<app.h>
#include<cameraLoader.h>
namespace fpcameraNS{
	using namespace textRendererNS;

	
	int               FlyingCamera::instanceCounter;
	const std::string FlyingCamera::camType{ FLYINGCAMERA };
	int               GroundCamera::instanceCounter;
	const std::string GroundCamera::camType{ GROUNDCAMERA };
	const std::string PanoramicCamera::camType{ PANORAMICCAMERA };
	int PanoramicCamera::instanceCounter;


	void Transformation::update()
	{
		this->setCamera();
		updateLookat();
		
		if (printInfos) 
		{/*use UserInterface or print helper to print any relevant infos*/		}
    }




	

	

	void Transformation::load(std::ifstream& in) {}

	void Transformation::save(std::ofstream& out) {

		out << saveloadNS::CameraSavings::CAMERATAG << std::endl;
		out << saveloadNS::CameraSavings::CAMERAID<< std::endl;
		out << getCameraType() << std::endl;
		out << saveloadNS::CameraSavings::CAMERAGLBCOORDS << std::endl;
		out << camForGLBcoords[0] << " ";
		out << camForGLBcoords[1] << " ";
		out << camForGLBcoords[2] << " ";
		out << std::endl;
		out << saveloadNS::CameraSavings::CAMERAORIENTATION << std::endl;
		out << camOrientation.w << " "
			<< camOrientation.x << " "
			<< camOrientation.y << " "
			<< camOrientation.z << std::endl;
		out << saveloadNS::CameraSavings::CAMERAMATRIX1<< std::endl;
		logNS::Logger::saveMatrix44(out, prev_M);
		out << std::endl;
		out << saveloadNS::CameraSavings::CAMERAMATRIX2<< std::endl;
		logNS::Logger::saveMatrix44(out, reverse_prev_x_rot);
		out << std::endl;
		out << saveloadNS::CameraSavings::ENDCAMERATAG << std::endl;
	}


	void Transformation::getCameraTransformation(vmath::mat4& mat) const
	{
		/*questo metodo sfrutta delle funzioni contenute in RigidBody ...
		sarebbe forse il caso di esternalizzare queste funzioni in una libreria ?!*/
		RigidBody *body = new RigidBody;

		body->setPosition(camForGLBcoords[0], camForGLBcoords[1], camForGLBcoords[3]);
		body->setOrientation(camOrientation.w, camOrientation.x, camOrientation.y, camOrientation.z);

		body->_calculateTransformMatrix(body->transformMatrix, body->position, body->orientation);
		body->getGLTransform(mat);

	}


	std::array<float, 3>  Transformation::getCamGLBCoords() const
	{

		static constexpr int sign = -1;
		array<float, 3> glbCoords{ sign*camForGLBcoords[0], sign*camForGLBcoords[1],sign*camForGLBcoords[2] };
		return glbCoords;
	}

	mymathlibNS::Quaternion  Transformation::getCameraOrientation() const
	{

		static constexpr int sign = -1;
		mymathlibNS::Quaternion orientation{ camOrientation.w, sign*camOrientation.x,sign*camOrientation.y,sign*camOrientation.z };
		return orientation;
	}
	





void Transformation::computeGlobalCoordsFromInverseM() {}



void Transformation::updateLookat() {


	lookat[0] = 0;
	lookat[1] = 0;
	lookat[2] = -1;


	lookat[0] =  M[0][2] * lookat[2];
	lookat[1] =  M[1][2] * lookat[2];
	lookat[2] =  M[2][2] * lookat[2];

}


void FlyingCamera::rotXcw(const GLfloat& xrot)
{
	static GLfloat prev_xrot = xrot;
	static GLfloat delta_xrot;
	delta_xrot = xrot - prev_xrot;
	xangle += delta_xrot;
	prev_xrot = xrot;
}

void FlyingCamera::rotYcw(const GLfloat& yrot)
{
	static GLfloat prev_yrot = yrot;
	static GLfloat delta_yrot;
	delta_yrot = yrot - prev_yrot;
	yangle += delta_yrot;
	prev_yrot = yrot;
}


void GroundCamera::rotXcw(const GLfloat& xrot)
{

	static GLfloat prev_xrot = xrot;
	static GLfloat delta_xrot;
	delta_xrot = xrot - prev_xrot;
	xangle += delta_xrot;
	prev_xrot = xrot;
}
void GroundCamera::rotYcw(const GLfloat& yrot)
{
	static GLfloat prev_yrot = yrot;
	static GLfloat delta_yrot;
	delta_yrot = yrot - prev_yrot;
	yangle += delta_yrot;
	prev_yrot = yrot;
}







void FlyingCamera::setCamera()
{
	typedef mymathlibNS::Quaternion Quaternion;

	delta_pos[0] = xtr - prev_pos[0];
	delta_pos[1] = ytr - prev_pos[1];
	delta_pos[2] = ztr - prev_pos[2];
	delta_rot[0] = xangle - prev_rot[0];
	delta_rot[1] = yangle - prev_rot[1];
	delta_rot[2] = zangle - prev_rot[2];

	if (std::abs(delta_pos[0]) > 0.01 || std::abs(delta_pos[1]) > 0.01 || std::abs(delta_pos[2]) > 0.01 ||
		std::abs(delta_rot[0]) > 0.01 || std::abs(delta_rot[1]) > 0.01 || std::abs(delta_rot[2]) > 0.01)
	{
		Quaternion rotX(mymathlibNS::Quaternion::getQuaternionfromXAngle(delta_rot[0]));
		Quaternion rotY(mymathlibNS::Quaternion::getQuaternionfromYAngle(delta_rot[1]));
		camOrientation = mymathlibNS::Quaternion::getProduct(camOrientation, rotX);
		camOrientation = mymathlibNS::Quaternion::getProduct(rotY, camOrientation);	
		/*costruisco la matrice di rotazione utilizzando il quaternione della camera e la funzione di cyclone*/
		 Matrix4 rotationMatrix_cyclone;
		 static const Vector3 pos_0(0.0, 0.0, 0.0);
		 mymathlibNS::calculateTransformMatrix(rotationMatrix_cyclone, pos_0, camOrientation);
		mymathlibNS::getGLTransform(rotationMatrix_cyclone, rot_m);

		/*moltiplico il vettore delta_pos per la matrice di rotazione per proiettarlo appropriatamente*/
		vmath::vec4 Dpos{ delta_pos[0], delta_pos[1], delta_pos[2],0.0 };
		Dpos = Dpos * rot_m;
		camForGLBcoords[0] += Dpos[0];
		camForGLBcoords[1] += Dpos[1];
		camForGLBcoords[2] += Dpos[2];

		Vector3 pos(camForGLBcoords[0], camForGLBcoords[1], camForGLBcoords[2]);
		mymathlibNS::Quaternion unitary(1.0, 0.0, 0.0, 0.0);
		Matrix4 translationMatrix_cyclone;
		mymathlibNS::calculateTransformMatrix(translationMatrix_cyclone, pos, unitary);
		mymathlibNS::getGLTransform(translationMatrix_cyclone, tr_m);

		M = rot_m*tr_m;
		PM = proj_mat * M;

		prev_pos[0] = xtr; prev_pos[1] = ytr; prev_pos[2] = ztr;
		prev_rot[0] = xangle; prev_rot[1] = yangle; prev_rot[2] = zangle;

	}

}

void PanoramicCamera::setCamera()
{
	delta_pos[0] = xtr - prev_pos[0];
	delta_pos[1] = ytr - prev_pos[1];
	delta_pos[2] = ztr - prev_pos[2];
	delta_rot[0] = xangle - prev_rot[0];
	delta_rot[1] = yangle - prev_rot[1];
	delta_rot[2] = zangle - prev_rot[2];

	if (std::abs(delta_pos[0]) > 0.01 || std::abs(delta_pos[1]) > 0.01 || std::abs(delta_pos[2]) > 0.01 ||
		std::abs(delta_rot[0]) > 0.01 || std::abs(delta_rot[1]) > 0.01 || std::abs(delta_rot[2]) > 0.01)
	{
		camForGLBcoords[0] += delta_pos[0];
		camForGLBcoords[1] += delta_pos[1];
		camForGLBcoords[2] += delta_pos[2];
		tr_m = vmath::translate(delta_pos[0], delta_pos[1], delta_pos[2]);

		mymathlibNS::Quaternion rotX(mymathlibNS::Quaternion::getQuaternionfromXAngle(delta_rot[0]));
		mymathlibNS::Quaternion rotY(mymathlibNS::Quaternion::getQuaternionfromYAngle(delta_rot[1]));

		/*ruoto orientamento epurato della rotazione X*/
		camOrientation = mymathlibNS::Quaternion::getProduct(rotY, camOrientation);
		camOrientation = mymathlibNS::Quaternion::getProduct(camOrientation, rotX);


		/*costruisco la matrice di rotazione utilizzando il quaternione della camera e la funzione di cyclone*/
		static const Vector3 pos_0(0.0, 0.0, 0.0);
		Matrix4 rotationMatrix_cyclone;
		mymathlibNS::calculateTransformMatrix(rotationMatrix_cyclone, pos_0, camOrientation);
		mymathlibNS::getGLTransform(rotationMatrix_cyclone, rot_m);

		Vector3 pos(camForGLBcoords[0], camForGLBcoords[1], camForGLBcoords[2]);
		mymathlibNS::Quaternion unitary(1.0, 0.0, 0.0, 0.0);
		Matrix4 translationMatrix_cyclone;
		mymathlibNS::calculateTransformMatrix(translationMatrix_cyclone, pos, unitary);
		mymathlibNS::getGLTransform(translationMatrix_cyclone, tr_m);

		M = tr_m* rot_m;
		PM = proj_mat * M;

		prev_pos[0] = xtr; prev_pos[1] = ytr; prev_pos[2] = ztr;
		prev_rot[0] = xangle; prev_rot[1] = yangle; prev_rot[2] = zangle;

	}


}





  
void GroundCamera::setCamera()
{

	typedef mymathlibNS::Quaternion Quaternion;

	delta_pos[0] = xtr - prev_pos[0];
	delta_pos[1] = ytr - prev_pos[1];
	delta_pos[2] = ztr - prev_pos[2];
	delta_rot[0] = xangle - prev_rot[0];
	delta_rot[1] = yangle - prev_rot[1];
	delta_rot[2] = zangle - prev_rot[2];

	if (std::abs(delta_pos[0]) > 0.01 || std::abs(delta_pos[1]) > 0.01 || std::abs(delta_pos[2]) > 0.01 ||
		std::abs(delta_rot[0]) > 0.01 || std::abs(delta_rot[1]) > 0.01 || std::abs(delta_rot[2]) > 0.01)
	{
		Quaternion rotX(mymathlibNS::Quaternion::getQuaternionfromXAngle(delta_rot[0]));
		Quaternion rotY(mymathlibNS::Quaternion::getQuaternionfromYAngle(delta_rot[1]));
		camOrientation = mymathlibNS::Quaternion::getProduct(camOrientation, rotX);
		camOrientation = mymathlibNS::Quaternion::getProduct(rotY, camOrientation);
		/*costruisco la matrice di rotazione utilizzando il quaternione della camera e la funzione di cyclone*/
		Matrix4 rotationMatrix_cyclone;
		static const Vector3 pos_0(0.0, 0.0, 0.0);
		mymathlibNS::calculateTransformMatrix(rotationMatrix_cyclone, pos_0, camOrientation);
		mymathlibNS::getGLTransform(rotationMatrix_cyclone, rot_m);

		/*moltiplico il vettore delta_pos per la matrice di rotazione per proiettarlo appropriatamente*/
		vmath::vec4 Dpos{ delta_pos[0], delta_pos[1], delta_pos[2],0.0 };
		Dpos = Dpos * rot_m;
		camForGLBcoords[0] += Dpos[0];
		camForGLBcoords[1] = height;
		camForGLBcoords[2] += Dpos[2];

		Vector3 pos(camForGLBcoords[0], camForGLBcoords[1], camForGLBcoords[2]);
		mymathlibNS::Quaternion unitary(1.0, 0.0, 0.0, 0.0);
		Matrix4 translationMatrix_cyclone;
		mymathlibNS::calculateTransformMatrix(translationMatrix_cyclone, pos, unitary);
		mymathlibNS::getGLTransform(translationMatrix_cyclone, tr_m);

		M = rot_m * tr_m;
		PM = proj_mat * M;

		prev_pos[0] = xtr; prev_pos[1] = ytr; prev_pos[2] = ztr;
		prev_rot[0] = xangle; prev_rot[1] = yangle; prev_rot[2] = zangle;

	}

}

void Transformation::resetAll() {

	xtr = default_pos[0];
	ytr = default_pos[1];
	ztr = default_pos[2];
	xangle = 0.0;
	yangle = 0.0;
	zangle = 0.0;
	camForGLBcoords[0] = default_pos[0];
	camForGLBcoords[1] = -default_pos[1];
	camForGLBcoords[2] = -default_pos[2];
	camForLCLcoords[0] = 0.0;
	camForLCLcoords[1] = 0.0;
	camForLCLcoords[2] = 0.0;
	lookat[0] = 0.0;
	lookat[1] = 0.0;
	lookat[2] = -1.0;
	M = vmath::mat4::identity();
	PM = vmath::mat4::identity();
	prev_M = vmath::mat4::identity();
	reverse_prev_tr = vmath::mat4::identity();
	reverse_prev_x_rot = vmath::mat4::identity();
	prev_pos[0] = 0;
	prev_pos[1] = 0;
	prev_pos[2] = 0;
	prev_rot[0] = 0;
	prev_rot[1] = 0;
	prev_rot[2] = 0;
	deltaS[0] = 0;
	deltaS[1] = 0;
	deltaS[2] = 0;
	delta_pos[0] = 0;
	delta_pos[1] = 0;
	delta_pos[2] = 0;
	delta_rot[0] = 0;
	delta_rot[1] = 0;
	delta_rot[2] = 0;
	x_rot_integral = 0;



}
  

}//namespace

