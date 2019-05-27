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

		if (fp != NULL)
			fclose(fp);
		if (outBin != NULL)
			fclose(outBin);

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
		fclose(bin);
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

/** Returns the tag of a field */
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
		fclose(bin);
		return;
	}

	// reads the field name and compare it to the header info
	scanf(" %s", fieldName);

	char tag = reg_getTag(hr, fieldName);
	if (tag == '#') { // invalid tag
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

/** Inserts a new RegOffset on the vector, keeping it sorted. Returns the position index of new RegOffset added */
int insertSorted(RegOffset** vec, int* n, RegOffset cur) {
	(*n)++;
	*vec = realloc(*vec, (*n) * sizeof(RegOffset));
	int i;

	// shift until find the correct position
	for (i = (*n) - 1; (*vec)[i-1].regSize >= cur.regSize; i--) {
		(*vec)[i] = (*vec)[i-1];
	}

	// update
	(*vec)[i] = cur;
	return i;
}

/** Function that calls the remotion of a data register, updating the byte offset vector */
void aux_remove(FILE* fp, DataRegister* dr, RegOffset** vecOffset, int* qttRemoved) {
	long backupOffset = ftell(fp);

	dr->removido = '*';

	RegOffset cur;
	cur.offset = ftell(fp) - dr->tamanhoRegistro; // gets the first byte offset of register
	cur.regSize = dr->tamanhoRegistro;

	int ind = insertSorted(vecOffset, qttRemoved, cur);

	// offset that it has to point - if current register is the largest, points to -1
	int64_t nextOffset = ind == (*qttRemoved) - 1 ? -1 : (*vecOffset)[ind+1].offset;

	// remove this register, updating the chaining offset
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
		fclose(fp);
		return;
	}

	/** Set status to 0 to alert something in case of program kill */
	fseek(fp, 0, SEEK_SET);
	char invalid = '0';
	fwrite(&invalid, 1, 1, fp);

	int qttRemoved = 0;
	RegOffset* vecOffset = NULL; // (sorted) vector that stores the offset of removed registers

	// initial charge to the offset vector
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

		str_removeQuotes(fieldValue, strlen(fieldValue)); // input can contain quotes

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
	
	free(vecOffset);

	/** Recover header status */
	fseek(fp, 0, SEEK_SET);
	invalid = '1';
	fwrite(&invalid, 1, 1, fp);

	fclose(fp);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileName);
}

/** Reads a string from stream on format "string to read" or NULO */
void std_scanString(char dest[]) {

	scanf(" %s", dest);
	if (!strcmp(dest, "NULO") || dest[0] != '\"') {
		return;
	}

	int cnt = 0; // qtt of quotes
	for (int i = 0; i < strlen(dest); i++) {
		cnt += dest[i] == '\"';
	}

	if (cnt == 2) {
		return; // open and close quotes are on string
	}
	
	char str[MAXSTR];
	scanf("%[^\"]\"", str);

	strcat(dest, str); // concatenate dest+str
}

/** Read register data from stdio */
DataRegister std_scanRegister() {
	DataRegister dr;

	// default info
	dr.removido = '-';
	dr.encadeamentoLista = -1;

	int ret;

	// scan id
	ret = scanf(" %d", &dr.idServidor);
	if (ret == 0) {
		scanf("%*s");
		dr.idServidor = -1;
	}

	// scan salario
	ret = scanf(" %lf", &dr.salarioServidor);
	if (ret == 0) {
		scanf(" %*s");
		dr.salarioServidor = -1;
	}

	// scan telefone
	scanf(" %16s ", dr.telefoneServidor);
	str_removeQuotes(dr.telefoneServidor, strlen(dr.telefoneServidor));
	if (!strcmp(dr.telefoneServidor, "NULO")) {
		str_fillEmpty(dr.telefoneServidor, 14, 1);
	}

	// scan nome
	std_scanString(dr.nomeServidor.desc);
	str_removeQuotes(dr.nomeServidor.desc, strlen(dr.nomeServidor.desc));
	if (!strcmp(dr.nomeServidor.desc, "NULO")) {
		dr.nomeServidor.size = 0;
		dr.nomeServidor.desc[0] = '\0';
	} else {
		dr.nomeServidor.size = strlen(dr.nomeServidor.desc) + 1;
	}
	dr.nomeServidor.tag = 'n';

	// scan cargo
	std_scanString(dr.cargoServidor.desc);
	if (!strcmp(dr.cargoServidor.desc, "NULO")) {
		dr.cargoServidor.size = 0;
		dr.cargoServidor.desc[0] = '\0';
	} else {
		str_removeQuotes(dr.cargoServidor.desc, strlen(dr.cargoServidor.desc));
		dr.cargoServidor.size = strlen(dr.cargoServidor.desc) + 1;
	}
	dr.cargoServidor.tag = 'c';

	// update the register size, according to info
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
		fclose(fp);
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
		fclose(fp);
		return;
	}

	/** Set status to 0 to alert something in case of program kill */
	fseek(fp, 0, SEEK_SET);
	char invalid = '0';
	fwrite(&invalid, 1, 1, fp);

	/** Executes the update N times */
	for (int i = 0; i < n; i++) {

		// Read info for the update
		char old_fieldName[MAXSTR], old_fieldValue[MAXSTR], new_fieldName[MAXSTR], new_fieldValue[MAXSTR];

		scanf(" %s", old_fieldName);
		std_scanString(old_fieldValue);
		str_removeQuotes(old_fieldValue, strlen(old_fieldValue));

		scanf("%s", new_fieldName);
		std_scanString(new_fieldValue);
		str_removeQuotes(new_fieldValue, strlen(new_fieldValue));

		char old_tag = reg_getTag(hr, old_fieldName);
		char new_tag = reg_getTag(hr, new_fieldName);

		// invalid field info
		if (old_tag == '#' || new_tag == '#') {
			printf("Falha no processamento do arquivo.\n");
			return;
		}

		// jump the first disk page (header)
		fseek(fp, MAXPAGE, SEEK_SET);

		DataRegister dr;
		long offset = ftell(fp); // offset to begin of register
		
		// reads all registers, and updated if needed
		while (bin_readRegister(fp, &dr)) {
			long backupOffset = ftell(fp);

			if (register_check(old_tag, old_fieldValue, hr, dr)) { // register has to be updated
				int delta, same = 0; // auxiliar variables
				DataRegister updated = dr;

				// update register according to desired tag
				reg_updateByTag(&updated, hr, new_tag, new_fieldValue, &delta, &same);
				if (same) continue; // same register, no need to update

				if (delta == 0) { // can be overwritten
					bin_overwriteRegister(fp, updated, offset, delta);
				} else { // remove and insert

					// Remove old register
					int qttRemoved = 0;
					RegOffset* vecOffset = NULL;
					bin_loadOffsetVector(fp, &vecOffset, &qttRemoved);

					fseek(fp, backupOffset, SEEK_SET);
					aux_remove(fp, &dr, &vecOffset, &qttRemoved);
					free(vecOffset);

					// Inserts new register
					bin_addRegister(fp, updated);
				}
			}
			
			// seeks to next register to read
			fseek(fp, backupOffset, SEEK_SET);
			offset = backupOffset;
		}
	}
	
	/** Recover header status */
	fseek(fp, 0, SEEK_SET);
	invalid = '1';
	fwrite(&invalid, 1, 1, fp);

	fclose(fp);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileName);
}

/** Comparator of 2 registers - cmp by idServidor */
int reg_cmp(const void* reg_1, const void* reg_2) {
	return ((DataRegister*)reg_1)->idServidor - ((DataRegister*)reg_2)->idServidor;
}

/** Store all registers from binary stream into a sorted register */
void reg_readAndSort(FILE* bin, DataRegister** dataRegVec, int* numRegister) {
	fseek(bin, MAXPAGE, SEEK_SET);

	DataRegister dr;
	*numRegister = 0;

	while (bin_readRegister(bin, &dr)) {
		if (dr.removido == '*')
			continue;

		dr.tamanhoRegistro = register_size(dr);

		(*numRegister)++;
		*dataRegVec = realloc(*dataRegVec, (*numRegister) * sizeof(DataRegister));
		(*dataRegVec)[(*numRegister)-1] = dr;
	}

	qsort(*dataRegVec, *numRegister, sizeof(DataRegister), reg_cmp);
}

/** Print the content of a DataRegister vector to a binary stream */
void printRegVec(FILE* bin, DataRegister* dataRegVec, int numRegister) {
	for (int i = 0; i < numRegister; i++) {
		int qttEmpty = 0;

		if (i != numRegister - 1) { // if there is element[i+1]
			long curPosition = ftell(bin) % MAXPAGE + dataRegVec[i].tamanhoRegistro;
			if (dataRegVec[i+1].tamanhoRegistro + curPosition > MAXPAGE) { // disk page will be full
				dataRegVec[i].tamanhoRegistro += MAXPAGE - curPosition;
				qttEmpty = MAXPAGE - curPosition;
			}
		}

		bin_printRegister(bin, dataRegVec[i]);

		if (qttEmpty != 0) { // fill empty spaces with '@'
			bin_printEmpty(bin, qttEmpty);
		}
	}
}

/** Store all non-removed registers from binary stream into a output binary stream */
void bin_sortRegisters() {
	char fileNameIn[MAXSTR], fileNameOut[MAXSTR];
	scanf(" %s %s", fileNameIn, fileNameOut);

	FILE* fpIn = fopen(fileNameIn, "rb");
	FILE* fpOut = fopen(fileNameOut, "wb");

	if (fpIn == NULL || fpOut == NULL) {
		printf("Falha no processamento do arquivo.\n");

		if (fpIn != NULL)
			fclose(fpIn);
		if (fpOut != NULL)
			fclose(fpOut);

		return;
	}

	HeaderRegister hr;
	bin_loadHeader(fpIn, &hr);

	// invalid status
	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn);
		fclose(fpOut);
		return;
	}

	// read registers to vector
	DataRegister *dataRegVec = NULL;
	int numRegister = 0;
	reg_readAndSort(fpIn, &dataRegVec, &numRegister);
	fclose(fpIn);

	// print header with invalid status
	hr.status = '0';
	hr.topoLista = -1;
	bin_printHeader(fpOut, hr);

	// print the sorted register
	printRegVec(fpOut, dataRegVec, numRegister);
	free(dataRegVec);
	
	/** Recover header status */
	fseek(fpOut, 0, SEEK_SET);
	char invalid = '1';
	fwrite(&invalid, 1, 1, fpOut);

	// prevent memory leaks
	fclose(fpOut);
	bin_printScreenClosed(fileNameOut);
}

/** Merge two different binary streams into a sorted binary output file */
void bin_mergeRegisters() {
	char fileNameIn1[MAXSTR], fileNameIn2[MAXSTR], fileNameOut[MAXSTR];

	scanf(" %s %s %s", fileNameIn1, fileNameIn2, fileNameOut);

	FILE* fpIn1 = fopen(fileNameIn1, "rb"); // first input file
	FILE* fpIn2 = fopen(fileNameIn2, "rb"); // second input file
	FILE* fpOut = fopen(fileNameOut, "wb"); // output file

	// invalid files
	if (fpIn1 == NULL || fpIn2 == NULL || fpOut == NULL) {
		printf("Falha no processamento do arquivo.\n");

		if (fpIn1 != NULL)
			fclose(fpIn1);
		if (fpIn2 != NULL)
			fclose(fpIn2);
		if (fpOut != NULL)
			fclose(fpOut);

		return;	
	}

	HeaderRegister hr;
	bin_loadHeader(fpIn2, &hr);

	// invalid status (on second file)
	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn1);
		fclose(fpIn2);
		fclose(fpOut);
		return;
	}

	bin_loadHeader(fpIn1, &hr);

	// invalid status (on first file)
	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn1);
		fclose(fpIn2);
		fclose(fpOut);
		return;
	}

	// read all the registers
	DataRegister *vec1 = NULL, *vec2 = NULL;
	int numReg1 = 0, numReg2 = 0;
	reg_readAndSort(fpIn1, &vec1, &numReg1);
	reg_readAndSort(fpIn2, &vec2, &numReg2);

	fclose(fpIn1);
	fclose(fpIn2);

	// output vector
	DataRegister *vecOut = NULL;
	int numRegisters = 0;

	hr.status = '0';
	hr.topoLista = -1;
	bin_printHeader(fpOut, hr);

	// merge elements to new vector
	for (int i = 0, j = 0; i < numReg1 || j < numReg2;) {
		if (j >= numReg2) {
			numRegisters++;
			vecOut = realloc(vecOut, numRegisters * sizeof(DataRegister));
			vecOut[numRegisters-1] = vec1[i];
			i++;
		} else if (i >= numReg1) {
			numRegisters++;
			vecOut = realloc(vecOut, numRegisters * sizeof(DataRegister));
			vecOut[numRegisters-1] = vec2[j];
			j++;
		} else {
			if (vec1[i].idServidor < vec2[j].idServidor) {
				numRegisters++;
				vecOut = realloc(vecOut, numRegisters * sizeof(DataRegister));
				vecOut[numRegisters-1] = vec1[i];
				i++;
			} else if (vec1[i].idServidor > vec2[j].idServidor) {
				numRegisters++;
				vecOut = realloc(vecOut, numRegisters * sizeof(DataRegister));
				vecOut[numRegisters-1] = vec2[j];
				j++;
			} else {
				numRegisters++;
				vecOut = realloc(vecOut, numRegisters * sizeof(DataRegister));
				vecOut[numRegisters-1] = vec1[i];
				i++, j++;
			}
		}
	}

	// print output registers
	printRegVec(fpOut, vecOut, numRegisters);

	/** Recover header status */
	fseek(fpOut, 0, SEEK_SET);
	char invalid = '1';
	fwrite(&invalid, 1, 1, fpOut);

	// prevent memory leaks
	fclose(fpOut);
	free(vecOut);
	free(vec1);
	free(vec2);

	bin_printScreenClosed(fileNameOut);
}

/** Merge two different binary streams into a sorted binary output file */
void bin_matchRegisters() {
	char fileNameIn1[MAXSTR], fileNameIn2[MAXSTR], fileNameOut[MAXSTR];

	scanf(" %s %s %s", fileNameIn1, fileNameIn2, fileNameOut);

	FILE* fpIn1 = fopen(fileNameIn1, "rb"); // first input file
	FILE* fpIn2 = fopen(fileNameIn2, "rb"); // second input file
	FILE* fpOut = fopen(fileNameOut, "wb"); // output file

	// invalid files
	if (fpIn1 == NULL || fpIn2 == NULL || fpOut == NULL) {
		printf("Falha no processamento do arquivo.\n");

		if (fpIn1 != NULL)
			fclose(fpIn1);
		if (fpIn2 != NULL)
			fclose(fpIn2);
		if (fpOut != NULL)
			fclose(fpOut);

		return;	
	}

	HeaderRegister hr;
	bin_loadHeader(fpIn2, &hr);

	// invalid status on second file
	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn1);
		fclose(fpIn2);
		fclose(fpOut);
		return;
	}

	bin_loadHeader(fpIn1, &hr);

	// invalid status on first file
	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn1);
		fclose(fpIn2);
		fclose(fpOut);
		return;
	}

	// read input registers to vectors
	DataRegister *vec1 = NULL, *vec2 = NULL;
	int numReg1 = 0, numReg2 = 0;
	reg_readAndSort(fpIn1, &vec1, &numReg1);
	reg_readAndSort(fpIn2, &vec2, &numReg2);

	fclose(fpIn1);
	fclose(fpIn2);

	// print (invalid) output header register
	hr.status = '0';
	hr.topoLista = -1;
	bin_printHeader(fpOut, hr);

	// output register
	DataRegister *vecOut = NULL;
	int numRegisters = 0;

	// fill output vector with matching of two input vectors
	for (int i = 0, j = 0; i < numReg1 && j < numReg2;) {
		while (i < numReg1 && j < numReg2 && vec1[i].idServidor < vec2[j].idServidor) {
			i++;
		}

		while (i < numReg1 && j < numReg2 && vec1[i].idServidor > vec2[j].idServidor) {
			j++;
		}

		if (vec1[i].idServidor == vec2[j].idServidor) {
			numRegisters++;
			vecOut = realloc(vecOut, numRegisters * sizeof(DataRegister));
			vecOut[numRegisters-1] = vec1[i];
			i++, j++;
		}
	}

	// print output vector
	printRegVec(fpOut, vecOut, numRegisters);

	/** Recover header status */
	fseek(fpOut, 0, SEEK_SET);
	char invalid = '1';
	fwrite(&invalid, 1, 1, fpOut);

	// prevent memory leaks
	fclose(fpOut);
	free(vec1);
	free(vec2);
	free(vecOut);

	bin_printScreenClosed(fileNameOut);
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
	} else if (op == 7) { // sort all binary registers
		bin_sortRegisters();
	} else if (op == 8) { // merge registers from two binary streams into another file
		bin_mergeRegisters();
	} else if (op == 9) { // match registers from two binary streams into another file
		bin_matchRegisters();
	}

	return 0;
}
