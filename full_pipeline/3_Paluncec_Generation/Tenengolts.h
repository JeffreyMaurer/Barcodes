#pragma once
#include<string>
#include<vector>
#include"Helberg_Functions.h"

using namespace std;

typedef short digit;

static const int QUATERNARY = 4;
static const digit QUAT_DIGIT_MASK = 3;

length_t Power(int, int);										//Returns the power of one to the other as an int
void Moment(length_t code, int n, int d, int p, vector<int>& residues);		//Calculates the moment
int max(int, int);
int Prime(int);
string toQuad(int code, int n);

inline digit Digit(length_t code, int digit) { return ((code >> (digit * 2)) & QUAT_DIGIT_MASK); }