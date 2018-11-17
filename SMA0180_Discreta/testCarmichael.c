#include <stdio.h>
#include <stdbool.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

int gcd(int a, int b) {
	if (a%b == 0) return b;
	return gcd(b, a%b);
}

void extEuclidean(int n, int d, int* i, int* j) {
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

bool isCoPrime(int a, int b) {
	return gcd(max(a, b), min(a, b)) == 1;
}

int powerMod(int a, int b, int mod) {
	int ans = 1;
	for (int i = 0; i < b; i++)
		ans = (ans*a)%mod;
	return ans;
}

int calcInverseMod(int n, int mod) {
	int i, j;
	extEuclidean(n, mod, &i, &j);

	int k = 1;
	while ((j + k*mod)%mod < 0) k++;
	return (j + k*mod)%mod;
}

bool isPrime(int n) {
	for (int i = 2; i < n; i++) if (n%i == 0) return 0;
	return 1;
}

bool isPseudoPrime(int a, int mod) {
	return powerMod(a, mod-1, mod) == 1;
}

bool isCarmichael(int n) {
	if (isPrime(n)) return 0;

	for (int i = 2; i < n; i++)
		if (isCoPrime(i, n) && !isPseudoPrime(i, n)) return 0;
	return 1;
}

int RSA() {
	int p, q, e;
	int n = p*q;
	int phi = (p-1)*(q-1);

	int f = calcInverseMod(e, phi);
	
	int m = 100; //given value
	int c = powerMod(m, e, n); //encrypt
	int m = powerMod(c, f, n); //decrypt
}