#include<iostream>
#include<fstream>
#include<string>
using namespace std;

typedef short digit;
typedef int length_t;

int main()
{
//make the initial reads
	ifstream input; string inputname;
	inputname = "test.txt";
	input.open(inputname.c_str());
	string line;
	getline(input, line);
	line = line.substr(line.find("|")+3, 1);
	short GC = line.c_str()[0] - '0'; 
	int n = 5; //magic number
}

//Amplify
//output the final reads
	return 0;
}

inline digit Digit(length_t code, digit m)
{
	return (code >> (m * 2)) & 3;
}

string Assign_Nucleotides(int IntCode, short GC, int n){
    string Nucleotides;
    digit dig = 0;

    for (int j = 0; j < n; j++){

        dig = Digit(IntCode, j);

        switch (GC){
        case 0:switch (dig)
        {
          case 0: Nucleotides += 'G'; break;
          case 1: Nucleotides += 'C'; break;
          case 2: Nucleotides += 'A'; break;
          case 3: Nucleotides += 'T'; break;
        } break;

        case 1:switch (dig)
        {
          case 0: Nucleotides += 'G'; break;
          case 1: Nucleotides += 'T'; break;
          case 2: Nucleotides += 'C'; break;
          case 3: Nucleotides += 'A'; break;
        } break;

        case 2:switch (dig)
        {
          case 0: Nucleotides += 'A'; break;
          case 1: Nucleotides += 'G'; break;
          case 2: Nucleotides += 'C'; break;
          case 3: Nucleotides += 'T'; break;
        } break;

        case 3:switch (dig)
        {
          case 0: Nucleotides += 'G'; break;
          case 1: Nucleotides += 'A'; break;
          case 2: Nucleotides += 'T'; break;
          case 3: Nucleotides += 'C'; break;
        } break;

        case 4:switch (dig)
        {
          case 0: Nucleotides += 'A'; break;
          case 1: Nucleotides += 'G'; break;
          case 2: Nucleotides += 'T'; break;
          case 3: Nucleotides += 'C'; break;
        } break;

        case 5:switch (dig) 
        {
          case 0: Nucleotides += 'A'; break;
          case 1: Nucleotides += 'T'; break;
          case 2: Nucleotides += 'G'; break;
          case 3: Nucleotides += 'C'; break;
        } break;
        }
    }
    return Nucleotides;
}
length_t fromQuad(string quad)
{
	digit j(0); length_t result(0);
	for (digit i = quad.length() - 1; i >= 0; i--)
	{
		result += (((digit)quad[i]) - '0') * Power(4, quad.length() - (i+1));
	}
	return result;
}
