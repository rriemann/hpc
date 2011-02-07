# include <math.h>
# include "laplace.h"

void cg(field solution, 
        int stencil, int Nx, int Ny, double eps, int max_iter, 
        int *iterations, double *diff)
{
    field rhs = field_alloc(Ny, Nx);

    switch (stencil) {
	case 5:
	    cg_init5(solution, rhs, Nx, Ny);
            cg_kernel(cg_matrix_mult5, solution, rhs, Nx, Ny, eps, max_iter, 
                      iterations, diff);
            break;
	case 9:
	    cg_init9(solution, rhs, Nx, Ny);
            cg_kernel(cg_matrix_mult9, solution, rhs, Nx, Ny, eps, max_iter, 
                      iterations, diff);
            break;
	default:
	    die("unknown stencil");
	    break;
    }

    field_free(rhs);
}

void cg_init5(field solution, field rhs, int Nx, int Ny)
{
    int x, y;

    #pragma omp parallel for
    for (y = 0; y <= Ny + 1; y++) {
        for (x = 0; x <= Nx + 1; x++) {
            rhs[y][x] = solution[y][x];
	}
    }

    #pragma omp parallel for
    for (x = 1; x <= Nx; x++) {
        rhs[1][x] += rhs[0][x];
        rhs[Ny][x] += rhs[Ny + 1][x];
        solution[1][x] = rhs[1][x];
        solution[Ny][x] = rhs[Ny][x];
    }

    #pragma omp parallel for
    for (y = 1; y <= Ny; y++) {
        rhs[y][1] += rhs[y][0];
        rhs[y][Nx] += rhs[y][Nx + 1];
        solution[y][1] = rhs[y][1];
        solution[y][Nx] = rhs[y][Nx];
    }
}

void cg_init9(field solution, field rhs, int Nx, int Ny)
{
    int x, y;

    #pragma omp parallel for
    for (x = 1; x <= Nx; x++) {
	solution[1][x] = solution[1][x] + 4.0 * solution[0][x] 
                                              + solution[0][x - 1] 
                                              + solution[0][x + 1];
        solution[Ny][x] = solution[Ny][x] + 4.0 * solution[Ny + 1][x] 
                                                + solution[Ny + 1][x - 1] 
                                                + solution[Ny + 1][x + 1];
    }

    #pragma omp parallel for
    for (y = 1; y <= Ny; y++) {
	solution[y][1] = solution[y][1] + 4.0 * solution[y][0] 
                                              + solution[y - 1][0] 
                                              + solution[y + 1][0];
        solution[y][Nx] = solution[y][Nx] + 4.0 * solution[y][Nx + 1] 
                                                + solution[y - 1][Nx + 1] 
                                                + solution[y + 1][Nx + 1];
    }

    solution[1][1]  = solution[1][1] - solution[0][0];
    solution[Ny][1] = solution[Ny][1] - solution[Ny + 1][0];
    solution[1][Nx]  = solution[1][Nx] - solution[0][Nx + 1];
    solution[Ny][Nx] = solution[Ny][Nx] - solution[Ny + 1][Nx + 1];

    #pragma omp parallel for
    for (y = 0; y <= Ny + 1; y++) {
        for (x = 0; x <= Nx + 1; x++) {
            rhs[y][x] = solution[y][x];
	}
    }
}

void cg_matrix_mult5(field out, field in, int Nx, int Ny)
{
    int x, y;
    double a, b, c, d;

    for (y = 1; y <= Ny; y++) {
        for (x = 1; x <= Nx; x++) {
           if (x ==  1) a = 0;  else  a = in[y][x - 1];
           if (x == Nx) b = 0;  else  b = in[y][x + 1];
           if (y ==  1) c = 0;  else  c = in[y - 1][x];
           if (y == Ny) d = 0;  else  d = in[y + 1][x];

           out[y][x] = 4.0 * in[y][x] - a - b - c - d;
        }
    }
}      

void cg_matrix_mult9(field out, field in, int Nx, int Ny)
{
    int x, y;
    double n, s, e, w, ne, nw, se, sw;

    for (y = 1; y <= Ny; y++) {
        for (x = 1; x <= Nx; x++) {
	    n = in[y + 1][x];
	    s = in[y - 1][x];
	    e = in[y][x + 1];
	    w = in[y][x - 1];

	    ne = in[y + 1][x + 1];
	    nw = in[y + 1][x - 1];
	    se = in[y - 1][x + 1];
	    sw = in[y - 1][x - 1];


	    if (x ==  1) { w = 0; nw = 0; sw = 0; }
	    if (x == Nx) { e = 0; ne = 0; se = 0; }
	    if (y ==  1) { s = 0; se = 0; sw = 0; }
	    if (y == Ny) { n = 0; ne = 0; nw = 0; }

	    out[y][x] = 20.0 * in[y][x] - 4.0 * (n + s + e + w) - ne - nw - se - sw;
         }
    }
}      

void cg_kernel(MatrixMult matrix_mult, field x, field b, int Nx, int Ny, 
               double eps, int max_iter, int *iterations, double* diff)
{
    /* solves "matrix_mult * x = b" and returns number of iterations */

    field r = field_alloc(Ny, Nx);
    field p = field_alloc(Ny, Nx);
    field aap = field_alloc(Ny, Nx);
    double ak, bk, rtr, rtrold, paap;
    int i, j, niter;

    for (j = 0; j <= Ny + 1; j++) {
        for (i = 0; i <= Nx + 1; i++) {
            r[j][i] = 0;
            p[j][i] = 0;
            aap[j][i] = 0;
        }
    }

    matrix_mult(r, x, Nx, Ny);

    rtrold = 0;
    for (j = 1; j <= Ny; j++) {
        for (i = 1; i <= Nx; i++) {
            r[j][i] = b[j][i] - r[j][i];
            p[j][i] = r[j][i];
	    rtrold += r[j][i] * r[j][i];
        }
    }

    for (niter = 1; niter <= max_iter; niter++) {

        matrix_mult(aap, p, Nx, Ny);

        paap = 0;
        for (j = 1; j <= Ny; j++) {
            for (i = 1; i <= Nx; i++) {
	        paap += p[j][i] * aap[j][i];
            }
        }

        ak = rtrold / paap;

        rtr = 0;
        for (j = 1; j <= Ny; j++) {
            for (i = 1; i <= Nx; i++) {
                x[j][i] += ak * p[j][i];
                r[j][i] -= ak * aap[j][i];
                rtr += r[j][i] * r[j][i];
            }
	}

        if (rtr <= eps * eps) break;

        bk = rtr / rtrold;
        rtrold = rtr;

        for (j = 1; j <= Ny; j++) {
            for (i = 1; i <= Nx; i++) {
	        p[j][i] = bk * p[j][i] + r[j][i];
            }
        }

    }

    *iterations = niter;
    *diff = sqrt(rtr);

    field_free(r);
    field_free(p);
    field_free(aap);
}
