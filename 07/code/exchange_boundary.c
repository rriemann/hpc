# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void exchange_boundary(field v, int Lx, int Ly)
{
  int y;
  MPI_Status status[4];
  MPI_Request req[4];

  MPI_Datatype Row;
  MPI_Type_contiguous(Lx, MPI_DOUBLE, &Row);
  MPI_Type_commit(&Row);

  MPI_Isend(&v[Ly][1],   1, Row, decomp.north, 0, MPI_COMM_WORLD, &req[0]);
  MPI_Irecv(&v[Ly+1][1], 1, Row, decomp.north, 0, MPI_COMM_WORLD, &(*status));

  MPI_Isend(&v[1][1], 1, Row, decomp.south, 0, MPI_COMM_WORLD, &req[1]);
  MPI_Irecv(&v[0][1], 1, Row, decomp.south, 0, MPI_COMM_WORLD, &status[1]);

  MPI_Datatype Column;
  MPI_Type_vector(Ly, 1, Lx+2, MPI_DOUBLE, &Column);
  MPI_Type_commit(&Column);

  MPI_Isend(&v[1][Lx],   1, Column, decomp.east, 0, MPI_COMM_WORLD, &req[2]);
  MPI_Irecv(&v[1][Lx+1], 1, Column, decomp.east, 0, MPI_COMM_WORLD, &status[2]);

  MPI_Isend(&v[1][1], 1, Column, decomp.west, 0, MPI_COMM_WORLD, &req[3]);
  MPI_Irecv(&v[1][0], 1, Column, decomp.west, 0, MPI_COMM_WORLD, &status[3]);

  MPI_Waitall(4,req,status);

  MPI_Type_free(&Row);
  MPI_Type_free(&Column);
}
