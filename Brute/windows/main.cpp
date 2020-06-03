#include"Tree.h"
#include"Check.h"
#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<iterator>
#include<random>
using namespace std;

int main()
{
	using namespace chrono;
	auto begin = high_resolution_clock::now();

	int length = 4;
	int del = 2;

	ofstream out("BruteL" + to_string(length) + "D" + to_string(del) + ".txt");

	try
	{
		Tree tree(length, del);
		tree.solution_search();
		tree.print_solutions(out);

	}
	catch (int& error)
	{
		string error_message;
		switch (error)
		{
		case 0: error_message = "Wanted error-correction capability too large compared to desired length."; break;
		case 1: error_message = "Incorrect number of deletions--either nonnegative or too high."; break;
		default:
			break;
		}
		cout << error_message << endl;
	}
	
	auto end = high_resolution_clock::now();
	duration<double> dur = duration_cast<duration<double>> (end - begin);
	cout << "took " << dur.count() << " seconds" << endl;

	system("pause");

	return 0;
}