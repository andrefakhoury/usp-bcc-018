
#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include <stdint.h>
#include "register.h"

#define MAXINDEXSTR 120

/** Struct of the index header */
typedef struct HeaderIndex {
    char status;
    int nroRegistros;
} HeaderIndex;

/** Struct of the index data */
typedef struct DataIndex {
    char chaveBusca[120];
    int64_t byteOffset;
} DataIndex;

/** Writes data from header to destination index stream */
void index_printHeader(FILE* dest, HeaderIndex hi);

/** Update the HeaderIndex info */
void index_updateHeader(FILE* fp, HeaderIndex hi);

/** Print a register to index stream */
void index_printRegister(FILE* fp, DataIndex di);

/** Reads the index header */
void index_loadHeader(FILE* fp, HeaderIndex* hi);

/** Reads a index register */
int index_readRegister(FILE* fp, DataIndex* di, int* numPaginas);

/** Reads index file and push elements to vector */
void index_readIndexToVector(FILE* fp, DataIndex** indexVector, int* qttIndex);

#endif