# include <stdio.h>
# include "laplace.h"

int main(int argc, char *argv[])
{
    int    Nx, Ny;
    double eps;
    int    solver, stencil;
    char   datafile[] = "input.data";
    FILE  *para;
  
    if (argc != 3) die("Usage: laplace solver stencil");
 
    solver = atoi(argv[1]);
    stencil = atoi(argv[2]);

    para = fopen("input.para", "r");
    fscanf(para, "%d", &Nx);
    fscanf(para, "%d", &Ny);
    fscanf(para, "%lg", &eps);
    fclose(para);

    write_para(solver, stencil, eps);

    switch (solver) {
	case 0:
	    laplace(datafile, Nx, Ny, eps, jacobi, stencil);
	    break;
	case 1:
	    laplace(datafile, Nx, Ny, eps, gauss_seidel, stencil);
	    break;
	case 2:
	    laplace(datafile, Nx, Ny, eps, cg, stencil);
	    break;
	case 3:
	    laplace(datafile, Nx, Ny, eps, gauss_seidel_col, stencil);
	    break;
    }

    return 0;
}

void write_para(int solver, int stencil, double eps)
{
    puts(" Iterative solution of the Laplace equation");
    puts(" ------------------------------------------");

    switch (solver) {
	case 0:
	    printf(" solver:            %d (Jacobi)\n", solver);
	    break;
	case 1:
	    printf(" solver:            %d (Gauss-Seidel)\n", solver);
	    break;
	case 2:
	    printf(" solver:            %d (conjugate gradient)\n", solver);
	    break;
	case 3:
	    printf(" solver:            %d (Gauss-Seidel with checkerboard/colouring)\n", solver);
	    break;
        default:
            die("unknown solver");
            break;
    }

    printf(" stencil:           %d point\n", stencil);
    printf(" eps:               %8.2e\n", eps);
}
