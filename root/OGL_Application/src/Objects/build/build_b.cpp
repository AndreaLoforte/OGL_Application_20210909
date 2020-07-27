#include<build_b.h>

namespace myobjectNS {

	void Build_b::render(const fpcameraNS::Transformation& cam)
	{
		
		glUseProgram(shader_prog);
		glBindVertexArray(VAO);
		
		GLuint modelviewT_loc = glGetUniformLocation(shader_prog, "modelviewT");
		GLuint physicsT_loc = glGetUniformLocation(shader_prog, "physicsT");


		glUniform4fv(0, 1, AOcolor);
		glUniformMatrix4fv(physicsT_loc, 1, GL_FALSE, AOTrMatrix);
		glUniformMatrix4fv(modelviewT_loc, 1, GL_FALSE, cam.getPlayerCamera());
		

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);//unbind current vao
		
		
		
	}



	void Build_b::update(const float& duration){

		body->integrate(duration);
		CollisionPrimitive::calculateInternals();

		//metto body->transformMatrix in physics_transformation
		body->getGLTransform(AOTrMatrix);

		//VOGLIO VEDERE LA MATRICE DI TRASFORMAZIONE FISICA E QUELLA DEL COLLISORE
	/*	TextRendererTest::printMatrix44(physics_transformation, "build : physicsT");
		TextRendererTest::printMatrix43(CollisionPrimitive::transform, "build : Transform");*/

	}


	void Build_b::setParameters() {

		setRigidBodyParameters();

	}
	


	void Build_b::setRigidBodyParameters() {

		body->clearAccumulators();

		body->setInertiaTensor(Matrix3());
		body->setInverseInertiaTensor(Matrix3());
		body->setOrientation(Quaternion(1.0, 0.0,.0,.0));
		body->setRotation(Vector3(0.0, 0.0, 0.0));

		body->setLinearDamping(1.0);
		body->setAngularDamping(1.0);

		body->setAwake(false);

		body->setInverseMass(.1);
		body->setMass(10.0);



		body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
		body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
		body->setVelocity(0.0, 0.0, 0.0);

		body->setAcceleration(Vector3::GRAVITY);

		body->_calculateTransformMatrix(body->transformMatrix,body->position,body->orientation);
		CollisionPrimitive::calculateInternals();

	}

	void Build_b::setPosition(const std::array<float, 3>& pos) {

		/*position[0] = x;
		position[1] = y;
		position[2] = z;*/

	}





	void Build_b::create() {

		GLfloat w = L1/2, h = L2/2, d = L3/2, s = 1.0f;
		using namespace vmath;
		const vec4 vertices[N] =
		{
			//square base
			vec4(-w, -h, d, s),
			vec4(w, -h, d, s),
			vec4(-w, -h, -d, s),
			vec4(w, -h, d, s),
			vec4(w, -h, -d, s),
			vec4(-w, -h, -d, s),
			//wquare top
			vec4(-w, h, d, s),
			vec4(w, h, d, s),
			vec4(-w, h, -d, s),
			vec4(w, h, d, s),
			vec4(w, h, -d, s),
			vec4(-w, h, -d, s),
			//back side
			vec4(w, h, -d, s),
			vec4(-w, h, -d, s),
			vec4(-w, -h, -d, s),
			vec4(-w, -h, -d, s),
			vec4(w, -h, -d, s),
			vec4(w, h, -d, s),
			//front side
			vec4(w, h, d, s),
			vec4(-w, h, d, s),
			vec4(-w, -h, d, s),
			vec4(-w, -h, d, s),
			vec4(w, -h, d, s),
			vec4(w, h, d, s),
			//right side
			vec4(-w, h, d, s),
			vec4(-w, h, -d, s),
			vec4(-w, -h, d, s),
			vec4(-w, -h, d, s),
			vec4(-w, -h, -d, s),
			vec4(-w, h, -d, s),
			//left side
			vec4(w, h, d, s),
			vec4(w, h, -d, s),
			vec4(w, -h, d, s),
			vec4(w, -h, d, s),
			vec4(w, -h, -d, s),
			vec4(w, h, -d, s)
		};


		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glCreateBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glNamedBufferStorage(buffer, sizeof(vertices), NULL, GL_DYNAMIC_STORAGE_BIT);


		setShaders();
		GLuint attribIndex = glGetAttribLocation(shader_prog, "vertices");
		GLuint bindingIndex = 0, offset = 0, stride = 4 * sizeof(GLfloat), num_coord_per_vert = 4;

		glNamedBufferSubData(buffer, offset, sizeof(vertices), vertices);

		glVertexArrayAttribBinding(VAO, attribIndex, bindingIndex);
		glVertexArrayVertexBuffer(VAO, bindingIndex, buffer, offset, stride);
		glVertexArrayAttribFormat(VAO, attribIndex, num_coord_per_vert, GL_FLOAT, GL_FALSE, 0);
		glEnableVertexArrayAttrib(VAO, attribIndex);


	}













}



