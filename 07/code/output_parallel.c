# include "mpi.h"
# include "laplace.h"
# include "decomp.h"
# include <string.h>

extern Decomp decomp;

void output_parallel(field v, int Lx, int Ly)
{
  field      vv = field_alloc(decomp.Ny, decomp.Nx);
  int        x, y, x_local, y_local, home_of_xy;
  MPI_Status status;

  MPI_Datatype Row;
  MPI_Type_contiguous(decomp.Lx, MPI_DOUBLE, &Row);
  MPI_Type_commit(&Row);

  for (y = 0; y <= decomp.Ny + 1; y++) {
    for (x = 0; x <= decomp.Nx + 1; x++) {
      global2local(x, y, &x_local, &y_local, &home_of_xy);

      if (x_local == 1) {
        if (decomp.my_rank == 0) {
          if (home_of_xy == 0) {
            memcpy(&vv[y][x],&v[y][x],decomp.Lx*sizeof(double));
          } else {
            MPI_Recv(&vv[y][x], 1, Row, home_of_xy, 0, MPI_COMM_WORLD, &status);
          }
        } else {
          if (decomp.my_rank == home_of_xy) {
            MPI_Ssend(&v[y_local][x_local], 1, Row, 0, 0, MPI_COMM_WORLD);
          }
        }
        x = x + decomp.Lx - 1;
        continue;
      }

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

  MPI_Type_free(&Row);

  field_free(vv);
}
