#include "rsa.h"

struct rsa {
	
};

long long GCD(long long n, long long d, long long* i, long long* j) { 
	if (n < d) {
		long long a = n;
		n = d;
		d = a;
	}

	if(n%d == 0) {
		*i = 0;
		*j = 1;
		return d;
	} else {
		long long tM = GCD(d, n%d, i, j);
		long long tI = *i;
		*i = *j;
		*j = tI - (*j)*(n/d);

		return tM;
	}
}

long long powMod(long long n, long long e, long long m) {
	long long ret = n%m;
	while(e--) ret = ((ret*n)%m);
	return ret;
}

long long inverse(long long num, long long mod) {
	long long i, j;
	GCD(mod, num, &i, &j);

	long long o1 = (j+mod)%mod, o2 = (i+mod)%mod;
	return (o1*num)%mod == 1 ? o1 : o2;
}