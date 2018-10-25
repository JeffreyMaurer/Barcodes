#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<map>

using namespace std;

typedef short digit;

void add_map(map<int, int> &m, int n)
{
    if (!m[n]) m[n]=1;
    else m[n]++;
}


int main(int argc, char * argv[])
{
    digit length;
    digit del = 2;
    ofstream out("count.txt");
    
    if (atoi(argv[1]) > 15 || atoi(argv[2]) > 15) return -1;

    for (length = atoi(argv[1]); length <= atoi(argv[2]); length++)
    {
        time_t now = time(0);
        map<int, int> counts;

        for (short i = 0; i < 5; i++)
        {
            for (short j = 0; j < 5; j++)
            {
                string inputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Tossed/" + 
				to_string(length) + "length/TL" + to_string(length) + "D" + 
				to_string(del) + "R" + to_string(i) + "-" + to_string(j) + "TT.txt";

                ifstream input(inputname.c_str());

                string code;
                while (getline(input, code))
                {
                    int count(0);
                    getline(input, code);
                    while (isdigit(code[0]))
                    {
                        count++;
                        getline(input, code);
                    }
                    add_map(counts, count);
                } //while
            } //j
        } //i
        out << "length: " << length << '\n';
        for (auto& c : counts)
        {
            out << c.first << ':' << c.second << '\n';
        }
        out << "time: " << time(0) - now << endl << endl;
    }//length
    return 0;
}//main




