std::vector<double> startwerte;		// beide vektoren nach startwerte-eintraegen sortieren
std::vector<int> laengen;		// -> dann alle laengen[i] array-elemente mit den entsprechenden zahlen addieren

#pragma omp parallel for
for (i = 1; i <= N; i++) {
  int n_of_threads = omp_get_num_threads();
  a[i] += a[i-1];
}


// eine threadnummer kann mehrmals vorkommen? -> ja
// ->problem: nach welchem kriterium an welche vektor-stelle schreiben? globaler/shared counter einfuehren?

// wie sortiert man laengen mit startwerte mit? eigene funktion? map?