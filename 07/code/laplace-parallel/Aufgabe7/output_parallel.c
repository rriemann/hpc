# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void output_parallel(field v, int Lx, int Ly)
{
  field      vv = field_alloc(decomp.Ny, decomp.Nx);
  int        x, y, x_local, y_local, home_of_xy;
  MPI_Status status;

  for (y = 0; y <= decomp.Ny + 1; y++) {
    for (x = 0; x <= decomp.Nx + 1; x++) {
      global2local(x, y, &x_local, &y_local, &home_of_xy);

      if (decomp.my_rank == 0) {
	if (home_of_xy == 0) {
	  vv[y][x] = v[y][x];
	} else {
	  MPI_Recv(&vv[y][x], 1, MPI_DOUBLE, home_of_xy, 0, MPI_COMM_WORLD, &status);
	}
      } else {
	if (decomp.my_rank == home_of_xy) {
	  MPI_Ssend(&v[y_local][x_local], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
      }
    }
  }
  
  if (decomp.my_rank == 0)
    output(vv, decomp.Nx, decomp.Ny);

  field_free(vv);
}
