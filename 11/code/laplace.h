typedef double **field;

field field_alloc(int ny, int nx); 
void field_free(field);

typedef void Solver(field solution, 
                    int stencil, int Nx, int Ny, double eps, int max_iter, 
                    int *iterations, double *diff);

typedef void MatrixMult(field out, field in, int Nx, int Ny);

void die(char *msg);
void write_para(int solver, int stencil, double eps);
void laplace(char *datafile, int Nx, int Ny, double eps, Solver solver, int stencil);
void init(char *datafile, field v, int Nx, int Ny);

Solver jacobi;
void jacobi5(field vneu, field valt, int Nx, int Ny, double *diff);
void jacobi9(field vneu, field valt, int Nx, int Ny, double *diff);

Solver gauss_seidel;
void gauss_seidel5(field v, int Nx, int Ny, double *diff);
void gauss_seidel9(field v, int Nx, int Ny, double *diff);

Solver gauss_seidel_col;
void gauss_seidel_col5(field v, int Nx, int Ny, double *diff);
void gauss_seidel_col9(field v, int Nx, int Ny, double *diff);

Solver cg;
void cg_init5(field solution, field rhs, int Nx, int Ny);
void cg_init9(field solution, field rhs, int Nx, int Ny);
MatrixMult cg_matrix_mult5;
MatrixMult cg_matrix_mult9;
void cg_kernel(MatrixMult matrix_mult, field x, field b, int Nx, int Ny, 
               double eps, int max_iter, int *iterations, double* diff);

void residuum(char *datafile, field solution, int stencil, int Nx, int Ny, 
              double *diff);
void output(field v, int Nx, int Ny);
