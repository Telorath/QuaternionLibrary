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

		Quaternion(const Quaternion & Other) : A(Other.A), X(Other.X), Y(Other.Y), Z(Other.Z) { };

		Quaternion& operator=(const Quaternion& Other) { A = Other.A; X = Other.X; Y = Other.Y; Z = Other.Z; return *this; };

		Quaternion(numtype _A, numtype _X, numtype _Y, numtype _Z) : A(_A), X(_X), Y(_Y), Z(_Z) { };

		Quaternion(numtype _A, Vector3<numtype> _Vector) :
			A(_A), VectorPart(_Vector)
		{

		}

		static Quaternion Identity()
		{
			return Quaternion(1, 0, 0, 0);
		}

		static Quaternion GetRotationDegrees(numtype Degrees, const Vector3<numtype> & Axis)
		{

			//convert degrees to radians for our functions.

			//pi / 180 = ~0.0174533

			numtype Radians = (numtype)(Degrees * 0.0174533);

//			Radians *= 0.5;

//			return Quaternion(cos(Radians), Axis * sin(Radians)).Normalize();
		
			return GetRotationRadians(Radians, Axis);

		}

		static Quaternion GetRotationRadians(numtype Radians, const Vector3<numtype> & Axis)
		{

			//convert degrees to radians for our functions.

			//pi / 180 = ~0.0174533

//numtype Radians = (numtype)(Degrees * 0.0174533);

			Radians *= 0.5;

			return Quaternion(cos(Radians), Axis * sin(Radians)).Normalize();

		}

		static Quaternion GetRotationBetweenVectors(const Vector3<numtype> & Start, const Vector3<numtype> & End)
		{

			Vector3<numtype> StartCopy = Start.GetNormalized();

			Vector3<numtype> EndCopy = End.GetNormalized();;

			Vector3<numtype> Axis = StartCopy.Cross(EndCopy).GetNormalized();

			numtype Angle = StartCopy.Dot(EndCopy);

			Angle = acos(Angle);

			return GetRotationRadians(Angle, Axis);
		}

		Quaternion& Normalize()
		{
			if (SqrMagnitude() == 1)
			{
				return *this;
			}
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

#pragma region Mathematical Operators

		Quaternion operator + (const Quaternion & other) const
		{
			Quaternion Out(*this);

			Out += other;

			return Out;
		}

		Quaternion& operator += (const Quaternion & other)
		{
			A += other.A;
			X += other.X;
			Y += other.Y;
			Z += other.Z;
			return *this;
		}

		Quaternion operator - (const Quaternion & other) const
		{
			Quaternion Out(*this);

			Out -= other;

			return Out;
		}

		Quaternion& operator -= (const Quaternion & other)
		{
			A -= other.A;
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;
			return *this;
		}

		//29 Operations
		Quaternion operator* (const Quaternion & other) const
		{
			Quaternion Out(*this);

			Out *= other;

			return Out;
		}

		Quaternion& operator*=(const Quaternion & other)

		{
			//7 Operations
			A = A * other.A - other.VectorPart.Dot(VectorPart);

			//22 Operations

			VectorPart = VectorPart.Cross(other.VectorPart) + A * other.VectorPart + other.A * VectorPart;

			return *this;
		}

		Quaternion operator/ (const Quaternion & other) const
		{
			Quaternion Out(*this);
			Out /= other;
			return Out;
		}

		Quaternion& operator/= (const Quaternion & other)
		{
			operator*=(other.Conjugate());
			return *this;
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

#pragma endregion

		void CheckNearlyZero()
		{
			for (size_t i = 0; i < 4; i++)
			{
				if (abs(Array[i]) < tinynumber)
				{
					Array[i] = 0;
				}
			}
		}

		Quaternion Conjugate() const
		{
			Quaternion Out;

			Out.A = A;
			Out.X = -X;
			Out.Y = -Y;
			Out.Z = -Z;

			return Out;
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

		return Right * Left;

	}


	typedef Quaternion<float> Quaternionf;
	typedef Quaternion<double> Quaterniond;
}