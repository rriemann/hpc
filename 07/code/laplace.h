typedef double **field;

field field_alloc(int ny, int nx); 
void field_free(field);

void die(char *msg);
void laplace(int Nx, int Ny, double eps);
void init(field v1, field v2, int Nx, int Ny);
void jacobi(field vneu, field valt, int Nx, int Ny);
void jacobi9(field vneu, field valt, int Nx, int Ny);
double diff(field v1, field v2, int Nx, int Ny);
void output(field v, int Nx, int Ny);
