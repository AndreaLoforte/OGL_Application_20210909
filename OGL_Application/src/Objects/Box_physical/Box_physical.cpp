#include<Box_physical.h>

namespace myobjectNS {

	void Box_physical::render(const fpcameraNS::Transformation& cam)
	{
		
		glUseProgram(shader_prog);
		glBindVertexArray(VAO);
		
		GLuint modelviewT_attrib_loc = glGetUniformLocation(shader_prog, "modelviewT");
		GLuint AOTrMatrix_attrib_loc = glGetUniformLocation(shader_prog, "AOTrMatrix");


		glUniform4fv(0, 1, AOcolor);
		glUniformMatrix4fv(AOTrMatrix_attrib_loc, 1, GL_FALSE, AOTrMatrix);
		glUniformMatrix4fv(modelviewT_attrib_loc, 1, GL_FALSE, cam.getPlayerCamera());
		

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);//unbind current vao
		
		
		
	}



	void Box_physical::update(const float& duration){

		/*body->integrate(duration);
		CollisionPrimitive::calculateInternals();*/

		//metto body->transformMatrix in physics_transformation
		body->getGLTransform(AOTrMatrix);

	}


	void Box_physical::setParameters() {

		setRigidBodyParameters();
		create();

	}

	void Box_physical::setRigidBodyParameters() {

		body->clearAccumulators();

		body->setInertiaTensor(Matrix3());
		body->setInverseInertiaTensor(Matrix3());
		body->setOrientation(Quaternion(1.0, 0.0,.0,.0));
		body->setRotation(Vector3(0.0, 0.0, 0.0));

		body->setLinearDamping(1.0);
		body->setAngularDamping(1.0);

		body->setAwake(true);

		body->setInverseMass(.1);
		body->setMass(10.0);



		body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
		body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
		body->setVelocity(0.0, 0.0, 0.0);

		body->setAcceleration(Vector3::GRAVITY);

		/*la funzione _calculateTransformMatrix va a settare la matrice body->transformMatrix
		in base ai vettori position e orientation. Questa matrice viene utilizzata in tutta la parte fisica
		ma non può essere inviata allo shader (non è il formato adatto per openGL). Pertanto si utilizza
		la funzione getGLTransform per scrivere su AOTrMatrix la matrice da inviare allo shader per
		trasformare il disegno*/
		body->_calculateTransformMatrix(body->transformMatrix,body->position,body->orientation);
		body->getGLTransform(AOTrMatrix);
		CollisionPrimitive::calculateInternals();

	}

	void Box_physical::setPosition(const std::array<float, 3>& pos) {

		/*position[0] = x;
		position[1] = y;
		position[2] = z;*/

	}





	void Box_physical::create() {

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



