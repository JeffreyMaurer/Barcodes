#pragma once
#include<vector>

using namespace std;

typedef int length_t;
typedef short digit;

static const digit QUAD_DIG_MASK = 3;

//setup for the tree
bool Check(length_t first, length_t second, digit length, digit del); //adapted from Tran's algorithm

//go through a recursive algorithm to see if they are twins
bool Delete_Tree(vector<digit> &first, vector<digit> &second, 
		digit FIRST_DEPTH, digit SECOND_DEPTH, bool &answer, digit start);

//convert a code to a quaternary string for printing
string toQuad(length_t m, digit n);

//convert a quaternary string to a number
length_t fromQuad(string quad);

//what is the n to the power of m
length_t Power(int n, int m);

//returns the specified digit
inline digit Digit(length_t code, digit d) { return (code >> (d * 2)) & QUAD_DIG_MASK; }

//returns the larger of the two numbers
inline digit Max(digit i, digit j)
{
	if (i > j) return i;
}
