#pragma once
#include<vector>
using namespace std;

struct node
{
	node * const parent;
	const int value;
	vector<int> next;

	node() : value(0), parent(nullptr) {}

	node(node* parent_) : parent(parent_), value(parent_->next.back()), next(parent_->next) {}

	node(node* parent_, int value_) : parent(parent_), value(value_), next(parent_->next) {}
};