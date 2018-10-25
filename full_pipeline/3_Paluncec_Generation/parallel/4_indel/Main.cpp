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
5)merge files into the 25 for each length using a shell script


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
    bool 
        single = false, 
        mult1 = true;

    int arg1 = atoi(argv[1]), arg2 = atoi(argv[2]);
    string logname =	"/csm_data/experimentalmath/maurer/Logfiles/Tenengolts/Generate/parallel/" + 
			to_string(arg1) + "_" + to_string(arg2) + ".txt";
    ofstream log(logname.c_str());

    //TODO: less needed, but make mM work
    //mM matrix(del, p);

    //process the lengths of blah to blah
    for (length = atoi(argv[1]); length <= atoi(argv[2]); length++)
    {
        //time profiling
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        vector<codeword>  codewords(Power(QUATERNARY, length));

        //make the data
        for (length_t i = 0; i < Power(QUATERNARY, length); i++) //embarrassingly parallel
        {
            codewords[i].number = i;
            Moment(i, length, del, p, codewords[i].residues);
            //matrix.push_back(residues, i);
        }

        //out << matrix;
        
        //for time profiling purposes
        chrono::high_resolution_clock::time_point processing = chrono::high_resolution_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(processing - start);
        log << "time processing: " << time_span.count() << endl;

        //find a way to neatly output the data
        /*if (single) //works
        {
            vector< vector<codeword> > sections(Power(p, 2));
            auto cend = codewords.end();

            for (int i = 0; i < p; i++)
            {
                for (int j = 0; j < p; j++)
                {
                    cout << "(" << i << "," << j << ")" << '\r' << flush;
                    //place thread here???
                    short position = (i * p) + j;
                    //section off the total list of codewords so that each useless code is not read more than a few times
                    for (auto sword = codewords.begin(); sword != cend;)
                    {
                        if (sword->residues[0] == i && sword->residues[1] == j)
                        {
                            sections[position].push_back(*sword);
                            cend--;
                            *sword = *cend;
                        }
                        else 
                        {
                            sword++;
                        }
                    }
                    
                    auto end = sections[position].end();

                    //place thread here
                    string outname = "TL" + to_string(length) + "D" + to_string(del) + "R" + to_string(i) + "-" + to_string(j) + ".txt";
                    ofstream out(outname.c_str());

                    length_t w = Weight(length, BINARY, del);
                    for (int k = 0; k < w; k++)
                    {
                        out << "HR" << k << endl;
                        
                        //do the same sectioning here
                        for (auto word = sections[position].begin(); word != end;)
                        {
                            if (word->residues[2] == k)
                            {
                                out << toQuad(word->number, length) << endl; //do one more sectioning so that writing can be all at once?
                                --end;
                                *word = *end;
                            } //if
                            else
                            {
                                word++;
                            } //else
                        } //section
                        out << endl;
                    } //k
                    //out.close();
                } //j
            } //i
        } //if*/
        if (mult1)
        {
            vector< vector<codeword> > sections(Power(p, del)); //del = 2
            vector<thread> workers;
            //auto cend = codewords.end();

            for (auto& word : codewords)
            {
                sections[word.residues[B1_RESIDUE] * p + word.residues[B2_RESIDUE]].push_back(word);
            }

            for (int i = 0; i < p; i++) //make into a single loop
            {
                for (int j = 0; j < p; j++)
                {
                    log << "(" << i << "," << j << ") ";// << '\n';
                    //place thread here???
                    short position = (i * p) + j;
                    //section off the total list of codewords so that each useless code is not read more than a few times
                    /*for (auto sword = codewords.begin(); sword != cend;)
                    {
                        if (sword->residues[0] == i && sword->residues[1] == j)
                        {
                            sections[position].push_back(*sword);
                            cend--;
                            *sword = *cend;
                        }
                        else
                        {
                            sword++;
                        }
                    }*/

                    string outname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Raw/" + 
				to_string(length)+ "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + ".txt";
                    
                    workers.emplace_back(Output, outname, ref(sections[position]), Weight(length, BINARY, del), length);
                    //Output( ofstream(outname.c_str()), ref(sections[position]), Weight(length, BINARY, del), length);
                } //j
                log << '\n';
            } //i
            Join(workers);
        } //if
        chrono::high_resolution_clock::time_point done = chrono::high_resolution_clock::now();
        chrono::duration<double> time_span2 = chrono::duration_cast<chrono::duration<double> >(done - start);
        log << "time " << length << ": " << time_span2.count() << endl;
        
    } //length loop
    log.close();
    return 0;
}


void Output(string outname, vector<codeword>& section, length_t weight, digit length)
{
    //auto end = section.end();
    /*vector< vector<codeword> > helberg(weight);

    for (auto& word : section)
    {
        helberg[word.residues[HELBERG_RESIDUE]].push_back(word);
    }*/
    ofstream out(outname.c_str());
    for (int k = 0; k < weight; k++) 
    {
        string output = "HR" + to_string(k) + '\n';
        //out << "HR" << k << endl;
        //do the same sectioning here
        //for (auto word = section.begin(); word != end;)
        for (auto& word : section) //check at rucc
        {
            if (word.residues[HELBERG_RESIDUE] == k)
            {
                //out << toQuad(word->number, length) << endl; //do one more sectioning so that writing can be all at once?
                output += toQuad(word.number, length) + '\n';
                //--end;
                //word = *end;
            } //if
            //else
            //{
            //    word++;
            //} //else
        } //section
        //out << endl;*/

        /*for (auto& word : helberg[k])
        {
            output += toQuad(word.number, length) + '\n';
        }*/
        output += '\n';
        out << output;
    }
}

void Join(vector<thread> &workers)
{
    for (auto& worker : workers)
    {
        worker.join();
    }
}
