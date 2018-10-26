#pragma once
#include"node.h"
#include"Check.h"
#include<vector>
#include<string>
#include<fstream>
#include<chrono>
using namespace std;
using namespace chrono;

//TODO: use SFML to visualize the tree

enum eDuration
{
	CREATION, POP, CHECK, REMOVE_ERASE, SOLUTION, SIZE
};

class Tree
{
private:
	node m_root;
	digit length;
	vector<string> solutions;
	short solution_length;
	Check check;
	void next_layer(node& leaf);
	duration<double> durs;
public:
	Tree(digit length_, digit del);
	void solution_search();
	void print_solutions(ofstream& out);
	~Tree();
};

