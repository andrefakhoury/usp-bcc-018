#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include <stdint.h>
#include "register.h"

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

void index_createIndexFile(FILE* fp);

#endif