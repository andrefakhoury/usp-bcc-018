#include <bits/stdc++.h>
using namespace std;

const set<string> stGood = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
const set<string> stBad = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
const set<string> stInv = {"nao", "jamais", "nunca"};

struct product {
	string str;
	map<string, int> bag;

	int qttGood, qttBad;
	product(string a) {
		str = a;
		qttGood = qttBad = 0;
	}
};

vector<product> prods;

int getInd(string p) {

	int id = 0;
	for (product prod : prods) {
		if (prod.str == p) return id;
		id++;
	}

	prods.emplace_back(p);
	return prods.size() - 1;
}

int main() {
	int n, q; cin >> n >> q;

	while (n--) {
		string s, t;
		cin >> s >> t;
		s += t;

		int ind = getInd(s);

		int good = 0, bad = 0, inv = 0;

		while (cin >> s) {
			if (s == "Ø") break;
			prods[ind].bag[s]++;

			if (inv) bad += stGood.count(s);
			else good += stGood.count(s);

			if (inv) good += stBad.count(s);
			else bad += stBad.count(s);

			if (stInv.count(s)) inv = 4;
			inv = max(inv - 1, 0);
		}

		if (good > bad) prods[ind].qttGood++;
		else prods[ind].qttBad++;
	}

	while (q--) {
		string a, b, c, d, e;
		cin >> a >> b >> e >> c >> d;
		c += d;
		
		int ind = getInd(c);

		if (a == "palavra") {
			cout << prods[ind].bag[b] << endl;
		} else {
			double ans;
			if (b == "negativos") {
				ans = 100.0 * (prods[ind].qttBad)/(prods[ind].qttBad + prods[ind].qttGood);
			} else {
				ans = 100.0 * (prods[ind].qttGood)/(prods[ind].qttBad + prods[ind].qttGood);
			}
			printf("%.1lf%%\n", ans);
		}
	}
}