#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void master();
void slave();
const int length[] = {1, 10, 100, 1000, 10000, 100000}; //, 1000000};
const int arrlength = sizeof(length)/sizeof(length[0]);
char *msg;
int rank;
MPI_Status status;

int main(int argc, char *argv[])
{

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0) {
    master();
  } else {
    slave();
  }

  MPI_Finalize();
}


void master()
{
  int task;
  int i, wiederholungen;

  for (i = 0; i < arrlength; i++){
//     printf("vor malloc\n");
    msg = (char *)malloc(length[i]);
//     printf("nach malloc\n");
    for (wiederholungen = 0; wiederholungen < 1000; wiederholungen++){
      printf("rank %d, %d, %d\n", rank, i, wiederholungen);
//       memset(msg, 0x0,length[i]);
      MPI_Send(msg, length[i], MPI_CHAR, 1, 0, MPI_COMM_WORLD);
//       printf("vor rec\n");
      MPI_Recv(msg, length[i], MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
//       printf("nach rec\n");
    }
//     printf("vor free\n");
    free(msg);
  }
}


void slave()
{
  int dest, i, wiederholungen;
  for(i = 0; i < arrlength; i++) {

    msg = (char *)malloc(length[i]);
    for (wiederholungen = 0; wiederholungen < 1000; wiederholungen++){
      printf("rank %d, %d, %d\n", rank, i, wiederholungen);
//       printf("vor rec\n");
      MPI_Recv(msg, length[i], MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//       printf("nach rec\n");
//       memset(msg, 0x0,length[i]);
      MPI_Send(msg, length[i], MPI_INT, 0, 0, MPI_COMM_WORLD);
//       printf("nach send\n");
    }
    free(msg);
  }
}
