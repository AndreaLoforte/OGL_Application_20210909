#pragma once

#include<string>
#include<vmath.h>
#include<array>
#include<mymathlib.h>
namespace tostringNS {

	class vmathTostring {
	public:
		static std::string vec4Tostring(const vmath::vec4& v)
		{
			return std::to_string(v[0]) +"  "+ std::to_string(v[1]) + "  "  + std::to_string(v[2]) + "  " + std::to_string(v[3]);
		}


	};



	class stdToString {
	public:
		static std::string arrayfloat3(const std::array<float, 3>& arr)
		{
			return std::to_string(arr[0]) + " " + std::to_string(arr[1]) + " " + std::to_string(arr[2]);
		}
	};


	class mymathlibToString {
	public:
		static std::string quaternion(const mymathlibNS::Quaternion& q)
		{
			return std::to_string(q.w)+ " "+std::to_string(q.x) + " " + std::to_string(q.y) + " " + std::to_string(q.z);
		}
	};





}