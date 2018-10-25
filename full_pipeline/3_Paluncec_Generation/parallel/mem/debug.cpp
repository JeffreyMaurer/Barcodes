#include<iostream>
#include<fstream>
#include<vector>
#include<thread>
#include"Tenengolts.h"
#include"Helberg_Functions.h"

using namespace std;

length_t fromQuad(string quad);

void print(vector<int>& set);

int hell()
{
	codeword temp(fromQuad("31323312"));
	//0  1  1  0  1  0  1
	//33 20 12 7  4  2  1
	//1+4+12+20 = 37
	//1  2  4  7 12 20 33
	//2 4 12 33 = 51
	//0 1 0 1  1  0  1
	//1 2 4 7 12 20 33 = 54 = 0
	//
	Moment(temp.number, 8, 2, 5, temp.residues);


	//codeword temp1(fromQuad("22303"));
	//Moment(temp1.number, 5, 2, 5, temp1.residues);
	//1 1 0 1
	//1 2 4 7 12
	//HB10

	//codeword temp2(fromQuad("010233110"));
	//Moment(temp2.number, 9, 2, 5, temp2.residues);
	//1  0  1 1 1 0 1 0
	//1  0  1  1  1  0  1  0
	//1  2  4  7  12 20 33 54 88
	//1 4 7 12 33 = 57
	vector<int> full_set(100);

	for (int i = 0; i < full_set.size(); i++)
	{
		full_set[i] = i;
	}

	//ofstream out("debugging_thread.vector_races.txt");

	system("pause");
	return 0;
}

void print(vector<int>& set)
{
	vector<int> little_set;
	for (int i = 0; i < set.size(); i++)
	{
		little_set.push_back(set[i]);
	}
}

length_t fromQuad(string quad)
{
	digit j(0); length_t result(0);
	for (digit i = quad.length() - 1; i >= 0; i--)
	{
		//cout << "digit: " << quad[i] << endl;
		//cout << "digit resolved: " << (((digit)quad[i]) - 48) << endl;
		//cout << "unit: " << Power(4, quad.length() - (i+1)) << endl;
		result += (((digit)quad[i]) - 48) * Power(4, quad.length() - (i + 1));
		//cout << "result" << result << endl;
	}
	return result;
}

/*
for (int i = 0; i < 5; i++)
{
	static int j(0);
	cout << j++ << endl;
}
*/