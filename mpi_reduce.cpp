#include "mpi.h"
#include <iostream>
#include <cstdlib>

using namespace std; 
int main(int argc, char **argv){
	int proc, total=0, subtotal=0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank( MPI_COMM_WORLD, &proc);
	subtotal = proc+1;
	MPI_Reduce(&subtotal, &total, 1,  MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	cout << " Proc  "<< proc << "\tTotal= " << total << "\tsubtotal= " << subtotal  << endl;

	MPI_Finalize();
	return 0;
}

