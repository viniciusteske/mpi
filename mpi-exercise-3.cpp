#include "mpi.h"
#include <iostream>
#include <string.h>

#define MAX 10

using namespace std;

int main(int argc, char **argv){
    int rank, size;
    int p;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	int n = atoi(argv[1]);
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
        char *local_array = (char *)malloc(MAX*sizeof(char));
        MPI_Scatter(array, MAX, MPI_CHAR, local_array, MAX, MPI_CHAR, 0, MPI_COMM_WORLD);
        // for(int i=0; i<n; ++i)
		// 	MPI_Bcast(array[i], MAX, MPI_CHAR, 0, MPI_COMM_WORLD);	
        
        printf("%d ", rank);
        printf("%s\n", local_array);
        // for(int j=0; j<n; ++j){
        //     printf("%s ", array[j]);
        // }
        printf("\n");
        free(local_array);
        for(int i=0; i<n; ++i)
        	free(array[i]);
        free(array);
        
        MPI_Finalize();
    }else{
        printf("Too many processes for this array size.\n");
    }
    return 0;
}
