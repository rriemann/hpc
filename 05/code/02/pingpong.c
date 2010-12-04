# include <mpi.h>
# include <stdio.h>

void proc0();
void proc1(void);
const int length[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
const int arrlength = 2;

int main(int argc, char *argv[])
{
    int rank;

//     printf("Arraylaenge: %d\n", arrlength);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
	proc0();
    else
	proc1();

    MPI_Finalize();
}


void proc1()
{
  int rank, msg, task;
    MPI_Status status;
    int i, wiederholungen;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     printf("rank proc1 %d\n", rank);

    for (i = 0; i < arrlength; i++){
      for (wiederholungen = 0; wiederholungen < 1000; wiederholungen++){
	MPI_Send(&msg, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
	MPI_Recv(&task, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

	printf("rank %d: working on task %d\n", rank, task);
// 	system("sleep 0.001");
      }
    }
//     printf("test2\n");
}


void proc0()
{
    int size, msg, task, dest, rank;
    int wiederholungen;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     printf("rank proc0 %d\n", rank);
    
    for (task = 1; task <= arrlength; task++) {	
      for (wiederholungen = 0; wiederholungen < 1000; wiederholungen++){
	MPI_Recv(&msg, 0, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
	MPI_Send(&task, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      }
    }
//     printf("test0\n");

//     task = -1;
//     for (dest = 1; dest < size; dest++) {
// 	MPI_Recv(&msg, 0, MPI_INT, dest, 0, MPI_COMM_WORLD, &status);
// 	MPI_Send(&task, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
//     }
//     printf("test1\n");
}
