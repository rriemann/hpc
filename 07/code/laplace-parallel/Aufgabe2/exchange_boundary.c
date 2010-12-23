# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void exchange_boundary(field v, int Lx, int Ly)
{
  int y;
  MPI_Status status;
  
  MPI_Datatype Row;
  MPI_Type_contiguous(Lx, MPI_DOUBLE, &Row);
  MPI_Type_commit(&Row);

//   MPI_Ssend(&v[Ly][1],  1, Row, decomp.north, 0, MPI_COMM_WORLD);
//   MPI_Recv(&v[Ly+1][1], 1, Row, decomp.north, 0, MPI_COMM_WORLD, &status);
  MPI_Sendrecv(&v[Ly][1], 1, Row, decomp.north, 0, &v[Ly+1][1], 1, Row, decomp.north, 0, MPI_COMM_WORLD, &status);
  
//   MPI_Ssend(&v[1][1],   1, Row, decomp.south, 0, MPI_COMM_WORLD);
//   MPI_Recv(&v[0][1],    1, Row, decomp.south, 0, MPI_COMM_WORLD, &status);
  MPI_Sendrecv(&v[1][1], 1, Row, decomp.south, 0, &v[0][1], 1, Row, decomp.south, 0, MPI_COMM_WORLD, &status);

  MPI_Type_free(&Row);
  
//   for (y = 1; y <= Ly; y++) {
//      MPI_Ssend(&v[y][Lx],  1, MPI_DOUBLE, decomp.east, 0, MPI_COMM_WORLD);
//      MPI_Recv(&v[y][0],    1, MPI_DOUBLE, decomp.west, 0, MPI_COMM_WORLD, &status);
// 
//      MPI_Ssend(&v[y][1],   1, MPI_DOUBLE, decomp.west, 0, MPI_COMM_WORLD);
//      MPI_Recv(&v[y][Lx+1], 1, MPI_DOUBLE, decomp.east, 0, MPI_COMM_WORLD, &status);
//   }
  
//  TODO: geht noch nicht. "laplace: error: no convergence" mit der for-loop oben geht es wieder
  MPI_Datatype Column;
  MPI_Type_vector(Ly, 1, Lx+1, MPI_DOUBLE, &Column);
  MPI_Type_commit(&Column);
  
  MPI_Sendrecv(&v[1][Lx], 1, Column, decomp.east, 0, &v[1][Lx+1], 1, Column, decomp.east, 0, MPI_COMM_WORLD, &status);
  MPI_Sendrecv(&v[1][1], 1, Column, decomp.west, 0, &v[1][0], 1, Column, decomp.west, 0, MPI_COMM_WORLD, &status);
  
  MPI_Type_free(&Column);
}
