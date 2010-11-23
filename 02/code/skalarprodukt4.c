# include <stdio.h>
# include <stdlib.h>

double wall_time(void);
double skalar(double a[], double b[], int n, int step);
void empty(void);

int main(int argc, char *argv[])
{
    int i, j, n, r, step;
    double s, time, ttime, *a, *b;

    n = atoi(argv[1]);
    r = atoi(argv[2]);
    step = atoi(argv[3]);
    a = (double *) malloc(step * n * sizeof(double));
    b = (double *) malloc(step * n * sizeof(double));

    time = wall_time();
    time = wall_time();
    for (i = 0; i < r; i++)
        empty();
    ttime = wall_time() - time;

    for (i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 1.0 / (i + 1);
    }

    time = wall_time();
    for (j = 0; j < r; j++) {
        s = skalar(a, b, n, step);
    }
    time = wall_time() - time;

    printf("Skalarprodukt  : %f\n", s);
    printf("Laufzeit       : %f s\n", time);
    printf("Overhead       : %g s\n", ttime);
    printf("Zeit pro Wdhlg : %g s\n", time / r);
    printf("Overhead       : %g s\n", ttime / r);
//     printf("Rechenleistung : %6.1f MFlop/s\n", 2.0 * n * r * 1e-6 / (time - ttime));
    printf("Rechenleistung : %6.1f MFlop/s\n", 2.0 * n/step * r * 1e-6 / (time - ttime));

    free(a);
    free(b);
    return 0;
}
