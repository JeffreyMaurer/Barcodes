#include"TwinToss.h"

using namespace std;

//TODO: will sorting fix the problem?
bool Toss(codebook &book)
{
   //auto max = book.codes.begin(); //lwhere is the one with the most incongruencies?
    auto max = &book.codes.front(); //where is the one with the most incongruencies?
    int maxSize = 0; //how many is it incompatible with?
    length_t maxValue; //what is it?
/*for (auto i = book.codes.begin(); i != book.codes.end(); i++)
  {
   if (i->bad.size() > maxSize)
   {
     max = i;
     maxSize = i->bad.size();
     maxValue = i->word;
   }
  }*/
    for (auto& i : book.codes)
    {
        if (i.bad.size() > maxSize)
        {
            max = &i;
            maxSize = i.bad.size();
            maxValue = i.word;
        }
    }
    //cout << "current maxSize: " << maxSize << endl;*/ 
    //if (maxSize) book.codes.erase(max); //get rid of it

    if (maxSize) { max->word = 0; max->bad.clear(); }

    for (auto& i : book.codes) //test
    {
        for (auto j = i.bad.begin();
            j != i.bad.end();)
        {
            if (*j == maxValue) { j = i.bad.erase(j);  break; } //send to back and pop
            else j++;
        }
    }

    if (!maxSize) return false;
    else return true;
}

