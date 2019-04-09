#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	long long p = 131071;
	for (long long i = 1; i <= 100; i++) {
		string b = std::bitset<32>(p * i).to_string();

		cout << b << endl;
	}
}