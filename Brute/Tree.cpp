#include "Tree.h"
#include"helper.h"
#include<algorithm>
#include<iomanip>
#include<thread>
using namespace std;

Tree::Tree(digit length_, digit del_) : length(length_), check(length_, del_), solution() {}

void Tree::solution_search()
{
	int num = power(quaternary, length);
	ofstream log("logs/" + to_string(length) + "log.txt");
	for (int contender = 0; contender < num; contender++)
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

/*void Tree::next_layer(node& root)
{
	thread dump(&node::mem_dump, root.parent);

	while (root.next.size())
	{
		//new node!!
		node leaf(&root);

		//remove the value used to create leaf
		root.next.pop_back();
		leaf.next.pop_back();

		//3 ideas for prune, f_it e, r_it e, and e-r idiom

		//prune next
		for (auto num = leaf.next.begin(); num != leaf.next.end(); num++)
		{
			if (!check.is_compatible(leaf.value, *num))
			{
				*num = INT_MAX;
			}
		}

		leaf.next.erase(remove(leaf.next.begin(), leaf.next.end(), INT_MAX), leaf.next.end());

		leaf.next.shrink_to_fit();

		//we made it to the end, is this a solution route?
		if (leaf.next.empty())
		{
			if (leaf.distance > solution_length)
			{
				solutions.clear();
				solution_length = leaf.distance;

				node * backtrack = &leaf;
				string solution;
				while (backtrack->parent != nullptr)
				{
					solution += to_string(backtrack->value) + " ";
					backtrack = backtrack->parent;
				}

				solutions.push_back(solution);
				if (solution_length >= 5390)
				{
					ofstream out("data/L12D2S" + to_string(solution_length) + "_mem.txt");
					//node * backtrack = &leaf;
					//while (backtrack->parent != nullptr)
                                	//{
                                        	//out << to_string(backtrack->value) << '\n';
                                        	//backtrack = backtrack->parent;
                                	//}
                                	out << solution << endl;
				}
			}
			else if (leaf.distance == solution_length)
			{
				node * backtrack = &leaf;
				string solution;
				while (backtrack->parent != nullptr)
				{
					solution += to_string(backtrack->value) + " ";
					backtrack = backtrack->parent;
				}

				solutions.push_back(solution);
			}

			continue;
		}

		//recurse!! depth first
		next_layer(leaf);

	} //while loop

	dump.join();
	root.parent->mem_retrieve();
}*/

void Tree::print_solutions(ofstream& out)
{
	out << solution << endl;
	out << solution.size() << endl;
}

Tree::~Tree() {}
