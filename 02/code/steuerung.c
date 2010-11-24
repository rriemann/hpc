# include <stdio.h>
# include <stdlib.h>

double wall_time(void);
void daxpy(double x[], double y[], int n, int step);
void empty(void);

int main(int argc, char *argv[])
{
    int i, j, n, r, step;
    double time, ttime, *x, *y;

    n = atoi(argv[1]);
    r = atoi(argv[2]);
    step = atoi(argv[3]);
    x = (double *) malloc(step * n * sizeof(double));
    y = (double *) malloc(step * n * sizeof(double));

    time = wall_time();
    time = wall_time();
    for (i = 0; i < r; i++)
        empty();
    ttime = wall_time() - time;

    for (i = 0; i < n; i++) {
        x[i] = i;
        y[i] = 1.0 / (i + 1);
    }

    time = wall_time();
    for (j = 0; j < r; j++) {
        daxpy(x, y, n, step);
    }
    time = wall_time() - time;

    printf("Laufzeit       : %f s\n", time);
    printf("Overhead       : %g s\n", ttime);
    printf("Zeit pro Wdhlg : %g s\n", time / r);
    printf("Overhead       : %g s\n", ttime / r);
//     printf("Rechenleistung : %6.1f MFlop/s\n", 2.0 * n * r * 1e-6 / (time - ttime));
    printf("Rechenleistung : %6.1f MFlop/s\n", 2.0 * (n/step+1) * r * 1e-6 / (time - ttime));

    free(x);
    free(y);
    return 0;
}
