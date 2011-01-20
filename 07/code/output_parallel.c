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
  
  MPI_Datatype Column;
  MPI_Type_vector(decomp.Ly, 1, Lx+2, MPI_DOUBLE, &Column);
  MPI_Type_commit(&Column);

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




# include "mpi.h"
# include "laplace.h"
# include "decomp.h"
# include <string.h>
 
extern Decomp decomp;
 
void output_parallel(field v, int Lx, int Ly)
{
  field      vv = field_alloc(decomp.Ny, decomp.Nx);
  int        x, y, i, x_local, y_local, home_of_xy;
  MPI_Status status;
 
  MPI_Datatype Row;
  MPI_Type_contiguous(decomp.Lx, MPI_DOUBLE, &Row);
  MPI_Type_commit(&Row);
 
  MPI_Datatype Block;
  MPI_Type_vector(decomp.Ly, Row, (decomp.procs_x-1)*decomp.Lx+2, MPI_DOUBLE, &Block);
  MPI_Type_commit(&Block);
 
  for (x = 0; x < decomp.procs_x; ++x) {
    for (y = 0; y < decomp.procs_y; ++y) {
      global2local(x*decomp.Lx+1, y*decomp.Ly+1, &x_local, &y_local, &home_of_xy);
      if (decomp.my_rank == 0) {
        if (home_of_xy == 0) {
          for (i = 0; i <= decomp.Ly; ++i) {
            memcpy(&vv[y*decomp.Ly+1+i][x*decomp.Lx+1],&v[y*decomp.Ly+1+i][x*decomp.Lx+1],decomp.Lx*sizeof(double));
          }
        } else {
          MPI_Recv(&vv[ydecomp.Ly+1][x*decomp.Lx+1], 1, Block, home_of_xy, 0, MPI_COMM_WORLD, &status);
        }
      } else {
        if (decomp.my_rank == home_of_xy) {
          MPI_Ssend(&v[1][1], 1, Block, 0, 0, MPI_COMM_WORLD);
        }
      }
    }
  }
 
  // TODO Randaustausch: rank-nummer an empfänger mitgeben!!
  
  if (decomp.my_rank != 0) {
    MPI_Ssend(&v[0][0], 1, Row, 0, 0, MPI_COMM_WORLD);
    MPI_Ssend(&v[0][decomp.Lx], 1, Row, 0, 0, MPI_COMM_WORLD);
    MPI_Ssend(&v[0][0], 1, Column, 0, 0, MPI_COMM_WORLD);
    MPI_Ssend(&v[decomp.Ly][0], 1, Column, 0, 0, MPI_COMM_WORLD);
  } else {
    MPI_Recv(&vv[0][0], 1, MPI_DOUBLE, home_of_xy, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&vv[0][decomp.Lx], 1, MPI_DOUBLE, home_of_xy, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&vv[0][0], 1, MPI_DOUBLE, home_of_xy, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&vv[decomp.Ly][0], 1, MPI_DOUBLE, home_of_xy, 0, MPI_COMM_WORLD, &status);
  }
 
  if (decomp.my_rank == 0)
    output(vv, decomp.Nx, decomp.Ny);
 
  MPI_Type_free(&Row);
  MPI_Type_free(&Block);
 
  field_free(vv);
}