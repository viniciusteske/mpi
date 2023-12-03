#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>

#define NUM 2

int main(int argc, char **argv){
    int size, rank;
    int result = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n = size;
    int *a = (int *)malloc(NUM*size*sizeof(int));
    if(rank == 0){
        srand(time(NULL));
        for(int i=0; i<n; ++i){
            for(int j=0; j<NUM; ++j){
                a[NUM*i+j] = rand()%100;
                printf("%d ", a[NUM*i+j]);
            }
        }
        printf("\n");
    }

    int *c = (int *)malloc(NUM * sizeof(int));
    MPI_Scatter(a, NUM, MPI_INT, c, NUM, MPI_INT, 0, MPI_COMM_WORLD);
    int local_mult = 1;
    for(int i = 0; i < NUM; ++i)
        local_mult *= c[i];
    MPI_Reduce(&local_mult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("%d %d\n", rank, result);
    free(a);
    free(c);
    MPI_Finalize();

    return 0;
}