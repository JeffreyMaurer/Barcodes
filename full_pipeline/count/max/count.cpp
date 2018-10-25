#include<iostream>
#include<fstream>
#include<string>
#include<time.h>

using namespace std;

typedef short digit;

int main(int argc, char * argv[])
{
    digit length;
    digit del = 2;
    ofstream out("count.txt");

//    for (length = atoi(argv[1]); length <= atoi(argv[2]); length++)
    for (length = 3; length <= 15; length++)
    {
        time_t now = time(0);
        int largest_c(0), largest_i(0), largest_j(0); string residue;

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
                    string bookname = code;
                    int count(0);

                    getline(input, code);
                    while (isdigit(code[0]))
                    {
                        count++;
                        getline(input, code);
                    }

                    if (count > largest_c) {largest_c = count; largest_i = i; largest_j = j; residue = bookname;}
                } //while
            } //j
        } //i
        out << "length: " << length << "\nlargest: " << residue << 'T' << 
               largest_i << '-' << largest_j << "\nsize: " << largest_c << endl;
        out << "time: " << time(0) - now << endl << endl;
    }//length
    return 0;
}//main




