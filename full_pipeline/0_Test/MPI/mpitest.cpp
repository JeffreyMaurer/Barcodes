#include <boost/mpi.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  int rank;
  char hostname[256];

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  gethostname(hostname,255);

  cout << "Hello world!  I am process number: "<< rank << " on host " << hostname << endl;

  MPI_Finalize();

  return 0;
}
