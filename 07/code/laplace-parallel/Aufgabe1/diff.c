# include <math.h>
# include "laplace.h"
#include "decomp.h"
#include "mpi.h"

double global_sum(double localsum)
{
  double sum = 0;
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Allreduce( &localsum, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD );
  return sum;
}

double diff(field v1, field v2, int Nx, int Ny)
{
    int    x, y;
    double d, sum;

    sum = 0;
    for (y = 1; y <= Ny; y++)
        for (x = 1; x <= Nx; x++) {
            d = v1[y][x] - v2[y][x];
            sum += d * d;
        }

    sum = global_sum(sum);

    return sqrt(sum);
}
