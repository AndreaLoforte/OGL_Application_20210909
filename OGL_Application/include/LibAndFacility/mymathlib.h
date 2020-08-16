#ifndef MYMATHLIB_H
#define MYMATHLIB_H
#include<vmath.h>
#include<iostream>
#include<core.h>
#include<gl3w.h>
#include<array>
#include<vector>


using namespace std;

namespace mymathlibNS{

void printMatrix(const vmath::mat4&);
 void printMatrix44(const float*);
int  power(int,int);
float determinant44(const vmath::mat4&);
float cofactor(const vmath::mat4&,const int&,const int&);	
vmath::vec4 mat44vec4Product(vmath::mat4,vmath::vec4);
void inverseMatrix(const vmath::mat4&,vmath::mat4&);
vmath::mat4  inverseMatrix(const vmath::mat4& input_mat);
void transpose(const vmath::mat4& ,vmath::mat4&);
vmath::mat4  transpose(const vmath::mat4& input_matrix);
 void rotate(const float&, const float&, const float&, float*);
 void multMatrix44(const float*,const float *,float*);
 void stdVectorProdFloat(std::vector<float>&, float);

 extern float identity[16];
 extern float identity_[4][4];

 class Quaternion {
 public:
	 float w, x, y, z;
	 //float norm;
 
	 Quaternion() {};
	 Quaternion(GLfloat qr, GLfloat qx, GLfloat qy, GLfloat qz) :w(qr),x(qx),y(qy),z(qz){
		 /*norm = sqrt(pow(qr, 2) + pow(qx, 2) + pow(qy, 2) + pow(qz, 2));*/
		 //e se non viene inizializzato con i valori?
	 }
	 static Quaternion getQuaternionProductfromAngles(const float& xangle, const float& yangle, const float& zangle);
	 static Quaternion getQuaternionfromXAngle(const float& angle);
	 static Quaternion getQuaternionfromYAngle(const float& angle);
	 static Quaternion getQuaternionfromZAngle(const float& angle);
	 static Quaternion getQuaternionfromMatrix(const vmath::mat4&);
	 static Quaternion getProduct(const Quaternion&, const Quaternion&);
	 static Quaternion getProductByScalar(const Quaternion&, const float&);
	 static Quaternion getConiugate(const Quaternion&);
	 static Quaternion getInverse(const Quaternion &);
	 /*static float norm(const Quaternion& q){ 
		 return sqrt(pow(q.w, 2) + pow(q.x, 2) + pow(q.y, 2) + pow(q.z, 2));
	 }*/

	 float norm() const {
		 return sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
	 }
	 
	 
	 Quaternion operator *(const float& f) {
		 Quaternion result;
		 result.w = this->w*f;
		 result.x = this->x*f;
		 result.y = this->y*f;
		 result.z = this->z*f;
		 return result;
	 }

	 Quaternion operator +(const Quaternion& q) {
		 Quaternion result(q);
		 result.w += this->w;
		 result.x += this->x;
		 result.y += this->y;
		 result.z += this->z;
		 return result;
	 }


	 Quaternion operator /(const float& f) {
		 Quaternion result;
		 result.w = this->w / f;
		 result.x = this->x / f;
		 result.y = this->y / f;
		 result.z = this->z / f;
		 return result;
	 }

	 float& operator [](const unsigned& i) {

		 if (i == 0)
			 return w;
		 if (i == 1)
			 return x;
		 if (i == 2)
			 return y;
		 if (i == 3)
			 return z;
		 
	 }

 };


 void calculateTransformMatrix(Matrix4 &transformMatrix,
	 const Vector3 &position,
	 const Quaternion &orientation);

 void getGLTransform(Matrix4 transformMatrix, float output_matrix[16]);

 /*classe utile a convertire oggetti della libreria Cycloone (Libro di Ian Milligan)
 con oggetti della libreri vmath (libro OpenGLSuperbible)*/


 

 using namespace std;
 struct stdLibHelper {
	 

	 /*a1-a2*/
	 static array<float, 3> array3fDiff(const array<float, 3>&a1, const array<float, 3>& a2)
	 {
		 array<float, 3> result{ a1.at(0) - a2.at(0),a1.at(1) - a2.at(1),a1.at(2) - a2.at(2) };
		 return result;
	 }

	 static array<float, 3> array3fSum(const array<float, 3>&a1, const array<float, 3>& a2)
	 {
		 array<float, 3> result{ a1.at(0) + a2.at(0),a1.at(1) + a2.at(1),a1.at(2) + a2.at(2) };
		 return result;
	 }

	 static array<float, 3> array3fProd1s(const array<float, 3>&a1, const float& f)
	 {
		 array<float, 3> result{ a1.at(0)*f,a1.at(1)*f,a1.at(2)*f };
		 return result;
	 }

	 static float norm(const array<float, 3>& a)
	 {
		 return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	 }

	 static float squareNorm(const array<float, 3>& a)
	 {
		 return (a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	 }

	 static float array3fScalarProduct(const array<float, 3>& a1, const array<float, 3>& a2)
	 {
		 return { a1[0] * a2[0] + a1[1] * a2[1] + a1[2] * a2[2] };
	 }

	 static array<float, 3> array3Normalize(const array<float, 3>& a)
	 {
		 float n(norm(a));
		 return { a[0] / n, a[1] / n, a[2] / n };
	 }

	 static array<float, 3> array3VectorProduct(const array<float, 3>& a, const array<float, 3>& b)
	 {
		 return { a[1] * b[2] - a[2] * b[1],a[0] * b[2] - a[2] * b[0],a[0] * b[1] - a[1] * b[0] };
	 }


  };



 struct Vector {


	 static float computeNorm(const std::array<float, 3>& vec)
	 {
		 float norm(sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2)));
		 return norm;
	 }

	 static std::array<float, 3> normalize(const std::array<float, 3>& vec)
	 {
		 std::array<float, 3> normalized(vec);
		 float vecNorm = computeNorm(vec);
		 normalized[0] /= vecNorm;
		 normalized[1] /= vecNorm;
		 normalized[2] /= vecNorm;

		 return normalized;
	 }

 };


 struct vmatMatrix
 {
	 static vector<array<float, 3>>  getProduct(const vector<array<float, 3>>& v, const vmath::mat4& m);
 };

 
}
#endif
