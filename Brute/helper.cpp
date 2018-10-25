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

ostream& operator<<(ostream& os, vector<bool>& input)
{
	for (int i = 0; i < input.size(); i++)
	{
		os << input[i] << " ";
	}
	return os;
}

ostream& operator<<(ostream& os, vector< duration<double> >& input)
{
	for (int i = 0; i < input.size(); i++)
	{
		os << input[i].count() << " ";
	}
	return os;
}

ostream& operator<<(ostream& os, vector<int>& input)
{
	for (int i = input.size() - 1; i >= 0; i--)
	{
		os << input[i] << "\n";
	}
	return os;
}

ostream& operator<<(ostream& os, node& input)
{
	os << "value: " << input.value << "\t parent value: " << input.parent->value <<
		"\nvalues of next: " << input.next << endl;
	return os;
}

ostream& operator<<(ostream& os, Data& input)
{
	os << input.length << ',' << input.setsize << ',' << input.num_additions << ',' <<
		input.avg_num_attempts;

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