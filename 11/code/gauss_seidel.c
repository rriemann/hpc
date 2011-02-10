# include <math.h>
# include "laplace.h"

void gauss_seidel(field solution, 
                  int stencil, int Nx, int Ny, double eps, int max_iter, 
                  int *iterations, double *diff)
{
    int niter;

    // nicht parallelisierbar, da break-Anweisungen ausgeführt werden müssten,
    // was nicht erlaubt ist
    for (niter = 1; niter <= max_iter; niter++) {

	switch (stencil) {
	    case 5:
		gauss_seidel5(solution, Nx, Ny, diff);
		break;
	    case 9:
		gauss_seidel9(solution, Nx, Ny, diff);
		break;
	    default:
		die("unknown stencil");
		break;
	}

	if (*diff < eps) break;
    }

    *iterations = niter;
}

void gauss_seidel5(field v, int Nx, int Ny, double *diff)
{
    int x, y;
    double vold, d, sum;

    sum = 0;
    // nicht praktikabel parallelisierbar, da die Reihenfolge der Ausführung
    // relevant ist. Nur mit sehr großem Aufwand ließe sich eine Parallelisierung
    // umsetzen
    for (y = 1; y <= Ny; y++) {
        // nicht parallelisierbar (siehe Argument für äußere Schleife)
        for (x = 1; x <= Nx; x++) {
            vold = v[y][x];
            v[y][x] = (v[y][x - 1] 
                     + v[y][x + 1]
                     + v[y - 1][x] 
                     + v[y + 1][x]) * 0.25;
            d = v[y][x] - vold;
	    sum += d * d;
	}
    }

    *diff = 4.0 * sqrt(sum);
}

void gauss_seidel9(field v, int Nx, int Ny, double *diff)
{
    int x, y;
    double vold, d, sum;

    sum = 0;
    // beide Schleifen nicht parallelisierbar, Argument: siehe gauss_seidel5
    for (y = 1; y <= Ny; y++) {
        for (x = 1; x <= Nx; x++) {
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

    *diff = 20.0 * sqrt(sum);
}
