#pragma once
namespace QuaternionLibrary
{

	template <typename numtype, typename returntype> struct Fraction
	{
		void SetNumerator(numtype newnumerator)
		{
			numerator = newnumerator;
			decimal = (float)numerator / (float)denominator;
		}
		void SetDenominator(numtype newdenominator)
		{
			denominator = newdenominator;
			decimal = (float)numerator / (float)denominator;
		}
		numtype GetNumerator() { return numerator; }
		numtype GetDenominator() { return denominator; }
		returntype GetDecimal() { return decimal; }
	private:
		numtype numerator = 1;
		numtype denominator = 1;
		returntype decimal = 1;
	};
}