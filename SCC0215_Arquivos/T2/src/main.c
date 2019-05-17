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

	/** Print header with status = 0 */
	csv_loadHeader(fp, &hr); // loads info from csv
	hr.status = '0';
	bin_printHeader(outBin, hr); // store info on binary

	DataRegister dr, *dataRegVec = NULL;
	int qttRegister = 0;

	int* endOfPage = NULL;

	// reads data registers from csv and stores it on a vector
	size_t totalSize = 0;
	while(csv_readRegister(fp, &dr)) {
		qttRegister++;
		dataRegVec = realloc(dataRegVec, qttRegister * sizeof(DataRegister));
		endOfPage  = realloc(endOfPage, qttRegister * sizeof(int));

		dataRegVec[qttRegister - 1] = dr;
		endOfPage[qttRegister - 1] = 0;

		// end of a disk page
		size_t curSize = dr.tamanhoRegistro;
		if (totalSize + curSize > MAXPAGE) {
			dataRegVec[qttRegister - 2].tamanhoRegistro += MAXPAGE - totalSize;
			endOfPage[qttRegister - 2] = 1;
			totalSize = 0;
		}

		totalSize += curSize;
	}

	// prints the data from the vector
	for (int i = 0; i < qttRegister; i++) {
		bin_printRegister(outBin, dataRegVec[i]);

		// end of a disk page, print empty characters to fill
		if (endOfPage[i] == 1)
			bin_printEmpty(outBin, dataRegVec[i].tamanhoRegistro - register_size(dataRegVec[i]));
	}

	printf("%s", outFile);

	/** Set status to 1 */
	fseek(outBin, 0, SEEK_SET);
	hr.status = '1';
	fwrite(&hr.status, 1, 1, outBin);

	// free memory used
	free(endOfPage);
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
	int numRegister = 0; // header and last register
	while (bin_readRegister(bin, &dr)) {
		if (dr.removido == '*')
			continue;

		numRegister++;
		register_toStream(dr);
	}

	if (numRegister == 0) { // no register found
		printf("Registro inexistente.\n");
	} else { // registers found, print disk pages accessed.
		int numPaginas = (ftell(bin) + MAXPAGE - 1) / MAXPAGE;
		printf("Número de páginas de disco acessadas: %d\n", numPaginas);
	}

	// free memory used
	fclose(bin);
}

char reg_getTag(HeaderRegister hr, char fieldName[]) {
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
	}

	return tag;
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

	char tag = reg_getTag(hr, fieldName);
	if (tag == '#') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// jump the first disk page
	fseek(bin, MAXPAGE, SEEK_SET);

	// reads the value to find
	scanf(" %[^\n\r] ", fieldValue);

	// go through the registers from binary file
	DataRegister dr;
	int numRegister = 0; // header and last register
	while (bin_readRegister(bin, &dr)) {
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
		int numPaginas = (ftell(bin) + MAXPAGE - 1) / MAXPAGE;
		printf("Número de páginas de disco acessadas: %d\n", numPaginas);
	}
}

/** Remove quotes from string */
void str_removeQuotes(char str[], size_t len) {
	if (str[0] == '\"') {
		for (int i = 1; i <= len; i++) {
			if (str[i] == '\"') {
				str[i-1] = '\0';
			} else {
				str[i-1] = str[i];
			}			
		}
		len--;
	}
}

int insertSorted(RegOffset** vec, int* n, RegOffset cur) {
	(*n)++;
	*vec = realloc(*vec, (*n) * sizeof(RegOffset));

	int i;
	for (i = (*n) - 1; (*vec)[i-1].regSize >= cur.regSize; i--) {
		(*vec)[i] = (*vec)[i-1];
	}
	(*vec)[i] = cur;
	return i;
}

/** Function that calls the remotion of a data register, updating the byte offset vector */
void aux_remove(FILE* fp, DataRegister* dr, RegOffset** vecOffset, int* qttRemoved) {
	long backupOffset = ftell(fp);

	dr->removido = '*';

	RegOffset cur;
	cur.offset = ftell(fp) - dr->tamanhoRegistro - 5;
	cur.regSize = dr->tamanhoRegistro;

	int ind = insertSorted(vecOffset, qttRemoved, cur);

	int64_t nextOffset = ind == (*qttRemoved) - 1 ? -1 : (*vecOffset)[ind+1].offset;

	bin_removeRegister(fp, *dr, (*vecOffset)[ind-1].offset, cur.offset, nextOffset);

	fseek(fp, backupOffset, SEEK_SET);
}

/** Remove registers from binary file */
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
	bin_loadHeader(fp, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	/** Set status to 0 to alert something in case of program kill */
	fseek(fp, 0, SEEK_SET);
	char invalid = '0';
	fwrite(&invalid, 1, 1, fp);

	int qttRemoved = 0;
	RegOffset* vecOffset = NULL;
	bin_loadOffsetVector(fp, &vecOffset, &qttRemoved);

	/** Executes the remotion N times */
	for (int i = 0; i < n; i++) {
		char fieldName[MAXSTR], fieldValue[MAXSTR];

		scanf(" %s %[^\n\r]", fieldName, fieldValue);
		char tag = reg_getTag(hr, fieldName);
		if (tag == '#') {
			printf("Falha no processamento do arquivo.\n");
			return;
		}

		str_removeQuotes(fieldValue, strlen(fieldValue));

		DataRegister dr;

		// jump the first disk page
		fseek(fp, MAXPAGE, SEEK_SET);

		/** Check each register, and removes if needed */
		while (bin_readRegister(fp, &dr)) {
			if (register_check(tag, fieldValue, hr, dr)) {
				aux_remove(fp, &dr, &vecOffset, &qttRemoved);
			}
		}
	}

	/** Recover header status */
	fseek(fp, 0, SEEK_SET);
	invalid = '1';
	fwrite(&invalid, 1, 1, fp);

	fclose(fp);

	free(vecOffset);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileName);
}

/** Reads a string, preventing the NULO case */
void std_scanString(char dest[]) {

	scanf(" %s", dest);
	if (!strcmp(dest, "NULO")) {
		return;
	}

	char str[MAXSTR];

	if (dest[0] != '\"') {
		return;
	} else {
		int cnt = 0;
		for (int i = 0; i < strlen(dest); i++)
			cnt += dest[i] == '\"';
		if (cnt == 2) return;
		
		scanf("%[^\"]\"", str);
	}

	strcat(dest, str);
}

/** Read register data from stdio */
DataRegister std_scanRegister() {
	DataRegister dr;
	dr.removido = '-';
	dr.encadeamentoLista = -1;

	int ret;

	ret = scanf(" %d", &dr.idServidor);
	if (ret == 0) {
		scanf("%*s");
		dr.idServidor = -1;
	}

	ret = scanf(" %lf", &dr.salarioServidor);
	if (ret == 0) {
		scanf(" %*s");
		dr.salarioServidor = -1;
	}

	scanf(" %16s ", dr.telefoneServidor);
	str_removeQuotes(dr.telefoneServidor, strlen(dr.telefoneServidor));
	if (!strcmp(dr.telefoneServidor, "NULO")) {
		str_fillEmpty(dr.telefoneServidor, 14, 1);
	}

	std_scanString(dr.nomeServidor.desc);
	str_removeQuotes(dr.nomeServidor.desc, strlen(dr.nomeServidor.desc));
	if (!strcmp(dr.nomeServidor.desc, "NULO")) {
		dr.nomeServidor.size = 0;
		dr.nomeServidor.desc[0] = '\0';
	} else {
		dr.nomeServidor.size = strlen(dr.nomeServidor.desc) + 1;
	}
	dr.nomeServidor.tag = 'n';

	std_scanString(dr.cargoServidor.desc);
	if (!strcmp(dr.cargoServidor.desc, "NULO")) {
		dr.cargoServidor.size = 0;
		dr.cargoServidor.desc[0] = '\0';
	} else {
		str_removeQuotes(dr.cargoServidor.desc, strlen(dr.cargoServidor.desc));
		dr.cargoServidor.size = strlen(dr.cargoServidor.desc) + 1;
	}
	dr.cargoServidor.tag = 'c';

	dr.tamanhoRegistro = register_size(dr);

	return dr;
}

/** Insert some registers to binary file */
void bin_insertReg() {
	char fileName[MAXSTR];
	int n;

	scanf(" %s %d", fileName, &n);

	FILE* fp = fopen(fileName, "r+b");
	if (fp == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	HeaderRegister hr;
	bin_loadHeader(fp, &hr);

	/** Invalid status */
	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	/** Set status to 0 to alert something in case of program kill */
	fseek(fp, 0, SEEK_SET);
	char invalid = '0';
	fwrite(&invalid, 1, 1, fp);

	/** Executes the insertion N times */
	for (int i = 0; i < n; i++) {
		bin_addRegister(fp, std_scanRegister());
	}

	/** Recover header status */
	fseek(fp, 0, SEEK_SET);
	invalid = '1';
	fwrite(&invalid, 1, 1, fp);

	fclose(fp);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileName);
}

/** Update some registers from binary file */
void bin_updateReg() {
	char fileName[MAXSTR];
	int n;

	scanf(" %s %d", fileName, &n);

	FILE* fp = fopen(fileName, "r+b");
	if (fp == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	HeaderRegister hr;
	bin_loadHeader(fp, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	/** Set status to 0 to alert something in case of program kill */
	fseek(fp, 0, SEEK_SET);
	char invalid = '0';
	fwrite(&invalid, 1, 1, fp);

	/** Executes the remotion N times */
	for (int i = 0; i < n; i++) {
		printf("------------------------------\n");
		char old_fieldName[MAXSTR], old_fieldValue[MAXSTR], new_fieldName[MAXSTR], new_fieldValue[MAXSTR];

		scanf(" %s", old_fieldName);
		std_scanString(old_fieldValue);
		str_removeQuotes(old_fieldValue, strlen(old_fieldValue));

		scanf("%s", new_fieldName);
		std_scanString(new_fieldValue);
		str_removeQuotes(new_fieldValue, strlen(new_fieldValue));

		char old_tag = reg_getTag(hr, old_fieldName);
		char new_tag = reg_getTag(hr, new_fieldName);

		if (old_tag == '#' || new_tag == '#') {
			printf("Falha no processamento do arquivo.\n");
			return;
		}

		// jump the first disk page
		fseek(fp, MAXPAGE, SEEK_SET);

		DataRegister dr;
		long offset;

		/** Check each register, and removes if needed */
		while (offset = ftell(fp), bin_readRegister(fp, &dr)) {
			long backupOffset = ftell(fp);

			if (register_check(old_tag, old_fieldValue, hr, dr)) {
				int delta;

				DataRegister updated = dr;

				int same = 0;
				reg_updateByTag(&updated, hr, new_tag, new_fieldValue, &delta, &same);

				if (same) continue;

				printf("Tamanho:: %d\n", dr.tamanhoRegistro);
				register_toStream(dr);
				// register_toStream(updated);

				int left;
				if (reg_canUpdate(dr, hr, new_tag, new_fieldValue, &left)) { // overwrite
					printf("Can overwrite :)\n");
					bin_overwriteRegister(fp, updated, offset, delta);
				} else { // remove and insert
					printf("Cannot overwrite :(\n");

					printf("Left: %d\n", left);
					
					updated.tamanhoRegistro += left;
					printf("%d -> %d [%d]\n", dr.tamanhoRegistro, updated.tamanhoRegistro, left);

					// printf("Tamanho registro: %d + %d = %d\n", dr.tamanhoRegistro, left, dr.tamanhoRegistro + left);
					// printf("(%d)\n---------\n", register_size(updated));

					int qttRemoved = 0;
					RegOffset* vecOffset = NULL;
					bin_loadOffsetVector(fp, &vecOffset, &qttRemoved);


					printf("Removed: %d\n", qttRemoved);
					for (int i = 0; i < qttRemoved; i++) {
						printf("%05ld\t%d\n", vecOffset[i].offset, vecOffset[i].regSize);
					}
					printf("----\n");

					printf("%d\n", dr.tamanhoRegistro);

					fseek(fp, backupOffset, SEEK_SET);
					aux_remove(fp, &dr, &vecOffset, &qttRemoved);

					printf("Removed: %d\n", qttRemoved);
					for (int i = 0; i < qttRemoved; i++) {
						printf("%05ld\t%d\n", vecOffset[i].offset, vecOffset[i].regSize);
					}
					printf("----\n");

					bin_addRegister(fp, updated);

					free(vecOffset);
				}
			}
			
			fseek(fp, backupOffset, SEEK_SET);
		}
	}

	/** Recover header status */
	fseek(fp, 0, SEEK_SET);
	invalid = '1';
	fwrite(&invalid, 1, 1, fp);

	fclose(fp);

	/** Print the file content to standard output stream */
	// bin_printScreenClosed(fileName);
}

/** Main function to manage function calls according to input option */
int main() {
	int op;
	scanf("%d", &op);

	if (op == 1) { // read from csv and print to binary stream
		CSV_toBinary();
	} else if (op == 2) { // read from binary and print to screen
		bin_toStream();
	} else if (op == 3) { // search for specified values on binary, and print to screen
		bin_searchReg();
	} else if (op == 4) { // search and remove specified registers on binary stream
		bin_removeReg();
	} else if (op == 5) { // add specified registers on binary stream
		bin_insertReg();
	} else if (op == 6) { // search and update specified registers on binary stream
		bin_updateReg();
	}

	return 0;
}
