void daxpy(double x[], double y[], int n, int step)
{
    int i;
    double n_max = n;
    for (i = 0; i < n_max; i+=step) {
	y[i] = 1.0134486542521 * x[i] + y[i];
    }
}
