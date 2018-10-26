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
inline string toQuad(length_t m, int n)           //length_t to quad int string
{
    string quad;
    int g;

    for (int j = (n - 1); j >= 0; j--)
    {
        g = (m & (3 * Power(4, j))) >> (j * 2);
        stringstream ss;
        ss << g;
        quad.append(ss.str());
    }

    return quad;
}
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

//Joins all of the biochem threads
void Join(vector<thread> &T)
{
    for (int i = 0; i < T.size(); i++) T[i].join();
}

//make sure input is good
bool Good_Args(int argc, char* argv[], int &start, int &end)
{
    if (argc == 1)
    {
        cerr << "No parameters passed" << endl;
        return 1;
    }
    else if (argc == 2)
    {
        if (atoi(argv[1]) >= MinLength && atoi(argv[1]) <= MaxLength)
        {
            start = atoi(argv[1]);
            end = atoi(argv[1]);
        }
        else if (!atoi(argv[1]))
        {
            cerr << "That parameter is not a number" << endl;
            return 1;
        }
        else if (atoi(argv[1]) < MinLength || atoi(argv[1]) > MaxLength)
        {
            cerr << "That codeword length has not been processed" << endl;
            return 1;
        }
    }
    else if (argc == 3)
    {
        if (atoi(argv[1]) && atoi(argv[2]) && atoi(argv[1]) < atoi(argv[2]) &&
            atoi(argv[1]) >= MinLength && atoi(argv[1]) <= MaxLength && atoi(argv[2]) >= MinLength && atoi(argv[2]) <= MaxLength)
        {
            start = atoi(argv[1]);
            end = atoi(argv[2]);
        }
        else if (atoi(argv[1]) && atoi(argv[2]) && atoi(argv[1]) > atoi(argv[2]) &&
                 atoi(argv[1]) >= MinLength && atoi(argv[1]) <= MaxLength && atoi(argv[2]) >= MinLength && atoi(argv[2]) <= MaxLength)
        {
            start = atoi(argv[2]);
            end = atoi(argv[1]);
        }
        else if (!atoi(argv[1]))
        {
            cerr << "Arg 1 is not a number" << endl;
            return 1;
        }
        else if(!atoi(argv[2]))
        {
            cerr << "Arg 2 is not a number" << endl;
            return 1;
        }
        else if (atoi(argv[1]) < MinLength || atoi(argv[1]) > MaxLength)
        {
            cerr << "That codeword length has not been processed for arg 1" << endl;
            return 1;
        }
        else if (atoi(argv[2]) < MinLength || atoi(argv[2]) > MaxLength)
        {
            cerr << "That codeword length has not been processed for arg 2" << endl;
            return 1;
        }
        else
        {
            cerr << "Two parameters passed. Something is wrong, more information needed to diagnose" << endl;
            return 1;
        }
    }
    else
    {
        cerr << "Either too many parameters passed, or something else entirely" << endl;
        return 1;
    }
}

