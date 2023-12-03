#include "mpi.h"
#include <iostream>
#include <cstdlib>

#define SIZE 5
using namespace std;

int main(int argc, char **argv){
    int size, rank, sendcount, recvcount, source;
    float total = 0;
    float sendbuf[SIZE][SIZE] = {
        {1.1, 2.0, 3.0, 4.0, 5.0}, 
        {5.0, 6.2, 7.0, 8.0, 4.0}, 
        {9.0, 10.0, 11.0, 12.4, 2.0}, 
        {10.0, 1.0, 11.0, 13.2, 4.2},
        {13.5, 14.0, 15.9, 16.1, 3.0}
    };
    float recvbuf[SIZE];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size == SIZE){
        source = 0;
        sendcount = SIZE;
        recvcount = SIZE;
        MPI_Scatter(sendbuf, sendcount, MPI_FLOAT, recvbuf, recvcount, MPI_FLOAT, source, MPI_COMM_WORLD);
        float local_total = 0; 
        for(int i=0; i<SIZE; ++i)
            local_total += recvbuf[i];
        cout << rank << ": " << local_total << endl;
        MPI_Reduce(&local_total, &total, 1, MPI_FLOAT, MPI_SUM, source, MPI_COMM_WORLD);
        if(rank == 0)
            cout << rank << ": " << total << endl;
        MPI_Finalize();
    }else{
        cout << "Must specify: " << SIZE << " processes." << endl;
    }
    return 0;
}