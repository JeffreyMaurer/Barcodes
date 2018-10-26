bool Good_Args(int argc, char* argv[], vector<int> &lengths)
{
    if (argc == 1)
    {
        cerr << "No parameters passed" << endl;
        return false;
    }
    else if (argc == 2)
    {
        if (atoi(argv[1]))
        {
            lengths.push_back(atoi(argv[1]))
        }
        else
        {
            cerr << "That parameter is not a number" << endl;
            return false;
        }
    }
    else if (argc == 3)
    {
        if (atoi(argv[1]) && atoi(argv[2]) && (atoi(argv[1]) < atoi(argv[2])))
        {
            for (int i = atoi(argv[1]); i < atoi(argv[2]); i++) lengths.push_back(i);
        }
        else if (atoi(argv[1]) && atoi(argv[2]) && atoi(argv[1]) > atoi(argv[2]))
        {
            for (int i = atoi(argv[2]); i < atoi(argv[1]); i++) lengths.push_back
(i);
        }
        else if (!atoi(argv[1]))
        {
            cerr << "Arg 1 is not a number" << endl;
            if(atoi(argv[2]))
            {
                lengths.push_back(atoi(argv[2]));
            }
            else
            {
                cerr << "Arg 2 is not a number either" << endl;
                return false;
            }    
        }
        else if(!atoi(argv[2]))
        {
            lengths.push_back(atoi(argv[1]));
            cerr << "Arg 2 is not a number" << endl;
            return false;
        }
        else
        {
            cerr << "Two parameters passed. Something is wrong, more information needed to diagnose" << endl;
            return false;
        }
    }
    else if (argc > 3 && argv[1] == "-i")
    {
        for (int i = 1; i <= argc; i++)
        {
            if (atoi(argv[i]) lengths.push_back(atoi(argv[i]));
        }
    }
    else
    {
        cerr << "Either too many parameters passed, or something else entirely" << endl;
        return false;
    }
}

~
