# include <stdio.h>
# include "mpi.h"
# include "laplace.h"

void die(char *msg)
{
    fputs("laplace: error: ", stderr);
    fputs(msg, stderr);
    putc('\n', stderr);
    MPI_Abort(MPI_COMM_WORLD, 1);
}
