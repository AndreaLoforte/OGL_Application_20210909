#pragma once
#include<vmath.h>
#include<iostream>
#include<core.h>
#include<gl3w.h>
#include<array>
#include<vector>

namespace mymathlibNS {
	class Quaternion;
}


namespace conversionLibNS {


	class conversionLibrary {

	public:
		static vmath::mat4 mat43Conversion_tovmath44(Matrix4& mat);
		static vmath::mat4 mat43Conversion_tovmath44T(Matrix4& mat);
		static Matrix4 mat44Conversion_toMat43Cyclone(const vmath::mat4&);
		static	void mat4Conversion_toCyclone(const vmath::mat4& mat, Matrix4& converted);
		static void floatArray_toCycloneVec3(const GLfloat arr[3], Vector3& vec);
		static void floatArray_toMyQuaternion(const GLfloat arr[4], mymathlibNS::Quaternion& q);
		static vmath::mat4 floatArray16ToVmathmat44(const GLfloat arr[16]);
		static std::array<float, 3> cycloneVec3TostdArray(const Vector3&);
		static std::array<float, 3> floatArrayTostdArray(const float[3]);
		static Vector3 stdArrayToCycloneVec3(const std::array<float, 3>&);
	};






}