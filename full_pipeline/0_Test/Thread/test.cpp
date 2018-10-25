#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<ctime>
#include<fstream>
using namespace std;

mutex mt;

void Print()
{

   for (int i = 0; i < 10000; i++) {int g = 0; while (g < 50) {g++}}
   //lock_guard<mutex> lock(mt);
   mt.lock();
   thread::id this_id = this_thread::get_id();
   cout << "Hello World" << this_id << endl;
   mt.unlock();

}

void JOIN(vector<thread>& q)
{
   for (int i = 0; i < q.size(); i++) q[i].join();
}

int main()
{
   vector<thread> g; time_t h = time(0); ofstream out("out.txt");
//parallel
   for (int i = 0; i < 10000; i++) g.push_back(thread(Print));
   JOIN(g);
   out << time(0) - h << endl;
   h = time(0);
//serial
   for (int i = 0; i < 10000; i++) Print();
   out << time(0) - h << endl;
   return 0;
}
