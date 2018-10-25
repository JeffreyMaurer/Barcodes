#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;

const short READ_LENGTH = 15;

typedef short digit;
typedef int length_t;

length_t Power(int base, int exponent);
length_t fromQuad(string quad);
void replicate();
string Assign_Nucleotides(int IntCode, short GC, int n);
string toQuad(length_t code, digit n);

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
	vector<string> DNA;
	getline(input, line);
	while (line)
	{
		DNA.push_back(line); //each line is a barcode
		getline(input, line);
	}
	for (auto& oliga : DNA)
	{
		string barcode = oliga;
		for (int i = 0; i < READ_LENGTH; i++)
		{
			oliga.append((char)(rand()%4)); //what is the actual sequence? add it to the oliga
		}
		oliga.append(barcode); //paired end barcodes
		//cout << oliga << endl;
		length_t word = fromQuad(oliga, n);
                oliga = Assign_Nucleotides(word, GC, n); //convert from numbers to letters
		oliga += "|" + Assign_Nucleotides(fromQuad(barcode), GC, n); //keep it straight what barcode we have
		cout << "oliga: " << oliga << endl;
	}


//Amplify

	for (int amp = 0; amp = 40; amp++)
	{
		int repeats = DNA.size();
		for (int oliga = 0; oliga < repeats; oliga++)
		{
			
		}		
	}
//output the final reads
//two bits left and right
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

length_t Power(int n, int m){                     //Returns the power of one to the other as an int
    if (m == 0) return 1;
    else if (m == 1) return n;
    length_t product = n;
    for (int i = 1; i < m; i++){
        product *= n;
    }
    return product;
}
string toQuad(length_t m, int n)
{
    string quad;
    for (int j = (n - 1); j >= 0; j--)
    {
        quad += to_string(Digit(m, j));
    }
    return quad;
}
