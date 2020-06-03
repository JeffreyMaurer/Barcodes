#pragma once
#include "helper.h"
#include<vector>
using namespace std;

class Check //can't this be replaced with just a function that gets the levenshtein distance?
{
private:
	digit length, del;
	vector< vector<bool> > routes;
	vector< vector<int> > dynamic_matrix;
public:
	Check(digit length, digit del);
	bool is_compatible(int first, int second);
	int levenshtein_dist(int first, int second);
	~Check();
};



