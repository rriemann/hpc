#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void master();
void slave();
const int length[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
const int arrlength = sizeof(length)/sizeof(length[0]);
char *msg;
int rank, r, i;
MPI_Status status;

int main(int argc, char *argv[])
{

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  for (i = 0; i < arrlength; i++){
    msg = (char *)malloc(length[i]);
    for (r = 0; r < 1000; r++){
      printf("rank %d, %d, %d\n", rank, i, r);
      if(rank == 0) {
        MPI_Send(msg, length[i], MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(msg, length[i], MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
      } else {
        MPI_Recv(msg, length[i], MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Send(msg, length[i], MPI_CHAR, 0, 0, MPI_COMM_WORLD);
      }
    }
    free(msg);
  }

  MPI_Finalize();
}
