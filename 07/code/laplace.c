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

//     int x,y;
//     int xx,yy;
//     rank2coord(decomp.my_rank,&xx,&yy);
//     for (x = 0; x < Nx+2; x++) {
//       for (y = 0; y < Ny+2; y++) {
//         vneu[y][x] =  (float)((xx*Nx)+x)/100.0;
//         vneu[y][x] += (float)((yy*Ny)+y)/10000.0;
//         valt[y][x] = vneu[y][x];
//       }
//     }
//     if (decomp.my_rank == 0) {
//       printf("nx, ny: %d %d\n",Nx,Ny);
//       printf("initialized with:\n");
//       output(vneu, Nx, Ny);
//     }
//     exchange_boundary(vneu, Nx, Ny);
//     MPI_Barrier(MPI_COMM_WORLD);
//     if (decomp.my_rank == 0) {
//       printf("ended up with:\n");
//       output(vneu, Nx, Ny);
//       die("jo");
//     }
//     MPI_Barrier(MPI_COMM_WORLD);

    for (iter = 1; iter <= max_iter; iter++) {
        tmp = vneu; 
        vneu = valt; 
        valt = tmp;
        /* jacobi(vneu, valt, Nx, Ny); */
        jacobi9(vneu, valt, Nx, Ny);
        if (diff(vneu, valt, Nx, Ny) < eps) break;
        exchange_boundary(vneu, Nx, Ny);
    }

    if (decomp.my_rank == 0) printf("#iterations: %i\n", iter);
    if (iter > max_iter) die("no convergence");

    output_parallel(vneu, Nx, Ny);

    field_free(valt);
    field_free(vneu);
}
