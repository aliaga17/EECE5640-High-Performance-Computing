#include <stdio.h>
#include <mpi.h>

const int COUNT_LIMIT = 64;

int main(int argc, char *argv[])
{
    int rank, size, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    //Counter variable
    int count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name, &namelen);
    
    if(count<COUNT_LIMIT){
        if(rank != 0)
            MPI_Recv(&count, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        count++;
        printf("Proces %d from the Node %s increments count from %d to %d.\n", rank, processor_name, count-1, count);
        if(rank!=size-1)
	   MPI_Send(&count, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
    }
    
   MPI_Finalize();
   return 0;
}
