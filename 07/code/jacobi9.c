# include "laplace.h"

void jacobi9(field vneu, field valt, int Nx, int Ny)
{
    int x, y;

    for (y = 1; y <= Ny; y++) {
        for (x = 1; x <= Nx; x++) {
            vneu[y][x] = 4.0 * (valt[y][x - 1] + valt[y][x + 1] + valt[y - 1][x] + valt[y + 1][x]) 
		+ valt[y - 1][x - 1] + valt[y - 1][x + 1] + valt[y + 1][x - 1] + valt[y + 1][x + 1];
            vneu[y][x] *= 0.05;
	}
    }
}
