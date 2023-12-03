#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n=4, m=size; // m columns n rows
    int* A = new int[n*m];
    int B[n];
    if(rank == 0){
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                cin >> A[i*n + j];
        for(int k = 0; k < n; ++k)
            cin >> B[k];
    }

    int Alocal[n];
    MPI_Scatter(A, n, MPI_INT, Alocal, n, MPI_INT, 0, MPI_COMM_WORLD);
    // for(int i = 0; i < n; ++i)
    //     cout << "rank:" << rank << ' ' << Alocal[i] << ' ';
    // cout << endl;
    MPI_Bcast(B, n, MPI_INT, 0, MPI_COMM_WORLD);
    int mult = 0, sum = 0;
    for(int i=0; i<n; ++i)
        mult += Alocal[i]*B[i];
    MPI_Gather(&mult, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        for(int i=0; i < n; ++i)
            cout << B[i] << " ";
        cout << endl;
    }
    MPI_Reduce(&mult, &sum, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
    cout << sum << endl;
    MPI_Finalize();
    return 0;
}