#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 200000000  // ~800 MB for int

int main(int argc, char *argv[]) {
    int rank;
    int *data_send = NULL;
    int *data_recv = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    data_send = (int *)malloc(SIZE * sizeof(int));
    data_recv = (int *)malloc(SIZE * sizeof(int));

    if (data_send == NULL || data_recv == NULL) {
        fprintf(stderr, "Memory allocation failed on process %d\n", rank);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    
    for (int i = 0; i < SIZE; i++) {
        data_send[i] = rank;
    }

    if (rank == 0) {
        MPI_Send(data_send, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(data_recv, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        MPI_Send(data_send, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(data_recv, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    
    printf("Process %d received first element: %d\n", rank, data_recv[0]);

    free(data_send);
    free(data_recv);

    MPI_Finalize();
    return 0;
}
