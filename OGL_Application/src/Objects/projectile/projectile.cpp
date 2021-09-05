#include<projectile/projectile.h>
#include<assert.h>
#include<cameraManager.h>
#include<conversionLIB.h>

namespace myobjectNS{


	

	void Projectile::render(const fpcameraNS::Transformation& cam)
	{
		glBindVertexArray(VAO);
		glUseProgram(shader_prog);
		glUniformMatrix4fv(2, 1, GL_FALSE, AOTrMatrix);
		glUniformMatrix4fv(1, 1, GL_FALSE, cam.getPlayerCamera());
		glPointSize(3.0);
		glDrawArrays(GL_POINTS, 0, 700);
		glBindVertexArray(0);


	}





void Projectile::update(const float & duration){
	
	body->integrate(duration);
	calculateInternals();
	//metto body->transformMatrix in physics_transformation
	body->getGLTransform(AOTrMatrix);

}





/*funzione che spara il proiettile avente come origine una posizione generica
nella direzione specificata (usato per enemy)*/
void Projectile::shoot(const std::array<float,3>& fireSpot,const std::array<float,3>& direction) {

	typedef conversionLibNS::conversionLibrary ConversionLib;
	typedef mymathlibNS::stdLibHelper stdLibHelper;

	body->clearAccumulators();
	body->setInertiaTensor(Matrix3());
	body->setInverseInertiaTensor(Matrix3());
	
	fireSpotShift = mymathlibNS::stdLibHelper::array3fProd1s(direction, fireSpotShiftModule);

	body->prevPosition = 
		ConversionLib::stdArrayToCycloneVec3(
		stdLibHelper::array3fSum(fireSpot, fireSpotShift));

	body->setPosition(body->prevPosition);
	body->_calculateTransformMatrix(body->transformMatrix, body->position, body->orientation);
	calculateInternals();
	body->getGLTransform(AOTrMatrix);


	velocity[0] =direction[0] * vel_module;
	velocity[1] =direction[1] * vel_module;
	velocity[2] =direction[2] * vel_module;

	body->setLinearDamping(1.0);
	body->setAngularDamping(0.0);
	body->setMass(1.0);
	body->setAwake(true);

	body->setVelocity(velocity[0], velocity[1], velocity[2]);
	body->setAcceleration(Vector3::GRAVITY);


}




void Projectile::setRigidBodyParameters() {
	const fpcameraNS::Transformation *cam = &fpcameraNS::CameraManager::getActiveCamera();
	
	body->clearAccumulators();
	body->setInertiaTensor(Matrix3());
	body->setInverseInertiaTensor(Matrix3());
	
	AOposition[0] = cam->camForGLBcoords[0];
	AOposition[1] = cam->camForGLBcoords[1];
	AOposition[2] = cam->camForGLBcoords[2];

	AOorientation[0] = cam->camOrientation.w;
	AOorientation[1] = cam->camOrientation.x;
	AOorientation[2] = cam->camOrientation.y;
	AOorientation[3] = cam->camOrientation.z;
	

	body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
	body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);

	body->_calculateTransformMatrix(body->transformMatrix, body->position, body->orientation);
	//metto body->transformMatrix in physics_transformation
	body->getGLTransform(AOTrMatrix);

	body->setLinearDamping(1.0);
	body->setAngularDamping(0.0);
	body->setMass(1.0);
	body->setAwake(true);

}

 

void Projectile::create() {

		setShaders();
		
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glVertexAttrib1f(3, radius);


}


 
 void Projectile::render()
 {

 }





 

    
}

