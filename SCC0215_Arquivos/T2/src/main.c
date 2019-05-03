/**
 * Program that stores, recover, remove, add and update data from binary and csv files.
 * Andre Fakhoury, 4482145
 * USP - Sao Carlos, 2019
 **/

/** Including important libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "register.h"

#define MAXSTR 256

/** Reads data from CSV and print to a Binary File. */
void CSV_toBinary() {
	char fileName[MAXSTR];
	scanf(" %s", fileName);

	// fixed output filename
	char outFile[] = "arquivoTrab1.bin";

	FILE* fp = fopen(fileName, "r");
	FILE* outBin = fopen(outFile, "wb");

	// error on opening the files
	if (fp == NULL || outBin == NULL) {
		printf("Falha no carregamento do arquivo.\n");
		return;
	}

	HeaderRegister hr;

	csv_loadHeader(fp, &hr); // loads info from csv
	bin_printHeader(outBin, hr); // store info on binary

	DataRegister dr, *dataRegVec = NULL;
	int qttRegister = 0;

	// reads data registers from csv and stores it on a vector
	size_t totalSize = 0;
	while(csv_readRegister(fp, &dr)) {
		qttRegister++;
		dataRegVec = realloc(dataRegVec, qttRegister * sizeof(DataRegister));
		dataRegVec[qttRegister - 1] = dr;

		// end of a disk page
		size_t curSize = dr.tamanhoRegistro;
		if (totalSize + curSize > MAXPAGE) {
			dataRegVec[qttRegister - 2].tamanhoRegistro += MAXPAGE - totalSize;
			totalSize = 0;
		}

		totalSize += curSize;
	}

	// prints the data from the vector
	for (int i = 0; i < qttRegister; i++) {
		bin_printRegister(outBin, dataRegVec[i]);

		// end of a disk page, print empty characters to fill
		if (dataRegVec[i].tamanhoRegistro != register_size(dataRegVec[i]))
			bin_printEmpty(outBin, dataRegVec[i].tamanhoRegistro - register_size(dataRegVec[i]));
	}

	printf("%s", outFile);

	// free memory used
	free(dataRegVec);
	fclose(fp);
	fclose(outBin);
}

/** Reads data from binary source and prints to stdout */
void bin_toStream() {
	char fileName[MAXSTR];
	scanf(" %s", fileName);

	FILE* bin = fopen(fileName, "rb");
	FILE* stream = stdout;

	// error on opening files
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

	// jump the first page - only contains the header
	fseek(bin, MAXPAGE, SEEK_SET);

	DataRegister dr;
	
	// reads from binary and print on screen
	int numRegister = 0, numPaginas = 2; // header and last register
	while (bin_readRegister(bin, &dr, &numPaginas)) {
		numRegister++;
		register_toStream(dr);
	}

	if (numRegister == 0) { // no register found
		printf("Registro inexistente.\n");
	} else { // registers found, print disk pages accessed.
		printf("Número de páginas de disco acessadas: %d\n", numPaginas);
	}

	// free memory used
	fclose(bin);
}

/** Search for specific values and print them */
void bin_searchReg() {
	char fileName[MAXSTR]; // main file
	char fieldName[MAXSTR], fieldValue[2048]; // field and value to search for

	scanf(" %s", fileName);

	FILE* bin = fopen(fileName, "rb");
	FILE* stream = stdout;

	// error on opening the files
	if (bin == NULL || stream == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// loads header register and search for status info
	HeaderRegister hr;
	bin_loadHeader(bin, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// reads the field name and compare it to the header info
	scanf(" %s", fieldName);
	char tag = '#';

	if (!strcmp(fieldName, "idServidor")) {
		tag = hr.tagCampo1;
	} else if (!strcmp(fieldName, "salarioServidor")) {
		tag = hr.tagCampo2;
	} else if (!strcmp(fieldName, "telefoneServidor")) {
		tag = hr.tagCampo3;
	} else if (!strcmp(fieldName, "nomeServidor")) {
		tag = hr.tagCampo4;
	} else if (!strcmp(fieldName, "cargoServidor")) {
		tag = hr.tagCampo5;
	} else {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// jump the first disk page
	fseek(bin, MAXPAGE, SEEK_SET);

	// reads the value to find
	scanf(" %[^\n\r] ", fieldValue);

	// go through the registers from binary file
	DataRegister dr;
	int numRegister = 0, numPaginas = 2; // header and last register
	while (bin_readRegister(bin, &dr, &numPaginas)) {
		int check = register_check(tag, fieldValue, hr, dr);

		if (check) { // is the value we are looking for
			register_printFormatted(dr, hr);
			numRegister++;
			if (tag == hr.tagCampo1)  { // there is only one id
				break;
			}
		}
	}

	if (numRegister == 0) { // no registers found
		printf("Registro inexistente.\n");
	} else { // printing the number of disk pages accessed
		printf("Número de páginas de disco acessadas: %d\n", numPaginas);
	}
}

void bin_removeReg() {
	char fileName[MAXSTR];
	int n;

	scanf(" %s %d", fileName, &n);

	FILE* fp = fopen(fileName, "r+b");
	if (fp == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	HeaderRegister hr;
	csv_loadHeader(fp, &hr);

	if (hr.status == '1') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	for (int i = 0; i < n; i++) {
		char tag[MAXSTR], desc[MAXSTR];
		scanf(" %s %[^\n\r]", tag, desc);

	}
}

void bin_insertReg() {}
void bin_updateReg() {}

/** Main function to coordinate function calls according to input option */
int main() {
	int op;
	scanf("%d", &op);

	if (op == 1) { // read from csv and print to binary stream
		CSV_toBinary();
	} else if (op == 2) { // read from binary and print to screen
		bin_toStream();
	} else if (op == 3) { // search for specified values on binary, and print to screen
		bin_searchReg();
	} else if (op == 4) {
		bin_removeReg();
	} else if (op == 5) {
		bin_insertReg();
	} else if (op == 6) {
		bin_updateReg();
	}

	return 0;
}
