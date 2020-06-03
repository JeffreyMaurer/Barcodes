#include"helper.h"

int power(int base, int exponent)
{
	if (exponent == 0) return 1;
	else if (exponent == 1) return base;
	else if (exponent == 2) return base*base;
 	int sum = base;
	for (int i = 1; i < exponent; i++) sum *= base;
	return sum;
}

ostream& operator<<(ostream& os, vector<int>& input)
{
	for (int i = input.size() - 1; i >= 0; i--)
	{
		os << input[i] << "\n";
	}
	return os;
}

inline string toQuad(int code, digit length)
{
	string num;
	for (int i = length - 1; i >= 0; i--)
	{
		num += to_string(Digit(code, i));
	}
	return num;
}