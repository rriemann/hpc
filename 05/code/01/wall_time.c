# include <sys/time.h>

double wall_time(void)
{
    struct timeval val;
    struct timezone zone;

    gettimeofday(&val, &zone);

    return (double) val.tv_sec + (double) val.tv_usec * 1e-6;
}

double wall_time_(void)  /* for calls from Fortran */
{
    struct timeval val;
    struct timezone zone;

    gettimeofday(&val, &zone);

    return (double) val.tv_sec + (double) val.tv_usec * 1e-6;
}
