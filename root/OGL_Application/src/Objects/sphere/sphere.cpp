#include<sphere.h>
#include<assert.h>


namespace myobjectNS{

int Sphere::instanceCounter;

	//constexpr GLuint Sphere::getNumberofPoints(){ return Sphere::puntiSfera; }

void Sphere::render(const fpcameraNS::Transformation& cam)
  {

		glUseProgram(shader_prog);
		glBindVertexArray(VAO);
		
		static GLuint physics_transf_location = glGetUniformLocation(shader_prog, "physics_transformation");
		static GLuint transf_matrix_location = glGetUniformLocation(shader_prog, "transformMatrix");
		glUniformMatrix4fv(physics_transf_location, 1, GL_FALSE, AOTrMatrix);
		glUniformMatrix4fv(transf_matrix_location, 1, GL_FALSE, cam.getPlayerCamera());
		glVertexAttrib4fv(2, AOcolor);

		glPointSize(1.0);
		glDrawArrays(GL_POINTS, 0, 5000);
		glBindVertexArray(0);

  }




void Sphere::render()
{

}



void Sphere::update(const float& duration){

   body->integrate(duration);

	/*funzione di collisionPrimitive : 
	aggiorna la matrice per il calcolo delle collisioni*/
	calculateInternals();
	
	
	//metto body->transformMatrix in physics_transformation
	body->getGLTransform(AOTrMatrix);
 
}




void Sphere::setRigidBodyParameters() {

	body->clearAccumulators();

	body->setInertiaTensor(Matrix3());
	body->setInverseInertiaTensor(Matrix3());
	//body->setOrientation(Quaternion(100.0, 1.0,.0,.0));
	body->setRotation(Vector3(5.0, .0, 0.0));


	body->setLinearDamping(1.0);
	body->setAngularDamping(1.0);

	body->setAwake(true);

	/* body->setInverseMass(10.0);*/
	body->setMass(10.0);

	body->setPosition(AOposition[0], AOposition[0], AOposition[0]);
	body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
	body->setVelocity(0.0, 50.0, 0.0);
	body->setAcceleration(Vector3::GRAVITY);

	body->_calculateTransformMatrix(body->transformMatrix,body->position,body->orientation);

}


void Sphere::setParameters() {

	setRigidBodyParameters();
}


void Sphere::create() {


	
	setShaders();
	
	
	//creo la prima circonferenza sul piano xy
	for (int j = 0; j < N; j++)
	{
		sphere[0][j][0] = radius * cos(j*theta_stride);
		sphere[0][j][1] = radius * sin(j*theta_stride);
		sphere[0][j][2] = radius * 0.0;
		sphere[0][j][3] =  1.0;
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



 
}

