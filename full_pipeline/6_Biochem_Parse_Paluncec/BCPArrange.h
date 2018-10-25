#pragma once
#include"BioChem.h"
#include<iostream> //output messages
#include<fstream>  //file manip
#include<sstream>  //convert int to string for file names
#include<cstdlib>  //atoi, though iostream includes it itself
#include<functional>
#include<thread>

using namespace std;

const int MaxLength = 15;
const int MinLength = 3;

const short THREADCOUNT = 25;

typedef short digit;

inline length_t ToLength_t(string i) //converts a string to length_t
{
    length_t m = 0;
    for (int j = 0; j < i.length(); j++){
        m += (i[j] - '0') * Power(4, (i.length() - j) - 1);
    }
    return m;
}
inline length_t ToLength_t(length_t i)          //does nothing
{
   return i;
}  
//This is the datatype that stores the CodeBooks
struct CodeBook
{
    string Residue;
    vector<length_t> CodeWords;
    short GC; //Consider bitset or char, GC <= 24 always
};

//this sorts the codebooks
inline bool Sort_Residues(CodeBook i, CodeBook j) 
{
return (i.CodeWords.size() > j.CodeWords.size());
}

inline digit Digit(length_t code, digit d)
{
	return ((code >> (2*d)) & 3);
}

bool Good_Args(int argc, char* argv[], int &start, int &end);
string toQuad(length_t m, int n);
void Join(vector<thread>& i);
