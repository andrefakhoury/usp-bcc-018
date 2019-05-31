#include "index.h"
#include <stdlib.h>

/** Writes data from header to destination index stream */
void index_printHeader(FILE* dest, HeaderIndex hi) {
	fwrite(&hi.status, 1, 1, dest);
	fwrite(&hi.nroRegistros, 4, 1, dest);

	bin_printEmpty(dest, MAXPAGE - 5);
}

/** Update the HeaderIndex info */
void index_updateHeader(FILE* fp, HeaderIndex hi) {
	fseek(fp, 0, SEEK_SET);
	fwrite(&hi.status, 1, 1, fp);
	fwrite(&hi.nroRegistros, 4, 1, fp);
}

/** Print a register to index stream */
void index_printRegister(FILE* fp, DataIndex di) {
    fwrite(&di.chaveBusca, MAXINDEXSTR, 1, fp);
    fwrite(&di.byteOffset, 8, 1, fp);
}

/** Reads the index header */
void index_loadHeader(FILE* fp, HeaderIndex* hi) {
    fread(&hi->status, 1, 1, fp);
    fread(&hi->nroRegistros, 4, 1, fp);

    fseek(fp, MAXPAGE, SEEK_SET);
}

/** Reads a index register */
int index_readRegister(FILE* fp, DataIndex* di, int* qttDiskPage) {
    int lastPage = (ftell(fp) + MAXPAGE - 1) / MAXPAGE;

    if (feof(fp)) {
        return 0;
    }

    fread(&di->chaveBusca, MAXINDEXSTR, 1, fp);
    fread(&di->byteOffset, 8, 1, fp);

    if (feof(fp)) {
        return 0;
    }

    int thisPage = (ftell(fp) + MAXPAGE - 1) / MAXPAGE;
    if (qttDiskPage != NULL) {
        (*qttDiskPage) += thisPage != lastPage;
    }
    
    return 1;
}

/** Reads index file and push elements to vector */
void index_readIndexToVector(FILE* fp, DataIndex** indexVector, int* qttIndex) {
    DataIndex *indexVectorAux = NULL, di;
	int qttIndexAux = 0;

	while(index_readRegister(fp, &di, NULL)) {
		qttIndexAux++;
		indexVectorAux = realloc(indexVectorAux, qttIndexAux * sizeof(DataIndex));
		indexVectorAux[qttIndexAux-1] = di;
	}

    *indexVector = indexVectorAux;
    *qttIndex = qttIndexAux;
}