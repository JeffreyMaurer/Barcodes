#include"BCPArrange.h"

using namespace std;

//length_t to quad int string
string toQuad(length_t m, int n)
{
    string quad;
    for (int j = (n - 1); j >= 0; j--)
    {
        quad += to_string(Digit(m, j));
    }
    return quad;
}

//make sure input is good TODO -i option
bool Good_Args(int argc, char* argv[], int &start, int &end)
{
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
}

void Join(vector<thread> &T)
{
    for (int i = 0; i < T.size(); i++) T[i].join();
}
