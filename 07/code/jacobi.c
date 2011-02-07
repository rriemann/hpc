# include "laplace.h"

void jacobi(field vneu, field valt, int Nx, int Ny)
{
    int x, y;

    for (y = 1; y <= Ny; y++)
        for (x = 1; x <= Nx; x++)
            vneu[y][x] = (valt[y][x - 1] + valt[y][x + 1]
                        + valt[y - 1][x] + valt[y + 1][x]) * 0.25;
}
