# include <stdlib.h>
# include "laplace.h"

/* type "field" is a vector of pointers pointing to the "x-lines" of an
   ([0..ny+1]*[0..nx+1])-Matrix stored contiguously in memory
*/

field field_alloc(int ny, int nx)
{
    double **tmp; 
    int i;
  
    ny += 2;
    nx += 2;

    tmp = (double **) malloc(ny * sizeof(double *));
    tmp[0] = (double *) malloc(nx * ny * sizeof(double));

    for (i = 1; i < ny; i++)
        tmp[i] = tmp[i - 1] + nx;

    return tmp;
}

void field_free(field x)
{
    free(x[0]);
    free(x);
}
