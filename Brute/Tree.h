#pragma once
#include"Check.h"
#include"node.h"
#include<vector>
#include<fstream>
using namespace std;

class Tree
{
private:
	node m_root;
	digit length;
	vector<length_t> solution;
	Check check;
	int solution_length;
	void Tree::next_layer(node& root);
public:
	Tree(digit length_, digit del);
	void solution_search();
	void print_solutions(ofstream& out);
	~Tree();
};

