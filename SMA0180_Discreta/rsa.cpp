#include <bits/stdc++.h>
using namespace std;

void euclides(int n, int d, int* i, int* j) {
	if (n%d == 0) {
		*j = 1;
		*i = 0;
	} else {
		euclides(d, n%d, i, j);
		int ti = *i;
		*i = *j;
		*j = ti - (*j)*(n/d);
	}
}

int calcInverseMod(int n, int mod) {
	int i, j;
	euclides(mod, n, &i, &j);
	return (j + 23*mod)%mod;
}

unsigned int expo(unsigned int a, int e, int mod) {
	unsigned int b = a;
	while(--e) a = (a*b)%mod;
	return a;
}

int main(int argc, const char *argv[]) {
	unsigned int m, c, n, phi;
	int p, q, e, f;

	p = 11;
	q = 19;
	e = 5;

	phi = (p-1)*(q-1);
	n = p*q;

	cin >> m;

	c = expo(m, e, n); //m^e mod n
	f = calcInverseMod(e, phi); //e^(-1) mod phi
	m = expo(c, f, n); //c^f mod n

	cout << "[Encrypt] c = " << c << endl;
	cout << "[Inverse] f = " << f << endl;
	cout << "[Decrypt] m = " << m << endl;

	return 0;
}