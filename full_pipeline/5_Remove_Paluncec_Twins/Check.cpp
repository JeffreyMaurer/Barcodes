#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<bitset>
#include"Check.h"

using namespace std;

bool Check(length_t first, length_t second, digit length, digit del)
{
	vector<digit> vfirst(length), vsecond(length);
	for (digit i = 0; i < length; i++)
	{
		vfirst[i] = Digit(first, i);
		vsecond[i] = Digit(second, i);
	}

	bool answer = true;
	return Delete_Tree(vfirst, vsecond, del, del, answer, del);
}

bool Delete_Tree(vector<digit> &first, vector<digit> &second, digit FIRST_DEPTH, digit SECOND_DEPTH, bool &answer, digit iter)
{
	//add condition that says that !answer || depth both zero and vectors are equal
	if (!answer) return answer; //if the answer has been found, pop

	bool CHANGE = false; //change indicates whether there is an inequality present

	while (iter < first.size()) //go through the words
	{
		if (first[iter - FIRST_DEPTH] != second[iter - SECOND_DEPTH])
		{
			CHANGE = true;  break;
		}
		else 
		{ 
			iter++; 
		}
	}

	if (CHANGE) //if change is true, we found an inequality
	{
		if (FIRST_DEPTH) //if there are still deletions left here, go down
		{
			Delete_Tree(first, second, --FIRST_DEPTH, SECOND_DEPTH, answer, iter);
		}
		if (SECOND_DEPTH && answer) //if the other if statement did not find the answer and there are still deletions left here, go down
		{
			Delete_Tree(first, second, FIRST_DEPTH, --SECOND_DEPTH, answer, iter);
		}
		if (!(FIRST_DEPTH || SECOND_DEPTH)) //the counters are both zero, hence at a leaf and found a change
		{
			//inequality but out of deletions, not twins using this path
			return answer;
		}
	}
	//made it to the end of the word and found no inequalities
	//given that not breaking at a leaf, there are still deletions left
	//thus, they are less than 2 distance apart
	else answer = false;

	return answer;
}

string toQuad(length_t m, digit n)
{
	string quad;

	for (int j = (n - 1); j >= 0; j--)
	{
		quad += to_string(Digit(m, j));
	}

	return quad;
}

//check this, make it better
length_t fromQuad(string quad)
{
	digit j(0); length_t result(0);
	for (digit i = quad.length() - 1; i >= 0; i--)
	{
		result += (((digit)quad[i]) - '0') * Power(4, quad.length() - (i+1));
	}
	return result;
}

length_t Power(int n, int m){ //Returns the power of one to the other as an int
	if (m == 0) return 1;
	else if (m == 1) return n;
	length_t product = n;
	for (int i = 1; i < m; i++){
		product *= n;
	}
	return product;
}
