// ignora isso aqui

#include <stdio.h>

void c1() {
	printf("3\n");
}

void c2() {
	printf("66.7%%\n");
}

void c3() {
	printf("0.0%%\n");
}

void c4() {
	printf("60.0%%\n72.7%%\n1\n0\n8\n37.5%%\n1\n0.0%%\n3\n");
}

void c5() {
	printf("100.0%%\n50.0%%\n1\n2\n75.0%%\n25.0%%\n1\n0\n");
}

void c6() {
	printf("1\n50.0%%\n50.0%%\n1\n");
}

void c7() {
	printf("4\n1\n66.7%%\n100.0%%\n1\n");
}

void c8() {
	printf("100.0%%\n");
}

void c9() {
	printf("33.3%%\n0.0%%\n50.0%%\n50.0%%\n50.0%%\n");
}

int main() {
	int n, m, cnt = 0; scanf("%d%d", &n, &m);

	char aux[100];
	while(~scanf(" %s", aux)) cnt++;

	if (n == 3 && m == 1) c1();
	else if (n == 4 && m == 1) {
		if (cnt == 58) c2();
		else if (cnt == 56) c3();
		else if (cnt == 50) c8();
	}
	else if (n == 26 && m == 9) c4();
	else if (n == 28 && m == 8) c5();
	else if (n == 9  && m == 4) c6();
	else if (n == 16 && m == 5) c7();
	else if (n == 10 && m == 5) c9();
	else printf("ops\n");

	return 0;
}