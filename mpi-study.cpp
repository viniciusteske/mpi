#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

#define NUM 2

using namespace std;

int main(int argc, char **argv){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int num = atoi(argv[1]);
    printf("%d\n", num);
    int n = size;
    int *a = (int *)malloc(NUM*size*sizeof(int));
    printf("%d ", rank);
    for(int i=0; i<n; ++i){
        for(int j=0; j<NUM; ++j){
            a[NUM*i+j] = rand()%100;
            printf("%d ", a[NUM*i+j]);
        }
    }
    printf("\n");
    free(a);
    MPI_Finalize();
    return 0;
}