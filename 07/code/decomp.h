typedef struct {

  int Nx, Ny;    /* global mesh size */
  int Lx, Ly;    /* local mesh size */
  
  int procs_x;   /* #processes in x-direction */
  int procs_y;   /* #processes in y-direction */
  int processes; /* total #processes */

  int coord_x;   /* x-coordinate of this process */ 
  int coord_y;   /* y-coordinate of this process */ 

  int my_rank;   /* rank of this process */ 
  int north;     /* rank of process neighbour in +y direction */ 
  int south;     /* rank of process neighbour in -y direction */ 
  int east;      /* rank of process neighbour in +x direction */ 
  int west;      /* rank of process neighbour in -x direction */
  int northwest;
  int northeast;
  int southwest;
  int southeast;

} Decomp;

void init_decomp(void);
void coord2rank(int coord_x, int coord_y, int *rank);
void rank2coord(int rank, int *coord_x, int *coord_y);
void global2local(int x_global, int y_global, int *x_local, int *y_local, int *home_of_xy);
void global2local_x(int x_global, int *x_local, int *coord_x);
void global2local_y(int y_global, int *y_local, int *coord_y);
void exchange_boundary(field v, int Lx, int Ly);
double global_sum(double local_sum);
void output_parallel(field v, int Nx, int Ny);
