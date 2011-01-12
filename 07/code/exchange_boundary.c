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

  MPI_Sendrecv(&v[Ly][1], 1, Row, decomp.north, 0, &v[Ly+1][1], 1, Row, decomp.north, 0, MPI_COMM_WORLD, &status);

  MPI_Sendrecv(&v[1][1], 1, Row, decomp.south, 0, &v[0][1], 1, Row, decomp.south, 0, MPI_COMM_WORLD, &status);

  MPI_Type_free(&Row);

  MPI_Datatype Column;
  MPI_Type_vector(Ly+2, 1, Lx+2, MPI_DOUBLE, &Column);
  MPI_Type_commit(&Column);

  MPI_Sendrecv(&v[0][Lx], 1, Column, decomp.east, 0, &v[0][Lx+1], 1, Column, decomp.east, 0, MPI_COMM_WORLD, &status);
  MPI_Sendrecv(&v[0][1], 1, Column, decomp.west, 0, &v[0][0], 1, Column, decomp.west, 0, MPI_COMM_WORLD, &status);

  MPI_Type_free(&Column);
}
