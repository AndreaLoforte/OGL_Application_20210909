#include<mymathlib.h>
//#define PRINT_MAT_LOG
namespace mymathlibNS{


	void stdVectorProdFloat(std::vector<float>& vec,  float f)
	{ 
		for (int i = 0; i < vec.size(); i++)
			vec[i] = f * vec[i];
	}
	


	void calculateTransformMatrix(Matrix4 &transformMatrix,
		const Vector3 &position,
		const Quaternion &orientation)
	{
		transformMatrix.data[0] = 1 - 2 * orientation.y*orientation.y -
			2 * orientation.z*orientation.z;
		transformMatrix.data[1] = 2 * orientation.x*orientation.y -
			2 * orientation.w*orientation.z;
		transformMatrix.data[2] = 2 * orientation.x*orientation.z +
			2 * orientation.w*orientation.y;
		transformMatrix.data[3] = position.x;

		transformMatrix.data[4] = 2 * orientation.x*orientation.y +
			2 * orientation.w*orientation.z;
		transformMatrix.data[5] = 1 - 2 * orientation.x*orientation.x -
			2 * orientation.z*orientation.z;
		transformMatrix.data[6] = 2 * orientation.y*orientation.z -
			2 * orientation.w*orientation.x;
		transformMatrix.data[7] = position.y;

		transformMatrix.data[8] = 2 * orientation.x*orientation.z -
			2 * orientation.w*orientation.y;
		transformMatrix.data[9] = 2 * orientation.y*orientation.z +
			2 * orientation.w*orientation.x;
		transformMatrix.data[10] = 1 - 2 * orientation.x*orientation.x -
			2 * orientation.y*orientation.y;
		transformMatrix.data[11] = position.z;
	}


	void getGLTransform(Matrix4 transformMatrix, float output_matrix[16])
	{
		output_matrix[0] = (float)transformMatrix.data[0];
		output_matrix[1] = (float)transformMatrix.data[4];
		output_matrix[2] = (float)transformMatrix.data[8];
		output_matrix[3] = 0;

		output_matrix[4] = (float)transformMatrix.data[1];
		output_matrix[5] = (float)transformMatrix.data[5];
		output_matrix[6] = (float)transformMatrix.data[9];
		output_matrix[7] = 0;

		output_matrix[8] = (float)transformMatrix.data[2];
		output_matrix[9] = (float)transformMatrix.data[6];
		output_matrix[10] = (float)transformMatrix.data[10];
		output_matrix[11] = 0;

		output_matrix[12] = (float)transformMatrix.data[3];
		output_matrix[13] = (float)transformMatrix.data[7];
		output_matrix[14] = (float)transformMatrix.data[11];
		output_matrix[15] = 1;
	}



	Quaternion Quaternion::getQuaternionfromMatrix(const vmath::mat4& M) {
		//funzione che restituisce un quaternione q (x,y,z,w)

		GLfloat m00, m01, m02, m10, m11, m12, m20, m21, m22, t;
		Quaternion q, q2;

		m00 = M[0][0];
		m01 = M[0][1];
		m02 = M[0][2];
		m10 = M[1][0];
		m11 = M[1][1];
		m12 = M[1][2];
		m20 = M[2][0];
		m21 = M[2][1];
		m22 = M[2][2];


		if (m22 < 0) {
			if (m00 > m11) {
				t = 1 + m00 - m11 - m22;
				q = Quaternion(t, m01 + m10, m20 + m02, m12 - m21);
			}
			else {
				t = 1 - m00 + m11 - m22;
				q = Quaternion(m01 + m10, t, m12 + m21, m20 - m02);
			}
		}
		else {
			if (m00 < -m11) {
				t = 1 - m00 - m11 + m22;
				q = Quaternion(m20 + m02, m12 + m21, t, m01 - m10);
			}
			else {
				t = 1 + m00 + m11 + m22;
				q = Quaternion(m12 - m21, m20 - m02, m01 - m10, t);
			}
		}
		q = q* 0.5 / sqrt(t);

		
		
		q2.x = q.w;
		q2.y = q.x;
		q2.z = q.y;
		q2.w = q.z;


		//q2.z = 0;
		return q2;
	}


	vmath::vec4 mat44vec4Product(vmath::mat4 mat, vmath::vec4 vec) {

		vmath::vec4 result;

		result[0] = mat[0][0] * vec[0] + mat[0][1] * vec[1] +
			mat[0][2] * vec[2] +mat[0][3] * vec[3];
		result[1] = mat[1][0] * vec[0] + mat[1][1] * vec[1] +
			mat[1][2] * vec[2]+mat[1][3] * vec[3];
		result[2] = mat[2][0] * vec[0] + mat[2][1] * vec[1] +
			mat[2][2] * vec[2] +mat[2][3] * vec[3];
		result[3] = mat[3][0] * vec[0] + mat[3][1] * vec[1] +
			mat[3][2] * vec[2] +mat[3][3]* vec[3];

		return result;
	}



	

	Quaternion Quaternion::getQuaternionProductfromAngles(const float& xangle, const float& yangle, const float& zangle)
	{
		static GLfloat xrad, yrad, zrad;
		xrad = xangle/ 180.0 * 3.1415926535;
		yrad = yangle/ 180.0 * 3.1415926535;
		zrad = zangle/ 180.0 * 3.1415926535;


		//un quaternione è definito da un angolo e un asse
		//in questo caso ricevo in input 3 angoli (uno per quaternione ) e nessun asse perchè gli assi qui usati saranno x,y,z.

		Quaternion qx(cos(xrad / 2), sin(xrad / 2), 0, 0);
		Quaternion qy(cos(yrad / 2), 0, sin(yrad / 2), 0);

		/*in quaternions product, order is very important.
		This is the right order of product, but i don't know why 
		(but the idea is that y rotation must come first because we
		want to rotate about y original axis, and not about a rotated y axis*/
		Quaternion qxy(getProduct(qx,qy));

		//now we can proceed with the rotation about z axis
		//remember: even if the rotation has angle = 0 , doesn t mean you can avoid to make the product
		//(you still are in 3 dimensions)
		Quaternion qz(cos(zrad / 2), 0, 0, sin(zrad / 2));


		//quaternion product qy*qx*qz
		Quaternion qzxy(getProduct(qxy, qz));

		return qzxy;


	}


	 Quaternion Quaternion::getQuaternionfromXAngle(const float& angle)
	 {
		 /*if (angle == 0)
			 return Quaternion(0.0, 0.0, 0.0, 0.0);*/

		 GLfloat rad;
		 rad = angle / 180.0 * 3.1415926535;
		 //un quaternione è definito da un angolo e un asse

		 Quaternion q(cos(rad / 2), sin(rad / 2), 0, 0);

		 return q;
	 }

	 Quaternion Quaternion::getQuaternionfromYAngle(const float& angle)
	 {
		/* if (angle == 0)
			 return Quaternion(0.0, 0.0, 0.0, 0.0);*/

		 GLfloat rad;
		 rad = angle / 180.0 * 3.1415926535;
		 //un quaternione è definito da un angolo e un asse

		 Quaternion q(cos(rad / 2), 0.0, sin(rad / 2), 0);

		 return q;
	 }

	 Quaternion Quaternion::getQuaternionfromZAngle(const float& angle)
	 {

		/* if (angle == 0)
			 return Quaternion(0.0, 0.0, 0.0, 0.0);*/

		 GLfloat rad;
		 rad = angle / 180.0 * 3.1415926535;
		 //un quaternione è definito da un angolo e un asse

		 Quaternion q(cos(rad / 2),0.0, 0, sin(rad / 2));

		 return q;
	 }






	
	Quaternion Quaternion::getProduct(const Quaternion& q1, const Quaternion& q2) {
	
		//IMPORTANTE : IL PRIMO FATTORE VA PASSATO SEMPRE A Q2 .
		//es : devo moltiplicare q1 * q2 => getProduct(q2,q1)
			

		GLfloat g0, g1, g2, g3, h0, h1, h2, h3;
		g0 = q1.w;
		g1 = q1.x;
		g2 = q1.y;
		g3 = q1.z;
		h0 = q2.w;
		h1 = q2.x;
		h2 = q2.y;
		h3 = q2.z;

		Quaternion q12
		((h0 *g0 - h1 * g1 - h2 * g2 - h3 * g3),
		(h1*g0 + h0 * g1 - h3 * g2 + h2 * g3),
		(h2*g0 + h3 * g1 + h0 * g2 - h1 * g3),
		(h3*g0 - h2 * g1 + h1 * g2 + h0 * g3));


		return q12;

	}



	Quaternion Quaternion::getConiugate(const Quaternion& q)
	{
		Quaternion result(q.w, -q.x, -q.y, -q.z );
		return result;
	}

	Quaternion Quaternion::getInverse(const Quaternion& q)
	{
		Quaternion result(getConiugate(q));
		float f = 1 / q.norm();
		return getProductByScalar(result, f*f);

	}

	Quaternion Quaternion::getProductByScalar(const Quaternion& q, const float& f)
	{
		Quaternion result(f*q.w, f*q.x, f*q.y, f*q.z);
		return result;
	}


  
 float identity[16] =
   {
     1.0,0.0,0.0,0.0,
     0.0,1.0,0.0,0.0,
     0.0,0.0,1.0,0.0,
     0.0,0.0,0.0,1.0
   };


 float identity_[4][4] =
 {
	 {1.0,0.0,0.0,0.0},
	{0.0,1.0,0.0,0.0 },
	{ 0.0,0.0,1.0,0.0},
	 {0.0,0.0,0.0,1.0 }
 };

  
void printMatrix(const vmath::mat4& matrix)
{
      for(int i = 0; i < 4; i ++)
	{
	  std::cout<<std::endl;
	  for(int j = 0; j < 4; j++)
	    std::cout<<matrix[i][j]<<" ";
	}

      std::cout<<std::endl;
}

void printMatrix(const vmath::mat3& matrix)
{
      for(int i = 0; i <3; i ++)
	{
	  std::cout<<std::endl;
	  for(int j = 0; j < 3; j++)
	    std::cout<<matrix[i][j]<<" ";
	}

      std::cout<<std::endl;
}

  void printMatrix44(const float *matrix)
{
      for(int i = 0; i <4; i ++)
	{
	  std::cout<<std::endl;
	  for(int j = 0; j < 4; j++)
	    std::cout<<matrix[i*4+j]<<" ";
	}

      std::cout<<std::endl;
}
  

  

 void multMatrix44(const float* mat1,const float*mat2,float*out)
  {

    for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
	{
	  
	  for(int k = 0; k < 4; k++)
	    {
	      out[4*i+j] += mat1[4*i+k]*mat2[4*k+j];
	    }
	}

  }


  void rotate(const float& phi,const float& theta,const  float& psi,float *rotateMat)
  {
    rotateMat[0] = cos(theta)*cos(psi);
    rotateMat[1] = cos(phi)*sin(psi) + sin(phi)*sin(theta)*cos(psi);
    rotateMat[2] = sin(phi)*sin(psi) - cos(phi)*sin(theta)*cos(psi);
    rotateMat[3] = 0.f;

    rotateMat[4] = -cos(theta)*sin(psi);
    rotateMat[5] = cos(phi)*cos(psi) - sin(phi)*sin(theta)*sin(psi);
    rotateMat[6] = sin(phi)*cos(psi)+ cos(phi)*sin(theta)*sin(psi);
    rotateMat[7] = 0.f;


    rotateMat[8] = sin(theta);
    rotateMat[9] = -sin(phi)*cos(theta);
    rotateMat[10] = cos(phi)*cos(theta);
    rotateMat[11] = 0.f;

    rotateMat[12] = .0f;
    rotateMat[13] = .0f;
    rotateMat[14] = .0f;
    rotateMat[15] = 1.0f;    
    
  }


int power(int number,int exponent)
{
  if(exponent == 1)
    return number;
  else
    return number*power(number,exponent-1);
}



    
  

float determinant44(const vmath::mat4& input_mat)
{
  float det[4];

  int uno = 0,due = 1,tre = 2,quattro = 3;

  const float& a = input_mat[0][0];
  const float& b = input_mat[0][1];
  const float& c = input_mat[0][2];
  const float& d = input_mat[0][3];

  const float& e = input_mat[1][0];
  const float& f = input_mat[1][1];
  const float& g = input_mat[1][2];
  const float& h = input_mat[1][3];

  const float& i = input_mat[2][0];
  const float& l = input_mat[2][1];
  const float& m = input_mat[2][2];
  const float& n = input_mat[2][3];

  const float& o = input_mat[3][0];
  const float& p = input_mat[3][1];
  const float& q = input_mat[3][2];
  const float& r = input_mat[3][3];
  

  det[0] = pow(-1,1+1)*a*(f*(m*r-n*q)-g*(l*r-n*p)+h*(l*q-m*p));
  det[1] = pow(-1,2+1)*e*(b*(m*r-n*q)-c*(l*r-n*p)+d*(l*q-m*p));
  det[2] = pow(-1,3+1)*i*(b*(g*r-h*q)-c*(f*r-h*p)+d*(f*q-g*p));
  det[3] = pow(-1,4+1)*o*(b*(g*n-h*m)-c*(f*n-h*l)+d*(f*m-g*l));

  float res = det[0] + det[1] + det[2] + det[3];

  #ifdef PRINT_MAT_LOG
  std::cout<<"determinante pari a : "<<res<<std::endl;

  if(res == 0)
    std::cout<<"la matrice non è invertibile"<<std::endl;
  #endif

  return res;
}




float cofactor(const vmath::mat4& mat,const int& k ,const int& j)
{

  vmath::mat3 complementar_matrix;

  int w = 0, z;

  for(int l = 0; l <4; l++)
    {
      if(l == k)
	continue;
      z =  0;
      for(int m = 0; m < 4; m++)
	{
	  if(m == j)
	    continue;
	  //std::cout<<" w  z "<<w<<" "<<z<<std::endl;
	  complementar_matrix[w][z++] = mat[l][m];
	}

      ++w;

    }

  // std::cout<<"complementar_matrix["<<k<<"]["<<j<<"]"<<std::endl;
  // printMatrix(complementar_matrix);

  //calcolo  del determmiinante per  la matrice commplementare
  float& a = complementar_matrix[0][0];
  float& b = complementar_matrix[0][1];
  float& c = complementar_matrix[0][2];

  float& d = complementar_matrix[1][0];
  float& e = complementar_matrix[1][1];
  float& f = complementar_matrix[1][2];

  float& g = complementar_matrix[2][0];
  float& h = complementar_matrix[2][1];
  float& i = complementar_matrix[2][2];

  float det;

  det = a*(e*i - f*h) - b*(d*i -f*g) +c*(d*h - e*g);

  float cofactor = pow(-1,k+1+j+1)*det;

  return cofactor;

}

void transpose(const vmath::mat4& input_matrix,vmath::mat4& out_mat)
{
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      out_mat[j][i] = input_matrix[i][j];
}

vmath::mat4  transpose(const vmath::mat4& input_matrix )
{
	vmath::mat4 out_mat;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			out_mat[j][i] = input_matrix[i][j];

	return out_mat;

}
  




void inverseMatrix(const vmath::mat4& input_mat,vmath::mat4&  output_mat) 
{

  static int n = 0 ;
  #ifdef PRINT_MAT_LOG
  std::cout<<"inversion number :"<<n++<<std::endl;
  #endif
  
  //si verifica l'invertibilità
  float det = determinant44(input_mat);
  if( det == 0)
    {
      #ifdef PRINT_MAT_LOG
      std::cout<<"non invertible matrix ! error! "<<std::endl;
      #endif
      ;
    }
  
  else
    {

      vmath::mat4 cofactor_matrix;

      //si calcola la matrice dei cofattori
      for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
	  cofactor_matrix[i][j] = cofactor(input_mat,i,j);

      #ifdef PRINT_MAT_LOG
      std::cout<<"cofactor_matrix"<<std::endl;
      printMatrix(cofactor_matrix);
      #endif


      //si calcola la trasposta 
      vmath::mat4 Tcofactor_matrix;
      transpose(cofactor_matrix,Tcofactor_matrix);

      //si moltiplica la matrice ottenuta per 1/det(input_matrix)

      output_mat = Tcofactor_matrix*(1/det);
    }

      
  
}


 

vmath::mat4  inverseMatrix(const vmath::mat4& input_mat)
{

	static int n = 0;
#ifdef PRINT_MAT_LOG
	std::cout << "inversion number :" << n++ << std::endl;
#endif

	//si verifica l'invertibilità
	float det = determinant44(input_mat);
	if (det == 0)
	{
#ifdef PRINT_MAT_LOG
		std::cout << "non invertible matrix ! error! " << std::endl;
#endif
		;
	}

	else
	{

		vmath::mat4 cofactor_matrix;

		//si calcola la matrice dei cofattori
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				cofactor_matrix[i][j] = cofactor(input_mat, i, j);

#ifdef PRINT_MAT_LOG
		std::cout << "cofactor_matrix" << std::endl;
		printMatrix(cofactor_matrix);
#endif


		//si calcola la trasposta 
		vmath::mat4 Tcofactor_matrix;
		transpose(cofactor_matrix, Tcofactor_matrix);

		//si moltiplica la matrice ottenuta per 1/det(input_matrix)

		vmath::mat4 outputMatrix(Tcofactor_matrix * (1 / det));

		return outputMatrix;


	}



}



void matXvec(vmath::mat4& mat,vmath::vec3& vec,vmath::vec3& ret)
{

  //ROW MAJOR ORDER
  /* ret[0] = mat[0][0]*vec[0]+mat[0][1]*vec[1]+mat[0][2]*vec[2]+mat[0][3]*1.0; */
  /* ret[1] = mat[1][0]*vec[0]+mat[1][1]*vec[1]+mat[1][2]*vec[2]+mat[1][3]*1.0; */
  /* ret[2] = mat[2][0]*vec[0]+mat[2][1]*vec[1]+mat[2][2]*vec[2]+mat[2][3]*1.0; */
  // ret[3] = mat[3][0]*vec[0]+mat[3][1]*vec[1]+mat[3][2]*vec[2]+mat[3][3]*1.0;

  //COLUMN MAJOR ORDER
    ret[0] = mat[0][0]*vec[0]+mat[1][0]*vec[1]+mat[2][0]*vec[2]+mat[3][0]*1.0;
  ret[1] = mat[0][1]*vec[0]+mat[1][1]*vec[1]+mat[2][1]*vec[2]+mat[3][1]*1.0;
  ret[2] = mat[0][2]*vec[0]+mat[1][2]*vec[1]+mat[2][2]*vec[2]+mat[3][2]*1.0;


}
  
}
