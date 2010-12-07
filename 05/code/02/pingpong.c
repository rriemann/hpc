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
  int rank, r, i, name_length, size;
  MPI_Status status;
  double time, ttime;
  char name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int destination[size]; // maps: rank => destination of messages
  MPI_Get_processor_name(name, &name_length);

  if(size == 2) {
    destination[0] = 1;
    destination[1] = 0;
  } else if(size == 4) {
    destination[0] = 3;
    destination[2] = 1;
    destination[3] = 0;
    destination[1] = 2;
  } else {
    MPI_Abort(MPI_COMM_WORLD,0);
  }

  if(rank == 0) printf("size is %d\n", size);
  printf("%s: got rank %d\n",name, rank);
  sleep(1);
  
  for (i = 0; i < arrlength; i++){
    msg = (char *)malloc(length[i]);

    if(rank%2 == 0) {
      time = wall_time();
      time = wall_time();
    }

    for (r = 0; r < r_max; r++){
      // printf("rank %d, %d, %d\n", rank, i, r);
      if(rank%2 == 0) {
        MPI_Send(msg, length[i], MPI_CHAR, destination[rank], 0, MPI_COMM_WORLD);
        MPI_Recv(msg, length[i], MPI_CHAR, destination[rank], 0, MPI_COMM_WORLD, &status);
      } else {
        MPI_Recv(msg, length[i], MPI_CHAR, destination[rank], 0, MPI_COMM_WORLD, &status);
        MPI_Send(msg, length[i], MPI_CHAR, destination[rank], 0, MPI_COMM_WORLD);
      }
    }

    if(rank%2 == 0) {
      time = wall_time() - time;
      printf("%s: Zeit um %7d Bytes 2*%d mal zu übertragen: %g s\n",name, length[i], r_max, time / r_max);
    }

    free(msg);
  }

  MPI_Finalize();
}
