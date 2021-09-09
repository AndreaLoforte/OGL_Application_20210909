#include<sphere/sphere/sphere.h>
#include<assert.h>


namespace myobjectNS{

int Sphere::instanceCounter;






void Sphere::render(){}



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
	body->setRotation(Vector3(0.0, .0, 0.0));


	body->setLinearDamping(1.0);
	body->setAngularDamping(1.0);

	body->setAwake(true);

	/* body->setInverseMass(10.0);*/
	body->setMass(10.0);

	body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
	body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
	body->setVelocity(0.0, 0.0, 0.0);
	body->setAcceleration(Vector3::GRAVITY);

	body->_calculateTransformMatrix(body->transformMatrix,body->position,body->orientation);
	body->getGLTransform(AOTrMatrix);

}


void Sphere::setParameters() {

	setRigidBodyParameters();
}


void Sphere::create() {
	
	
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


	static GLfloat sphere2[M][N][4];
	/* il primo indice indica la circonferenza (da 0 a M)
	il secondo il vertice (da 0 a N punti per una circonferenza)
	il terzo la coordinata (x,y,z,w)*/
	/*prendo i primi due punti della circonferenza 1 e poi il terzo della circonferenza 2*/


	bool clockwise = false, first_triangle = true;
	int n = 0;
	int x, y;
	//for (int j = 0; j < N;j++)
	//{
	//
	//		if (first_triangle) 
	//		{
	//			first_triangle = false;

	//			for (int l = j; l < j + 3; l++)
	//			{
	//				if (l == j + 2)
	//				{
	//					sphere2[0][l][0] = sphere[1][l - 1][0];
	//					sphere2[0][l][1] = sphere[1][l - 1][1];
	//					sphere2[0][l][2] = sphere[1][l - 1][2];
	//					sphere2[0][l][3] = sphere[1][l - 1][3];

	//					logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 1) + " " + std::to_string(0));
	//					logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 1) + " " + std::to_string(1));
	//					logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 1) + " " + std::to_string(2));
	//					logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 1) + " " + std::to_string(3));
	//					logNS::Logger::writeLog("\n");
	//				}
	//				else 
	//				{
	//					sphere2[0][l][0] = sphere[0][l][0];
	//					sphere2[0][l][1] = sphere[0][l][1];
	//					sphere2[0][l][2] = sphere[0][l][2];
	//					sphere2[0][l][3] = sphere[0][l][3];

	//					logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l) + " " + std::to_string(0));
	//					logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l) + " " + std::to_string(1));
	//					logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l) + " " + std::to_string(2));
	//					logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l) + " " + std::to_string(3));

	//					logNS::Logger::writeLog("\n");

	//				}
	//			}
	//			logNS::Logger::writeLog("AAAAAAAAAAAAAA\n");
	//		}
	//		else {
	//			if (clockwise == false)
	//			{
	//				clockwise = true;

	//				for (int l = j; l < j + 3; l++)
	//				{
	//					if (l >= j + 1)
	//					{
	//						sphere2[0][l + 1][0] = sphere[0][l - 1-n][0];
	//						sphere2[0][l + 1][1] = sphere[0][l - 1-n][1];
	//						sphere2[0][l + 1][2] = sphere[0][l - 1-n][2];
	//						sphere2[0][l + 1][3] = sphere[0][l - 1-n][3];



	//						logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l - 1-n) + " " + std::to_string(0));
	//						logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l - 1-n) + " " + std::to_string(1));
	//						logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l - 1-n) + " " + std::to_string(2));
	//						logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l - 1-n) + " " + std::to_string(3));
	//						logNS::Logger::writeLog("\n");

	//					}
	//					else
	//					{/*entro qui solo 1 volta*/
	//						sphere2[0][l + 1][0] = sphere[1][l-n][0];
	//						sphere2[0][l + 1][1] = sphere[1][l-n][1];
	//						sphere2[0][l + 1][2] = sphere[1][l-n][2];
	//						sphere2[0][l + 1][3] = sphere[1][l-n][3];



	//						logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l-n) + " " + std::to_string(0));
	//						logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l-n) + " " + std::to_string(1));
	//						logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l-n) + " " + std::to_string(2));
	//						logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l-n) + " " + std::to_string(3));
	//						logNS::Logger::writeLog("\n");
	//					}
	//				}
	//				logNS::Logger::writeLog("BBBBBBBBBBBBBBB\n");
	//			}
	//			else {/*is not first triangle*/
	//					clockwise = false;

	//					for (int l = j; l < j + 3; l++) 
	//					{
	//						if (l >= j + 1)
	//						{
	//							sphere2[0][l + 1][0] = sphere[1][l - 2-n][0];
	//							sphere2[0][l + 1][1] = sphere[1][l - 2-n][1];
	//							sphere2[0][l + 1][2] = sphere[1][l - 2-n][2];
	//							sphere2[0][l + 1][3] = sphere[1][l - 2-n][3];



	//							logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 2-n) + " " + std::to_string(0));
	//							logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 2-n) + " " + std::to_string(1));
	//							logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 2-n) + " " + std::to_string(2));
	//							logNS::Logger::writeLog("ilk : " + std::to_string(1) + "  " + std::to_string(l - 2-n) + " " + std::to_string(3));
	//							logNS::Logger::writeLog("\n");

	//						}
	//						else 
	//						{/*entro qui solo 1 volta*/
	//							sphere2[0][l + 1][0] = sphere[0][l-n][0];
	//							sphere2[0][l + 1][1] = sphere[0][l-n][1];
	//							sphere2[0][l + 1][2] = sphere[0][l-n][2];
	//							sphere2[0][l + 1][3] = sphere[0][l-n][3];



	//							logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l-n) + " " + std::to_string(0));
	//							logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l-n) + " " + std::to_string(1));
	//							logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l-n) + " " + std::to_string(2));
	//							logNS::Logger::writeLog("ilk : " + std::to_string(0) + "  " + std::to_string(l-n) + " " + std::to_string(3));
	//							logNS::Logger::writeLog("\n");
	//						}

	//					}
	//					logNS::Logger::writeLog("CCCCCCCCCCCCCCCCCCC\n");
	//					++n;
	//				}
	//			}
	//}
	//	

	sphere2[0][0][0] = sphere[0][0][0];    sphere2[0][3][0] = sphere[1][1][0];   sphere2[0][6][0] = sphere[0][2][0];
	sphere2[0][0][1] = sphere[0][0][1];	   sphere2[0][3][1] = sphere[1][1][1];	 sphere2[0][6][1] = sphere[0][2][1];
	sphere2[0][0][2] = sphere[0][0][2];	   sphere2[0][3][2] = sphere[1][1][2];	 sphere2[0][6][2] = sphere[0][2][2];
	sphere2[0][0][3] = sphere[0][0][3];	   sphere2[0][3][3] = sphere[1][1][3];	 sphere2[0][6][3] = sphere[0][2][3];

	sphere2[0][1][0] = sphere[0][1][0];	   sphere2[0][4][0] = sphere[0][1][0];	 sphere2[0][7][0] = sphere[1][1][0];
	sphere2[0][1][1] = sphere[0][1][1];	   sphere2[0][4][1] = sphere[0][1][1];	 sphere2[0][7][1] = sphere[1][1][1];
	sphere2[0][1][2] = sphere[0][1][2];	   sphere2[0][4][2] = sphere[0][1][2];	 sphere2[0][7][2] = sphere[1][1][2];
	sphere2[0][1][3] = sphere[0][1][3];	   sphere2[0][4][3] = sphere[0][1][3];	 sphere2[0][7][3] = sphere[1][1][3];

	sphere2[0][2][0] = sphere[1][1][0];	   sphere2[0][5][0] = sphere[0][2][0];	 sphere2[0][8][0] = sphere[1][2][0];
	sphere2[0][2][1] = sphere[1][1][1];	   sphere2[0][5][1] = sphere[0][2][1];	 sphere2[0][8][1] = sphere[1][2][1];
	sphere2[0][2][2] = sphere[1][1][2];	   sphere2[0][5][2] = sphere[0][2][2];	 sphere2[0][8][2] = sphere[1][2][2];
	sphere2[0][2][3] = sphere[1][1][3];	   sphere2[0][5][3] = sphere[0][2][3];	 sphere2[0][8][3] = sphere[1][2][3];
	/********3333333333**/				   /*******6666666666***/				 /*****99999999999*****/
	
	sphere2[0][9][0] = sphere[1][2][0];    sphere2[0][12][0] = sphere[0][3][0];   sphere2[0][15][0] = sphere[1][3][0];
	sphere2[0][9][1] = sphere[1][2][1];	   sphere2[0][12][1] = sphere[0][3][1];	  sphere2[0][15][1] = sphere[1][3][1];
	sphere2[0][9][2] = sphere[1][2][2];	   sphere2[0][12][2] = sphere[0][3][2];	  sphere2[0][15][2] = sphere[1][3][2];
	sphere2[0][9][3] = sphere[1][2][3];	   sphere2[0][12][3] = sphere[0][3][3];	  sphere2[0][15][3] = sphere[1][3][3];

	sphere2[0][10][0] = sphere[0][2][0];   sphere2[0][13][0] = sphere[1][2][0];	  sphere2[0][16][0] = sphere[0][3][0];
	sphere2[0][10][1] = sphere[0][2][1];   sphere2[0][13][1] = sphere[1][2][1];	  sphere2[0][16][1] = sphere[0][3][1];
	sphere2[0][10][2] = sphere[0][2][2];   sphere2[0][13][2] = sphere[1][2][2];	  sphere2[0][16][2] = sphere[0][3][2];
	sphere2[0][10][3] = sphere[0][2][3];   sphere2[0][13][3] = sphere[1][2][3];	  sphere2[0][16][3] = sphere[0][3][3];

	sphere2[0][11][0] = sphere[0][3][0];   sphere2[0][14][0] = sphere[1][3][0];	  sphere2[0][17][0] = sphere[0][4][0];
	sphere2[0][11][1] = sphere[0][3][1];   sphere2[0][14][1] = sphere[1][3][1];	  sphere2[0][17][1] = sphere[0][4][1];
	sphere2[0][11][2] = sphere[0][3][2];   sphere2[0][14][2] = sphere[1][3][2];	  sphere2[0][17][2] = sphere[0][4][2];
	sphere2[0][11][3] = sphere[0][3][3];   sphere2[0][14][3] = sphere[1][3][3];	  sphere2[0][17][3] = sphere[0][4][3];
	/********12121212***/				   /*********15151515**/				  /***********181818*/
	
	sphere2[0][18][0] = sphere[0][4][0];   sphere2[0][21][0] = sphere[1][4][0];  sphere2[0][24][0] = sphere[0][5][0];
	sphere2[0][18][1] = sphere[0][4][1];   sphere2[0][21][1] = sphere[1][4][1];	 sphere2[0][24][1] = sphere[0][5][1];
	sphere2[0][18][2] = sphere[0][4][2];   sphere2[0][21][2] = sphere[1][4][2];	 sphere2[0][24][2] = sphere[0][5][2];
	sphere2[0][18][3] = sphere[0][4][3];   sphere2[0][21][3] = sphere[1][4][3];	 sphere2[0][24][3] = sphere[0][5][3];

	sphere2[0][19][0] = sphere[1][3][0];   sphere2[0][22][0] = sphere[0][4][0];	 sphere2[0][25][0] = sphere[1][4][0];
	sphere2[0][19][1] = sphere[1][3][1];   sphere2[0][22][1] = sphere[0][4][1];	 sphere2[0][25][1] = sphere[1][4][1];
	sphere2[0][19][2] = sphere[1][3][2];   sphere2[0][22][2] = sphere[0][4][2];	 sphere2[0][25][2] = sphere[1][4][2];
	sphere2[0][19][3] = sphere[1][3][3];   sphere2[0][22][3] = sphere[0][4][3];	 sphere2[0][25][3] = sphere[1][4][3];

	sphere2[0][20][0] = sphere[1][4][0];   sphere2[0][23][0] = sphere[0][5][0];	 sphere2[0][26][0] = sphere[1][5][0];
	sphere2[0][20][1] = sphere[1][4][1];   sphere2[0][23][1] = sphere[0][5][1];	 sphere2[0][26][1] = sphere[1][5][1];
	sphere2[0][20][2] = sphere[1][4][2];   sphere2[0][23][2] = sphere[0][5][2];	 sphere2[0][26][2] = sphere[1][5][2];
	sphere2[0][20][3] = sphere[1][4][3];   sphere2[0][23][3] = sphere[0][5][3];	 sphere2[0][26][3] = sphere[1][5][3];
	/***********21*/				   /***********24*/					 /***********27*/

	sphere2[0][27][0] = sphere[1][5][0];   sphere2[0][30][0] = sphere[0][6][0];  sphere2[0][33][0] = sphere[1][6][0];
	sphere2[0][27][1] = sphere[1][5][1];   sphere2[0][30][1] = sphere[0][6][1];	 sphere2[0][33][1] = sphere[1][6][1];
	sphere2[0][27][2] = sphere[1][5][2];   sphere2[0][30][2] = sphere[0][6][2];	 sphere2[0][33][2] = sphere[1][6][2];
	sphere2[0][27][3] = sphere[1][5][3];   sphere2[0][30][3] = sphere[0][6][3];	 sphere2[0][33][3] = sphere[1][6][3];

	sphere2[0][28][0] = sphere[0][5][0];   sphere2[0][31][0] = sphere[1][5][0];	 sphere2[0][34][0] = sphere[0][6][0];
	sphere2[0][28][1] = sphere[0][5][1];   sphere2[0][31][1] = sphere[1][5][1];	 sphere2[0][34][1] = sphere[0][6][1];
	sphere2[0][28][2] = sphere[0][5][2];   sphere2[0][31][2] = sphere[1][5][2];	 sphere2[0][34][2] = sphere[0][6][2];
	sphere2[0][28][3] = sphere[0][5][3];   sphere2[0][31][3] = sphere[1][5][3];	 sphere2[0][34][3] = sphere[0][6][3];

	sphere2[0][29][0] = sphere[0][6][0];   sphere2[0][32][0] = sphere[1][6][0];	 sphere2[0][35][0] = sphere[0][7][0];
	sphere2[0][29][1] = sphere[0][6][1];   sphere2[0][32][1] = sphere[1][6][1];	 sphere2[0][35][1] = sphere[0][7][1];
	sphere2[0][29][2] = sphere[0][6][2];   sphere2[0][32][2] = sphere[1][6][2];	 sphere2[0][35][2] = sphere[0][7][2];
	sphere2[0][29][3] = sphere[0][6][3];   sphere2[0][32][3] = sphere[1][6][3];	 sphere2[0][35][3] = sphere[0][7][3];
	/***********30*/				   /***********33*/					 /***********36*/
	sphere2[0][36][0] = sphere[0][7][0];   sphere2[0][39][0] = sphere[1][7][0];  
	sphere2[0][36][1] = sphere[0][7][1];   sphere2[0][39][1] = sphere[1][7][1];	 
	sphere2[0][36][2] = sphere[0][7][2];   sphere2[0][39][2] = sphere[1][7][2];	 
	sphere2[0][36][3] = sphere[0][7][3];   sphere2[0][39][3] = sphere[1][7][3];	 

	sphere2[0][37][0] = sphere[1][6][0];   sphere2[0][40][0] = sphere[0][7][0];	 
	sphere2[0][37][1] = sphere[1][6][1];   sphere2[0][40][1] = sphere[0][7][1];	 
	sphere2[0][37][2] = sphere[1][6][2];   sphere2[0][40][2] = sphere[0][7][2];	 
	sphere2[0][37][3] = sphere[1][6][3];   sphere2[0][40][3] = sphere[0][7][3];	 

	sphere2[0][38][0] = sphere[1][7][0];   sphere2[0][41][0] = sphere[0][8][0];	 sphere2[0][41][0] = sphere[0][0][0];
	sphere2[0][38][1] = sphere[1][7][1];   sphere2[0][41][1] = sphere[0][8][1];	 sphere2[0][41][1] = sphere[0][0][1];
	sphere2[0][38][2] = sphere[1][7][2];   sphere2[0][41][2] = sphere[0][8][2];	 sphere2[0][41][2] = sphere[0][0][2];
	sphere2[0][38][3] = sphere[1][7][3];   sphere2[0][41][3] = sphere[0][8][3];	 sphere2[0][41][3] = sphere[0][0][3];
	/***********39*/						/***********42*/					 /***********36*/

	
	
	
	

	
	
	
	
	
	
	
	
	

	
	
	
	

	
	
	
	
	

	glCreateVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);


	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glNamedBufferStorage(VBO, sizeof(sphere2), NULL, GL_DYNAMIC_STORAGE_BIT);

	static GLuint attribIndex = glGetAttribLocation(shader_prog, "sphere"),
		bindingIndex = 0, offset = 0, stride = 4 * sizeof(GLfloat), num_coord_per_vert = 4;
	
	
	
	

	glNamedBufferSubData(VBO, offset, sizeof(sphere2), sphere2);

	glVertexArrayAttribBinding(VAO, attribIndex, bindingIndex);
	glVertexArrayVertexBuffer(VAO, bindingIndex, VBO, offset, stride);
	glVertexArrayAttribFormat(VAO, attribIndex, num_coord_per_vert, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(VAO, attribIndex);

	


}




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

	glPointSize(3.0);
	glDrawArrays(GL_TRIANGLES, 0, 42);
	//glDrawArrays(GL_POINTS, 0, 3);
	glBindVertexArray(-1);

}








 
}

