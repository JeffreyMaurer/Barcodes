#pragma once
#include"BioChem.h"
#include<iostream> //output messages
#include<fstream>  //file manip
#include<sstream>  //convert int to string for file names
#include<cstdlib>  //atoi, though iostream includes it itself

using namespace std;

const int MaxLength = 15;
const int MinLength = 3;

inline length_t ToLength_t(string);            //converts a string to length_t
inline length_t ToLength_t(length_t);          //does nothing
inline string toQuad(length_t, int);           //length_t to quad int string

//This is the datatype that stores the CodeBooks
struct CodeBook
{
    string Residue;
    vector<length_t> CodeWords;
    short GC; //Consider bitset or char, GC <= 24 always
};

//this sorts the codebooks
bool Sort_Residues(CodeBook i, CodeBook j) 
{
return (i.CodeWords.size() > j.CodeWords.size());
}

