# include <math.h>
# include "laplace.h"

void jacobi(field solution, 
            int stencil, int Nx, int Ny, double eps, int max_iter, 
            int *iterations, double *diff)
{
    int x, y, niter;
    field v = field_alloc(Ny, Nx);


    for (niter = 1; niter <= max_iter; niter++) {

	for (y = 0; y <= Ny + 1; y++) {
	    for (x = 0; x <= Nx + 1; x++) {
		v[y][x] = solution[y][x];
	    }
	}

	switch (stencil) {
	    case 5:
		jacobi5(solution, v, Nx, Ny, diff);
		break;
	    case 9:
		jacobi9(solution, v, Nx, Ny, diff);
		break;
	    default:
		die("unknown stencil");
		break;
	}

	if (*diff < eps) break;
    }

    *iterations = niter;

    field_free(v);
}

void jacobi5(field vneu, field valt, int Nx, int Ny, double *diff)
{
    int x, y;
    double d, sum;

    sum = 0;
    for (y = 1; y <= Ny; y++) {
        for (x = 1; x <= Nx; x++) {
            vneu[y][x] = (valt[y][x - 1] 
                        + valt[y][x + 1]
                        + valt[y - 1][x] 
                        + valt[y + 1][x]) * 0.25;
            d = vneu[y][x] - valt[y][x];
	    sum += d * d;
	}
    }

    *diff = 4.0 * sqrt(sum);
}

void jacobi9(field vneu, field valt, int Nx, int Ny, double *diff)
{
    int x, y;
    double d, sum;

    sum = 0;
    for (y = 1; y <= Ny; y++) {
        for (x = 1; x <= Nx; x++) {
            vneu[y][x] = 4.0 * (valt[y][x - 1] 
                              + valt[y][x + 1]
                              + valt[y - 1][x] 
                              + valt[y + 1][x])
	                      + valt[y - 1][x - 1]
                              + valt[y + 1][x - 1]
                              + valt[y - 1][x + 1]
		              + valt[y + 1][x + 1];
	    vneu[y][x] *= 0.05;
            d = vneu[y][x] - valt[y][x];
	    sum += d * d;
	}
    }

    *diff = 20.0 * sqrt(sum);
}
