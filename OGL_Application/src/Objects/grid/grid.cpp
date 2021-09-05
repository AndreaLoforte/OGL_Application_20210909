#include<grid/grid.h>
#include<conversionLIB.h>

namespace myobjectNS {

	unsigned Grid::instanceCounter = 0;

	void Grid::render(const fpcameraNS::Transformation& cam)
	{

		glBindVertexArray(VAO);
		glUseProgram(shader_prog);
		glUniformMatrix4fv(10, 1, GL_FALSE, cam.getPlayerCamera());
		glUniformMatrix4fv(0, 1, GL_FALSE, AOTrMatrix);
		glUniform4fv(3, 1, AOcolor);
		glUniform1f(1, size[0]);
		glUniform1f(2, size[2]);
		/*glPointSize(20.0f);*/

		glLineWidth(1);
		glDrawArrays(GL_LINES, 0, 40);

		glBindVertexArray(-1);
	}

	void Grid::setPosition(float x, float y, float z) {
	}


	void Grid::create() {

		setShaders();
		glCreateVertexArrays(1,&VAO);
		
		//setRigidBodyParameters();
	}


	void Grid::setParameters() {

		setRigidBodyParameters();
	
		body->getGLTransform(AOTrMatrix);
		//body->transformMatrix = conversionLibNS::conversionLibrary::mat44Conversion_toMat43Cyclone(AOTrMatrix);
		/*aggiorno la matrice di collisionFinitePlane*/
		calculateInternals();

		vmath::mat4 TpositionM = mymathlibNS::transpose(AOTrMatrix);
		//Nella trasposizione le componenti di traslazione sono finiti sulla 3a colonna
		//poich� devo solo ruotare il vettore planeNormal, devo eliminare queste componenti.
		//poich� per� mi servono per il calcolo dell'offset le salvo su un vettore traslazione
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

		/*la sola componente di traslazione che genera offset � quella parallela alla normale al piano.
		Moltiplico il vettore traslazione per la normale (prodotto scalare)*/

		offset[0] = traslaz[0] * planeNormal[0];
		offset[1] = traslaz[1] * planeNormal[1];
		offset[2] = traslaz[2] * planeNormal[2];
		offsetNorm = offset[0] + offset[1] + offset[2];

		


	}


	void Grid::setRigidBodyParameters() {

		body->clearAccumulators();

		body->setInertiaTensor(Matrix3());
		body->setInverseInertiaTensor(Matrix3());
		//body->setOrientation(Quaternion(1.0, 0.0,.0,.0));
		body->setRotation(Vector3(0.0, .0, 0.0));


		body->setLinearDamping(1.0);
		body->setAngularDamping(1.0);

		body->setAwake(true);

		body->setMass(10000000000000.0);

		body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
		body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
		body->_calculateTransformMatrix(body->transformMatrix, body->position, body->orientation);

	}





}//namespace