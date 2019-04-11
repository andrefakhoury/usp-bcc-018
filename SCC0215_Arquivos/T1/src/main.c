#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "register.h"

void CSV_toBinary() {
	char fileName[256];
	scanf(" %s", fileName);

	FILE* fp = fopen(fileName, "r");
	FILE* outBin = fopen("arquivoTrab1.bin", "wb");

	if (fp == NULL || outBin == NULL) {
		printf("Falha no carregamento do arquivo.\n");
		return;
	}

	HeaderRegister hr;

	csv_loadHeader(&hr, fp);
	csv_printHeader(hr, outBin);

	DataRegister dr, *dataRegVec = NULL;
	int qttRegister = 0;

	size_t totalSize = 0;
	while(csv_readRegister(fp, &dr)) {
		qttRegister++;
		dataRegVec = realloc(dataRegVec, qttRegister * sizeof(DataRegister));
		dataRegVec[qttRegister - 1] = dr;

		size_t curSize = dr.tamanhoRegistro;
		if (totalSize + curSize > MAXPAGE) {
			dataRegVec[qttRegister - 2].tamanhoRegistro += MAXPAGE - totalSize;
			totalSize = 0;
		}

		totalSize += curSize;
	}

	for (int i = 0; i < qttRegister; i++) {
		csv_printRegister(dataRegVec[i], outBin);

		if (dataRegVec[i].tamanhoRegistro != register_size(dataRegVec[i]))
			printEmpty(dataRegVec[i].tamanhoRegistro - register_size(dataRegVec[i]), outBin);
	}

	printf("arquivoTrab1.bin");

	free(dataRegVec);
	fclose(fp);
	fclose(outBin);
}

void bin_toStream() {
	char fileName[256];
	scanf(" %s", fileName);

	FILE* bin = fopen(fileName, "rb");
	FILE* stream = stdout;

	if (bin == NULL || stream == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	HeaderRegister hr;
	bin_loadHeader(bin, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	fseek(bin, MAXPAGE, SEEK_SET);

	DataRegister dr;
	
	int numRegister = 0, numPaginas = 2; // header and last register
	while (bin_readRegister(bin, &dr, &numPaginas)) {
		numRegister++;
		register_toStream(dr);
	}

	if (numRegister == 0) {
		printf("Registro inexistente.\n");
	}
	else {
		printf("Número de páginas de disco acessadas: %d\n", numPaginas);
	}	
}

void bin_searchReg() {
	char fileName[256];
	char fieldName[256], fieldValue[2048];

	scanf(" %s", fileName);

	FILE* bin = fopen(fileName, "rb");
	FILE* stream = stdout;

	if (bin == NULL || stream == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	HeaderRegister hr;
	bin_loadHeader(bin, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	scanf(" %s", fieldName);
	char tag = '#';

	if (!strcmp(fieldName, "idServidor")) tag = hr.tagCampo1;
	else if (!strcmp(fieldName, "salarioServidor")) tag = hr.tagCampo2;
	else if (!strcmp(fieldName, "telefoneServidor")) tag = hr.tagCampo3;
	else if (!strcmp(fieldName, "nomeServidor")) tag = hr.tagCampo4;
	else if (!strcmp(fieldName, "cargoServidor")) tag = hr.tagCampo5;
	else return;

	fseek(bin, MAXPAGE, SEEK_SET);

	scanf(" %[^\n\r] ", fieldValue);

	DataRegister dr;
	int numRegister = 0, numPaginas = 2; // header and last register
	while (bin_readRegister(bin, &dr, &numPaginas)) {
		int check = register_check(tag, fieldValue, hr, dr);

		if (check) {
			register_printFormatted(dr, hr);
			numRegister++;
			if (tag == hr.tagCampo1) break;
		}
	}

	if (numRegister == 0) {
		printf("Registro inexistente.\n");
	}
	else {
		printf("Número de páginas de disco acessadas: %d\n", numPaginas);
	}
}

int main() {
	int op;
	scanf("%d", &op);

	if (op == 1)
		CSV_toBinary();
	else if (op == 2)
		bin_toStream();
	else if (op == 3)
		bin_searchReg();

	return 0;
}