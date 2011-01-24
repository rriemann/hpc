
# include "mpi.h"
# include "laplace.h"
# include "decomp.h"
# include <string.h>

extern Decomp decomp;

void output_parallel(field v, int Lx, int Ly)
{
  field      vv = field_alloc(decomp.Ny, decomp.Nx);
  int        x, y, i, x_local, y_local, x_global, y_global, home_of_xy;
  MPI_Status status;

  MPI_Datatype Row;
  MPI_Type_contiguous(decomp.Lx, MPI_DOUBLE, &Row);
  MPI_Type_commit(&Row);

  MPI_Datatype Block;
//   if (decomp.my_rank == 0) {
//     MPI_Type_vector(decomp.Ly, 1, decomp.Nx+2, Row, &Block);
//   } else {
    MPI_Type_vector(decomp.Ly, 1, decomp.Lx+2, Row, &Block);
//   }
  MPI_Type_commit(&Block);


  if (decomp.my_rank == 0) {
    for (y = 0; y < decomp.procs_y; ++y) {
      for (x = 0; x < decomp.procs_x; ++x) {
        x_global = x*decomp.Lx+1;
        y_global = y*decomp.Ly+1;
        global2local(x_global, y_global, &x_local, &y_local, &home_of_xy);
        printf("%d %d %d\n",x,y,home_of_xy);
        if (home_of_xy == 0) {
          for (i = 0; i <= decomp.Ly; ++i) {
            memcpy(&vv[y_global+i][x_global+1],&v[1+i][1],decomp.Lx*sizeof(double));
          }
        } else {
//           MPI_Recv(&vv[y_global][x_global], 1, Block, home_of_xy, 0, MPI_COMM_WORLD, &status);
        }
        printf("x\n\n",x,y);
      }
    }
  } else {
//     MPI_Ssend(&v[1][1], 1, Block, 0, 0, MPI_COMM_WORLD);
  }

  // TODO Randaustausch

  if (decomp.my_rank == 0) {
    memcpy(&vv[0,0],&v[0,0],(decomp.Nx+2)*sizeof(double)); // bottom
    memcpy(&vv[decomp.Ny+1,0],&v[decomp.Ly+1,0],(decomp.Nx+2)*sizeof(double)); // top
    for (i = 1; i < decomp.Ny + 1; ++i) {
      vv[i,0] = v[i,0]; // left
      vv[i,decomp.Nx+1] = v[i,decomp.Nx+1]; // right
    }
    output(vv, decomp.Nx, decomp.Ny);
  }

  MPI_Type_free(&Row);
  MPI_Type_free(&Block);

  field_free(vv);
}