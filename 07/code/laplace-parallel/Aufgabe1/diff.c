# include <math.h>
# include "laplace.h"
# include "mpi.h"

// http://scv.bu.edu/~kadin/advanced-MPI/chapter1/chapter1.html
void gauss_sum(double *in, double *inout, int *len, MPI_Datatype *type) {
    int i;
    double sum = 0;    
    for(i = 0; i < *len; ++i) {
        sum += in[i] * in[i];
    }
    *inout += sum;
}
    
double diff(field v1, MPI_Op op)
{
    static double last_sum = -1;
    double sum, res;
    int len;
    
    len = sizeof(v1[0])/sizeof(double);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(v1[0], &sum, len, MPI_DOUBLE, op, MPI_COMM_WORLD);
    if(last_sum = -1) {
      res = sqrt(sum);
    } else {
      res = sqrt(fabs(sum - last_sum));
      last_sum = sum;
    }
    return res;    
}
