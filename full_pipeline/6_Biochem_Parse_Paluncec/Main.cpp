//scales approximately O(nlogn)
#include"BCPArrange.h"

using namespace std;

int main(int argc, char * argv[])
{

    int start, end;

    //make this look professional
    if (!Good_Args( argc, argv, start, end)) return 1;

    ofstream log; string logname;

    logname = "/csm_data/experimentalmath/maurer/Logfiles/Tenengolts/BioChem/parallel/log" + to_string(start) + "to" + to_string(end) + ".txt";
    log.open(logname.c_str());

    for (int n = start; n <= end; n++){ //which files should I look at?
    time_t now = time(0); //for profiling speed of each length
    for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) 
    {
        time_t now = time(0); //for profiling speed of each file
        ifstream Input; string inputname; 
        const int LogEvery = 1 << n;
        int d = 2;

        inputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/Tossed/" +
                        to_string(n) + "length/TL" + to_string(n) + "D2R" + to_string(i) + "-" + 
			to_string(j) + "TT.txt";
        //inputname = "testfiles/TL7D2R0-0TT.txt";
        Input.open(inputname.c_str());

        vector<CodeBook> CodeBooks(Weight(n,2, d)); 
        vector<thread> parallel(THREADCOUNT);
        string code;
        for (length_t r = 0; r < Weight(n, 2, d); r++)
        {
            getline(Input, code);
            CodeBooks[r].Residue = code.substr(0, code.find('|'));  
            //read input file
            getline(Input, code);
            while (isdigit(code[0]))
            { //code, needs fixing for fringe cases though
               CodeBooks[r].CodeWords.push_back(ToLength_t(code));
               getline(Input, code);
            }
            //process codebooks; if large enough, process in a new thread
            if (CodeBooks[r].CodeWords.size() > 2) 
            {
                if (parallel[r % THREADCOUNT].joinable()) parallel[r % THREADCOUNT].join();
                parallel[r % THREADCOUNT] = thread(Biochem, ref(CodeBooks[r].CodeWords), n, ref(CodeBooks[r].GC));
            }
            else 
            {
                Biochem(CodeBooks[r].CodeWords, n, CodeBooks[r].GC);
            }
            //log progress
            //if (r%LogEvery==0) {log << (100*(float)r/Weight(n, 2, d)) << endl;} 
        }
        Join(parallel);

        Input.close();

        //deleting the codes
        for (length_t r = 0; r < Weight(n, 2, d); r++)
        {   
             CodeBooks[r].CodeWords.erase(remove(CodeBooks[r].CodeWords.begin(), CodeBooks[r].CodeWords.end(), 0), CodeBooks[r].CodeWords.end());
        }                    

        log << "sorting" << endl;
        sort(CodeBooks.begin(), CodeBooks.end(), Sort_Residues); //TODO:vector that holds largest book & empties if it finds a larger one

        log << "printing" << endl;
        ofstream Output; string outputname;
        outputname = "/csm_data/experimentalmath/maurer/Tenengolts_Generate/BioChem/" +
                        to_string(n) + "length/TL" + to_string(n) + "D2R" + to_string(i) + "-" +
                        to_string(j) + "BioChem5545.txt";
//        outputname = "TL7D2R0-0BioChem.txt";
        Output.open(outputname.c_str());
        for (length_t r = 0; r < Weight(n, 2, d); r++)
        {
//            if (CodeBooks[r].CodeWords.size() >= CodeBooks[0].CodeWords.size())//TODO:cutoff value in *.h
//            {
                Output << CodeBooks[r].Residue << "|GC" << CodeBooks[r].GC << "|" << CodeBooks[r].CodeWords.size() << endl; //print residue
                for (length_t i = 0; i < CodeBooks[r].CodeWords.size(); i++){ //TODO:better looping for readability, put everything in string before writing
                    Output << toQuad(CodeBooks[r].CodeWords[i], n) << endl; //print codewords
                }
                Output << endl;
        }
        Output.close();

        log << "file:" << i << ":" << j << ":" << time(0) - now << endl;
    }//j
    }//i
    log << "length:" << n << ":" << time(0) - now << endl;
    }//n

    log.close();  

    return 0;
} //end main
