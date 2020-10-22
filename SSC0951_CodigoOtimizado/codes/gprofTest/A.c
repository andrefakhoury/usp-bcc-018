#include <stdio.h>

int f11() {
	int i = 0;
	for (; i <= 0xFFFFF; i++);
}

int f02() {
	int i = 0;
	for (; i <= 0xFFFFFF; i++);
}

int f01() {
	int i = 0;
	for (; i <= 0xFFF; i++);
	f02();
}

int main() {
	f01();
	f11();
}