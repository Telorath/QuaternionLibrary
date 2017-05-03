#pragma once
#include <string>
#include <sstream>
#include "Quaternion.h"
namespace QuaternionLibrary
{
	template <typename numtype> std::string QuaternionToString(Quaternion<numtype> Quat)
	{

		std::stringstream out;

		out << "[";

		out << Quat.A;
		out << ", ";
		out << Quat.X;
		out << ", ";
		out << Quat.Y;
		out << ", ";
		out << Quat.Z;

		out << "]";

		return out.str();
	}
}