//scales approximately O(nlogn)
#include"BCPArrange.h"

using namespace std;

int main(int argc, char * argv[])
{

    int start, end;

    //make this look professional
    if (argc == 1)
    {
        cerr << "No parameters passed" << endl;
        return 1;
    }
    else if (argc == 2)
    {
        if (atoi(argv[1]) >= MinLength && atoi(argv[1]) <= MaxLength)
        {
            start = atoi(argv[1]);
            end = atoi(argv[1]);
        }
        else if (!atoi(argv[1]))
        {
            cerr << "That parameter is not a number" << endl;
            return 1;
        }
        else if (atoi(argv[1]) < MinLength || atoi(argv[1]) > MaxLength)
        {
            cerr << "That codeword length has not been processed" << endl;
            return 1;
        }
    }
    else if (argc == 3)
    {
        if (atoi(argv[1]) && atoi(argv[2]) && atoi(argv[1]) < atoi(argv[2]) &&
            atoi(argv[1]) >= MinLength && atoi(argv[1]) <= MaxLength && atoi(argv[2]) >= MinLength && atoi(argv[2]) <= MaxLength)
        {
            start = atoi(argv[1]);
            end = atoi(argv[2]);
        }
        else if (atoi(argv[1]) && atoi(argv[2]) && atoi(argv[1]) > atoi(argv[2]) &&
                 atoi(argv[1]) >= MinLength && atoi(argv[1]) <= MaxLength && atoi(argv[2]) >= MinLength && atoi(argv[2]) <= MaxLength)
        {
            start = atoi(argv[2]);
            end = atoi(argv[1]);
        }
        else if (!atoi(argv[1]))
        {
            cerr << "Arg 1 is not a number" << endl;
            return 1;
        }
        else if(!atoi(argv[2]))
        {
            cerr << "Arg 2 is not a number" << endl;
            return 1;
        }
        else if (atoi(argv[1]) < MinLength || atoi(argv[1]) > MaxLength)
        {
            cerr << "That codeword length has not been processed for arg 1" << endl;
            return 1;
        }
        else if (atoi(argv[2]) < MinLength || atoi(argv[2]) > MaxLength)
        {
            cerr << "That codeword length has not been processed for arg 2" << endl;
            return 1;
        }
        else
        {
            cerr << "Two parameters passed. Something is wrong, more information needed to diagnose" << endl;
            return 1;
        }
    }
    else
    {
        cerr << "Either too many parameters passed, or something else entirely" << endl;
        return 1;
    }

    for (int n = start; n <= end; n++){ //which files should I look at?

        time_t now; //for profling speed
        ifstream Input; string inputfile; 
        ofstream log; string logname;
        stringstream N; //to convert length to a string
        const int LogEvery = 1 << n;

        now = time(0);
    
        N << n;
    
//        inputfile = "/mathematics/datamine/bayruns/FINALWORDS/COMBINED_CW_B4_D2_L" + N.str() + ".txt";    
        inputfile = "/csm_data/experimentalmath/maurer/FINALWORDS/COMBINED_CW_B4_D2_L" + N.str() + ".txt";
        logname = "/csm_data/experimentalmath/maurer/SerialLogs/LOG" + N.str();

        log.open(logname.c_str());
        try 
        {
            Input.open(inputfile.c_str());
        }
        catch(string a)
        {
            cerr << "File issues" << endl;
            log << "File issues" << endl;
        }

        //TODO: r and d need R&D to later be made user specific/loop-able
        int d = 2; length_t r = 0;
        string code;

        vector<CodeBook> CodeBooks(Weight(n+1, 4, d)); 

        getline(Input, code);/* Input >> code;*/ //Some residues do not respond well with >> syntax

        log << Weight(n+1, 4, d) << " residues to process" << endl;

        /*CodeBook temp;*/

        for (r = 0; r < Weight(n+1, 4, d); r++)
        {

            CodeBooks[r].Residue = code;/*temp.Residue = code;*/ 

            getline(Input, code);

            while (/* Input >> code &&*/ isdigit(code[0]))
            {
               CodeBooks[r].CodeWords.push_back(ToLength_t(code));/*temp.CodeWords.push_back(ToLength_t(code));*///}
               getline(Input, code);
            }

            CodeBooks[r].GC = Biochem(CodeBooks[r].CodeWords, n);/*temp.GC = Biochem(temp.CodeWords, n);*/
            /*CodeBooks.push_back(temp);
            temp.CodeWords.clear();*/
            if (r%LogEvery==0) {log << (100*(float)r/Weight(n+1, 4, d)) << endl;} //progress
        }

        Input.close();

        log << "sorting" << endl;

        std::sort(CodeBooks.begin(), CodeBooks.end(), Sort_Residues); //TODO:vector that holds largest book & empties if it finds a larger one

        ofstream Output; string outputfile;

        outputfile = "/csm_data/experimentalmath/maurer/SerialResults/COMBINED_CW_B4_D2_L" + N.str() + "_BIO_Arranged.txt";
        Output.open(outputfile.c_str());

        log << "printing" << endl;

        for (r = 0; r < Weight(n+1, 4, d); r++)
        {
            if (CodeBooks[r].CodeWords.size() >= CodeBooks[0].CodeWords.size())//TODO:cutoff value in *.h
            {
                Output << CodeBooks[r].Residue << "|GC" << CodeBooks[r].GC << endl; //print residue

                for (length_t i = 0; i < CodeBooks[r].CodeWords.size(); i++)
                    Output << toQuad(CodeBooks[r].CodeWords[i], n) << endl; //print codewords
                Output << endl;
            }
        }

        Output.close();

        log << "Finished " << n << " in " << time(0) - now << " s" << endl;
        log.close();
    }

    return 0;
} //end main

length_t Tolength_t(length_t i)
{
    return i;
}

length_t ToLength_t(string i)
{
    length_t m = 0;
    for (int j = 0; j < i.length(); j++){
        m += (i[j] - '0') * Power(4, (i.length() - j) - 1);
    }
    return m; 
}

string toQuad(length_t m, int n)
{

    string quad;
    int g;

    for (int j = (n - 1); j >= 0; j--)
    {
        g = (m & (3 * Power(4, j))) >> (j * 2);
        stringstream ss;
        ss << g;
        quad.append(ss.str());
    }

    return quad;
}

