//Imprime a maquina onde cada processo esta sendo executado
#include "mpi.h"
#include <iostream>
#include <cstdlib>

using namespace std;
int main(int argc, char **argv)
{
	int size, rank;
	char name[MPI_MAX_PROCESSOR_NAME];
	int s_size;
	MPI_Init(&argc,&argv);
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name,&s_size);
	
	cout << "Sou o processo " << rank << " da maquina " << name << endl;
	MPI_Finalize();
	return 0;
}
