#include "mpi.h"
#include <iostream>
#include <string.h>

#define MAX 10

using namespace std;

int main(int argc, char **argv){
    int rank, size;
    int bigger = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	int n = atoi(argv[1]);
    int p = atoi(argv[2]);
    char **array = (char **)malloc(n *sizeof(char*));
    for(int i=0; i<n; ++i)
    	array[i] = (char *)malloc(MAX*sizeof(char));
    if(n == size){
        if(rank == 0){
            for(int i=0; i<n; i++){
        		char buffer[MAX];
                scanf("%10s", buffer);
                strcpy(array[i], buffer);
            }
        }
        char *send_buffer = (char *)malloc(n * MAX * sizeof(char));
        if (rank == 0) {
            for (int i = 0; i < n; ++i) {
                strcpy(send_buffer + i * MAX, array[i]);
            }
        }
        char *local_array = (char *)malloc(MAX*sizeof(char));
        MPI_Scatter(send_buffer, MAX, MPI_CHAR, local_array, MAX, MPI_CHAR, 0, MPI_COMM_WORLD);
        int local = 0;
        if(strlen(local_array) > p)
            local += 1;
        MPI_Reduce(&local, &bigger, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
        if(rank == 1)
            printf("%d\n", bigger);
        
        free(local_array);
        free(send_buffer);
        for(int i=0; i<n; ++i)
        	free(array[i]);
        free(array);
        
        MPI_Finalize();
    }else{
        printf("Too many processes for this array size.\n");
    }
    return 0;
}
