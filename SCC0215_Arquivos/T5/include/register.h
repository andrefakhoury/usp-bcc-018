#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <stdint.h>

/** Macro for an empty character */
#define EMPTY '@'

/** Number of registers in a DiskPage */
#define MAXPAGE 32000

/** Number of char on header descriptions */
#define MAXHEADERSTRING 40

/** Number of char to the phone */
#define MAXPHONE 14

/** Struct for the HeaderRegister */
typedef struct _Header {
	char status;
	int64_t topoLista;

	char tagCampo1, desCampo1[MAXHEADERSTRING]; //idServidor
	char tagCampo2, desCampo2[MAXHEADERSTRING]; //salarioServidor
	char tagCampo3, desCampo3[MAXHEADERSTRING]; //telefoneServidor
	char tagCampo4, desCampo4[MAXHEADERSTRING]; //nomeServidor
	char tagCampo5, desCampo5[MAXHEADERSTRING]; //cargoServidor
} HeaderRegister;

/** Struct for the DataRegister */
typedef struct _Data {
	char removido; //removed flag
	int tamanhoRegistro; //size of current register
	int64_t encadeamentoLista;

	int idServidor;
	double salarioServidor;
	char telefoneServidor[MAXPHONE];
	
	struct varSizeRegister {
		int size;
		char tag;
		char desc[1024];
	} nomeServidor, cargoServidor;
} DataRegister;

/** Struct for the removed registers */
typedef struct {
	int regSize;
	int64_t offset;
} RegOffset;

/** Loads the header of csv source file to hr */
void csv_loadHeader(FILE* source, HeaderRegister* hr);

/** Reads the data of source file to dr */
int csv_readRegister(FILE* fp, DataRegister* dr);

/** Writes data from header to destination file */
void bin_printHeader(FILE* dest, HeaderRegister hr);

/** Writes data from dr to destination file */
void bin_printRegister(FILE* dest, DataRegister dr);

/** Prints to destination file a string with empty characters */
void bin_printEmpty(FILE* dest, int size);

/** Reads a data register from binary source, and update the number of DiskPages accessed. */
int bin_readRegister(FILE* bin, DataRegister* dr, int* numPaginas);

/** Load header info from bin file */
void bin_loadHeader(FILE* bin, HeaderRegister* hr);

/** Load RegOffset vector with removed registers at binary file */
void bin_loadOffsetVector(FILE* bin, RegOffset** vec, int* qttRemoved);

/** Deletes register from binary stream */
void bin_removeRegister(FILE* bin, DataRegister dr, int64_t prevOffset, int64_t offset, int64_t nextOffset);

/** Insert a register in binary stream. Returns new byteOffset of register */
int64_t bin_addRegister(FILE* bin, DataRegister dr);

/** Overwrite some register, filling empty the size difference */
void bin_overwriteRegister(FILE* bin, DataRegister dr, int64_t offset, int delta);

/** Set the HeaderRegister status to `status` */
void bin_setHeaderStatus(FILE* bin, char status);

/** Returns the size of dr */
int register_size(DataRegister dr);

/** Check if current register equals some desired value */
int register_check(char tag, char value[], HeaderRegister hr, DataRegister dr);

/** Update a DataRegister according to the update tag */
void reg_updateByTag(DataRegister* dr, HeaderRegister hr, char tag, char value[], int* delta, int* same);

/** Prints data from dr to stdout */
void register_toStream(DataRegister dr);

/** Print data from dr and hr to stdout in a formatted way */
void register_printFormatted(DataRegister dr, HeaderRegister hr);

/** Fills empty chars of src string with @. If all is set, str is fully filled. */
void str_fillEmpty(char* src, int totalSize, int all);

/** Prints a binary file to stdout. @author Matheus Carvalho */
void bin_printScreenOpen(FILE *fp);

/** Prints a binary file to stdout. @author Matheus Carvalho */
void bin_printScreenClosed(char *fileName);


#endif
