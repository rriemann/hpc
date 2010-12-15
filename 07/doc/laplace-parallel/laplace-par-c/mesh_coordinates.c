# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void global2local(int x, int y, int *x_local, int *y_local, int *home_of_xy)
{
  int home_x, home_y;

  global2local_x(x, x_local, &home_x);
  global2local_y(y, y_local, &home_y);
  coord2rank(home_x, home_y, home_of_xy);
}

void global2local_x(int x_global, int *x_local, int *coord_x)
{
  if (x_global == 0) {
    *x_local = 0;
    *coord_x = 0;
  } else if (x_global == decomp.Nx + 1) {
    *x_local = decomp.Lx + 1;
    *coord_x = decomp.procs_x -1;
  } else {
    *x_local = (x_global - 1) % decomp.Lx + 1;
    *coord_x = (x_global - 1) / decomp.Lx;
  }
}

void global2local_y(int y_global, int *y_local, int *coord_y)
{
  if (y_global == 0) {
    *y_local = 0;
    *coord_y = 0;
  } else if (y_global == decomp.Ny + 1) {
    *y_local = decomp.Ly + 1;
    *coord_y = decomp.procs_y -1;
  } else {
    *y_local = (y_global - 1) % decomp.Ly + 1;
    *coord_y = (y_global - 1) / decomp.Ly;
  }
}
