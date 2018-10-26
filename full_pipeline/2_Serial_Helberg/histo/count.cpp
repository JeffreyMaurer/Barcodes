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

        string inputname = "/csm_data/experimentalmath/maurer/FINALWORDS/COMBINED_CW_B4_D2_L" + 
                   to_string(length) + ".txt";

        ifstream input(inputname.c_str());

        string code; getline(input, code);
        while (getline(input, code))
        {
            int count(0);
            while (isdigit(code[0]))
            {
                count++;
                getline(input, code);
            }
            add_map(counts, count);
        } //while

        out << "length: " << length << '\n';
        for (auto& c : counts)
        {
            out << c.first << ':' << c.second << '\n';
        }
        out << "time: " << time(0) - now << endl << endl;
    }//length
    return 0;
}//main




