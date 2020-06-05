#include "Tree.h"
#include"helper.h"
#include<algorithm>
#include<iomanip>
#include<thread>
using namespace std;

Tree::Tree(digit length_, digit del_) : length(length_), del(del_), check(length_, del_), solution() {}

void Tree::solution_search()
{
	int num = power(quaternary, length); //off-by-one
	ofstream log("log/L" + to_string(length) + "D" + to_string(del) + "log.txt");
	solution.push_back(0);
	for (int contender = 1; contender < num; contender++)
	{
		//can this number work with all previous
		//this loop can be parallelized, but bad must be atomized
		bool bad = false;
		for (auto& value : solution)
		{
			if (!check.is_compatible(contender, value))
			{
				bad = true;
				break;
			}
		}
		if (!bad) 
		{
			solution.push_back(contender);
			log << (float) contender / num<< endl;
		}
	}
}

void Tree::print_solutions(ofstream& out)
{
	for (auto& value : solution)
	{
		out << toQuad(value, length) << endl;
	}
	out << endl;
	out << solution.size() << endl;
}

Tree::~Tree() {}
