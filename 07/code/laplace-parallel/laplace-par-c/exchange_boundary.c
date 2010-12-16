# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void exchange_boundary(field v, int Lx, int Ly)
{
  int y;
  MPI_Status status;

  if (decomp.north >= 0) MPI_Ssend(&v[Ly][1],  Lx, MPI_DOUBLE, decomp.north, 0, MPI_COMM_WORLD);
  if (decomp.south >= 0) MPI_Recv(&v[0][1],    Lx, MPI_DOUBLE, decomp.south, 0, MPI_COMM_WORLD, &status);
  
  if (decomp.south >= 0) MPI_Ssend(&v[1][1],   Lx, MPI_DOUBLE, decomp.south, 0, MPI_COMM_WORLD);
  if (decomp.north >= 0) MPI_Recv(&v[Ly+1][1], Lx, MPI_DOUBLE, decomp.north, 0, MPI_COMM_WORLD, &status);

  for (y = 1; y <= Ly; y++) {
     if (decomp.east >= 0) MPI_Ssend(&v[y][Lx],  1, MPI_DOUBLE, decomp.east, 0, MPI_COMM_WORLD);
     if (decomp.west >= 0) MPI_Recv(&v[y][0],    1, MPI_DOUBLE, decomp.west, 0, MPI_COMM_WORLD, &status);

     if (decomp.west >= 0) MPI_Ssend(&v[y][1],   1, MPI_DOUBLE, decomp.west, 0, MPI_COMM_WORLD);
     if (decomp.east >= 0) MPI_Recv(&v[y][Lx+1], 1, MPI_DOUBLE, decomp.east, 0, MPI_COMM_WORLD, &status);
  }
}
