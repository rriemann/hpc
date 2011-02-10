# include <stdio.h>
# include "laplace.h"

void init(char *datafile, field v, int Nx, int Ny)
{
    int     x, y;
    double  value;
    FILE   *data;

    #pragma omp parallel for private(x)
    for (y = 0; y <= Ny + 1; y++) {
        for (x = 0; x <= Nx + 1; x++) {
            v[y][x] = 0;
        }
    }

    data = fopen(datafile, "r");

    while (fscanf(data, "%d %d %lg", &x, &y, &value) != EOF) {
        v[y][x] = value;
    }

    fclose(data);
}
