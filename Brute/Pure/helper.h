#pragma once
#include<iostream>
#include<vector>
#include<chrono>
#include<string>
#include"node.h"
using namespace std;
using namespace chrono;

using digit = short;
const int quaternary = 4;

int power(int base, int exponent);
ostream& operator<<(ostream& os, vector<int>& input);

template<typename T>
ostream& operator<<(ostream& os, vector<T>& input)
{
	for (int i = 0; i < input.size(); i++)
	{
		os << input[i] << "\n";
	}
	return os;
}

inline string toQuad(int code, digit length);

inline int num_permutations(digit deletions)
{
	if (deletions == 0) return 1;
	if (deletions == 1) return 2;
	if (deletions == 2) return 6;
	if (deletions == 3) return 20;
	if (deletions == 4) return 70;
	else
	{
		throw 1;
	}
}

inline digit Digit(int num, digit dig)
{
	return (num >> (dig * 2)) & 3;
}