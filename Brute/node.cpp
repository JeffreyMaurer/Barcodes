#include"node.h"
#include<fstream>
#include<string>
#include<iostream>
#include<cstdio>
using namespace std;

/*void node::mem_dump() 
{
	ofstream next_data;
	if (parent != nullptr) 
	{
		next_data.open("/csm_data/experimentalmath/maurer/Tenengolts_Generate/brute/" + to_string(value) + "from" + to_string(parent->value) + ".txt");
	}
	else
	{
		next_data.open("/csm_data/experimentalmath/maurer/Tenengolts_Generate/brute/" + to_string(value) + "from_root.txt");
	}

	for (int i = 0; i < next.size(); i++)
	{
		next_data << next[i] << '\n';
	}

	vector<int>().swap(next);

	next_data.close();
}

void node::mem_retrieve()
{
	ifstream next_data;
	string name;
	if (parent != nullptr)
	{
		name = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/brute/" + to_string(value) + "from" + to_string(parent->value) + ".txt";
		next_data.open(name.c_str());
	}
	else
	{
		name = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/brute/" + to_string(value) + "from_root.txt";
		next_data.open(name.c_str());
	}

	string one_entry;
	while (getline(next_data, one_entry))
	{
		next.push_back(stoi(one_entry));
	}

	next_data.close();

	remove(name.c_str());
}*/


