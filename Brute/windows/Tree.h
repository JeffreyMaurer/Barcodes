#pragma once
#include"node.h"
#include"Check.h"
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class Tree
{
private:
	node m_root;
	digit length;
	vector<string> solutions;
	short solution_length;
	Check check;
	void next_layer(node& leaf);
public:
	Tree(digit length_, digit del);
	void solution_search();
	void print_solutions(ofstream& out);
	~Tree();
};

