double skalar(double a[], double b[], int n)
{
    int i;
    double s = 0;

    for (i = 0; i < n; i++) {
	s = s + a[i] * b[i];
    }

    return s;
}    
