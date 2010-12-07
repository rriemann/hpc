#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

double wall_time(void);

int main(int argc, char *argv[])
{
  const int length[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
  const int arrlength = sizeof(length)/sizeof(length[0]);
  const int r_max = 1000; // wiederholungen
  char *msg;
  int rank, r, i;
  MPI_Status status;
  double time, ttime;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  char name[MPI_MAX_PROCESSOR_NAME];
  int len;
  MPI_Get_processor_name(name,&len);
  printf("hie: %s\n",name);

  for (i = 0; i < arrlength; i++){
    msg = (char *)malloc(length[i]);

    if(rank == 0) {
      time = wall_time();
      time = wall_time();
    }

    for (r = 0; r < r_max; r++){
      // printf("rank %d, %d, %d\n", rank, i, r);
      if(rank == 0) {
        MPI_Send(msg, length[i], MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(msg, length[i], MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
      } else {
        MPI_Recv(msg, length[i], MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Send(msg, length[i], MPI_CHAR, 0, 0, MPI_COMM_WORLD);
      }
    }

    if(rank == 0) {
      time = wall_time() - time;
      printf("Zeit um %7d Bytes 2*%d mal zu übertragen: %g s\n",length[i], r_max, time / r_max);
    }

    free(msg);
  }

  MPI_Finalize();
}
