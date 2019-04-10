#include <stdio.h>
#include "register.h"

void CSV_toBinary() {
	char fileName[256];
	scanf(" %s", fileName);

	FILE* fp = fopen(fileName, "r");
	FILE* outBin = fopen("binario.bin", "wb");

	HeaderRegister hr;

	csv_loadHeader(&hr, fp);
	csv_printHeader(hr, outBin);

	DataRegister dr;

	size_t totalSize = 0;
	while(csv_readRegister(fp, &dr)) {
		size_t curSize = register_size(dr);

		if (totalSize + curSize > MAXPAGE) {
			printEmpty(MAXPAGE - totalSize, outBin);
			totalSize = 0;
		}

		totalSize += curSize;

		csv_printRegister(dr, outBin);
	}

	if (totalSize != 0) {
		printEmpty(MAXPAGE - totalSize, outBin);
	}

	fclose(fp);
	fclose(outBin);
}

int main() {
	int op;
	scanf("%d", &op);

	if (op == 1) CSV_toBinary();
	
	

	return 0;
}