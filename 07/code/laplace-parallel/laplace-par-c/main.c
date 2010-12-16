# include <stdio.h>
# include "mpi.h"
# include "laplace.h"
# include "decomp.h"

extern Decomp decomp;

int main(int argc, char *argv[])
{
    double eps;
    FILE *para;

    MPI_Init(&argc, &argv);

    if (argc != 3) die("Usage: laplace procs_x procs_y");

    decomp.procs_x = atoi(argv[1]);
    decomp.procs_y = atoi(argv[2]);

    para = fopen("input.para", "r");

    fscanf(para, "%d %*s", &decomp.Nx);
    fscanf(para, "%d %*s", &decomp.Ny);
    fscanf(para, "%lg %*s", &eps);
  
    fclose(para);
    
    init_decomp();
    laplace(decomp.Lx, decomp.Ly, eps);
    MPI_Finalize();
}
