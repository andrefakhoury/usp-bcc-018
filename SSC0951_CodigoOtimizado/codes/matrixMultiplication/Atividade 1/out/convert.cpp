#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL_PC
	#define debug(args...) cout.flush(); fflush(stdout); fprintf(stderr, args)
#else
	#define debug(args...) ; /*  */
#endif
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class num> inline void rd(num &x) {
	char c; while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
	x = (x << 3) + (x << 1) + c - '0';
	if (neg) x = -x;
}
template <class T, class... Args> inline void rd(T& x, Args&... args) { rd(x); rd(args...); }

const int MAXN = 2e5 + 5, INF = 0x3f3f3f3f;

inline void ign() {
	scanf(" %*[^\n\r]");
}

double get_time(char* s) {
	int n = strlen(s);

	string xx;
	for (int i = 0; i < n; i++) {
		if (s[i] == ',') xx += '.';
		else xx += s[i];
	}

	return stod(xx);
}

ll get_int(char* s) {
	int n = strlen(s);
	string xx;
	for (int i = 0; i < n; i++) {
		if (s[i] == '.') continue;
		xx += s[i];
	}
	return stoll(xx);
}

int main() {
	ign();
	char l1_l[100]; scanf(" %s", l1_l);
	ign();
	char l1_m[100]; scanf(" %s", l1_m);
	ign();
	char br_i[100]; scanf(" %s", br_i);
	ign();
	char br_m[100]; scanf(" %s", br_m);
	ign();
	char secs[100]; scanf(" %s", secs);
	ign();

	printf("%lld\n%lld\n%lld\n%lld\n%.9lf\n", get_int(l1_l), get_int(l1_m), get_int(br_i), get_int(br_m), get_time(secs));	
	return 0;
}