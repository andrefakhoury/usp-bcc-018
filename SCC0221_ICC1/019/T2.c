#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 32
#define max(a, b) a > b ? a : b

#define QTTGOOD 12
#define QTTBAD 12
#define QTTINV 3

typedef struct Word {
	char str[MAX];
	int qtt;
} Word;

typedef struct Product {
	char type[MAX], brand[MAX];
	Word bag[MAX];
	int qttOnBag;
} Product;

int findProduct(char type[], char brand[], Product prods[], int qtt) {
	int i;
	for (i = 0; i < qtt; i++) {
		if (!strcmp(type, prods[i].type) && !strcmp(brand, prods[i].brand))
			break;
	}
	return i;
}

int getQttOnBag(char word[], Product prod) {
	for (int i = 0; i < prod.qttOnBag; i++) {
		if (!strcmp(prod.bag[i].str, word)) {
			return prod.bag[i].qtt;
		}
	}

	return 0;
}

double getPercentage(char word[], Product prod) {
	int query = !strcmp(word, "negativos") ? 1 : 0;

	char positive[QTTGOOD][MAX] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char negative[QTTBAD][MAX] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	char inverse[QTTINV][MAX] = {"nao", "jamais", "nunca"};

	int qttPos = 0, qttNeg = 0;

	for (int i = 0; i < prod.qttOnBag; i++) {
		for (int j = 0; j < QTTGOOD; j++) {
			if (!strcmp(prod.bag[i].str, positive[j]))
				qttPos += prod.bag[i].qtt;
		}

		for (int j = 0; j < QTTBAD; j++) {
			if (!strcmp(prod.bag[i].str, negative[j]))
				qttNeg += prod.bag[i].qtt;
		}
	}

	double total = qttPos + qttNeg;
	return query ? (100 * qttNeg)/total : (100 * qttPos)/total;
}

void addOnBag(Word bag[], int* qtt, char str[]) {
	for (int i = 0; i < *qtt; i++) {
		if (!strcmp(bag[i].str, str)) {
			bag[i].qtt++;
			return;
		}
	}

	bag[*qtt].qtt = 1;
	strcpy(bag[*qtt].str, str);
	(*qtt)++;
}

void scanAndAdd(Product prods[], int* qttProd) {
	char aux_t[MAX], aux_b[MAX];
	scanf(" %s %s ; ", aux_t, aux_b);

	int ind = findProduct(aux_t, aux_b, prods, *qttProd);

	if (ind == *qttProd) {
		prods[ind].qttOnBag = 0;
		strcpy(prods[ind].type, aux_t);
		strcpy(prods[ind].brand, aux_b);

		(*qttProd)++;
	}

	char aux[MAX];
	while (scanf(" %s", aux), strcmp(aux, "Ø")) {
		addOnBag(prods[ind].bag, &(prods[ind].qttOnBag), aux);
	}
}

int main() {
	int n_prod, n_query;
	scanf("%d%d", &n_prod, &n_query);

	Product prods[MAX];
	int qttProd = 0;

	for (int i = 0; i < n_prod; i++) {
		scanAndAdd(prods, &qttProd);
	}

	for (int i = 0; i < n_query; i++) {

		char question[MAX], word[MAX], aux_t[MAX], aux_b[MAX];
		scanf(" %s %s %*s %s %s", question, word, aux_t, aux_b);
		int ind = findProduct(aux_t, aux_b, prods, qttProd);

		if (!strcmp(question, "palavra")) {
			printf("%d\n", getQttOnBag(word, prods[ind]));
		} else {
			printf("%.1f%%\n", getPercentage(word, prods[ind]));
		}

	}
}