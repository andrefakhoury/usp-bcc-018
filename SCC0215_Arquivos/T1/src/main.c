#include <stdio.h>
#include "register.h"

void CSV_toBinary() {
	char fileName[256];
	scanf(" %s", fileName);

	FILE* fp = fopen(fileName, "r");

	HeaderRegister hr;

	csv_loadHeader(&hr);
	csv_printHeader(hr, stdout);

	csv_ignoreLine(fp);

	DataRegister dr;

	size_t totalSize = 0;
	while(csv_readRegister(fp, &dr)) {
		size_t curSize = register_size(dr);

		if (totalSize + curSize > MAXPAGE) {
			printEmpty(MAXPAGE - totalSize, stdout);
			totalSize = 0;
		}

		totalSize += curSize;

		csv_printRegister(dr, stdout);
	}

	if (totalSize != 0) {
		printEmpty(MAXPAGE - totalSize, stdout);
	}

	fclose(fp);
}

int main() {
	int op;
	scanf("%d", &op);

	if (op == 1) CSV_toBinary();
	
	

	return 0;
}