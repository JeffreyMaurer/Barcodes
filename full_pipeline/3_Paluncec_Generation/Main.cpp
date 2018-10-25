#include<iostream>
#include<vector>
//#include<list>
#include<fstream>
#include<string>
#include<chrono>
#include<ctime>
#include<ratio>
#include<algorithm>
#include<thread>
#include"Tenengolts.h"
#include"Helberg_Functions.h"
//#include"MultiMatrix.h"

using namespace std;

struct codeword
{
   length_t number;
   vector<int> residues;
   codeword(int i) : residues(3), number(i) {}
   codeword() {}
};

//void Output(int, int, int, int, const vector<codeword>&);

int main(int argc, char * argv[])
{
   //some variables

   length_t length;
   int del = 2;
   int p = Prime(max(QUATERNARY - 1, del)); //the length of each dimension
   bool //single = false, 
      mult1 = true;
      //mult2 = false, 
      //parallel = false;

   //TODO: less needed, but make mM work
   //mM matrix(del, p);


   //process the lengths of blah to blah
   for (length = atoi(argv[1]); length <= atoi(argv[argc-1]); length++)
   {
      //time profiling
      chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
      vector<codeword> codewords(Power(4, length));

      //make the data
      for (length_t i = 0; i < Power(4, length); i++)
      {
         codeword temp0(i);
         Moment(i, length, del, p, temp0.residues);
         //matrix.push_back(residues, i);
         codewords[i] = temp0;
      }

      //out << matrix;
      chrono::high_resolution_clock::time_point processing = chrono::high_resolution_clock::now();
      chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(processing - start);
      cout << "time processing: " << time_span.count() << endl;

      //find a way to neatly output the data
      if (mult1) //works
      {
         auto cend = codewords.end();

         for (int i = 0; i < p; i++)
         {
            for (int j = 0; j < p; j++)
            {

               //section off the total list of codewords so that each useless code is not read more than a few times
               vector<codeword> section;// (Power(4, length - 1)); length_t q(0);
               for (auto sword = codewords.begin(); sword != cend;)
               {
                  if (sword->residues[0] == i && sword->residues[1] == j)
                  {
                     section.push_back(*sword);
                     cend--;
                     *sword = *cend;
                  }
                  else 
                  {
                     sword++;
                  }
               }
               
               auto end = section.end();

               //place thread here
               for (int k = 0; k < Weight(length + 1, BINARY, del); k++)
               {
                  string outname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/" + 
				to_string(length)+ "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + "-" + to_string(k) + ".txt";
                  ofstream out(outname.c_str());
                  
                  //do the same sectioning here
                  for (auto word = section.begin(); word != end;)
                  {
                     if (word->residues[2] == k)
                     {
                        out << word->number << endl;
                        --end;
                        *word = *end;
                     }
                     else
                     {
                        word++;
                     }
                  } //word
                  out.close();
               } //k
            } //j
         } //i
      } //if
      chrono::high_resolution_clock::time_point done = chrono::high_resolution_clock::now();
      chrono::duration<double> time_span2 = chrono::duration_cast<chrono::duration<double> >(done - start);
      
      cout << "time " << length << ": " << time_span2.count() << endl;
   }

   return 0;
}

/*
void Output(int del, int length, int i, int j, const vector<codeword>& codewords)
{
   string prologue = "TL" + to_string(length) + "D" + to_string(del) + "R" + to_string(i) + "-" to_string(j) + "-"
   for (int k = 0; k < Weight(length + 1, BINARY, del); k++)
   {
      string outname =   prologue + to_string(k) + ".txt";
      ofstream out(outname.c_str());

      for (auto word = section.begin(); word != end;)
      {
         if (word->residues[2] == k)
         {
            out << word->number << endl;
            //if (back == word) break;
            *word = *back;
            back--; --end;
         }
         else
         {
            word++;
         }
      } //word
      out.close();
   } //k
}*/

/*if (single) //works
{
ofstream out; string outname;
outname = "TL" + to_string(length) + "D" + to_string(del) + ".txt";
out.open(outname.c_str());

for (int i = 0; i < p; i++)
{
for (int j = 0; j < p; j++)
{
out << "(" << i << "," << j << ")" << endl;
for (int k = 0; k < codewords.size(); k++)
{
if (codewords[k].residues[0] == i && codewords[k].residues[1] == j)
out << codewords[k].number << endl;
}
out << endl;
}
}
}*/

/*else if (mult2) //works
{
vector<ofstream*> out;
for (int m = 0; m < p; m++)
{
for (int n = 0; n < p; n++)
{
string outname = "TL" + to_string(length) + "D" + to_string(del) + "R" + to_string(n) + "-" + to_string(m) + ".txt";
out.push_back(new ofstream(outname.c_str()));
}
}

for (int k = 0; k < codewords.size(); k++)
{
*out[codewords[k].residues[0] * p + codewords[k].residues[1]] << to_string(codewords[k].number) << endl;
}

for (auto& q : out)
{
q->close();
}
}
else if (parallel) //parallel
{
vector<thread> workers;

for (int i = 0; i < p; i++)
{
for (int j = 0; j < p; j++)
{
workers.emplace_back(thread(Output, del, length, i, j, codewords));
}
}

for (auto& worker : workers)
{
worker.join();
}
}*/
