#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

int main(int argc, char **argv){
    int size, rank, n=0;
    int total_species;
    float goal;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    n = atoi(argv[1]);
    float *a = (float *)malloc(n*sizeof(float));
    if(rank == 0){
        for(int i=0; i<n; ++i){
            scanf("%f", &a[i]);
        }

        sort(a, a+n);
        
        scanf("%f", &goal);
    }
    MPI_Bcast(a, n, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&goal, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    int ratio = n/size;
    int start = rank*ratio;
    int end = start + ratio;
    
    if(n%size != 0)
        if(rank == size-1)
            end += n%size;
    int species = 0;
    for(int i = start; i < end; ++i)
        if(a[i]+i >= goal)
            species += 1;
    MPI_Reduce(&species, &total_species, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0)
        printf("%d\n", total_species);
    free(a);
    MPI_Finalize();
    return 0;
}