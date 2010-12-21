# include <stdio.h>
# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

void laplace(int Nx, int Ny, double eps)
{
    field valt = field_alloc(Ny, Nx);
    field vneu = field_alloc(Ny, Nx);
    field tmp;
    const int max_iter = 1000;
    int iter;

    init(vneu, valt, Nx, Ny);

    for (iter = 1; iter <= max_iter; iter++) {
        tmp = vneu; 
        vneu = valt; 
        valt = tmp;
        jacobi(vneu, valt, Nx, Ny);
        /* jacobi9(vneu, valt, Nx, Ny); */
        if (diff(vneu, valt, Nx, Ny) < eps) break;
        exchange_boundary(vneu, Nx, Ny);
    }

    if (decomp.my_rank == 0) printf("#iterations: %i\n", iter);
    if (iter > max_iter) die("no convergence");

    output_parallel(vneu, Nx, Ny);

    field_free(valt);
    field_free(vneu);
}
