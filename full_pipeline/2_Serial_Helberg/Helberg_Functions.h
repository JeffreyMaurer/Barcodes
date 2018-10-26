#pragma once
#include<vector>

using namespace std;

typedef unsigned int length_t;

const int MAX_LENGTH = 16;
const int MAX_DELETION = 5;

//const int ALPHABET = 4; //resurrect if not working on DNA anymore

static length_t weights[MAX_LENGTH][MAX_DELETION];            //stores known weights so there need not be more calculations than necessary

length_t Power(int, int);                        //Returns the power of one to the other as an int
length_t Moment(int, int, int, int);                    //Calculates the moment
length_t Weight(int, int, int);                    //Calculates the weight
bool Sort_Vector_Int(vector<int> i, vector<int> j);        //Sorts the Bad_Codes vector
