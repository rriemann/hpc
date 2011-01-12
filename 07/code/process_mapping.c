# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void coord2rank(int coord_x, int coord_y, int *rank)
{
  if (coord_x < 0 ||
      coord_y < 0 ||
      coord_x >= decomp.procs_x ||
      coord_y >= decomp.procs_y )
    *rank =  MPI_PROC_NULL;

  else
    *rank = coord_x + coord_y * decomp.procs_x;

}

void rank2coord(int rank, int *coord_x, int *coord_y)
{
  *coord_x = rank % decomp.procs_x;
  *coord_y = rank / decomp.procs_x;
}
