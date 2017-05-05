#pragma once
#include <cmath>
#include "Fraction.h"
#include "Vector.h"
#include "Defines.h"

namespace QuaternionLibrary
{

	template <typename numtype> struct Quaternion
	{
	public:
		union
		{
			numtype Array[4];
			struct
			{
				numtype A;
				union
				{
					Vector3<numtype> VectorPart;
					struct
					{
						numtype X;
						numtype Y;
						numtype Z;
					};
				};
			};
		};

		Quaternion() : A(0), X(0), Y(0), Z(0) {  };
		Quaternion(numtype _A, numtype _X, numtype _Y, numtype _Z) : A(_A), X(_X), Y(_Y), Z(_Z) { };

		Quaternion(numtype _A, Vector3<numtype> _Vector) :
			A(_A), VectorPart(_Vector)
		{

		}

		static Quaternion Identity()
		{
			return Quaternion(1, 0, 0, 0);
		}

		static Quaternion GetRotationDegrees(numtype Degrees, Vector3<numtype> const & Axis)
		{

			//convert degrees to radians for our functions.

			//pi / 180 = ~0.0174533

			numtype Radians = (numtype)(Degrees * 0.0174533);

			Radians *= 0.5;

			return Quaternion(cos(Radians), Axis * sin(Radians)).Normalize();

		}

		Quaternion& Normalize()
		{
			Fraction<double, double> Frac;
			Frac.SetNumerator(1.0);
			Frac.SetDenominator(Magnitude());
			for (size_t i = 0; i < 4; i++)
			{
				Array[i] *= (numtype)Frac.GetDecimal();
			}
			return *this;
		};

		Quaternion GetNormalized() const
		{
			Quaternion Out(*this);
			Out.Normalize();
			return Out;
		}

		Quaternion operator* (Quaternion const & other) const
		{
			Quaternion Out;

			Out.A = A * other.A - other.VectorPart.Dot(VectorPart);

			Out.VectorPart = other.A * VectorPart + A * other.VectorPart + other.VectorPart.Cross(VectorPart);

			return Out;
		}

		Vector3<numtype> operator* (Vector3<numtype> const & other) const
		{
			Vector3<numtype> Out;

			Out = other;

				Out = Out + 2 * A * VectorPart.Cross(other);
				
				Out = Out + 2 * (VectorPart.Cross(VectorPart.Cross(other)));

				Out.CheckNearlyZero();

			return Out;
		}

		void CheckNearlyZero()
		{
			for (size_t i = 0; i < 4; i++)
			{
				if (Array[i] < tinynumber)
				{
					Array[i] = 0;
				}
			}
		}

	private:

		numtype SqrMagnitude() const
		{
			numtype Sum = 0;
			for (size_t i = 0; i < 4; i++)
			{
				Sum += Array[i] * Array[i];
			}
			return Sum;
		};

		double Magnitude() const
		{
			return sqrt((double)SqrMagnitude());
		}

	};


	template <typename numtype> Vector3<numtype> operator* (Vector3<numtype> const & Left, Quaternion<numtype> const & Right)
	{
		Vector3<numtype> Out;

		Out = Left + 2 * Right.A * Right.VectorPart.Cross(Left) + 2 * (Right.VectorPart.Cross(Right.VectorPart.Cross(Left)));

		Out.CheckNearlyZero();

		return Out;
	}


	typedef Quaternion<float> Quaternionf;
	typedef Quaternion<float> Quaterniond;
}