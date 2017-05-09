#pragma once
#include "Defines.h"
#include "Fraction.h"
namespace QuaternionLibrary
{

	template <typename numtype> struct Vector3
	{
		union
		{
			numtype Array[3];
			struct
			{

				numtype X;
				numtype Y;
				numtype Z;

			};
		};
		Vector3()
		{

		}
		Vector3(numtype _X, numtype _Y, numtype _Z) :
			X(_X), Y(_Y), Z(_Z)
		{

		}
		Vector3 operator+(Vector3 const & Other) const
		{
			return Vector3(X + Other.X, Y + Other.Y, Z + Other.Z);
		}
		Vector3 operator-(Vector3 const & Other) const
		{
			return Vector3(X - Other.X, Y - Other.Y, Z - Other.Z);
		}
		Vector3 operator*(numtype Other) const
		{
			return Vector3(X * Other, Y * Other, Z * Other);
		}
		//5 Operations: 3 multiplication, 2 addition
		numtype Dot(Vector3 const &Other) const
		{
			return (X * Other.X + Y * Other.Y + Z * Other.Z);
		}
		//10 Operations: 7 multiplication, 3 subtraction
		Vector3 Cross(Vector3 const &Other) const
		{
			Vector3 Out;
			//The following diagram breaks down a proper cross product between two vectors.

			//To get any value, you exclude that value's column from the table to leave you with a 2x2 matrix

			//Then you multiply the upper left with the bottom right to get A.

			//Then you multiply the bottom left with the upper right to get B.

			//Subtract B from A to get your value

			//Finally, if you are getting the value for Y, your final value will be the NEGATION of A - B.

			//////////////////////////////////////////////////////////////
			//   I |-J | K           X' = Y * z - y * Z                ///
			// V X | Y | Z  = V'    -Y' = X * z - x * Z                ///
			// v x | y | z           Z' = X * y - x * Y                ///
			//////////////////////////////////////////////////////////////

			////////////////////////////////////////////////
			//     J | K         Y * z                    //
			// V   Y | Z        +y * Z                    //
			// v   y | z         = X'                     //
			////////////////////////////////////////////////

			//3 operations: 2 multiplication, 1 subtraction
			Out.X = Y * Other.Z - Other.Y * Z;

			////////////////////////////////////////////////
			//     I | K         X * z                    //
			// V   X | Z        +x * Z     Y' = -1 * -Y'  //
			// v   x | z         =-Y'                     //
			////////////////////////////////////////////////

			//4 Operations: 3 multiplication, 1 subtraction
			Out.Y = -1 * (X * Other.Z - Other.X * Z);

			////////////////////////////////////////////////
			//     I | J         X * y                    //
			// V   X | Y        +x * Y                    //
			// v   x | y         = Z'                     //
			////////////////////////////////////////////////

			//3 operations: 2 multiplication, 1 subtraction
			Out.Z = X * Other.Y - Other.X * Y;

			return Out;
		}

		static Vector3 AxisX() { return Vector3(1, 0, 0); }
		static Vector3 AxisY() { return Vector3(0, 1, 0); }
		static Vector3 AxisZ() { return Vector3(0, 0, 1); }


		Vector3& Normalize()
		{
			Fraction<double, double> Frac;
			Frac.SetNumerator(1.0);
			Frac.SetDenominator(Magnitude());
			for (size_t i = 0; i < 3; i++)
			{
				Array[i] *= (numtype)Frac.GetDecimal();
			}
			return *this;
		};

		Vector3 GetNormalized() const
		{
			Vector3 Out(*this);
			Out.Normalize();
			return Out;
		}

		numtype SqrMagnitude() const
		{
			numtype Sum = 0;
			for (size_t i = 0; i < 3; i++)
			{
				Sum += Array[i] * Array[i];
			}
			return Sum;
		};

		double Magnitude() const
		{
			return sqrt((double)SqrMagnitude());
		}

		void CheckNearlyZero()
		{
			for (size_t i = 0; i < 3; i++)
			{
				if (abs(Array[i]) < tinynumber)
				{
					Array[i] = 0;
				}
			}
		}
	};

	template <typename numtype, typename othernumtype> Vector3<numtype> operator*(othernumtype Left, Vector3<numtype> const & Right)
	{
		return Vector3<numtype>((Right.X * (numtype)Left), (Right.Y * (numtype)Left), (Right.Z * (numtype)Left));
	}

	typedef Vector3<float> Vec3f;
	typedef Vector3<double> Vec3d;
}