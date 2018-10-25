#include<iostream>
#include<fstream>
#include<vector>
#include"Tenengolts.h"
#include"Helberg_Functions.h"
/*
Moment(length_t code, int n, int d, int p, vector<int> &residues)
*/

int hell()
{
	vector<int> residues(3);
	Moment(10, //code 022
		3, //length
		2, //d
		5, //p
		residues //vector, should be 4, 3, x
		);
	for (int i = 0; i < residues.size(); i++)
		cout << residues[i] << endl;
	system("pause");
	return 0;
}