#include <bits/stdc++.h>
using namespace std;

void euclides(int n, int d, int* i, int* j) {
	if (n%d == 0) {
		*j = 1;
		*i = 0;
	} else {
		euclides(d, n%d);
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
	while(--e) {
		a = (a*b)%mod;
	}
	return a;
}

int main(int argc, const char *argv[]){
	unsigned int m, c;
	int p = 65537;
	int q = 257;
	unsigned int n = p*q;
	unsigned int phi = (p-1)*(q-1);
	int e = 7;

	int aa, bb, cc; cin >> aa >> bb >> cc;
	cout << expo(aa, bb, cc) << endl;
	return 0;

	p = 11;
	q = 19;
	e = 5;
	phi = (p-1)*(q-1);
	n = 1241;
	cin >> m;
	c = expo(m, e, n);

	cout << "c = " << c << endl;
	int f = calcInverseMod(e, phi);
	cout << "f = " << f << endl;
	m = expo(c, f, n);
	cout << "m = " << m << endl;


	return 0;
}
