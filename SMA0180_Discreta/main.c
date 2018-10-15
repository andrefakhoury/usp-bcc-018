#include <stdio.h>


int main() {
	long long p = 7529, q = 4481; //dois primos grandes
	long long n = p*q; //publico
	long long phi = (p-1)*(q-1); //secreto
	long long e = 293; //pertencente a Zphi tal que phi e e sao coprimos
	long long f = inverse(e, phi); //e^(-1) em Zphi

	return 0;
}