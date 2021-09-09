#include<surface/surface/surface.h>
#include<cameraManager.h>
#include<conversionLIB.h>
#include<vector>
namespace myobjectNS {

	unsigned Surface::instanceCounter = 0;


	void Surface::render(const fpcameraNS::Transformation& cam)
	{
		
		renderSurface();
		//renderCollisionPrimitive();

	}

	void Surface::renderSurface()
	{
		glUseProgram(shader_prog);
		glBindVertexArray(VAO);
		static GLuint modelviewMAttribLocation = glGetUniformLocation(shader_prog, "modelviewM");
		static GLuint transfMAttribLocation = glGetUniformLocation(shader_prog, "transfM");
		static GLuint colorAttribLoc = glGetUniformLocation(shader_prog, "color");
		glUniformMatrix4fv(modelviewMAttribLocation, 1, GL_FALSE, fpcameraNS::CameraManager::getActiveCamera().getPlayerCamera());
		glUniformMatrix4fv(transfMAttribLocation, 1, GL_FALSE, AOTrMatrix);
		glUniform4fv(colorAttribLoc, 1, AOcolor);
		glLineWidth(1);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

	}
	void Surface::renderCollisionPrimitive()
	{
		glUseProgram(shader_prog);
		glBindVertexArray(VAO);
		static GLuint modelviewMAttribLocation = glGetUniformLocation(shader_prog, "modelviewM");
		static GLuint transfMAttribLocation = glGetUniformLocation(shader_prog, "transfM");
		static GLuint colorAttribLoc = glGetUniformLocation(shader_prog, "color");
		glUniformMatrix4fv(modelviewMAttribLocation, 1, GL_FALSE, fpcameraNS::CameraManager::getActiveCamera().getPlayerCamera());
		glUniformMatrix4fv(transfMAttribLocation, 1, GL_FALSE, conversionLibNS::conversionLibrary::mat43Conversion_tovmath44T(CollisionPrimitive::transform));
		
		static float collisorColor[4]{ 1.0,1.0,1.0,.5};
		glUniform4fv(colorAttribLoc, 1, collisorColor);
		glLineWidth(1);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}


	void Surface::update(const float& duration) {

		body->integrate(duration);
		calculateInternals();
	}


	void Surface::setColor(float r, float g, float b, float a) {

		AOcolor[0] = r;
		AOcolor[1] = g;
		AOcolor[2] = b;
		AOcolor[3] = a;

	}


	

	void Surface::setRigidBodyParameters() {

		body->clearAccumulators();

		body->setInertiaTensor(Matrix3());
		body->setInverseInertiaTensor(Matrix3());
		//body->setOrientation(Quaternion(1.0, 0.0,.0,.0));
		body->setRotation(Vector3(0.0, .0, 0.0));


		body->setLinearDamping(1.0);
		body->setAngularDamping(1.0);

		body->setAwake(true);
		body->setMass(10000000000000.0);
	}




	void Surface::setParameters(){

		//////////////////////////////////////////////////////////////////////////
		body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
		body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
		body->_calculateTransformMatrix(body->transformMatrix, body->position, body->orientation);
		body->getGLTransform(AOTrMatrix);

		/*updating AOvertices*/
	/*	{
			
			AOvertices = mymathlibNS::vmatMatrix::getProduct(vertices, AOTrMatrix);
		}
	*/
		
		//body->transformMatrix = mymathlibNS::conversionLibrary::mat44Conversion_toMat43Cyclone(AOTrMatrix);
		/*aggiorno la matrice di collisionFinitePlane*/
		calculateInternals();

		vmath::mat4 TpositionM = mymathlibNS::transpose(AOTrMatrix);
		//Nella trasposizione le componenti di traslazione sono finiti sulla 3a colonna
		//poichè devo solo ruotare il vettore planeNormal, devo eliminare queste componenti.
		//poichè però mi servono per il calcolo dell'offset le salvo su un vettore traslazione

		


		vmath::vec4 traslaz(
			vmath::vec4(
				TpositionM[0][3],
				TpositionM[1][3],
				TpositionM[2][3],
				TpositionM[3][3]));

		TpositionM[0][3] = 0;
		TpositionM[1][3] = 0;
		TpositionM[2][3] = 0;
		TpositionM[3][3] = 0;

		planeNormal = vmath::vec4(0.0, 1.0, 0.0, 1.0);

		planeNormal = mymathlibNS::mat44vec4Product(TpositionM, planeNormal);
		normal[0] = planeNormal[0];
		normal[1] = planeNormal[1];
		normal[2] = planeNormal[2];

		/*la sola componente di traslazione che genera offset è quella parallela alla normale al piano.
		Moltiplico il vettore traslazione per la normale (prodotto scalare)*/

		offset[0] = traslaz[0] * planeNormal[0];
		offset[1] = traslaz[1] * planeNormal[1];
		offset[2] = traslaz[2] * planeNormal[2];
		offsetNorm = offset[0] + offset[1] + offset[2];

		

		setRigidBodyParameters();


	
	}


	void Surface::create() {
		
		GLfloat l1 = size[0], l2 = size[2];
	
		//il disegno sta sull'asse xz
		GLfloat  vertices_[6][4]{
			{-l1, 0.0f, l2, 1.0f},
			{-l1, 0.0f, -l2, 1.0f},
			{l1, 0.0f, -l2, 1.0f},
			{-l1, 0.0f, l2, 1.0f},
			{l1, 0.0f, l2, 1.0f},
			{l1, 0.0f, -l2, 1.0f}
		};
		

		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		glCreateBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glNamedBufferStorage(VBO, sizeof(vertices_), NULL, GL_DYNAMIC_STORAGE_BIT);

		GLuint attribIndex = glGetAttribLocation(shader_prog, "vertices");
		
		
		GLuint 
			bindingIndex = 0, 
			offset = 0, 
			stride = 4 * sizeof(GLfloat),
			num_coord_per_vert = 4;



		glNamedBufferSubData(VBO, offset, sizeof(vertices_), vertices_);

		glVertexArrayAttribBinding(VAO, attribIndex, bindingIndex);
		glVertexArrayVertexBuffer(VAO, bindingIndex, VBO, offset, stride);
		glVertexArrayAttribFormat(VAO, attribIndex, num_coord_per_vert, GL_FLOAT, GL_FALSE, 0);
		glEnableVertexArrayAttrib(VAO, attribIndex);





	}





}//namespace