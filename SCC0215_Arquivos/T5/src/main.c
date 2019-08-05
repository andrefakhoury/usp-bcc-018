/**
 * Program that stores, recover, remove, add and update data from binary and csv files;
 * Merge, match and sort binary streams;
 * Index registers by predetermined field;
 * Use a B-Tree to quickly search and insert registers.
 * 
 * Andre Fakhoury, 4482145
 * Debora Buzon, 10851687
 * USP - Sao Carlos, 2019
 **/

/** Including important libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "register.h"
#include "index.h"
#include "btree.h"

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
	bin_setHeaderStatus(outBin, '1');

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
	int numRegister = 0, numPaginas = 2; // header and last register
	while (bin_readRegister(bin, &dr, &numPaginas)) {
		if (dr.removido == '*')
			continue;

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

/** Auxiliar search method: search for `fieldValue` (of `tag` field) on `bin` file, acessing `numPaginas` pages and fetching `numRegister` registers. */
void aux_search(FILE* bin, char* fieldValue, char tag, HeaderRegister hr, int* numPaginas, int* numRegister) {
	// jump the first disk page
	fseek(bin, MAXPAGE, SEEK_SET);
	
	// go through the registers from binary file
	DataRegister dr;
	while (bin_readRegister(bin, &dr, numPaginas)) {
		int check = register_check(tag, fieldValue, hr, dr);

		if (check) { // is the value we are looking for
			register_printFormatted(dr, hr);
			(*numRegister)++;
			if (tag == hr.tagCampo1)  { // there is only one id
				break;
			}
		}
	}
}

/** Search for specific values and print them. If `forcePrint`, forces the print of disk pages acessed. */
int bin_searchReg(char* fileNameAux, char* fieldNameAux, char* fieldValueAux, int forcePrint) {
	char fileName[MAXSTR]; // main file
	char fieldName[MAXSTR], fieldValue[2048]; // field and value to search for

	if (fileNameAux != NULL) { // fileName already set
		strcpy(fileName, fileNameAux);
	} else {
		scanf(" %s", fileName);
	}

	FILE* bin = fopen(fileName, "rb");
	FILE* stream = stdout;

	// error on opening the files
	if (bin == NULL || stream == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return 0;
	}

	// loads header register and search for status info
	HeaderRegister hr;
	bin_loadHeader(bin, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(bin);
		return 0;
	}

	// reads the field name and compare it to the header info
	if (fieldNameAux != NULL) { // already given
		strcpy(fieldName, fieldNameAux);
	} else {
		scanf(" %s", fieldName);
	}

	char tag = reg_getTag(hr, fieldName);
	if (tag == '#') { // invalid tag
		printf("Falha no processamento do arquivo.\n");
		fclose(bin);
		return 0;
	}

	// reads the value to find - if necessary
	if (fieldValue != NULL) {
		strcpy(fieldValue, fieldValueAux);
	} else {
		scanf(" %[^\n\r] ", fieldValue);
	}

	int numRegister = 0, numPaginas = 1; // number of registers found and acessed disk pages

	// calls auxiliar search procedure
	aux_search(bin, fieldValue, tag, hr, &numPaginas, &numRegister);	

	int ret = 0; // return value

	if (numRegister == 0) { // no registers found
		printf("Registro inexistente.\n");
		ret = -1;
	}
	
	if (forcePrint || ret == 0) { // printing the number of disk pages accessed
		printf("Número de páginas de disco acessadas: %d\n", numPaginas);
		ret = numPaginas;
	}

	return ret;
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
	bin_setHeaderStatus(fp, '0');

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
			fclose(fp);
			free(vecOffset);
			return;
		}

		str_removeQuotes(fieldValue, strlen(fieldValue)); // input can contain quotes

		DataRegister dr;

		// jump the first disk page
		fseek(fp, MAXPAGE, SEEK_SET);

		/** Check each register, and removes if needed */
		while (bin_readRegister(fp, &dr, NULL)) {
			if (register_check(tag, fieldValue, hr, dr)) {
				aux_remove(fp, &dr, &vecOffset, &qttRemoved);
			}
		}
	}
	
	/** Recover header status */
	bin_setHeaderStatus(fp, '1');

	free(vecOffset);

	fclose(fp);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileName);

	return;
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
	bin_setHeaderStatus(fp, '0');

	/** Executes the insertion N times */
	for (int i = 0; i < n; i++) {
		bin_addRegister(fp, std_scanRegister());
	}

	/** Recover header status */
	bin_setHeaderStatus(fp, '1');

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
	bin_setHeaderStatus(fp, '0');

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
			fclose(fp);
			return;
		}

		// jump the first disk page (header)
		fseek(fp, MAXPAGE, SEEK_SET);

		DataRegister dr;
		long offset = ftell(fp); // offset to begin of register
		
		// reads all registers, and updated if needed
		while (bin_readRegister(fp, &dr, NULL)) {
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
	bin_setHeaderStatus(fp, '1');

	fclose(fp);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileName);
}

/** Store all registers from binary stream into a sorted register */
void reg_readAndSort(FILE* bin, DataRegister** dataRegVec, int* numRegister, int (*checkRegister)(DataRegister), int (*compareRegister)(const void*, const void*)) {
	fseek(bin, MAXPAGE, SEEK_SET);

	DataRegister dr;
	*numRegister = 0;

	while (bin_readRegister(bin, &dr, NULL)) {
		if (!checkRegister(dr))
			continue;

		dr.tamanhoRegistro = register_size(dr);

		(*numRegister)++;
		*dataRegVec = realloc(*dataRegVec, (*numRegister) * sizeof(DataRegister));
		(*dataRegVec)[(*numRegister)-1] = dr;
	}

	qsort(*dataRegVec, *numRegister, sizeof(DataRegister), compareRegister);
}

/** Print the content of a DataRegister vector to a binary stream */
void reg_printRegVec(FILE* bin, DataRegister* dataRegVec, int numRegister) {
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

/** Checks if `dr` is not removed */
int checkNotRemovedRegister(DataRegister dr) {
	return dr.removido != '*';
}

/** Comparator of 2 registers by idServidor */
int reg_cmpId(const void* reg_1, const void* reg_2) {
	return ((DataRegister*)reg_1)->idServidor - ((DataRegister*)reg_2)->idServidor;
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
	reg_readAndSort(fpIn, &dataRegVec, &numRegister, checkNotRemovedRegister, reg_cmpId);
	fclose(fpIn);

	// print header with invalid status
	hr.status = '0';
	hr.topoLista = -1;
	bin_printHeader(fpOut, hr);

	// print the sorted register
	reg_printRegVec(fpOut, dataRegVec, numRegister);
	free(dataRegVec);
	
	/** Recover header status */
	bin_setHeaderStatus(fpOut, '1');

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
	reg_readAndSort(fpIn1, &vec1, &numReg1, checkNotRemovedRegister, reg_cmpId);
	reg_readAndSort(fpIn2, &vec2, &numReg2, checkNotRemovedRegister, reg_cmpId);

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
	reg_printRegVec(fpOut, vecOut, numRegisters);

	/** Recover header status */
	bin_setHeaderStatus(fpOut, '1');

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
	reg_readAndSort(fpIn1, &vec1, &numReg1, checkNotRemovedRegister, reg_cmpId);
	reg_readAndSort(fpIn2, &vec2, &numReg2, checkNotRemovedRegister, reg_cmpId);

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
	reg_printRegVec(fpOut, vecOut, numRegisters);

	/** Recover header status */
	bin_setHeaderStatus(fpOut, '1');

	// prevent memory leaks
	fclose(fpOut);
	free(vec1);
	free(vec2);
	free(vecOut);

	bin_printScreenClosed(fileNameOut);
}

/** Checks if `dr` is not removed and `nomeServidor` is not null */
int checkNameRegister(DataRegister dr) {
	return dr.removido != '*' && dr.nomeServidor.size > 0;
}

/** Comparator of 2 registers by nomeServidor */
int reg_cmpName(const void* reg_1, const void* reg_2) {
	DataIndex dr1 = *(DataIndex*)reg_1;
	DataIndex dr2 = *(DataIndex*)reg_2;

	int cmp = strcmp(dr1.chaveBusca, dr2.chaveBusca);
	if (cmp == 0) { // strings are equal, sort by byteoffset
		return dr1.byteOffset - dr2.byteOffset;
	} else {
		return cmp;
	}
}

/** Store all registers from binary stream into a sorted index register */
void reg_readAndSortIndex(FILE* bin, DataIndex** dataIndexVec, int* numRegister, int (*checkRegister)(DataRegister), int (*compareRegister)(const void*, const void*)) {
	fseek(bin, MAXPAGE, SEEK_SET);

	DataRegister dr;
	*numRegister = 0;

	int64_t offset = ftell(bin); // stores offset of next register

	while (bin_readRegister(bin, &dr, NULL)) {
		if (!checkRegister(dr)) { // invalid register
			offset = ftell(bin);
			continue;
		}

		// add register to vector
		(*numRegister)++;
		*dataIndexVec = realloc(*dataIndexVec, (*numRegister) * sizeof(DataIndex));
		
		(*dataIndexVec)[(*numRegister)-1].byteOffset = offset;
		strcpy((*dataIndexVec)[(*numRegister)-1].chaveBusca, dr.nomeServidor.desc);
		str_fillEmpty((*dataIndexVec)[(*numRegister)-1].chaveBusca, MAXINDEXSTR, 0);

		// update offset
		offset = ftell(bin);
	}

	// sort values
	qsort(*dataIndexVec, *numRegister, sizeof(DataIndex), compareRegister);
}

/** Print data from a index vector to desired binary stream */
void index_printRegVecIndex(FILE* bin, DataIndex* dataIndexVec, int numRegister) {
	for (int i = 0; i < numRegister; i++) {
		index_printRegister(bin, dataIndexVec[i]);
	}
}

/** Create a Index File based on a input file */
void bin_createIndexReg() {
	char fileNameIn[MAXSTR], fileNameIndex[MAXSTR];
	scanf(" %s %s", fileNameIn, fileNameIndex);

	FILE* fpIn = fopen(fileNameIn, "rb");
	if (fpIn == NULL) { // invalid file
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	FILE* fpIndex = fopen(fileNameIndex, "wb");
	if (fpIndex == NULL) { // invalid index file
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn);
		return;
	}

	// set index status to invalid
	HeaderIndex hi;
	hi.status = '0';
	hi.nroRegistros = 0;
	index_printHeader(fpIndex, hi);

	HeaderRegister hr;
	bin_loadHeader(fpIn, &hr);

	// invalid status on file
	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn);
		fclose(fpIndex);
		return;
	}

	// read input registers to vector
	DataIndex *vecIn = NULL;
	int numRegister = 0;
	reg_readAndSortIndex(fpIn, &vecIn, &numRegister, checkNameRegister, reg_cmpName);
	fclose(fpIn);

	// print everything to binary stream
	index_printRegVecIndex(fpIndex, vecIn, numRegister);
	free(vecIn);

	// recover status
	hi.status = '1';
	hi.nroRegistros = numRegister;
	index_updateHeader(fpIndex, hi);

	fclose(fpIndex);

	bin_printScreenClosed(fileNameIndex);
}

/** Search for registers after find byteOffset on index file. If `forcePrint`, forces the print of disk pages acessed. */
int bin_searchBasedOnIndex(char* fileNameAux, char* fileNameIndexAux, char* fieldNameAux, char* fieldValueAux, int forcePrint) {
	char fileName[MAXSTR], fileNameIndex[MAXSTR], fieldName[MAXSTR], fieldValue[MAXSTR];

	// string already given
	if (fileNameAux != NULL) {
		strcpy(fileName, fileNameAux);
	} else {
		scanf(" %s", fileName);
	}

	// string already given
	if (fileNameIndexAux != NULL) {
		strcpy(fileNameIndex, fileNameIndexAux);
	} else {
		scanf(" %s", fileNameIndex);
	}

	// string already given
	if (fieldNameAux != NULL) {
		strcpy(fieldName, fieldNameAux);
	} else {
		scanf(" %s", fieldName);
	}

	// string already given
	if (fieldValueAux != NULL) {
		strcpy(fieldValue, fieldValueAux);
	} else {
		scanf(" %[^\n\r]", fieldValue);
	}

	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) { // invalid file
		printf("Falha no processamento do arquivo.\n");
		return 0;
	}

	FILE* fpIndex = fopen(fileNameIndex, "rb");
	if (fpIndex == NULL) { // invalid index file
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		return 0;
	}

	HeaderIndex hi;
	index_loadHeader(fpIndex, &hi);

	if (hi.status == '0') { // invalid index status
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		fclose(fpIndex);
		return 0;
	}

	HeaderRegister hr;
	bin_loadHeader(fp, &hr);

	if (hr.status == '0') { // invalid status
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		fclose(fpIndex);
		return 0;
	}

	char tag = reg_getTag(hr, fieldName);

	if (tag == '#') { // invalid tag given
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		fclose(fpIndex);
		return 0;
	}

	int numPaginas = 1, numPaginasIndex = 1; // number of acessed diskpages
	int numRegister = 0; // number of different registers found
	int64_t *registerPositions = NULL; // vector of all offsets
	DataIndex di;
	
	// read from index file and compares to desired value
	while(index_readRegister(fpIndex, &di, &numPaginasIndex)) {
		if (!strcmp(di.chaveBusca, fieldValue)) {
			numRegister++;
			registerPositions = realloc(registerPositions, numRegister * sizeof(int64_t));
			registerPositions[numRegister-1] = di.byteOffset;
		}
	}

	fclose(fpIndex);

	int lastDiskPage = -1; // last disk page acessed - used to find qtt of disk pages

	// print registers based on byteoffset found on index file
	for (int i = 0; i < numRegister; i++) {
		int curDiskPage = (registerPositions[i] + MAXPAGE - 1) / MAXPAGE;
		numPaginas += curDiskPage != lastDiskPage;

		fseek(fp, registerPositions[i], SEEK_SET);
		DataRegister dr;
		bin_readRegister(fp, &dr, NULL);
		register_printFormatted(dr, hr);

		lastDiskPage = curDiskPage;
	}

	free(registerPositions);

	int ret = 0; // auxiliar variable to set return value

	if (numRegister == 0) { // no registers found
		printf("Registro inexistente.\n");
		ret = -1;
	}

	if (forcePrint || ret == 0) { // print number of disk accesses
		printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", numPaginasIndex);
		printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", numPaginas);

		ret = numPaginas;
	}

	fclose(fp);
	return ret;
}

/** Remove register by its byte offset */
void reg_removeByOffset(FILE* fp, int64_t offset, RegOffset** vecOffset, int* qttRemoved) {
	DataRegister dr;

	// jump to the offset
	fseek(fp, offset, SEEK_SET);

	// read register
	bin_readRegister(fp, &dr, NULL);

	// remove element
	aux_remove(fp, &dr, vecOffset, qttRemoved);
}

/** Gets interval [i, j) where value given is equal to vector range. */
void index_binarySearch(DataIndex* vecIndex, int n, char* value, int* i, int* j) {
	// basic binary search algorithm
	int lo = 0, hi = n-1;
	while (lo < hi) {
		int mi = (lo + hi) / 2;
		if (strcmp(value, vecIndex[mi].chaveBusca) <= 0) {
			hi = mi;
		} else {
			lo = mi + 1;
		}
	}

	// register not found
	if (strcmp(value, vecIndex[hi].chaveBusca) != 0) {
		*i = *j = -1;
		return;
	}

	// go through all the registers less than j, but equal to value
	*i = *j = hi;
	while (*i > -1 && !strcmp(value, vecIndex[*i].chaveBusca)) {
		*i -= 1;
	}

	// adjust the interval [i, j)
	*i += 1;
	*j += 1;
}

/** Erase positions [l, l+qtt] from vector */
void index_eraseVector(DataIndex** vec, int* n, int l, int qtt) {
	for (int i = 0; i < qtt; i++) {
		for (int j = l; j < (*n) - 1; j++) {
			(*vec)[j] = (*vec)[j+1];
		}

		*n -= 1;
	}

	*vec = realloc(*vec, (*n) * sizeof(DataIndex));
}

/** Push element to vector */
void index_pushVector(DataIndex** vec, int* n, DataIndex di) {
	(*n)++;
	*vec = realloc(*vec, sizeof(DataIndex) * (*n));
	(*vec)[(*n)-1] = di;
	qsort(*vec, *n, sizeof(DataIndex), reg_cmpName);
}

/** Remove specified registers on binary stream, and update the index file */
void bin_removeRegUpdateIndex() {
	char fileName[MAXSTR], fileNameIndex[MAXSTR];
	int n; // qtt of remotions
	scanf(" %s %s %d", fileName, fileNameIndex, &n);

	// check if file is valid
	FILE* fp = fopen(fileName, "r+b");
	if (fp == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// check if index is valid
	FILE* fpIndex = fopen(fileNameIndex, "rb");
	if (fpIndex == NULL) {
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		return;
	}

	// loads header register
	HeaderRegister hr;
	bin_loadHeader(fp, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		fclose(fpIndex);
		return;
	}

	// loads index header
	HeaderIndex hi;
	index_loadHeader(fpIndex, &hi);
	if (hi.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		fclose(fpIndex);
		return;		
	}

	// load all index data to RAM
	DataIndex *indexVector = NULL;
	int qttIndex = 0;
	index_readIndexToVector(fpIndex, &indexVector, &qttIndex);

	// reopen index file to write mode
	fclose(fpIndex);
	fpIndex = fopen(fileNameIndex, "wb");

	// Set data status to 0 to alert something in case of program kill
	bin_setHeaderStatus(fp, '0');

	RegOffset* vecOffset = NULL; // (sorted) vector that stores the offset of removed registers
	int qttRemoved = 0;

	// initial charge to the offset vector
	bin_loadOffsetVector(fp, &vecOffset, &qttRemoved);

	/** Executes the remotion N times */
	for (int i = 0; i < n; i++) {
		char fieldName[MAXSTR], fieldValue[MAXSTR];

		scanf(" %s %[^\n\r]", fieldName, fieldValue);
		char tag = reg_getTag(hr, fieldName);
		if (tag == '#') {
			printf("Falha no processamento do arquivo.\n");

			free(vecOffset);
			free(indexVector);
			fclose(fp);
			fclose(fpIndex);

			return;
		}

		str_removeQuotes(fieldValue, strlen(fieldValue)); // input can contain quotes

		int l, r;
		index_binarySearch(indexVector, qttIndex, fieldValue, &l, &r); // get interval of valid values

		for (int i = l; i < r; i++) { // remove everything
			reg_removeByOffset(fp, indexVector[i].byteOffset, &vecOffset, &qttRemoved);
		}

		if (l != -1 && r != -1) { // updates vector
			index_eraseVector(&indexVector, &qttIndex, l, r - l);
		}
	}

	free(vecOffset);
	
	/** Recover header status */
	bin_setHeaderStatus(fp, '1');

	fclose(fp);

	// bin_updateChaining(fp, vecOffset, qttRemoved);
	hi.status = '0';
	index_printHeader(fpIndex, hi);

	// refill index file
	index_printRegVecIndex(fpIndex, indexVector, qttIndex);
	free(indexVector);

	// update index header
	hi.nroRegistros = qttIndex;
	hi.status = '1';
	index_updateHeader(fpIndex, hi);

	fclose(fpIndex);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileNameIndex);
}

/** Add specified registers on binary stream, and update the index file */
void bin_addRegUpdateIndex() {
	char fileName[MAXSTR], fileNameIndex[MAXSTR];
	int n; // qtt of remotions
	scanf(" %s %s %d", fileName, fileNameIndex, &n);

	// check if file is valid
	FILE* fp = fopen(fileName, "r+b");
	if (fp == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// check if index is valid
	FILE* fpIndex = fopen(fileNameIndex, "rb");
	if (fpIndex == NULL) {
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		return;
	}

	// loads header register
	HeaderRegister hr;
	bin_loadHeader(fp, &hr);

	if (hr.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		fclose(fpIndex);
		return;
	}

	// loads index header
	HeaderIndex hi;
	index_loadHeader(fpIndex, &hi);
	if (hi.status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		fclose(fpIndex);
		return;		
	}

	// load all index data to RAM
	DataIndex *indexVector = NULL;
	int qttIndex = 0;
	index_readIndexToVector(fpIndex, &indexVector, &qttIndex);

	// reopen index file to write mode
	fclose(fpIndex);
	fpIndex = fopen(fileNameIndex, "wb");

	// Set data status to 0 to alert something in case of program kill
	bin_setHeaderStatus(fp, '0');

	/** Add N times */
	for (int i = 0; i < n; i++) {
		DataRegister dr = std_scanRegister(); // reads register
		DataIndex di;
		di.byteOffset = bin_addRegister(fp, dr); // add and gets the offset
		strcpy(di.chaveBusca, dr.nomeServidor.desc);

		if (dr.nomeServidor.size > 0) { // valid input to keep on index
			str_fillEmpty(di.chaveBusca, MAXINDEXSTR, 0);
			index_pushVector(&indexVector, &qttIndex, di);
		}
	}
	
	/** Recover header status */
	bin_setHeaderStatus(fp, '1');

	fclose(fp);

	// bin_updateChaining(fp, vecOffset, qttRemoved);
	hi.status = '0';
	index_printHeader(fpIndex, hi);

	// refill index file
	index_printRegVecIndex(fpIndex, indexVector, qttIndex);
	free(indexVector);

	// updates index header
	hi.nroRegistros = qttIndex;
	hi.status = '1';
	index_updateHeader(fpIndex, hi);

	fclose(fpIndex);

	/** Print the file content to standard output stream */
	bin_printScreenClosed(fileNameIndex);
}

/** Compare access to disk on two different ways */
void bin_compareDiskAcces() {
	char fileName[MAXSTR], fileNameIndex[MAXSTR], fieldName[MAXSTR], fieldValue[MAXSTR];
	scanf(" %s %s %s %[^\n\r]", fileName, fileNameIndex, fieldName, fieldValue);

	// test without index help
	printf("*** Realizando a busca sem o auxílio de índice\n");
	int numberWithout = bin_searchReg(fileName, fieldName, fieldValue, 1);
	if (numberWithout == 0) {
		return;
	}

	// test using strongly connected index
	printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");
	int numberWith = bin_searchBasedOnIndex(fileName, fileNameIndex, fieldName, fieldValue, 1);
	if (numberWith == 0) {
		return;
	}

	// prints difference
	printf("\nA diferença no número de páginas de disco acessadas: %d\n", numberWithout - numberWith);
}

/** Create b-tree based on data file */
void btree_create() {

	// scan file names
	char filenameIn[MAXSTR], filenameOut[MAXSTR];
	scanf(" %s %s", filenameIn, filenameOut);

	// try to open files
	FILE *fpIn, *fpOut;
	fpIn = fopen(filenameIn, "rb");

	if (fpIn == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	fpOut = fopen(filenameOut, "wb+");
	if (fpOut == NULL) {
		fclose(fpIn);
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// read the header register from input file
	HeaderRegister hr;
	bin_loadHeader(fpIn, &hr);
	if (hr.status == '0') { // invalid status
		printf("Falha no processamento do arquivo.\n");
		fclose(fpIn);
		fclose(fpOut);
		return;
	}

	// print a new header to b-tree
	HeaderBTree hbt;
	hbt.status = '0'; // invalid status
	hbt.rootNode = -1; // invalid root
	btree_printHeader(fpOut, hbt);

	// jump the first page - only contains the header
	fseek(fpIn, MAXPAGE, SEEK_SET);

	// read all the registers from data file, and insert to b-tree
	DataRegister dr;
	int64_t offset = ftell(fpIn);
	while (bin_readRegister(fpIn, &dr, NULL)) {
		if (dr.removido == '*') { // logically removed
			offset = ftell(fpIn);
			continue;
		}

		// insert to b-tree
		btree_insertRegister(fpOut, dr.idServidor, offset);
		offset = ftell(fpIn);
	}

	// update the status to valid
	btree_updateHeaderStatus(fpOut, '1');

	// close files
	fclose(fpIn);
	fclose(fpOut);

	// print info from b-tree file
	bin_printScreenClosed(filenameOut);
}

/** Search for specified registers on b-tree */
void btree_search() {
	// read filenames
	char filenameData[MAXSTR], filenameBTree[MAXSTR];
	scanf(" %s %s", filenameData, filenameBTree);

	// read field names and values
	char fieldName[MAXSTR], fieldValue[MAXSTR];
	int idServidor; // key to find
	scanf(" %s %s", fieldName, fieldValue);

	// invalid field name (only idServidor was expected)
	if (strcmp(fieldName, "idServidor")) {
		printf("Falha no processamento do arquivo.\n");
		return;
	} else {
		sscanf(fieldValue, "%d", &idServidor); // convert fieldValue to integer
	}

	// try to open files
	FILE *fpData, *fpBTree;
	fpData = fopen(filenameData, "rb");

	if (fpData == NULL) {
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	fpBTree = fopen(filenameBTree, "rb");
	if (fpBTree == NULL) {
		fclose(fpData);
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// test header info from both files
	HeaderRegister hr;
	bin_loadHeader(fpData, &hr);

	HeaderBTree ht;
	btree_loadHeader(fpBTree, &ht);

	if (hr.status == '0' || ht.status == '0') { // invalid status
		printf("Falha no processamento do arquivo.\n");
		fclose(fpData);
		fclose(fpBTree);
		return;
	}

	int level = 0; // depth percurred on b-tree

	// try to find the offset of key on b-tree index
	int64_t offset = btree_findRegister(fpBTree, ht, idServidor, &level);

	if (offset == -1) { // not found
		printf("Registro inexistente.\n");
	} else {
		// found - read info from data file and print it
		fseek(fpData, offset, SEEK_SET);
		DataRegister dr;
		bin_readRegister(fpData, &dr, NULL);
		register_printFormatted(dr, hr);

		// print qtt of levels of b-tree
		printf("Número de níveis do índice árvore-B percorridos: %d\n", level);
	}

	fclose(fpData);
	fclose(fpBTree);
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
		bin_searchReg(NULL, NULL, NULL, 0);
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
	} else if (op == 10) { // create a index file based on a input file
		bin_createIndexReg();
	} else if (op == 11) { // search for registers after find byteOffset on index file
		bin_searchBasedOnIndex(NULL, NULL, NULL, NULL, 0);
	} else if (op == 12) { // remove specified registers on binary stream, and update the index file
		bin_removeRegUpdateIndex();
	} else if (op == 13) { // add specified registers on binary stream, and update the index file
		bin_addRegUpdateIndex();
	} else if (op == 14) {	// compare statistics between direct disk access and access with index file
		bin_compareDiskAcces();
	} else if (op == 15) { // create b-tree based on data file
		btree_create();
	} else if (op == 16) { // search for specified registers on b-tree
		btree_search();
	} else { // invalid input
		printf("Falha no processamento do arquivo.\n");
	}

	return 0;
}
