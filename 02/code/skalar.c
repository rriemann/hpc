double skalar(double a[], double b[], int n, int step)
{
    int i;
    double s = 0;
    double n_max = n*step;
    for (i = 0; i < n_max; i+=step) {
	s = s + a[i] * b[i];
    }

    return s;
}
