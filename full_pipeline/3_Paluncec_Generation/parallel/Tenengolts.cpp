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

//Calculates the moment
void Moment(length_t code, int length, int d, int p, vector<short> &residues)
{	
	short sum1(0);
	for (int j = 0; j < length; j++)
	{
		sum1 += Digit(code, j);
	}
	residues[B1_RESIDUE] = sum1 % p;

	short sum2(0);
	for (int j = 0; j < length; j++)
	{
		sum2 += Power(Digit(code, j), 2);
	}
	residues[B2_RESIDUE] = sum2 % p;
	
	//Binary Helberg Code
	short binary_code(0);
	for (int k = length-1; k >= 0; k--)
	{
		digit m = Digit(code, k);
		digit n = Digit(code, k-1);
		if (n >= m)
		{
			binary_code += (1 << (length - (k+1)));
		}
	}

	length_t h = Helberg_Moment(bitset<MAX_INDEX>(binary_code), length-1, BINARY, d);

	residues[HELBERG_RESIDUE] = h % Weight(length, BINARY, d);
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

string toQuad(length_t code, digit n)
{
	string output;
	for (int i = n - 1; i >= 0; i--)
	{
		output += to_string(Digit(code, i));
	}
	return output;
}
