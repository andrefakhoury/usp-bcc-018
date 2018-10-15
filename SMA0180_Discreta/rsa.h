#ifndef RSA_H
#define RSA_H

typedef struct rsa RSA;

long long GCD(long long n, long long d, long long* i, long long* j);
long long powMod(long long n, long long e, long long m);
long long inverse(long long num, long long mod);

#endif