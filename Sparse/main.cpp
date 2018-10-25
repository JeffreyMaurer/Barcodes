#include<iostream>
#include<random>
#include<fstream>
#include"helper.h"
#include"Check.h"
using namespace std;

//TODO: popcorn statistics

int main()
{
	time_t now = time(0);
	
	int del = 2;
	minstd_rand gen;
	gen.seed(random_device{}());
	//int set_size = 5400; //depend on length
	const int num_additions = 1000 * 10; //depend on length, set_size
	int candidate;
	const int num_seeds_max = 10;

	/*	//ofstream out("Sparse.txt");
	//out << "length,set_size,num_additions,avg_num_seeds" << endl;

	for (int length = 3; length < 7; length++)
	{
		const int num_additions_max = power(10, length - 1);
		const int num_seeds_max = power(10, length);

		uniform_int_distribution<int> random_number(0, power(4, length));
		vector<int> answer(length);
		Check check(length, del);
		int candidate;
		int num_seeds(0); //the output
		time_t set_size_time = time(0); //limit time to a minute
		for (set_size = answer.size();
			time(0) - set_size_time < 60 && num_seeds < num_seeds_max;
			set_size++)
		{
			set_size_time = time(0);
			for (num_additions = set_size; num_additions < num_additions_max; num_additions *= 2)
			{
				num_seeds = 0;
				answer.clear(); //make sure that the while loop is done at least once
				while (answer.size() < set_size && num_seeds < num_seeds_max)
				{
					vector<int>  temp_answer;

					//seed the algorithm
					temp_answer.push_back(random_number(gen));

					//go through n random numbers and see if they work
					for (int j = 0; j < num_additions; j++)
					{
						candidate = random_number(gen);
						int k = 0;

						//go through all of the current set to see if this number works with this set
						for (; k < temp_answer.size(); k++)
						{
							if (!check.is_compatible(candidate, temp_answer[k]))
							{
								//if one of the numbers does not play nice, the number is void
								break;
							}
						}
						//if it did not void (break) then k == size
						if (k == temp_answer.size())
						{
							temp_answer.push_back(candidate);
						}
					}

					//after going through 1000 random numbers, does this set exceed the current best?
					if (temp_answer.size() > answer.size())
					{
						answer = temp_answer;
					}
					num_seeds++;
				}
				if (num_seeds < num_seeds_max) data_points.push_back(Data(length, set_size, num_additions, num_seeds));
				cout << answer << endl;
			}
		}
	}*/
	
	for (int length = 13; length <= 13; length++)
	{
		vector<vector<int>> data_points(num_seeds_max);
		vector<int> answer;
		uniform_int_distribution<int> random_number(0, power(4, length));
		Check check(length, del);
		int num_seeds(0);

		while (num_seeds < num_seeds_max)
		{
			vector<int>  temp_answer;

			//seed the algorithm
			temp_answer.push_back(random_number(gen));

			//go through n random numbers and see if they work
			for (int j = 0; j < num_additions; j++)
			{
				candidate = random_number(gen);
				int k = 0;

				//go through all of the current set to see if this number works with this set
				for (; k < temp_answer.size(); k++)
				{
					if (!check.is_compatible(candidate, temp_answer[k]))
					{
						//if one of the numbers does not play nice, the number is void
						break;
					}
				}
				//if it did not void (break) then k == size
				if (k == temp_answer.size())
				{
					temp_answer.push_back(candidate);
					data_points[num_seeds].push_back(j);
				}
			}

			//after going through n random numbers, does this set exceed the current best?
			if (temp_answer.size() > answer.size())
			{
				answer = temp_answer;
			}
			num_seeds++;
		}
		ofstream out("Sparse_histo" + to_string(length) + ".txt");

		for (auto& data_point : data_points)
		{
			for (int i = 0; i < data_point.size(); i++)
			{
				out << data_point[i] << ',';
			}
			out << '\n';
		}

		cout << answer << endl;
		cout << "num seeds: " << num_seeds << endl;
		cout << "num in set: " << answer.size() << endl;
		cout << "took about: " << time(0) - now << " seconds" << endl;
	}
		

		/*for (auto& point : data_points)
		{
		out << point.length << ',';
		for (auto& num : point.hits)
		{
		out << toQuad(num, length) << ',';
		}
		out << '\n';
		}*/

		
	std::system("pause");

	return 0;
}