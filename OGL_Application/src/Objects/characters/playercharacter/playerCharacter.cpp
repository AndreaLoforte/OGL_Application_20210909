#include<playerCharacter.h>
#include<assert.h>
#include<cameraManager.h>
#include<conversionLIB.h>
namespace myobjectNS {

	PlayerCharacter* PlayerCharacter::main;
	bool PlayerCharacter::mainIsSet;
	int PlayerCharacterOC::instanceCounter;
	PlayerCharacterOC* PlayerCharacterOC::main;
	bool PlayerCharacterOC::mainIsSet;


	int PlayerCharacter::instanceCounter;


	void PlayerCharacter::render(const fpcameraNS::Transformation& cam)
	{

		glUseProgram(shader_prog);
		glBindVertexArray(VAO);

		static GLuint physics_transf_location = glGetUniformLocation(shader_prog, "physics_transformation");
		static GLuint transf_matrix_location = glGetUniformLocation(shader_prog, "transformMatrix");
		glUniformMatrix4fv(physics_transf_location, 1, GL_FALSE, AOTrMatrix);
		glUniformMatrix4fv(transf_matrix_location, 1, GL_FALSE, cam.getPlayerCamera());
		glVertexAttrib4fv(2, AOcolor);

		/*se size < 2.0 non si vede il disegno!*/
		glPointSize(2.0);
		glDrawArrays(GL_POINTS, 0, 5000);
		glBindVertexArray(0);

	}

	void PlayerCharacter::update(const float& duration) {

		cameraTransformation(this);
		body->integrate(duration);
		calculateInternals();
		body->getGLTransform(AOTrMatrix);
		/*aggiorno la matrice di collision primitive*/


		static float i = 70.0;
		static constexpr int M = 100;

		AOcolor[0] = 0.0;//cos(i/M);
		AOcolor[1] = cos(i / M);
		AOcolor[2] = cos(i / M);// cos(i++ / M);
		AOcolor[3] = 0.8;// cos(i);


	}




	void PlayerCharacter::setRigidBodyParameters() {

		body->clearAccumulators();
		body->setInertiaTensor(Matrix3());
		body->setInverseInertiaTensor(Matrix3());
		body->setRotation(Vector3(0.0, .0, 0.0));
		body->setLinearDamping(1.0);
		body->setAngularDamping(1.0);
		body->setAwake(false);
		body->setAcceleration(Vector3::GRAVITY);
		body->setMass(10.0);
		body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
		body->setPrevPosition(AOposition[0], AOposition[1], AOposition[2]);
		body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
		body->_calculateTransformMatrix(body->transformMatrix, body->position, body->orientation);
	}


	void PlayerCharacter::OSsetParameters() {

		setRigidBodyParameters();
	}


	void PlayerCharacter::cameraTransformation(myobjectNS::ApplicationObject* obj)
	{
		lookat = conversionLibNS::conversionLibrary::floatArrayTostdArray(fpcameraNS::CameraManager::getActiveCamera().lookat);


		static float i = 0.0;
		static const int M = 10;
		//mymathlibNS::Quaternion orientation(fpcameraNS::CameraManager::getActiveCamera().getCameraOrientation());
		mymathlibNS::Quaternion orientation(fpcameraNS::CameraManager::getActiveCamera().getCameraOrientation());
		static const mymathlibNS::Quaternion orientation_offset(mymathlibNS::Quaternion::getQuaternionfromYAngle(90.0));
		orientation = mymathlibNS::Quaternion::getProduct(orientation_offset, orientation);

		mymathlibNS::Quaternion moving_offset(mymathlibNS::Quaternion::getQuaternionfromXAngle(i++ / M));
		orientation = mymathlibNS::Quaternion::getProduct(moving_offset, orientation);
		obj->setOrientation(orientation);

		std::array<float, 3> pos = fpcameraNS::CameraManager::getActiveCamera().getCamGLBCoords();
		obj->setPosition(pos);

		obj->setParameters();
	}


	void PlayerCharacter::reset() {
		setRigidBodyParameters();
	}


	PlayerCharacter* PlayerCharacter::getNewInstance()
	{
		if (mainIsSet)
			return main;
		else
		{
			main = new PlayerCharacter(shader_prog_name);
			main->AOinstanceNumber = instanceCounter;
			mainIsSet = true;
			return main;
		}



	}


	void PlayerCharacter::setParameters() { setRigidBodyParameters(); }
	PlayerCharacter * PlayerCharacter::getPlayer()
	{
		return getNewInstance();
	}



	void PlayerCharacter::create() {

		setShaders();


		//creo la prima circonferenza sul piano xy
		for (int j = 0; j < N; j++)
		{
			sphere[0][j][0] = radius * cos(j*theta_stride);
			sphere[0][j][1] = radius * sin(j*theta_stride);
			sphere[0][j][2] = radius * 0.0;
			sphere[0][j][3] = 1.0;
		}

		vmath::mat4 rotateCirconference;

		for (int i = 1; i < M; i++) {
			rotateCirconference = vmath::rotate(phi_stride*i, vmath::vec3(1.0, 0.0, 0.0));
			for (int j = 0; j < N; j++)
			{
				sphere[i][j][0] =
					rotateCirconference[0][0] * sphere[0][j][0] +
					rotateCirconference[0][1] * sphere[0][j][1] +
					rotateCirconference[0][2] * sphere[0][j][2] +
					rotateCirconference[0][3] * sphere[0][j][3];

				sphere[i][j][1] =
					rotateCirconference[1][0] * sphere[0][j][0] +
					rotateCirconference[1][1] * sphere[0][j][1] +
					rotateCirconference[1][2] * sphere[0][j][2] +
					rotateCirconference[1][3] * sphere[0][j][3];
				sphere[i][j][2] =
					rotateCirconference[2][0] * sphere[0][j][0] +
					rotateCirconference[2][1] * sphere[0][j][1] +
					rotateCirconference[2][2] * sphere[0][j][2] +
					rotateCirconference[2][3] * sphere[0][j][3];
				sphere[i][j][3] =
					rotateCirconference[3][0] * sphere[0][j][0] +
					rotateCirconference[3][1] * sphere[0][j][1] +
					rotateCirconference[3][2] * sphere[0][j][2] +
					rotateCirconference[3][3] * sphere[0][j][3];
			}
		}


		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		glCreateBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glNamedBufferStorage(VBO, sizeof(sphere), NULL, GL_DYNAMIC_STORAGE_BIT);

		static GLuint attribIndex = glGetAttribLocation(shader_prog, "sphere"),
			bindingIndex = 0, offset = 0, stride = 4 * sizeof(GLfloat), num_coord_per_vert = 4;


		glNamedBufferSubData(VBO, offset, sizeof(sphere), sphere);

		glVertexArrayAttribBinding(VAO, attribIndex, bindingIndex);
		glVertexArrayVertexBuffer(VAO, bindingIndex, VBO, offset, stride);
		glVertexArrayAttribFormat(VAO, attribIndex, num_coord_per_vert, GL_FLOAT, GL_FALSE, 0);
		glEnableVertexArrayAttrib(VAO, attribIndex);


	}




	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////


	


	PlayerCharacterOC* PlayerCharacterOC::OCgetNewInstance()
	{
		
		if (mainIsSet)
		{
			InputsNS::Controls::setPlayer(this);
			return main;
		}
			
		else
		{
			main = new PlayerCharacterOC();
			mainIsSet = true;
			InputsNS::Controls::setPlayer(this);
			return main;
		}
	}

	PlayerCharacterOC * PlayerCharacterOC::getPlayer()
	{
		if (mainIsSet)
			return main;
		else
		{
			main = new PlayerCharacterOC();
			mainIsSet = true;
			return main;
		}
	}




	void PlayerCharacterOC::shoot()
	{
		gun.shootTowards(pc.getPosition(), pc.lookat);
	}

	void PlayerCharacterOC::changeFirepower(const double& yscroll)
	{
		gun.changeFirepower(yscroll);
	}




	//void PlayerCharacterOC::create() {}
	//
	// 
	//}
	//

}
