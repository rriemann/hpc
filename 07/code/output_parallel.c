
# include "mpi.h"
# include "laplace.h"
# include "decomp.h"
# include <string.h>
# include <stdio.h>

extern Decomp decomp;

void output_parallel(field v, int Lx, int Ly)
{
  int x, y, i, x_local, y_local, x_global, y_global, home_of_xy;
  field vv = field_alloc(decomp.Ny, decomp.Nx);

  // Rand durch erneuten einlesen setzen
  FILE *data = fopen("input.data", "r");
  double value;

  while (fscanf(data, "%d %d %lg", &x, &y, &value) != EOF) {
    vv[y][x] = value;
  }
  fclose(data);

  // Anlegen des Datentyps zur Übertragung
  MPI_Datatype Block;

  if (decomp.my_rank == 0) {
    MPI_Type_vector(decomp.Ly, decomp.Lx, decomp.Nx+2, MPI_DOUBLE, &Block);
  } else {
    MPI_Type_vector(decomp.Ly, decomp.Lx, decomp.Lx+2, MPI_DOUBLE, &Block);
  }
  MPI_Type_commit(&Block);

  // Einsammeln der Daten und abspeichern bei rank 0
  MPI_Status status;

  for (y = 0; y < decomp.procs_y; ++y) {
    for (x = 0; x < decomp.procs_x; ++x) {
      x_global = x*decomp.Lx+1;
      y_global = y*decomp.Ly+1;
      global2local(x_global, y_global, &x_local, &y_local, &home_of_xy);
      if (decomp.my_rank == 0) {
        if (home_of_xy == 0) {
          for (i = 0; i < decomp.Ly; ++i) {
            memcpy(&vv[y_global+i][x_global],&v[1+i][1],decomp.Lx*sizeof(double));
          }
        } else {
            MPI_Recv(&vv[y_global][x_global], 1, Block, home_of_xy, 0, MPI_COMM_WORLD, &status);
        }
      } else {
        if (home_of_xy == decomp.my_rank) {
          MPI_Ssend(&v[1][1], 1, Block, 0, 0, MPI_COMM_WORLD);
        }
      }
    }
  }

  if (decomp.my_rank == 0) {
    output(vv, decomp.Nx, decomp.Ny);
  }

  MPI_Type_free(&Block);

  field_free(vv);
}