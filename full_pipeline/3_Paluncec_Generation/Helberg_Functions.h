#pragma once
#include<string>
#include<vector>
#include<bitset>

using namespace std;

typedef int length_t;

const int MAX_INDEX = 16;
const int BINARY = 2;

static length_t weights[MAX_INDEX];								//stores known weights so there need not be more calculations than necessary

length_t Helberg_Moment(bitset<16> code, int n, int q, int d);	//Calculates the moment
length_t Weight(int i, int q, int d);							//Calculates the weight