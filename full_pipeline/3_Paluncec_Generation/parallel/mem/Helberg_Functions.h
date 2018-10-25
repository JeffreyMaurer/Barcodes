#pragma once
#include<string>
#include<vector>
#include<bitset>

using namespace std;

typedef long length_t;

const int MAX_INDEX = 16;
const int BINARY = 2;

static length_t weights[MAX_INDEX];		//hash table for weights

length_t Helberg_Moment(bitset<MAX_INDEX> code,	//Calculates the moment
	int length, int q, int del);	

length_t Weight(int i, int q, int d);		//Calculates the weight
