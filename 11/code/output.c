# include <stdio.h>
# include "laplace.h"

void output(field v, int Nx, int Ny)
{
    int x, y;

    // Ausgaben zu parallisieren macht keinen Sinn. Zeitintensiv ist hier das
    // printf, welches an sich nicht multithreadingfähig ist, da es bei IO
    // sonst zu Race-Conditions kommen könnte.
    for (y = Ny + 1; y >= 0; y--) {
        printf("%4i     ", y);
        for (x = 0; x <= Nx + 1; x++)
            printf("%9.5f", v[y][x]);
        printf("\n");
    }

    printf("   ^     \n");
    printf("   y  x >");
    // gleiches Argument wie oben
    for (x = 0; x <= Nx + 1; x++)
        printf("%6i   ", x);
    printf("\n");
}
