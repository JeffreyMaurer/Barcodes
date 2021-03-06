#include"Tree.h"
#include"Check.h"
#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<cstdlib>
#include<vector>
using namespace std;

inline bool GoodArgs(int argc, char** argv)
{
	return (argc == 4) && //3 arguments 
		   (atoi(argv[1]) <= atoi(argv[2])) && //lower bound smaller than larger bound
		   (atoi(argv[3]) < atoi(argv[1])); //del arg smaller than smallest length
}

int main(int argc, char** argv)
{
	if (!GoodArgs(argc, argv)) {std::cout << "bad input" << endl; return -1;}

	digit del = atoi(argv[3]);
	for (digit length = atoi(argv[1]); length <= atoi(argv[2]); length++) 
	{
		using namespace chrono;
		auto begin = high_resolution_clock::now();

		ofstream out("data/BruteL" + to_string(length) + "D" + to_string(del) + "_greedy.txt");

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
			std::cout << error_message << endl;
		}
	
		auto end = high_resolution_clock::now();
		auto dur = duration_cast<duration<double>> (end - begin);
		out << "took " << dur.count() << " seconds" << endl;
	}

	return 2;
}
