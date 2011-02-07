# include <math.h>
# include "laplace.h"

void gauss_seidel_col(field solution, 
                      int stencil, int Nx, int Ny, double eps, int max_iter, 
                      int *iterations, double *diff)
{
    int niter;

    for (niter = 1; niter <= max_iter; niter++) {

	switch (stencil) {
	    case 5:
		gauss_seidel_col5(solution, Nx, Ny, diff);
		break;
	    case 9:
		gauss_seidel_col9(solution, Nx, Ny, diff);
		break;
	    default:
		die("unknown stencil");
		break;
	}

	if (*diff < eps) break;
    }

    *iterations = niter;
}

void gauss_seidel_col5(field v, int Nx, int Ny, double *diff)
{
    int x, y, eo;
    double vold, d, sum;

    sum = 0;
    for (eo = 0; eo <= 1; eo++) {
    for (y = 1; y <= Ny; y++) {
        for (x = 1; x <= Nx; x++) {
	    if ((x + y) % 2 == eo) {
		vold = v[y][x];
		v[y][x] = (v[y][x - 1] 
			   + v[y][x + 1]
			   + v[y - 1][x] 
			   + v[y + 1][x]) * 0.25;
		d = v[y][x] - vold;
		sum += d * d;
	    }
	}
    }
    }

    *diff = 4.0 * sqrt(sum);
}

void gauss_seidel_col9(field v, int Nx, int Ny, double *diff)
{
    int x, y, col, colx, coly, colour[2][2];
    double vold, d, sum;

    colour[1][1] = 0;
    colour[0][0] = 1;
    colour[1][0] = 2;
    colour[0][1] = 3;

    sum = 0;
    for (col = 0; col <= 3; col++) {
    for (y = 1; y <= Ny; y++) {
	coly = y % 2;
        for (x = 1; x <= Nx; x++) {
            colx= x % 2;
	    if (colour[coly][colx] == col) {
		vold = v[y][x];
		v[y][x] = 4.0 * (v[y][x - 1] 
				 + v[y][x + 1]
				 + v[y - 1][x] 
				 + v[y + 1][x])
		                 + v[y - 1][x - 1]
		                 + v[y + 1][x - 1]
		                 + v[y - 1][x + 1]
		                 + v[y + 1][x + 1];
		v[y][x] *= 0.05; 
		d = v[y][x] - vold;
		sum += d * d;
	    }
	}
    }
    }

    *diff = 20.0 * sqrt(sum);
}
