#include <stdio.h>
#include <stdbool.h>

//O(n**2)
void bruteForce(bool* isPrime, int n) {
	isPrime[0] = isPrime[1] = false;
	isPrime[2] = true;
	for (int i = 3; i < n; i++) {
		isPrime[i] = true;
		for (int j = 2; j < i; j++) {
			if (i%j == 0) {
				isPrime[i] = false;
				break;
			}
		}
	}
}

void crivoEratostenes(bool* notPrime, int n) {
	for (int i = 2; i <= )
}

int main() {
	int n = 50;
	bool* isPrime = (bool*) calloc(n, sizeof(bool));

}