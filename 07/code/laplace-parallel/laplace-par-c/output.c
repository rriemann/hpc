# include <stdio.h>
# include "laplace.h"

void output(field v, int Nx, int Ny)
{
    int x, y;

    for (y = Ny + 1; y >= 0; y--) {
        printf("%4i     ", y);
        for (x = 0; x <= Nx + 1; x++)
            printf("%9.5f", v[y][x]);
        printf("\n");
    }

    printf("   ^     \n");
    printf("   y  x >");
    for (x = 0; x <= Nx + 1; x++)
        printf("%6i   ", x);
    printf("\n");
}
