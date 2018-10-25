#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<chrono>
#include<ctime>
#include<ratio>
#include<algorithm>
#include<thread>
#include<functional>
#include <unistd.h>
#include"Tenengolts.h"
#include"Helberg_Functions.h"
//#include"MultiMatrix.h"

using namespace std;

/*
The next step in this for the longer codes will be to process a few at time 
so that we don't use too much RAM. Thus the algorithm will be:

1)Clear all files, create 1 file per unique residue set.
2)Go through the generation loop a few times but not all the way around.
3)Append to the files the found codewords.
4)Go back to 2 until all codes have been looked at.
5)merge files into the 25 for each length using a shell script TODO


#!/bin/csh

for i=0 to 4:
	for j=0 to 4:
		cat `ls "*${i}-${j}*"`
	next
next

*/

//ptint output, called for each unique set of tenengolts codes
void Output(string outname, vector<codeword>& section, length_t weight, digit length);

//join all threads that the vector contains
void Join(vector<thread>& workers);

int main(int argc, char * argv[])
{
    //some variables
    length_t length;
    int del = 2;
    int p = Prime(max(QUATERNARY - 1, del)); //the length of each dimension
    int arg1 = atoi(argv[1]), arg2 = atoi(argv[2]), arg3 = atoi(argv[3]);

    if (arg2 > 16) return -1;
    if (arg2 > 14 && arg3 < 7) return -1;
    if (arg2 > 15 && arg3 < 31) return -1;
    if (arg2 > 16 && arg3 < 127) return -1;
    if (arg2 > 17 && arg3 < 255) return -1;
    if (arg2 > 18 && arg3 < 1023) return -1;

    //TODO: less needed, but make mM work
    //mM matrix(del, p);

    //process the lengths of blah to blah
    for (length = arg1; length <= arg2; length++)
    {
      string logname ="/csm_data/experimentalmath/maurer/Logfiles/Tenengolts/Generate/parallel/" +
                      to_string(length) + "mem" + to_string(arg3) + ".txt";
      ofstream log(logname.c_str());

      for (int mem = 0; mem < arg3; mem++){
        //time profiling
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        vector<codeword>  codewords(Power(QUATERNARY, length)/arg3);

        log << "mem: " << mem << endl;

        //make the data, embarrassingly parallel
        for (length_t i = ((Power(QUATERNARY, length) * mem) / arg3); 
             i < ((Power(QUATERNARY, length) * (mem + 1)) / arg3); i++) 
        {
            length_t iter = i %(Power(QUATERNARY, length)/arg3);
            codewords[iter].number = i;
            Moment(i, length, del, p, codewords[iter].residues);
            //matrix.push_back(residues, i);
        }

        //out << matrix;
        
        //for time profiling purposes
        chrono::high_resolution_clock::time_point processing = chrono::high_resolution_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(processing - start);
        log << "time processing: " << time_span.count() << endl;

        vector< vector<codeword> > sections(Power(p, del)); //del = 2
        vector<thread> workers;

        for (auto& word : codewords)
        {
            sections[word.residues[B1_RESIDUE] * p + word.residues[B2_RESIDUE]].push_back(word);
        }

        for (int i = 0; i < p; i++) //make into a single loop
        {
            for (int j = 0; j < p; j++)
            {
                log << "(" << i << "," << j << ") ";// << '\n';
                short position = (i * p) + j;

                string outname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Pieces/" + 
				to_string(length)+ "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + 
				"P" + to_string(mem) + ".txt";
                    
                workers.emplace_back(Output, outname, ref(sections[position]), Weight(length, BINARY, del), length);
            } //j
            log << '\n';
        } //i
        Join(workers);

        chrono::high_resolution_clock::time_point done = chrono::high_resolution_clock::now();
        chrono::duration<double> time_span2 = chrono::duration_cast<chrono::duration<double> >(done - start);
        log << "time " << length << ": " << time_span2.count() << endl;

      }//mem
      log.close();
    } //length loop

    return 0;
}


void Output(string outname, vector<codeword>& section, length_t weight, digit length)
{
    ofstream out(outname.c_str());
    for (int k = 0; k < weight; k++) 
    {
        string output = "HR" + to_string(k) + '\n';
        for (auto& word : section) //check at rucc
        {
            if (word.residues[HELBERG_RESIDUE] == k)
            {
                output += toQuad(word.number, length) + '\n';
            } //if
        } //section
        output += '\n';
        out << output;
    }//k
}

void Join(vector<thread> &workers)
{
    for (auto& worker : workers)
    {
        worker.join();
    }
}
