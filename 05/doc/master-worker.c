# include <mpi.h>
# include <stdio.h>

void master(const int maxtask);
void worker(void);

int main(int argc, char *argv[])
{
    const int maxtask = 40;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
	master(maxtask);
    else
	worker();

    MPI_Finalize();
}


void master(const int maxtask)
{
    int size, msg, task, dest;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    for (task = 1; task <= maxtask; task++) {	
        MPI_Recv(&msg, 0, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        MPI_Send(&task, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
    }

    task = -1;
    for (dest = 1; dest < size; dest++) {
	MPI_Recv(&msg, 0, MPI_INT, dest, 0, MPI_COMM_WORLD, &status);
	MPI_Send(&task, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }
}


void worker(void)
{
    int rank, msg, task;
    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while(1) {
	MPI_Send(&msg, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
	MPI_Recv(&task, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        if (task < 0) break;

        printf("rank %d: working on task %d\n", rank, task);
	system("sleep 1");
    }
}
