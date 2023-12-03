#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv){
    int rank, size, buffer, tag=0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Send(&rank, 1, MPI_INT, size-1-rank, tag, MPI_COMM_WORLD);
    MPI_Recv(&buffer, 1, MPI_INT, size-1-rank, tag, MPI_COMM_WORLD, &status);
    cout << "Rank: " << rank << " Msg from: " << buffer << endl;
    MPI_Finalize();
    return 0;
}