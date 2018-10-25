#include "Helberg_Functions.h"
#include "Tenengolts.h"
#include<iostream>

using namespace std;

//how to do the binary conversion
length_t Helberg_Moment(bitset<16> code, int n, int q, int d){//Calculates the moment
	length_t sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += Weight(i, q, d) * code[i-1];
	}
	return sum;
}

length_t Weight(int i, int q, int d){//Calculates the weight
	if (weights[i])
		return weights[i];
	if (i <= 0)
		return 0;
	else if (i == 1)
		return 1;
	length_t sum = 0;
	for (int j = 1; j <= d; j++)
	{
		sum += Weight((i - j), q, d);
	}
	sum = 1 + ((q - 1) * sum);
	weights[i] = sum;
	return sum;
}
