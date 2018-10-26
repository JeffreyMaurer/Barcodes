#include"BioChem.h"
#include<thread>
#include<mutex>
#include<functional>

mutex g_badlock;

int Biochem(vector<length_t> &VectorCode, int n, short &max_GC){

    if (VectorCode.empty()) return -1; //very cheap way to avoid issues

    //6 is a magic number, find a word for it and stick in *.h
    vector<vector<int> > Bad_Codes(6);    //This will hold the values that need to be removed
    vector<vector<string> > Nucleotide_Codes(6);

    //setup Bad_Codes
    for (int i = 0; i < 6; i++)
        Bad_Codes[i].push_back(i);

        //Setup Nucleotide_Codes
    for (int j = 0; j < 6; j++){
        Nucleotide_Codes[j].resize(VectorCode.size());
    }
    for (int Loop_GC_Partitions = 0; Loop_GC_Partitions < 6; Loop_GC_Partitions++){
        for (unsigned int Loop_Code = 0; Loop_Code < VectorCode.size(); Loop_Code++){
            Nucleotide_Codes[Loop_GC_Partitions][Loop_Code] = (Assign_Nucleotides(VectorCode[Loop_Code], Loop_GC_Partitions, n));
        }
    }
/*
    thread GC(GC_Content, ref(Bad_Codes), ref(Nucleotide_Codes));             //Check GC content

    thread Pal(Palindromes, ref(Bad_Codes), ref(Nucleotide_Codes));                //Look through for palindromes and inverted repeats

    GC.join(); Pal.join();
*/
    GC_Content(Bad_Codes, Nucleotide_Codes);
    Palindromes(Bad_Codes, Nucleotide_Codes);

    //Base_Stacking_Stability(Bad_Codes, Nucleotide_Codes);        //check base stacking stability
    
    sort(Bad_Codes.begin(), Bad_Codes.end(), Sort_Bad_Codes);    //sort the vectors by size, choose smallest

    Tandem_Repeat(Bad_Codes, Nucleotide_Codes);                //check for tandem repeats

    //TODO: Look up indel frequencies and neighbor effects - 80 - 90%???

    //marking the bad codes
    for (unsigned int i = 1; i < Bad_Codes[0].size(); i++)
        VectorCode[(Bad_Codes[0][i])] = 0;

    max_GC = Bad_Codes[0][0];

    return 0;
}

void Add_Bad_Code(vector<vector<int> > &Bad_Codes, int GC, int Word){
    bool R = true;
    g_badlock.lock();
    for (unsigned int i = 1; i < Bad_Codes[GC].size(); i++){
        if (Bad_Codes[GC][i] == Word) {R = false; break;}
    }
    if (R) Bad_Codes[GC].push_back(Word);
    g_badlock.unlock();
}

string Assign_Nucleotides(int IntCode, int partition, int n){
    string Nucleotides;
    int Digit = 0;

    for (int j = 0; j < n; j++){

        Digit = ((IntCode & (3 * Power(4, j))) >> (j * 2));

        switch (partition){
        case 0:switch (Digit)
        {
        case 0: Nucleotides += 'G'; //cout << Nucleotides[j] << endl; 
            break;
        case 1: Nucleotides += 'C'; //cout << Nucleotides[j] << endl; 
            break;
        case 2: Nucleotides += 'A'; //cout << Nucleotides[j] << endl; 
            break;
        case 3: Nucleotides += 'T'; //cout << Nucleotides[j] << endl; 
            break;
        }; break;
        case 1:switch (Digit)
        {
        case 0: Nucleotides += 'G'; break;
        case 1: Nucleotides += 'T'; break;
        case 2: Nucleotides += 'C'; break;
        case 3: Nucleotides += 'A'; break;
        } break;

        case 2:switch (Digit)
        {
        case 0: Nucleotides += 'A'; break;
        case 1: Nucleotides += 'G'; break;
        case 2: Nucleotides += 'C'; break;
        case 3: Nucleotides += 'T'; break;
        } break;

        case 3:switch (Digit)
        {
        case 0: Nucleotides += 'G'; break;
        case 1: Nucleotides += 'A'; break;
        case 2: Nucleotides += 'T'; break;
        case 3: Nucleotides += 'C'; break;
        } break;

        case 4:switch (Digit)
        {
        case 0: Nucleotides += 'A'; break;
        case 1: Nucleotides += 'G'; break;
        case 2: Nucleotides += 'T'; break;
        case 3: Nucleotides += 'C'; break;
        } break;

        case 5:switch (Digit) 
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

string Reverse_Complement(string Nucleotides){

    string RC;

    for (int i = (Nucleotides.length() - 1); i >= 0; i--){
        if (Nucleotides[i] == 'A') RC += 'T';
        else if (Nucleotides[i] == 'T') RC += 'A';
        else if (Nucleotides[i] == 'C') RC += 'G';
        else RC += 'C';
    }

    return RC;

}

/*
void Base_Stacking_Stability(vector<vector<int> > &Bad_Codes, vector<vector<string> > &Nucleotide_Codes)    {

    //TODO: MORE RESEARCH ON BASE STACKING, HOW IMPORTANT IS IT???

    string pair_stacking;

    unsigned int n = Nucleotide_Codes.size();
    for (int Loop_GC_Partitions = 0; Loop_GC_Partitions < 6; Loop_GC_Partitions++){ //loop through each GC partition
        for (unsigned int Loop_Code = 0; Loop_Code < n; Loop_Code++){ //loop through each code in the codebook
            float stability = 0.0;
            for (unsigned int Loop_Letter = 0; Loop_Letter < n - 2; Loop_Letter++){//loop through each letter to find the palindromes
                pair_stacking = Nucleotide_Codes[Loop_GC_Partitions][Loop_Code].substr(Loop_Letter, 1);
                stability += Stacking_Stability(pair_stacking);
            }
            if ((stability/Nucleotide_Codes[Loop_GC_Partitions][Loop_Code].length()) < Stacking_cutoff){ // what should this value be
                //cout << "Stacking" << Nucleotide_Codes[Loop_GC_Partitions][Loop_Code] << endl;
                //Bad_Codes[Loop_GC_Partitions].push_back(Loop_Code);
                Add_Bad_Code(Bad_Codes, Loop_GC_Partitions, Loop_Code);
            }
        }
    }
}

double Stacking_Stability(string pair_stacking){
    //this returns the delta G value
    if (pair_stacking == "AA" || pair_stacking == "TT") return 1.9;
    else if (pair_stacking == "AT") return 1.5;
    else if (pair_stacking == "TA") return 0.9;
    else if (pair_stacking == "CA") return 1.9;
    else if (pair_stacking == "GT") return 1.3;
    else if (pair_stacking == "CT") return 1.6;
    else if (pair_stacking == "GA") return 1.6;
    else if (pair_stacking == "CG") return 3.6;
    else if (pair_stacking == "GC") return 3.1;
    else if (pair_stacking == "GG" || pair_stacking == "CC") return 3.1;
}
*/

void GC_Content(vector<vector<int> > &Bad_Codes, vector<vector<string> > &Nucleotide_Codes){

    //TODO: What is this special GC content?
    //Hickman: 50%???
    //Intuition: Same as the sample???
    
    for (int Loop_GC_Partitions = 0; Loop_GC_Partitions < 6; Loop_GC_Partitions++){ //loop through each GC partition

        for (unsigned int Loop_Code = 0; Loop_Code < Nucleotide_Codes[Loop_GC_Partitions].size(); Loop_Code++){ //loop through each code in the codebook

            float GC_Content = 0.0;

            for (int Loop_Letter = 0; Loop_Letter < Nucleotide_Codes[0][0].length(); Loop_Letter++){
                if (Nucleotide_Codes[Loop_GC_Partitions][Loop_Code][Loop_Letter] == 'C' || Nucleotide_Codes[Loop_GC_Partitions][Loop_Code][Loop_Letter] == 'G') GC_Content++;
            }
            if (GC_Content / Nucleotide_Codes[0][0].length() < GC_min || GC_Content / Nucleotide_Codes[0][0].length() > GC_max){ 
                //Bad_Codes[Loop_GC_Partitions].push_back(Loop_Code);
                Add_Bad_Code(Bad_Codes, Loop_GC_Partitions, Loop_Code);
            }
        }
    }
}

void Tandem_Repeat(vector<vector<int> > &Bad_Codes, vector<vector<string> > &Nucleotide_Codes){

    //check for homopolymers; single < 3 for roche sequencing and <8 for PCR, double < 6
    //Quadruplet < 16 for 10% changed after PCR research to be done on the longer ones

    //TODO: Repeats that are bad, what are the parameters???

    bool bad = false;

    int size = Nucleotide_Codes[0].size();
    int length = Nucleotide_Codes[0][0].length();

    for (int Loop_Code = 0; Loop_Code < size; Loop_Code++){ //loop through each code in the codebook
        int Tandem_Repeat = 0, Repeat_Length;
        for (Repeat_Length = 1; Repeat_Length < STR_size; Repeat_Length++){    //This will loop through each possible STR length

            for (int Loop_Letter = 0; Loop_Letter <= (length - Repeat_Length); Loop_Letter += Repeat_Length){    //Go through the codeword to find STRs with the selected repeat length
                string one = Nucleotide_Codes[0][Loop_Code].substr(Loop_Letter, Repeat_Length);
                string two =  Nucleotide_Codes[0][Loop_Code].substr(Loop_Letter + Repeat_Length, Repeat_Length);

                if (Loop_Letter == 0){
                    Tandem_Repeat = Repeat_Length;
                }
                else if (one == two) {
                    Tandem_Repeat = Tandem_Repeat+ Repeat_Length;
                }
                else {
                    Tandem_Repeat = Repeat_Length;
                }

                //TODO: more research on how the number of repeats affects mutations

                //Taq polymerase has 7-9 nucleotides in its active site at one time,
                //so is having all nucleotides inside it the determining factor?
                    //1*8 = 8, 2*5 = 10

                //For roche 454 sequencing,if length = 1, break should be at 3

                if (Tandem_Repeat > (TR_Cutoff - 1) && Repeat_Length == 1) {
                    bad = true; 
                    /*Bad_Codes[0].push_back(Loop_Code);*/
                    Add_Bad_Code(Bad_Codes, smallest, Loop_Code); 
                    break;
                }
                else if (Tandem_Repeat > TR_Cutoff) {
                    bad = true; 
                    //Bad_Codes[0].push_back(Loop_Code);  
                    Add_Bad_Code(Bad_Codes, smallest, Loop_Code);
                    break;
                }
            }
            if (bad) {
                break;
            }
        }

        if (bad) {
            bad = false;
        }
    }
}

void Palindromes(vector<vector<int> > &Bad_Codes, vector<vector<string> > &Nucleotide_Codes){

    //This piece of code needs to be dialed down.
    //TODO: what are these parameters?

    int size = Nucleotide_Codes[0].size();
    int length = Nucleotide_Codes[0][0].length();
    bool good = true;

    for (int Loop_GC_Partitions = 0; Loop_GC_Partitions < 6; Loop_GC_Partitions++) //loop through each GC partition
    {
        int Loop_Code = 0;
        while (Loop_Code < size)//loop through each code in the codebook
        {
            good = true;
            //TODO: What are the parameters of the next two loops
            int Loop_Size = p_length_min+2; 
            while ((Loop_Size <= floor(((float)length) / 2)) && good)//loop through the size of the palindrome
            {
                int Loop_Distance = 1;
                while ((Loop_Distance <= (length - (2 * Loop_Size))) && good)//loop through the distance between the palindromes
                {
                    int Loop_Letter = 0; 
                    while ((Loop_Letter <= (length - (Loop_Distance +(Loop_Size * 2)))) && good)//loop through each letter to find the palindromes
                    {
                        string RC = Reverse_Complement(Nucleotide_Codes[Loop_GC_Partitions][Loop_Code].substr(Loop_Letter, Loop_Size));
                        string Next = Nucleotide_Codes[Loop_GC_Partitions][Loop_Code].substr(Loop_Letter + Loop_Size + Loop_Distance, Loop_Size);
                        if (RC == Next)
                        {
                            //Bad_Codes[Loop_GC_Partitions].push_back(Loop_Code);
                            Add_Bad_Code(Bad_Codes, Loop_GC_Partitions, Loop_Code);
                            good = false;
                        }
                        Loop_Letter++;
                    }
                    Loop_Distance++;
                }
                Loop_Size++;
            }
            Loop_Code++;
        }
    }
}
/*
void Palindromes0(vector<vector<int> > &Bad_Codes, vector<vector<string> > &Nucleotide_Codes){

    //This piece of code needs to be dialed down.
    //TODO: what are these parameters?

    int size = Nucleotide_Codes[0].size();
    int length = Nucleotide_Codes[0][0].length();
    bool good = true;

    for (int Loop_GC_Partitions = 0; Loop_GC_Partitions < 6; Loop_GC_Partitions++) //loop through each GC partition
    {
        int Loop_Code = 0;
        while (Loop_Code < size)//loop through each code in the codebook
        {
            good = true;
            int Loop_Size = p_length_min; 
            while ((Loop_Size <= floor(((float)length) / 2)) && good)//loop through the size of the palindrome
            {
                int Loop_Distance = p_distance_min;
                while ((Loop_Distance <= (length - (2 * Loop_Size))) && good)//loop through the distance between the palindromes
                {
                    int Loop_Letter = 0; 
                    while ((Loop_Letter <= (length - (Loop_Distance +(Loop_Size * 2)))) && good)//loop through each letter to find the palindromes
                    {

                        string RC = Reverse_Complement(Nucleotide_Codes[Loop_GC_Partitions][Loop_Code].substr(Loop_Letter, Loop_Size));
                        string Next = Nucleotide_Codes[Loop_GC_Partitions][Loop_Code].substr(Loop_Letter + Loop_Size + Loop_Distance, Loop_Size);
 
                        int hbonds = 0;
 
                        for (int i = 0; i < RC.size(); i++)
                        {
                            if (RC[i] == 'G'||RC[i] == 'C') hbonds+=3;
                            else hbonds += 2;
                        }

                        if (RC == Next && hbonds > p_hbond_min)
                        {
                            //Bad_Codes[Loop_GC_Partitions].push_back(Loop_Code);
                            Add_Bad_Code(Bad_Codes, Loop_GC_Partitions, Loop_Code);
                            good = false;
                        }
                        Loop_Letter++;
                    }
                    Loop_Distance++;
                }
                Loop_Size++;
            }
            Loop_Code++;
        }
    }
}
*/



