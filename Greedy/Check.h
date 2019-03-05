#pragma once
#include "helper.h"
#include<vector>
using namespace std;

class Check
{
private:
	digit length, del;
	vector< vector<bool> > routes;
public:
	Check(digit length, digit del);
	bool is_compatible(int first, int second);
	~Check();
};

