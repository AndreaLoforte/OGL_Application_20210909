#include<Enemy.h>
#include<assert.h>
#include<playerCharacter.h>
#include<cameraManager.h>
#include<activeCharacterManager.h>


namespace myobjectNS{

int Enemy::instanceCounter;


void Enemy::render(const fpcameraNS::Transformation& cam)
{
	glUseProgram(shader_prog);
	glBindVertexArray(VAO);

	static GLuint physics_transf_location = glGetUniformLocation(shader_prog, "physics_transformation");
	static GLuint transf_matrix_location = glGetUniformLocation(shader_prog, "transformMatrix");
	glUniformMatrix4fv(physics_transf_location, 1, GL_FALSE, AOTrMatrix);
	glUniformMatrix4fv(transf_matrix_location, 1, GL_FALSE, fpcameraNS::CameraManager::getActiveCamera().getPlayerCamera());
	glVertexAttrib4fv(2, AOcolor);

	/*se size < 2.0 non si vede il disegno!*/
	glPointSize(2.0);
	glDrawArrays(GL_POINTS, 0, 5000);
	glBindVertexArray(0);
}

void Enemy::render()
{
	glUseProgram(shader_prog);
	glBindVertexArray(VAO);

	static GLuint physics_transf_location = glGetUniformLocation(shader_prog, "physics_transformation");
	static GLuint transf_matrix_location = glGetUniformLocation(shader_prog, "transformMatrix");
	glUniformMatrix4fv(physics_transf_location, 1, GL_FALSE, AOTrMatrix);
	glUniformMatrix4fv(transf_matrix_location, 1, GL_FALSE, fpcameraNS::CameraManager::getActiveCamera().getPlayerCamera());
	glVertexAttrib4fv(2, AOcolor);

	/*se size < 2.0 non si vede il disegno!*/
	glPointSize(2.0);
	glDrawArrays(GL_POINTS, 0, 5000);
	glBindVertexArray(0);
}



void Enemy::update(const float& duration){
	body->getGLTransform(AOTrMatrix);

	static float i = 70.0;
	static constexpr int M = 100;
 
}




void Enemy::setRigidBodyParameters() {

	body->clearAccumulators();

	body->setInertiaTensor(Matrix3());
	body->setInverseInertiaTensor(Matrix3());
	body->setRotation(Vector3(0.0, .0, 0.0));


	body->setLinearDamping(1.0);
	body->setAngularDamping(1.0);

	body->setMass(bodyMass);

	body->setPosition(AOposition[0], AOposition[1], AOposition[2]);
	body->setOrientation(AOorientation[0], AOorientation[1], AOorientation[2], AOorientation[3]);
	body->setAcceleration(Vector3::GRAVITY);
	body->_calculateTransformMatrix(body->transformMatrix,body->position,body->orientation);

}


void Enemy::OSsetParameters() {

	setRigidBodyParameters();
}




///////////////////////////ENEMYOC
///////////////////////////ENEMYOC
///////////////////////////ENEMYOC
///////////////////////////ENEMYOC
///////////////////////////ENEMYOC



void EnemyOC::canSleep(bool v)
{
	enemy.AOcanSleep(v);
	/*turn off/on AI*/
	brain.AIon = !v;
	/*turn off/on physics body*/
	enemy.body->setAwake(!v);
	/*turn off/on collector*/
	isOn = !v;
}




void EnemyOC::OCupdate(const float& duration)
{

	brain.follow(this, brain.target);

	for (int i = 0; i < enemycoll.size(); i++)
		enemycoll[i]->AOupdate(duration);

	/*tenere shoot dopo l'integratore altrimenti già
	al primo frame il proiettile è già molto distante dal fireSpot*/
	brain.shoot(this, brain.target, 30, gun);
	
}

EnemyOC::EnemyOC() : ActiveObject("enemy", &enemycoll)
{
	enemycoll.push_back(&enemy);
	brain.setTarget(myobjectNS::PlayerCharacterOC::getPlayer());
	gun.setCollectorOwnership(collectorID);
	enemy.setCollectorOwnership(collectorID);
}




void EnemyOC::setParameters() {
	enemy.setParameters();
	gun.setParameters();
	
}


void Enemy::create() {

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

	//glGenVertexArrays(1, &VAO);
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//glGenBuffers(1, &VBO);
	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glNamedBufferStorage(VBO, sizeof(sphere), NULL, GL_DYNAMIC_STORAGE_BIT);

	GLuint attribIndex = glGetAttribLocation(shader_prog, "sphere"),
		bindingIndex = 0, offset = 0, stride = 4 * sizeof(GLfloat), num_coord_per_vert = 4;





	glNamedBufferSubData(VBO, offset, sizeof(sphere), sphere);

	glVertexArrayAttribBinding(VAO, attribIndex, bindingIndex);
	glVertexArrayVertexBuffer(VAO, bindingIndex, VBO, offset, stride);
	glVertexArrayAttribFormat(VAO, attribIndex, num_coord_per_vert, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(VAO, attribIndex);

}



EnemyOC* EnemyOC::OCgetNewInstance()  
{
	//instanceCounter++;
	EnemyOC* s(new EnemyOC());
	//s->AOinstanceNumber = instanceCounter;

	activeObjectManagerNS::ActiveCharacterManager::add(s);
	
	return s;
}


}

