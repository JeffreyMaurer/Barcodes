#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<cstdlib>
#include<vector>

using namespace std;

typedef short digit;

int Weight(int i, int q, int d);
int g_weights[20];
const int BINARY = 2;

int main(int argc, char * argv[])
{
    digit length;
    digit del = 2;

    for (length = atoi(argv[1]); length <= atoi(argv[2]); length++)
    {
        ofstream log("logs/" + to_string(length) + ".txt");
        time_t now = time(0);

        for (short i = 0; i < 5; i++)
        {
            for (short j = 0; j < 5; j++)
            {
                vector<ifstream> inputs;
                int piece(0);
                string bookname;

                string outname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Raw/" +
                                to_string(length) + "length/TL" + to_string(length) + "D" +
                                to_string(del) + "R" + to_string(i) + "-" + to_string(j) + ".txt";
                ofstream out(outname.c_str());

                while (1) //number of pieces
                {
                    string inputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Pieces/" +
                                to_string(length) + "length/TL" + to_string(length) + "D" +
                                to_string(del) + "R" + to_string(i) + "-" + to_string(j) + "P" +
                                to_string(piece) + ".txt";

                    inputs.push_back(ifstream(inputname.c_str()));

                    if (!inputs.back().good()) {inputs.pop_back(); break;}

                    piece++;
                }

                for (int k = 0; k < Weight(length, BINARY, del); k++)//helbergs
                {
                    string code; vector<string> codes;
                    for (auto& input : inputs) //ifstreams
                    {
                        getline(input, code);
                        bookname = code;

                        getline(input, code);
                        while (isdigit(code[0])) //residues
                        {
                            codes.push_back(code);
                            getline(input, code);
                        }
                    } //ifstreams

                    out << bookname << '\n';
                    for (auto& word : codes)
                    {
                        out << word << '\n';
                    }
                    out << '\n';
                } //while
            } //j
        } //i
        log << "length:" << length << ": " << time(0) - now << endl;
    }//length
    return 0;
}//main

int Weight(int i, int q, int d)
{
    if (g_weights[i])
        return g_weights[i];
    if (i <= 0)
        return 0;
    else if (i == 1)
        return 1;
    int sum = 0;
    for (int j = 1; j <= d; j++)
    {
        sum += Weight((i - j), q, d);
    }
    sum = 1 + ((q - 1) * sum);
    g_weights[i] = sum;
    return sum;
}

