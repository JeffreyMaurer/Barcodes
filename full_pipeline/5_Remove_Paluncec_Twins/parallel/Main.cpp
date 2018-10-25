#include"TwinToss.h"

using namespace std;

void process(string outname, string inname, digit length, digit del, short i, short j);

int main(int argc, char * argv[])
{
    digit length;
    digit del = 2;

    for (length = atoi(argv[1]); length <= atoi(argv[2]); length++)
    {
        ofstream log("log/" + to_string(length) + ".txt");
        vector<thread> workers;
        time_t now = time(0);
        for (short i = 0; i < 5; i++)
        {
            for (short j = 0; j < 5; j++)
            {
                string inputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Raw/" + 
				to_string(length) + "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + ".txt";

                string outputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Tossed/" + 
				to_string(length) + "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + "TT.txt";

                workers.emplace_back(thread(process, outputname, inputname, length, del, i, j));
            } //j
        } //i
        Join(workers);
        log << length << ": " << time(0) - now << endl;
    }//length
    return 0;
}//main

void process(string outname, string inname, digit length, digit del, short i, short j)
{
    ifstream input(inname.c_str());
    ofstream output(outname.c_str());
    string code;

    while (getline(input, code))
    {
        codebook book; //this is what we shall be working on

        //fill up all of the raw data
        book.name = code;

        getline(input, code);
        while (isdigit(code[0]))
        {
            book.codes.push_back(codeword(code));
            getline(input, code);
        }

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

        //Toss the twins away
        while (Toss(book)) {} //replace this loop and loop inside function, make ordered list and compare average and best case sorts for first and subsequent sorts

        output << book.name << '|' << book.codes.size() << '\n';

        for (auto& i : book.codes) //iterating over a list...
        { //TODO: omit if == 0
            if (i.word)
                output << toQuad(i.word, length) << '\n';
        }
        output << '\n';
    } //while
}

