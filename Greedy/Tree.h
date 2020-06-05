#pragma once
#include"Check.h"
#include<vector>
#include<string>
#include<fstream>
#include<chrono>
using namespace std;

class Tree
{
private:
	digit length;
	digit del;
	vector<length_t> solution;
	Check check;
public:
	Tree(digit length_, digit del);
	void solution_search();
	void print_solutions(ofstream& out);
	~Tree();
};

