#pragma once
#include<vector>
using namespace std;

struct node
{
	node * const parent;
	const int distance;
	const int value;
	vector<int> next;

	node() : value(0), distance(0), parent(nullptr) {}

	node(node* parent_) : 
		parent(parent_), 
		value(parent_->next.back()), 
		distance(parent_->distance + 1), 
		next(parent_->next) 
		{}

	node(node* parent_, int value_) : 
		parent(parent_), 
		value(value_), 
		distance(parent_->distance + 1),
		next(parent_->next) 
		{}

	void mem_dump();
	void mem_retrieve();
};
