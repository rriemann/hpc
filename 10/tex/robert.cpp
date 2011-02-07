int length = sizeof(a)/sizeof(a[0]);           // Zahl der Elemente des Arrays a
int number_of_threads = omp_get_num_threads();
int piece_length = length/number_of_threads;   // Division mit Rest
#pragma omp parallel
{
  for (int i = 1+omp_get_thread_num()*piece_length; i <= (omp_get_thread_num()+1)*piece_length; ++i) {
    a[i] += a[i-1];
  }
}
for (int i = 1; i < number_of_threads; ++i) { // determine constants
  a[2*piece_length-1] += a[piece_lenght-1];
}
#pragma omp parallel
{
  if (omp_get_thread_num() == 0) { // wenn length/number_of_threads einen rest hat, berechne fehlende elemente
    for (int i = 1+number_of_threads*piece_length; i < length; ++i) {
      a[i] += a[i-1];
    }
  } else { // apply constants to all other elements
    int copy_from_index = omp_get_thread_num()*piece_length-1;
    for (int i = copy_from_index+1; i < (omp_get_thread_num()+1)*piece_length-1; ++i) {
      a[i] += a[copy_from_index];
    }
  }
}