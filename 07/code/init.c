# include <stdio.h>
# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void init(field vneu, field valt, int Nx, int Ny)
{
    int     x, y, x_local, y_local, home_of_xy;
    double  value;
    FILE   *data;

    for (y = 0; y <= Ny + 1; y++)
        for (x = 0; x <= Nx + 1; x++) {
            vneu[y][x] = 0;
            valt[y][x] = 0;
        }

    data = fopen("input.data", "r");

    while (fscanf(data, "%d %d %lg", &x, &y, &value) != EOF) {
        global2local(x, y, &x_local, &y_local, &home_of_xy);

        if (home_of_xy == decomp.my_rank) {
            vneu[y_local][x_local] = value;
            valt[y_local][x_local] = value;
        }
    }
    fclose(data);
}
