#pragma once
#include<string>
#include<vector>
#include"Helberg_Functions.h"

using namespace std;

typedef short digit;

struct codeword
{
	length_t number;
	vector<short> residues;
	codeword(int i) : residues(3), number(i) {}
	codeword() : residues(3)  //check this again once on server
	{}
};

static const int QUATERNARY = 4;
static const digit QUAT_DIGIT_MASK = 3;

static const short B1_RESIDUE = 0;
static const short B2_RESIDUE = 1;
static const short HELBERG_RESIDUE = 2;

//Returns the power of one to the other as an int
length_t Power(int, int);									

//Calculates the moment
void Moment(length_t code, int n, int d, int p, vector<short>& residues);

//returns the larger int
int max(int, int);

//returns the smallest prime number larger than m
int Prime(int m);

//converts an integer into a quaternary code
string toQuad(length_t code, digit n);

inline digit Digit(length_t code, int digit) { return ((code >> (digit * 2)) & QUAT_DIGIT_MASK); }

/*
vector<string> split(const char *str, char c)
{
vector<string> result;

do
{
const char *begin = str;

while(*str != c && *str)
str++;

result.push_back(string(begin, str));
} while (0 != *str++);

return result;
}
*/
