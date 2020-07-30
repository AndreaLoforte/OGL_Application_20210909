#include<conversionLIB.h>
#include<mymathlib.h>

namespace conversionLibNS {



	vmath::mat4 conversionLibrary::mat43Conversion_tovmath44(Matrix4& mat) {

		vmath::mat4 converted;


		converted[0][0] = mat[0];
		converted[0][1] = mat[1];
		converted[0][2] = mat[2];
		converted[0][3] = 0.0;
		converted[1][0] = mat[3];
		converted[1][1] = mat[4];
		converted[1][2] = mat[5];
		converted[1][3] = 0.0;
		converted[2][0] = mat[6];
		converted[2][1] = mat[7];
		converted[2][2] = mat[8];
		converted[2][3] = 0.0;
		converted[3][0] = mat[9];
		converted[3][1] = mat[10];
		converted[3][2] = mat[11];
		converted[3][3] = 1.0;

		return converted;

	}


	vmath::mat4 conversionLibrary::mat43Conversion_tovmath44T(Matrix4& mat) {

		vmath::mat4 converted;

		converted[0][0] = mat[0];
		converted[0][1] = mat[4];
		converted[0][2] = mat[8];
		converted[0][3] = 0.0;
		converted[1][0] = mat[1];
		converted[1][1] = mat[5];
		converted[1][2] = mat[9];
		converted[1][3] = 0.0;
		converted[2][0] = mat[2];
		converted[2][1] = mat[6];
		converted[2][2] = mat[10];
		converted[2][3] = 0.0;
		converted[3][0] = mat[3];
		converted[3][1] = mat[7];
		converted[3][2] = mat[11];
		converted[3][3] = 1.0;

		return converted;

	}


	std::array<float, 3> conversionLibrary::cycloneVec3TostdArray(const Vector3& vec)
	{
		std::array<float, 3> result{ vec[0],vec[1],vec[2] };
		return result;
	}

	std::array<float, 3> conversionLibrary::floatArrayTostdArray(const float arr[3])
	{
		std::array<float, 3> result{ arr[0],arr[1],arr[2] };
		return result;
	}

	Vector3 conversionLibrary::stdArrayToCycloneVec3(const std::array<float, 3>& v)
	{
		Vector3 result{ v[0],v[1],v[2] };
		return result;
	}


	vmath::mat4 conversionLibrary::floatArray16ToVmathmat44(const GLfloat arr[16]) {
		vmath::mat4 result;

		result[0][0] = arr[0];
		result[0][1] = arr[1];
		result[0][2] = arr[2];
		result[0][3] = arr[3];
		result[1][0] = arr[4];
		result[1][1] = arr[5];
		result[1][2] = arr[6];
		result[1][3] = arr[7];
		result[2][0] = arr[8];
		result[2][1] = arr[9];
		result[2][2] = arr[10];
		result[2][3] = arr[11];
		result[3][0] = arr[12];
		result[3][1] = arr[13];
		result[3][2] = arr[14];
		result[3][3] = arr[15];

		return result;

	}

	Matrix4 conversionLibrary::mat44Conversion_toMat43Cyclone(const vmath::mat4& mat) {

		Matrix4 converted;

		converted[0] = mat[0][0];
		converted[1] = mat[1][0];
		converted[2] = mat[2][0];
		converted[3] = mat[3][0];
		converted[4] = mat[0][1];
		converted[5] = mat[1][1];
		converted[6] = mat[2][1];
		converted[7] = mat[3][1];
		converted[8] = mat[0][2];
		converted[9] = mat[1][2];
		converted[10] = mat[2][2];
		converted[11] = mat[3][2];


		return converted;


	}


	void conversionLibrary::mat4Conversion_toCyclone(const vmath::mat4& mat, Matrix4& converted) {



		converted[0] = mat[0][0];
		converted[1] = mat[0][1];
		converted[2] = mat[0][2];
		converted[3] = mat[0][3];
		converted[4] = mat[1][0];
		converted[5] = mat[1][1];
		converted[6] = mat[1][2];
		converted[7] = mat[1][3];
		converted[8] = mat[2][0];
		converted[9] = mat[2][1];
		converted[10] = mat[2][2];
		converted[11] = mat[2][3];
		converted[12] = mat[3][0];
		converted[13] = mat[3][1];
		converted[14] = mat[3][2];
		converted[15] = mat[3][3];


	}



	void conversionLibrary::floatArray_toCycloneVec3(const GLfloat arr[3], Vector3& vec) {

		vec[0] = arr[0];
		vec[1] = arr[1];
		vec[2] = arr[2];

	}

	

	void conversionLibrary::floatArray_toMyQuaternion(const GLfloat arr[4], mymathlibNS::Quaternion& q) {

		q.x = arr[0];
		q.y = arr[1];
		q.z = arr[2];
		q.w = arr[3];

	}




}