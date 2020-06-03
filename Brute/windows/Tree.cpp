#include "Tree.h"
#include"helper.h"
#include<algorithm>

Tree::Tree(digit length_, digit del_) : length(length_), check(length_, del_), solution_length(1) {}

void Tree::solution_search()
{
	int num = power(quaternary, length);
	for (int i = 0; i < num - solution_length; i++)
	{
		//expand from the root
		node leaf(&m_root, i);

		//which nums can work with this num?
		for (int j = num-1; j >= i; j--)
		{
			if (check.is_compatible(i, j))
			{
				leaf.next.push_back(j);
			}
		}

		//start the depth-first search
		next_layer(leaf);
	}
}

void Tree::next_layer(node& root)
{
	while (root.next.size())
	{
		//new node!!
		node leaf(&root);

		//remove the value used to create leaf
		root.next.pop_back();
		leaf.next.pop_back();

		//prune next
		for (auto num = leaf.next.rbegin(); num != leaf.next.rend(); num++)
		{
			if (!check.is_compatible(leaf.value, *num))
			{
				*num = INT_MAX;
			}
		}

		leaf.next.erase(remove(leaf.next.begin(), leaf.next.end(), INT_MAX), leaf.next.end());

		//we made it to the end, is this a solution route?
		if (leaf.next.empty())
		{
			node * backtrack = &leaf;
			int distance(0);
			string solution;
			while (backtrack->parent != nullptr)
			{
				solution += to_string(backtrack->value) + " ";
				distance++;
				backtrack = backtrack->parent;
			}

			if (distance > solution_length)
			{
				solutions.clear();
				solution_length = distance;
				solutions.push_back(solution);
			}
			else if (distance == solution_length)
			{
				solutions.push_back(solution);
			}

			return;
		} // if (leaf.next.empty())
		else 
		{
			//recurse!! depth first
			next_layer(leaf);
		}

	} //for loop
}

void Tree::print_solutions(ofstream& out)
{
	for (auto& solution : solutions)
	{
		out << solution << endl;
	}
}

Tree::~Tree() {}
