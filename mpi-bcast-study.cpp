#include "mpi.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv){
    int rank, size;
    char msg[] = "ananab";
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0)
        strcpy(msg, "banana");
    MPI_Bcast(msg, 7, MPI_CHAR, 0, MPI_COMM_WORLD);
    cout << "Process: " << rank << " msg: " << msg << endl;
    MPI_Finalize();
    return 0;
}