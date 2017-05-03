#pragma once
#include <cmath>
#include "Fraction.h"

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
				numtype X;
				numtype Y;
				numtype Z;
			};
		};

		Quaternion() : A(0), X(0), Y(0), Z(0) {  };
		Quaternion(numtype _A, numtype _X, numtype _Y, numtype _Z) : A(_A), X(_X), Y(_Y), Z(_Z) { };

		void Normalize()
		{
			Fraction<double, double> Frac;
			Frac.SetNumerator(1.0);
			Frac.SetDenominator(Magnitude());
			for (size_t i = 0; i < 4; i++)
			{
				Array[i] *= (numtype)Frac.GetDecimal();
			}
		};

	private:

		numtype SqrMagnitude()
		{
			numtype Sum = 0;
			for (size_t i = 0; i < 4; i++)
			{
				Sum += Array[i] * Array[i];
			}
			return Sum;
		};

		double Magnitude()
		{
			return sqrt((double)SqrMagnitude());
		}

	};

	typedef Quaternion<float> Quaternionf;
	typedef Quaternion<float> Quaterniond;
}