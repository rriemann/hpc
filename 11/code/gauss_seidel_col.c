# include <math.h>
# include "laplace.h"

void gauss_seidel_col(field solution, 
                      int stencil, int Nx, int Ny, double eps, int max_iter, 
                      int *iterations, double *diff)
{
    int niter;

    // kann nicht parallelisiert werden, weil 
    // - spätere Schleifeniterationen von Daten abhängen, die bei früheren
    //   Iterationen erst berechnet werden müssen
    // - das if break eine parallelisierung nicht erlaubt
    // - gauss_...(...) ohnehin schon parallelisiert ist und eine weitere
    //   Verzweigung nicht möglich ist.
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
    double vold, d, sum, sum2;

    sum = 0;
    // - Äußerste for-Schleife reicht nur für 2 Threads
    // - Reihenfolge der Lese- und Schreibzugriffe von v[y][x] kann hier nicht
    //   vertauscht werden
    for (eo = 0; eo <= 1; eo++) {
        sum2 = 0;
        #pragma omp parallel for reduction(+:sum2) private(d,vold,x)
        for (y = 1; y <= Ny; y++) {
            for (x = 1; x <= Nx; x++) {
                if ((x + y) % 2 == eo) {
                    vold = v[y][x];
                    v[y][x] = (v[y][x - 1] 
                            + v[y][x + 1]
                            + v[y - 1][x] 
                            + v[y + 1][x]) * 0.25;
                    d = v[y][x] - vold;
                    sum2 += d * d;
                }
            }
        }
        sum += sum2;
    }

    *diff = 4.0 * sqrt(sum);
}

void gauss_seidel_col9(field v, int Nx, int Ny, double *diff)
{
    int x, y, col, colx, coly, colour[2][2];
    double vold, d, sum, sum2;

    colour[1][1] = 0;
    colour[0][0] = 1;
    colour[1][0] = 2;
    colour[0][1] = 3;

    sum = 0;
    // - Äußerste for-Schleife reicht nur für 4 Threads
    // - Reihenfolge der Lese- und Schreibzugriffe von v[y][x] kann hier nicht
    //   vertauscht werden
    for (col = 0; col <= 3; col++) {
        sum2 = 0;
        #pragma omp parallel for reduction(+:sum) private(d,vold,y,x,colx,coly)
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
                    sum2 += d * d;
                }
            }
        }
        sum += sum2;
    }

    *diff = 20.0 * sqrt(sum);
}
