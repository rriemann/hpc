# include <math.h>
# include "laplace.h"

void residuum(char *datafile, field solution, int stencil, int Nx, int Ny, 
              double *diff)
{
    double sum, d, sum2; 
    int i, j;
    field rhs = field_alloc(Ny, Nx);
    field aax = field_alloc(Ny, Nx);

    init(datafile, aax, Nx, Ny);

    switch (stencil) {
	case 5:
	    cg_init5(aax, rhs, Nx, Ny);
	    cg_matrix_mult5(aax, solution, Nx, Ny);
	    break;
	case 9:
	    cg_init9(aax, rhs, Nx, Ny);
	    cg_matrix_mult9(aax, solution, Nx, Ny);
 	    break;
    }

    sum = 0;
    #pragma omp parallel for reduction(+:sum) private(i,d,sum2)
    for (j = 1; j <= Ny; j++) {
        sum2 = 0;
	for (i = 1; i <= Nx; i++) {
	    d = aax[j][i] - rhs[j][i];
	    sum2 += d * d;
	}
	sum += sum2;
    }

    *diff = sqrt(sum);

    field_free(rhs);
    field_free(aax);
}

