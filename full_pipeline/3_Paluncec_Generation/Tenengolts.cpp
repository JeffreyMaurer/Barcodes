#include "Tenengolts.h"
#include"Helberg_Functions.h"
#include<string>
#include<iostream>

using namespace std;

length_t Power(int base, int exponent)
{
	if (exponent == 1) return base;
	else if (exponent == 2) return base*base;
	else if (exponent == 0)  return 1;
	length_t product = base;
	for (int i = 1; i < exponent; i++)
		product *= base;
	return product;
}

void Moment(length_t code, int n, int d, int p, vector<int> &residues){//Calculates the moment
	
	//tenengolts residues
	/*for (int i = 1; i <= d; i++)
	{
		short sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += Power(Digit(code, j), i);
		}
		residues[i-1] = (sum % p);
	}*/
	short sum(0);
	for (int j = 0; j < n; j++)
	{
		sum += Digit(code, j);
	}
	residues[0] = sum % p;

	sum = 0;
	for (int j = 0; j < n; j++)
	{
		sum += Power(Digit(code, j), 2);
	}
	residues[1] = sum % p;
	
	//Binary Helberg Code
	short binary_code(0);
	for (int k = 0; k < n - 1; k++)
	{
		digit m = (code >> k) % QUAT_DIGIT_MASK;
		digit n = (code >> k+1) % QUAT_DIGIT_MASK;
		if (n >= m) binary_code += (1 << k);
	}
	length_t h = Helberg_Moment(bitset<16>(binary_code), n, BINARY, d);
	
	residues[residues.size() - 1] = h % Weight(n + 1, BINARY, d);
}

int max(int n, int m)
{
	if (n > m) return n;
	else return m;
}

int Prime(int lower)
{
	/*
	bool divisible = false;
	lower++;
	while (true)
	{
		for (int i = 2; i <= (lower/2); i++)
		{
			if (0 == (lower % i)) { divisible = true; break; }
		}
		if (divisible) { lower++; divisible = false; }
		else return lower;
	}
	*/
	if (lower == 2 || lower == 1) return 3;
	else if (lower > 2 && lower < 5) return 5;
	else if (lower == 5 || lower == 6) return 7;
}

string toQuad(int code, int n)
{
	string output;
//	cout << code << endl;
//	cout << bitset<32>(code) << endl;
	for (int i = n - 1; i >= 0; i--)
	{
//		cout << Digit(code, i) << endl;
		output += to_string(Digit(code, i));
	}
	return output;
}