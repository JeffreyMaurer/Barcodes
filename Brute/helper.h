#pragma once
#include<iostream>
#include<vector>
#include<chrono>
#include<string>
#include"node.h"
using namespace std;
using namespace chrono;

using ull_t = unsigned long long;
using digit = short;
const int quaternary = 4;

struct Data
{
	int length;
	int setsize;
	int num_additions;

	int avg_num_attempts;

	Data(int length_ = 0, int setsize_ = 0, int num_additions_ = 0, int avg_num_attempts_ = 0) :
		length(length_), setsize(setsize_), num_additions(num_additions_),
		avg_num_attempts(avg_num_attempts_)	{}
};

int power(int base, int exponent);
ostream& operator<<(ostream& os, vector<bool>& input);
ostream& operator<<(ostream& os, vector<int>& input);
ostream& operator<<(ostream& os, vector< duration<double> >& input);
ostream& operator<<(ostream& os, node& input);
ostream& operator<<(ostream& os, Data& input);

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