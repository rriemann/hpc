# include <math.h>
# include "laplace.h"

double diff(field v1, field v2, int Nx, int Ny)
{
    int    x, y;
    double d, sum;

    sum = 0;
    for (y = 1; y <= Ny; y++)
        for (x = 1; x <= Nx; x++) {
            d = v1[y][x] - v2[y][x];
            sum += d * d;
        }

    return sqrt(sum);
}
