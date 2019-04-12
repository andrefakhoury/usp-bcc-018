#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <stdint.h>

/** Macro for an empty character */
#define EMPTY '@'

/** Number of registers in a DiskPage */
#define MAXPAGE 32000

/** Struct for the HeaderRegister */
typedef struct _Header {
	char status;
	int64_t topoLista;

	char tagCampo1, desCampo1[40]; //idServidor
	char tagCampo2, desCampo2[40]; //salarioServidor
	char tagCampo3, desCampo3[40]; //telefoneServidor
	char tagCampo4, desCampo4[40]; //nomeServidor
	char tagCampo5, desCampo5[40]; //cargoServidor
} HeaderRegister;

/** Struct for the DataRegister */
typedef struct _Data {
	char removido; //removed flag
	int tamanhoRegistro; //size of current register
	int64_t encadeamentoLista;

	int idServidor;
	double salarioServidor;
	char telefoneServidor[14];
	
	struct varSizeRegister {
		int size;
		char tag;
		char desc[1024];
	} nomeServidor, cargoServidor;
} DataRegister;

/** Loads the header of source csv file to hr */
void csv_loadHeader(HeaderRegister* hr, FILE* source);

/** Writes data from header to destination file */
void csv_printHeader(HeaderRegister hr, FILE* dest);

/** Reads the data of source file to dr */
int csv_readRegister(FILE* fp, DataRegister* dr);

/** Writes data from dr to destionation file */
void csv_printRegister(DataRegister dr, FILE* dest);

/** Returns the size of dr */
int register_size(DataRegister dr);

/** Fills empty chars of src string with @. If all is set, str is fully filled. */
void fillEmpty(char* src, int totalSize, int all);

/** Prints to destination file a string with empty characters */
void printEmpty(int size, FILE* dest);

/** Reads a data register from binary source, and update the number of DiskPages accessed. */
int bin_readRegister(FILE* bin, DataRegister* dr, int* numPaginas);

/** Prints data from dr to stdout */
void register_toStream(DataRegister dr);

/** Load header info from bin file */
void bin_loadHeader(FILE* bin, HeaderRegister* hr);

/** Check if current register equals some desired value */
int register_check(char tag, char value[], HeaderRegister hr, DataRegister dr);

/** Print data from dr and hr to stdout in a formatted way */
void register_printFormatted(DataRegister dr, HeaderRegister hr);

#endif