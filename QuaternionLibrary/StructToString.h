#pragma once
#include <string>
#include <sstream>
#include "Quaternion.h"
#include "Matrix.h"
#include "Vector.h"
namespace QuaternionLibrary
{
	template <typename numtype> std::string QuaternionToString(const Quaternion<numtype> & Quat)
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

	template <typename numtype> std::string MatrixToString(const Matrix4x4<numtype> & Matrix)
	{

		std::stringstream out;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				out << Matrix.Array2D[i][j] << " ";
			}
			out << "\n";
		}

		return out.str();
	}

	template <typename numtype> std::string VectorToString(const Vector3<numtype> & Vec)
	{

		std::stringstream out;

		out << "(";

		out << Vec.X;
		out << ", ";
		out << Vec.Y;
		out << ", ";
		out << Vec.Z;

		out << ")";

		return out.str();
	}

}