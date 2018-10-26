#include "Check.h"
#include<algorithm>
using namespace std;

Check::Check(digit length_, digit del_) : length(length_), del(del_), routes(num_permutations(del_))
{
	if (del >= length)
	{
		throw 0; // "too many del";
	}

	//first iteration
	vector<bool> iter(del*2);

	for (int i = iter.size() - 1; i >= del; i--)
	{
		iter[i] = 1;
	}

	//get the rest of the permutations
	do 
	{
		routes.push_back(iter);
	} while (next_permutation(iter.begin(), iter.end()));
}

bool Check::is_compatible(int first, int second)
{
	for (auto& route : routes)
	{
		int i(0);
		digit iter(del), first_iter(del), second_iter(del);
		for (; iter < length;)
		{
			if (Digit(first, iter - first_iter) == Digit(second, iter - second_iter))
			{
				iter++; //if same, increment
			}
			else //if different
			{
				//if there are no more mutations left, then through this path, the two are compatible
				if (i == route.size()) { break; }

				//decrement one of the two iters
				if (route[i])	{ first_iter--; }
				else			{ second_iter--; }

				//get ready for the next mutation
				i++; 

			} //if difference found

		} //iter loop

		//if the loop went through the entire sequence without breaking,
		//then the loop ended without breaking,
		//if there was not a break, then the two are incompatible through this path
		if (iter == length)  
		{
			return false;
		}

	} //routes loop

	return true;

} //fxn end

Check::~Check() {}

