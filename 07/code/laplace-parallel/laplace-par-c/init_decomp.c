# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

Decomp decomp;

void init_decomp(void)
{
  MPI_Comm_size(MPI_COMM_WORLD, &decomp.processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &decomp.my_rank);

  /* size of the local mesh */

  decomp.Lx = decomp.Nx / decomp.procs_x;
  decomp.Ly = decomp.Ny / decomp.procs_y;

  if (decomp.procs_x * decomp.procs_y != decomp.processes)
    die("procs_x * procs_y != processes");

  if (decomp.Nx % decomp.procs_x) die("mod(Nx, procs_x) != 0");
  if (decomp.Ny % decomp.procs_y) die("mod(Ny, procs_y) != 0");

  /* mapping: process coordinates <-> ranks */

  rank2coord(decomp.my_rank, &decomp.coord_x, &decomp.coord_y);
  coord2rank(decomp.coord_x, decomp.coord_y + 1, &decomp.north);
  coord2rank(decomp.coord_x, decomp.coord_y - 1, &decomp.south);
  coord2rank(decomp.coord_x + 1, decomp.coord_y, &decomp.east);
  coord2rank(decomp.coord_x - 1, decomp.coord_y, &decomp.west);
}
