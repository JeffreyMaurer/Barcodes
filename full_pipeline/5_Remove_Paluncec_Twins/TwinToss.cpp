//TODO: make parallel
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
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

int main(int argc, char * argv[])
{
    digit length;
    string code;
    digit del = 2;
    bool single = true, thread, multiple;

    ofstream log("logfile.txt");

    for (length = atoi(argv[1]); length <= atoi(argv[2]); length++)
    {
        time_t now = time(0);
        for (short i = 0; i < 5; i++)
        {
            for (short j = 0; j < 5; j++)
            {
                string inputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Raw/" + 
				to_string(length) + "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + ".txt";

                ifstream input(inputname.c_str());

                string outputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Tossed/" + 
				to_string(length) + "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + "TT.txt";

                ofstream output(outputname.c_str());

                //TODO: parallel this loop
                //two options: have a script activate this multiple times or thread it
                if (single)
                {
                    while (getline(input, code))
                    {
                        
                        codebook book; //this is what we shall be working on

                        //fill up all of the raw data
                        book.name = code;
                        log << "L" << length << "-" << i << '-' << j << '-' << book.name << '\n';
                        
                        getline(input, code);
                        while (isdigit(code[0]))
                        {
                            book.codes.push_back(codeword(code));
                            getline(input, code);
                        }

                        //log << "time input: " << time(0) - now << endl;
                        //now = time(0);
                        //which are incompatible with each other?
                        //TODO: with vectors? are normal for loops better?
                        for (auto i = book.codes.begin();
                            i != book.codes.end();
                            i++){
                            auto j = i;
                            j++;
                            while (j != book.codes.end()){
                                if (!Check(i->word, j->word, length, del))
                                {
                                    i->bad.push_back(j->word);
                                    j->bad.push_back(i->word);
                                }
                                j++;
                            }
                        }

                        //log << "time check: " << time(0) - now << endl;
                        //now = time(0);
                        //Toss the twins away
                        while (Toss(book)) {} //replace this loop and loop inside function, make ordered list and compare average and best case sorts for first and subsequent sorts

                        //log << "time toss: " << time(0) - now << endl;
                        //now = time(0);
                        output << book.name << endl;

                        for (auto& i : book.codes) //iterating over a list...
                        { //TODO: omit if == 0
                            if (i.word) 
                                output << toQuad(i.word, length) << endl;

                        }
                        output << endl;
                        //log << "time output: " << time(0) - now << endl;
                    } //while
                }//if
            } //j
        } //i
        log << "time total " << length << ": " << time(0) - now << endl;
    }//length
    return 0;
}//main

//TODO: will sorting fix the problem? 
bool Toss(codebook &book)
{
    //auto max = book.codes.begin(); //where is the one with the most incongruencies?
    auto max = &book.codes.front(); //where is the one with the most incongruencies?
    int maxSize = 0; //how many is it incompatible with?
    length_t maxValue; //what is it?
    /*for (auto i = book.codes.begin(); i != book.codes.end(); i++)
    {
        if (i->bad.size() > maxSize)
        {
            max = i; 
            maxSize = i->bad.size();
            maxValue = i->word;
        }
    }*/
    for (auto& i : book.codes)
    {
        if (i.bad.size() > maxSize)
        {
            max = &i;
            maxSize = i.bad.size();
            maxValue = i.word;
        }
    }
    //cout << "current maxSize: " << maxSize << endl;
    //system("pause");
    //if (maxSize) book.codes.erase(max); //get rid of it
    if (maxSize) { max->word = 0; max->bad.clear(); }

    for (auto& i : book.codes) //test
    {
        for (auto j = i.bad.begin();
            j != i.bad.end();)
        {
            if (*j == maxValue) { j = i.bad.erase(j);  break; } //send to back and pop
            else j++;
        }
    }

    if (!maxSize) return false;
    else return true;
}
