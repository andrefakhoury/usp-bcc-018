#include <bits/stdc++.h>
using namespace std;

#define szPop 5					//maximum population size
#define mutRatio 1				//mutation ratio
#define INF 100000000000000LL	//infinite
#define SEASON 10				//season time
#define MAXPRICE 50				//maximum price

struct seed {
	double buyPrice;
	double sellPrice;
	int growTime;

	seed() {
		buyPrice = rand()%(MAXPRICE*100)/100.0;
		sellPrice = rand()%(MAXPRICE*100)/100.0;
		growTime = rand()%(SEASON-1)+1;
	}
};

struct player {
	double money;
	vector<seed> inventory;
};

void initializeSeeds(vector<seed>& seeds, int qtt) {
	for (int i = 0; i < qtt; i++) {
		seed s;
		seeds.push_back(s);
	}
}

int main() {
	srand(time(NULL));

	vector<player> players(szPop);
	vector<seed> seeds;

	initializeSeeds(seeds, 20);

	for (int i = 0; i < 20; i++) {
		printf("%.2lf %.2lf %d\n", seeds[i].buyPrice, seeds[i].sellPrice, seeds[i].growTime);
	}

	
	return 0;
}