#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<cstdlib>
#include<cstdarg>

using namespace std;

int main()
{
   vector< vector<int> > data(19); int pillow[]={1,2,3,4,5,6,10,12,15,20,24,30,40,50,60,72,80,90,100};
   bool end = false;
   int i = 0; 
   string time; int j = 0;
   ofstream Output; 

   while (!end)
   {
      ifstream Input; string inputname;
      stringstream I;
      I << pillow[i];
      inputname = "./T" + I.str() + "/time";

      try
      {
         Input.open(inputname.c_str());
      }
      catch(...)
      {
         cerr << "file not found" << endl;
      }

      while (Input >> time) 
      {
         data[i].push_back(atoi(time.c_str()));
      }

      Input.close();

      i++;
      if (19 < i) end = true;
   }

   Output.open("Grid.txt");

   for (i = 0; i < 19; i++)
   {
      for (j = 0; j < data[i].size(); j++)
      {
          Output << data[i][j] << "\t";
      }
   Output << endl;
   }

   Output.close();

   return 0;
}
