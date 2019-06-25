#include "index.h"
#include <stdlib.h>

/** Writes data from header to destination index stream */
void index_printHeader(FILE* dest, HeaderIndex hi) {
	fwrite(&hi.status, sizeof(char), 1, dest);
	fwrite(&hi.nroRegistros, sizeof(int), 1, dest);

	bin_printEmpty(dest, MAXPAGE - 5); // MAXPAGE - bytes used on header
}

/** Update the HeaderIndex info */
void index_updateHeader(FILE* fp, HeaderIndex hi) {
	fseek(fp, 0, SEEK_SET);
	fwrite(&hi.status, sizeof(char), 1, fp);
	fwrite(&hi.nroRegistros, sizeof(int), 1, fp);
}

/** Print a register to index stream */
void index_printRegister(FILE* fp, DataIndex di) {
    fwrite(&di.chaveBusca, MAXINDEXSTR, 1, fp);
    fwrite(&di.byteOffset, sizeof(int64_t), 1, fp);
}

/** Reads the index header */
void index_loadHeader(FILE* fp, HeaderIndex* hi) {
    fread(&hi->status, sizeof(char), 1, fp);
    fread(&hi->nroRegistros, sizeof(int), 1, fp);

    fseek(fp, MAXPAGE, SEEK_SET);
}

/** Reads a index register. Returns wheter EOF is reached */
int index_readRegister(FILE* fp, DataIndex* di, int* numPaginas) {
    int lastPage = (ftell(fp) + MAXPAGE - 1) / MAXPAGE;

    if (feof(fp)) { // end of file
        return 0;
    }

    fread(&di->chaveBusca, MAXINDEXSTR, 1, fp);
    fread(&di->byteOffset, sizeof(int64_t), 1, fp);

    if (feof(fp)) {
        return 0;
    }

    // update qtt of disk pages
    int thisPage = (ftell(fp) + MAXPAGE - 1) / MAXPAGE;
    if (numPaginas != NULL) {
        (*numPaginas) += thisPage != lastPage;
    }
    
    return 1;
}

/** Reads index file and push elements to vector */
void index_readIndexToVector(FILE* fp, DataIndex** indexVector, int* qttIndex) {
    DataIndex *indexVectorAux = NULL, di;
	int qttIndexAux = 0;

    // read every index
	while(index_readRegister(fp, &di, NULL)) {
		qttIndexAux++;
		indexVectorAux = realloc(indexVectorAux, qttIndexAux * sizeof(DataIndex));
		indexVectorAux[qttIndexAux-1] = di;
	}

    // update parameters asked
    *indexVector = indexVectorAux;
    *qttIndex = qttIndexAux;
}