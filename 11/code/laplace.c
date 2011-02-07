# include <stdio.h>
# include "laplace.h"

void laplace(char *datafile, int Nx, int Ny, double eps, Solver solver, int stencil)
{
    field solution = field_alloc(Ny, Nx);
    double idiff, rdiff;
    const int max_iter = 1000;
    int iterations;

    init(datafile, solution, Nx, Ny);

    solver(solution, stencil, Nx, Ny, eps, max_iter, &iterations, &idiff);

    if (iterations > max_iter) die("no convergence");

    residuum(datafile, solution, stencil, Nx, Ny, &rdiff);

    printf(" iterated residuum: %8.2e\n", idiff);
    printf(" real residuum:     %8.2e\n", rdiff);
    printf(" iterations:        %d\n\n", iterations);

    output(solution, Nx, Ny);

    field_free(solution);
}
