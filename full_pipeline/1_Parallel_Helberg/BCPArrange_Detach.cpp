//scales approximately O(nlogn)
#include"BCPArrange.h"
#include<cstdarg> //ellipse

using namespace std;

int main(int argc, char * argv[])
{

    int start, end;

    //make this look professional
    if (!Good_Args(argc, argv, start, end)) return 1;
    //vector<int> Pillow {1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 24, 30, 40, 50, 60, 70, 80, 90, 100};
    //for (int threadloop = 0; threadloop < Pillow.size(); threadloop++){
    //int threadcount = Pillow[threadloop];
    for (int n = start; n <= end; n++){ //which files should I look at?

        time_t now; //for profling speed
        ifstream Input; string inputfile; 
        ofstream log; string logname;
        stringstream N;// TC; //to convert length to a string
        const int LogEvery = 1 << n;
        //vector<thread> parallel;

        now = time(0);
    
        N << n; //TC << threadcount;
    
        inputfile = "/csm_data/experimentalmath/maurer/FINALWORDS/COMBINED_CW_B4_D2_L" + N.str() + ".txt";
//        logname = "/csm_data/experimentalmath/maurer/ParallelLogs/LOG" + N.str();
        logname = "./Logs/Detach/LOG" + N.str();

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
            if (CodeBooks[r].CodeWords.size() > 2)
            {
                    thread th(Biochem, ref(CodeBooks[r].CodeWords), n, ref(CodeBooks[r].GC));
                    th.detach();
            }
            else 
            {
                Biochem(CodeBooks[r].CodeWords, n, CodeBooks[r].GC);
            }

            if (r%LogEvery==0) {log << (100*(float)r/Weight(n+1, 4, d)) << endl;} //progress
            //log << r << endl;
        }

        Input.close();

        //deleting the codes
        for (r = 0; r < Weight(n+1, 4, d); r++)
        {   
            //deleting the codes
             CodeBooks[r].CodeWords.erase(remove(CodeBooks[r].CodeWords.begin(), CodeBooks[r].CodeWords.end(), 0), CodeBooks[r].CodeWords.end());
        }                    

        log << "sorting" << endl;

        sort(CodeBooks.begin(), CodeBooks.end(), Sort_Residues); //TODO:vector that holds largest book & empties if it finds a larger one

        ofstream Output; string outputfile;

        outputfile = "./Results/COMBINED_CW_B4_D2_L" + N.str() + "_BIO_Arranged.txt";
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

