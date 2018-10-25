#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<thread>
#include"Check.h"

using namespace std;

struct codeword
{
    length_t word;
    vector<length_t> bad;
    //codeword(string a) : word(atoi(a.c_str())) {}
    codeword(string a) : word(fromQuad(a.c_str())) {}
};

struct codebook
{
    string name;
    vector<codeword> codes;
};

bool Toss(codebook&);

inline void Join(vector<thread>& T)
{
    for (auto& worker : T)
    {
        worker.join();
    }
}
