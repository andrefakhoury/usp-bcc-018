#include "register.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/** Loads the header of source csv file to hr */
void csv_loadHeader(FILE* source, HeaderRegister* hr) {	
	hr->status = '1';
	hr->topoLista = -1;

	hr->tagCampo1 = 'i';
	fscanf(source, "%[^,],", hr->desCampo1);
	str_fillEmpty(hr->desCampo1, 40, 0);

	hr->tagCampo2 = 's';
	fscanf(source, "%[^,],", hr->desCampo2);
	str_fillEmpty(hr->desCampo2, 40, 0);

	hr->tagCampo3 = 't';
	fscanf(source, "%[^,],", hr->desCampo3);
	str_fillEmpty(hr->desCampo3, 40, 0);

	hr->tagCampo4 = 'n';
	fscanf(source, "%[^,],", hr->desCampo4);
	str_fillEmpty(hr->desCampo4, 40, 0);

	hr->tagCampo5 = 'c';
	fscanf(source, "%[^\n\r] ", hr->desCampo5);
	str_fillEmpty(hr->desCampo5, 40, 0);
}

/** Reads the data of source file to dr */
int csv_readRegister(FILE* fp, DataRegister* dr) {
	if (fp == NULL || feof(fp))
		return 0;

	char test;
	fscanf(fp, "%c", &test);
	if (test == '\n' || test == '\r')
		return 0;

	fseek(fp, -1, SEEK_CUR);

	dr->removido = '-';
	dr->encadeamentoLista = -1;

	if (fscanf(fp, "%d", &dr->idServidor) == 0)
		dr->idServidor = -1;
	fscanf(fp, ",");

	if (fscanf(fp, "%lf", &dr->salarioServidor) == 0)
		dr->salarioServidor = -1;
	fscanf(fp, ",");

	if (fscanf(fp, "%[^,]14s", dr->telefoneServidor) == 0)
		str_fillEmpty(dr->telefoneServidor, 14, 1);
	fscanf(fp, ",");

	if (fscanf(fp, "%[^,]s", dr->nomeServidor.desc) == 0)
		dr->nomeServidor.size = 0;
	else
		dr->nomeServidor.size = strlen(dr->nomeServidor.desc) + 1;
	fscanf(fp, ",");

	if (fscanf(fp, "%[^\n\r]s", dr->cargoServidor.desc) == 0)
		dr->cargoServidor.size = 0;
	else 
		dr->cargoServidor.size = strlen(dr->cargoServidor.desc) + 1;
	fscanf(fp, "\n\r");

	dr->nomeServidor.tag = 'n';
	dr->cargoServidor.tag = 'c';

	dr->tamanhoRegistro = register_size(*dr);
	return 1;
}

/** Test whether the next character from a binary file is empty */
int bin_testEmpty(FILE* bin) {
	char temp;
	fread(&temp, 1, 1, bin);
	fseek(bin, -1, SEEK_CUR);
	return temp == EMPTY;
}

/** Writes data from header to destination file */
void bin_printHeader(FILE* dest, HeaderRegister hr) {
	fwrite(&hr.status, 1, 1, dest);
	fwrite(&hr.topoLista, 8, 1, dest);

	fwrite(&hr.tagCampo1, 1, 1, dest);
	fwrite(&hr.desCampo1, 40, 1, dest);

	fwrite(&hr.tagCampo2, 1, 1, dest);
	fwrite(&hr.desCampo2, 40, 1, dest);

	fwrite(&hr.tagCampo3, 1, 1, dest);
	fwrite(&hr.desCampo3, 40, 1, dest);

	fwrite(&hr.tagCampo4, 1, 1, dest);
	fwrite(&hr.desCampo4, 40, 1, dest);

	fwrite(&hr.tagCampo5, 1, 1, dest);
	fwrite(&hr.desCampo5, 40, 1, dest);

	bin_printEmpty(dest, MAXPAGE - 214);
}

/** Writes data from dr to destination file */
void bin_printRegister(FILE* dest, DataRegister dr) {

	fwrite(&dr.removido, 1, 1, dest);
	
	int tamanhoRegistro = dr.tamanhoRegistro - 5; // ignoring the fixed sized

	fwrite(&tamanhoRegistro, 4, 1, dest);

	fwrite(&dr.encadeamentoLista, 8, 1, dest);

	fwrite(&dr.idServidor, 4, 1, dest);
	fwrite(&dr.salarioServidor, 8, 1, dest);
	fwrite(&dr.telefoneServidor, 14, 1, dest);

	if (dr.nomeServidor.size > 0) {
		int nomeSize = dr.nomeServidor.size + 1;
		fwrite(&nomeSize, 4, 1, dest);
		fwrite(&dr.nomeServidor.tag, 1, 1, dest);
		fwrite(&dr.nomeServidor.desc, dr.nomeServidor.size, 1, dest);
	}

	if (dr.cargoServidor.size > 0) {
		int cargoSize = dr.cargoServidor.size + 1;
		fwrite(&cargoSize, 4, 1, dest);
		fwrite(&dr.cargoServidor.tag, 1, 1, dest);
		fwrite(&dr.cargoServidor.desc, dr.cargoServidor.size, 1, dest);
	}
}

/** Prints to destination file a string with empty characters */
void bin_printEmpty(FILE* dest, int size) {
	char empty = '@';
	for (int i = 0; i < size; i++)
		fwrite(&empty, 1, 1, dest);
}

/** Reads a data register from binary source, and update the number of DiskPages accessed. */
int bin_readRegister(FILE* bin, DataRegister* dr) {
	if (feof(bin))
		return 0;

	fread(&dr->removido, 1, 1, bin);
	if (feof(bin))
		return 0;

	fread(&dr->tamanhoRegistro, 4, 1, bin);

	fread(&dr->encadeamentoLista, 8, 1, bin);

	fread(&dr->idServidor, 4, 1, bin);
	fread(&dr->salarioServidor, 8, 1, bin);
	fread(&dr->telefoneServidor, 14, 1, bin);

	int bytesReaden = 34;

	dr->nomeServidor.desc[0] = '\0';
	dr->nomeServidor.tag = 'n';
	dr->nomeServidor.size = 0;

	dr->cargoServidor.desc[0] = '\0';
	dr->cargoServidor.tag = 'c';
	dr->cargoServidor.size = 0;

	if (dr->tamanhoRegistro > 34 && !bin_testEmpty(bin)) {

		int fieldSize;
		char fieldTag;

		fread(&fieldSize, 4, 1, bin);
		fread(&fieldTag, 1, 1, bin);

		if (fieldTag == dr->nomeServidor.tag) {
			fread(&dr->nomeServidor.desc, fieldSize - 1, 1, bin);
			dr->nomeServidor.size = fieldSize - 1;
		} else {
			fread(&dr->cargoServidor.desc, fieldSize - 1, 1, bin);
			dr->cargoServidor.size = fieldSize - 1;
		}
		
		bytesReaden += 4 + fieldSize;

		if (dr->tamanhoRegistro > 39 + fieldSize && !bin_testEmpty(bin)) {

			fread(&fieldSize, 4, 1, bin);
			fread(&fieldTag, 1, 1, bin);

			if (fieldTag == dr->nomeServidor.tag) {
				fread(&dr->nomeServidor.desc, fieldSize - 1, 1, bin);
				dr->nomeServidor.size = fieldSize - 1;
			} else {
				fread(&dr->cargoServidor.desc, fieldSize - 1, 1, bin);
				dr->cargoServidor.size = fieldSize - 1;
			}
		
			bytesReaden += 4 + fieldSize;
		}
	}

	if (bytesReaden != dr->tamanhoRegistro) {
		fseek(bin, dr->tamanhoRegistro - bytesReaden, SEEK_CUR);
	}

	return 1;
}

/** Load header info from bin file */
void bin_loadHeader(FILE* bin, HeaderRegister* hr) {
	fread(&hr->status, 1, 1, bin);
	fread(&hr->topoLista, 8, 1, bin);

	fread(&hr->tagCampo1, 1, 1, bin);
	fread(&hr->desCampo1, 40, 1, bin);

	fread(&hr->tagCampo2, 1, 1, bin);
	fread(&hr->desCampo2, 40, 1, bin);

	fread(&hr->tagCampo3, 1, 1, bin);
	fread(&hr->desCampo3, 40, 1, bin);

	fread(&hr->tagCampo4, 1, 1, bin);
	fread(&hr->desCampo4, 40, 1, bin);

	fread(&hr->tagCampo5, 1, 1, bin);
	fread(&hr->desCampo5, 40, 1, bin);
}

void bin_overwriteOffset(FILE* bin, int64_t newOffset, int64_t where, int64_t backup) {
	fseek(bin, where, SEEK_SET);
	fwrite(&newOffset, 8, 1, bin);
	fseek(bin, backup, SEEK_SET);
}

void bin_overwriteEmptyRegister(FILE* bin, size_t len) {
	char empty = '@';
	for (int i = 0; i < len; i++)
		fwrite(&empty, 1, 1, bin);
}

void bin_loadOffsetVector(FILE* bin, RegOffset** vec, int* qttRemoved) {
	fseek(bin, 1, SEEK_SET);

	*qttRemoved = 1;
	*vec = realloc(*vec, (*qttRemoved) * sizeof(RegOffset));

	(*vec)[0].offset = 1;
	(*vec)[0].regSize = 0;

	int64_t offset, nextOffset;
	fread(&offset, 8, 1, bin);

	while (offset != -1) {
		(*qttRemoved)++;
		*vec = realloc(*vec, (*qttRemoved) * sizeof(RegOffset));

		fseek(bin, offset + 1, SEEK_SET);

		int curSize;
		fread(&curSize, 4, 1, bin);

		(*vec)[(*qttRemoved) - 1].offset = offset;
		(*vec)[(*qttRemoved) - 1].regSize = curSize;

		fread(&nextOffset, 8, 1, bin);

		offset = nextOffset;
	}
}

/** Deletes register from binary stream */
void bin_removeRegister(FILE* bin, DataRegister dr, int64_t prevOffset, int64_t offset, int64_t nextOffset) {
	fseek(bin, offset, SEEK_SET);
	bin_overwriteOffset(bin, offset, prevOffset == 1 ? prevOffset : prevOffset + 5, offset);

	fwrite(&dr.removido, 1, 1, bin);
	fseek(bin, 4, SEEK_CUR);
	fwrite(&nextOffset, 8, 1, bin);

	char empty = '@';
	for (int i = 0; i < dr.tamanhoRegistro - 8; i++)
		fwrite(&empty, 1, 1, bin);
}

/** Insert a register in binary stream */
void bin_addRegister(FILE* bin, DataRegister dr) {
	fseek(bin, 1, SEEK_SET);
	
	int64_t offset, lastOffset = ftell(bin), nextOffset;
	fread(&offset, 8, 1, bin);

	int64_t finalOffset = -1, finalLastOffset = -1, finalNextOffset = -1;
	int finalSize = -1, count = 0;

	while (offset != -1) {
		count++;

		fseek(bin, offset + 1, SEEK_SET);

		int curSize;
		fread(&curSize, 4, 1, bin);
		
		int64_t auxOffset = ftell(bin);

		fread(&nextOffset, 8, 1, bin);

		if (dr.tamanhoRegistro <= curSize) {
			finalOffset = offset;
			finalLastOffset = lastOffset;
			finalNextOffset = nextOffset;
			finalSize = curSize + 5;
			break;
		}

		lastOffset = auxOffset;
		offset = nextOffset;
	}

	if (finalOffset == -1) { // appends to the end of file
		fseek(bin, 0, SEEK_END);
		if (count > 0) {
			bin_overwriteOffset(bin, ftell(bin), lastOffset, ftell(bin));
		}

		long curOffset = ftell(bin);
		long pagePos = curOffset % MAXPAGE;

		long curPage = (curOffset + MAXPAGE - 1) / MAXPAGE; // ceil(curOffse)

		if (dr.tamanhoRegistro + pagePos > MAXPAGE) { // end of disk page
			long qttEmpty = MAXPAGE - pagePos;

			for (int i = 0; i < qttEmpty; i++) {
				char empty = '@';
				fwrite(&empty, 1, 1, bin);
			}

			fseek(bin, curPage * MAXPAGE, SEEK_SET);

			DataRegister dr;

			while (bin_readRegister(bin, &dr));

			fseek(bin, - dr.tamanhoRegistro - 4, SEEK_CUR);
			dr.tamanhoRegistro += qttEmpty;
			bin_printRegister(bin, dr);
		}

		fseek(bin, 0, SEEK_END);
	} else { // overwrite some register
		dr.tamanhoRegistro = finalSize;
		fseek(bin, finalOffset, SEEK_SET);
		bin_overwriteEmptyRegister(bin, finalSize);
		fseek(bin, finalOffset, SEEK_SET);
		bin_overwriteOffset(bin, finalNextOffset, finalLastOffset, finalOffset);
	}

	bin_printRegister(bin, dr);
}

void bin_overwriteRegister(FILE* bin, DataRegister dr, int64_t offset, int delta) {
	fseek(bin, offset, SEEK_SET);
	bin_printRegister(bin, dr);
	bin_printEmpty(bin, delta);
}

/** Returns the size of dr */
int register_size(DataRegister dr) {
	int ans = 39;

	if (dr.nomeServidor.size > 0) {
		ans += 5 + dr.nomeServidor.size;
	}

	if (dr.cargoServidor.size > 0) {
		ans += 5 + dr.cargoServidor.size;
	}

	return ans;
}

/** Check if current register equals some desired value */
int register_check(char tag, char* value, HeaderRegister hr, DataRegister dr) {
	if (dr.removido == '*') return 0;

	if (tag == hr.tagCampo1) {
		if (!strcmp(value, "NULO"))
			return dr.idServidor == -1;

		int reg;
		sscanf(value, "%d", &reg);
		return reg == dr.idServidor;
	} else if (tag == hr.tagCampo2) {
		if (!strcmp(value, "NULO"))
			return dr.salarioServidor == -1;

		double salario;
		sscanf(value, "%lf", &salario);
		return salario == dr.salarioServidor;
	} else if (tag == hr.tagCampo3) {
		char aux[15];
		for (int i = 0; i < 14; i++)
			aux[i] = dr.telefoneServidor[i];
		aux[14] = '\0';

		if (!strcmp(value, "NULO"))
			return !strcmp(aux, "@@@@@@@@@@@@@@");
		return !strcmp(aux, value);

	} else if (tag == hr.tagCampo4) {
		if (!strcmp(value, "NULO"))
			return dr.nomeServidor.size == 0;

		return dr.nomeServidor.size > 0 && !strcmp(dr.nomeServidor.desc, value);
	} else if (tag == hr.tagCampo5) {
		if (!strcmp(value, "NULO"))
			return dr.cargoServidor.size == 0;

		return dr.cargoServidor.size > 0 && !strcmp(dr.cargoServidor.desc, value);
	}

	return 0;
}

/** Check if new register fits into old register */
int reg_canUpdate(DataRegister dr, HeaderRegister hr, char tag, char value[]) {
	if (tag == hr.tagCampo1 || tag == hr.tagCampo2 || tag == hr.tagCampo3) {
		return 1;
	} else {
		int curSize = strlen(value) + 1;
		if (!strcmp(value, "NULO"))
			curSize = 0;

		if (tag == hr.tagCampo4) {
			return curSize <= dr.nomeServidor.size;
		} else {
			return curSize <= dr.cargoServidor.size;
		}
	}

	return 0;
}

void reg_updateByTag(DataRegister* dr, HeaderRegister hr, char tag, char value[], int* delta) {
	*delta = 0;

	if (tag == hr.tagCampo1) {
		if (!strcmp(value, "NULO"))
			dr->idServidor = -1;
		else {
			int reg;
			sscanf(value, "%d", &reg);
			dr->idServidor = reg;
		}
	} else if (tag == hr.tagCampo2) {
		if (!strcmp(value, "NULO"))
			dr->idServidor = -1;
		else {
			double sal;
			sscanf(value, "%lf", &sal);
			dr->salarioServidor = sal;
		}
	} else if (tag == hr.tagCampo3) {
		if (!strcmp(value, "NULO"))
			str_fillEmpty(dr->telefoneServidor, 14, 1);
		else strcpy(dr->telefoneServidor, value);
	} else if (tag == hr.tagCampo4) {
		if (!strcmp(value, "NULO")) {
			*delta = dr->nomeServidor.size;
			dr->nomeServidor.size = 0;
		} else {
			*delta = dr->nomeServidor.size;

			strcpy(dr->nomeServidor.desc, value);
			dr->nomeServidor.size = strlen(dr->nomeServidor.desc) + 1;

			*delta -= dr->nomeServidor.size;
			if (*delta < 0) *delta = 0;
		}
	} else if (tag == hr.tagCampo5) {
		if (!strcmp(value, "NULO")) {
			*delta = dr->cargoServidor.size;
			dr->cargoServidor.size = 0;
		} else {
			*delta = dr->cargoServidor.size - strlen(value) - 1;			
			if (*delta < 0) *delta = 0;

			strcpy(dr->cargoServidor.desc, value);
			dr->cargoServidor.size = strlen(dr->cargoServidor.desc) + 1;
		}
	}
}

/** Prints data from dr to stdout */
void register_toStream(DataRegister dr) {
	if (dr.idServidor >= 0)
		printf("%d ", dr.idServidor);
	else
		printf("     ");
	
	if (dr.salarioServidor >= 0)
		printf("%.2lf ", dr.salarioServidor);
	else
		printf("         ");
	
	printf("%-14s ", dr.telefoneServidor);

	if (dr.nomeServidor.size > 0)
		printf("%d %s ", dr.nomeServidor.size - 1, dr.nomeServidor.desc);

	if (dr.cargoServidor.size > 0)
		printf("%d %s", dr.cargoServidor.size - 1, dr.cargoServidor.desc);

	printf("\n");
}

/** Print data from dr and hr to stdout in a formatted way */
void register_printFormatted(DataRegister dr, HeaderRegister hr) {
	if (dr.idServidor >= 0)
		printf("%s: %d\n", hr.desCampo1, dr.idServidor);
	else printf("%s: valor nao declarado\n", hr.desCampo1);

	if (dr.salarioServidor >= 0)
		printf("%s: %.2lf\n", hr.desCampo2, dr.salarioServidor);
	else printf("%s: valor nao declarado\n", hr.desCampo2);

	if (strlen(dr.telefoneServidor) > 0)
		printf("%s: %s\n", hr.desCampo3, dr.telefoneServidor);
	else printf("%s: valor nao declarado\n", hr.desCampo3);
	
	if (dr.nomeServidor.size > 0)
		printf("%s: %s\n", hr.desCampo4, dr.nomeServidor.desc);
	else printf("%s: valor nao declarado\n", hr.desCampo4);
	
	if (dr.cargoServidor.size > 0)
		printf("%s: %s\n", hr.desCampo5, dr.cargoServidor.desc);
	else printf("%s: valor nao declarado\n", hr.desCampo5);

	printf("\n");
}

/** Fills empty chars of src string with @. If all is set, str is fully filled. */
void str_fillEmpty(char* src, int totalSize, int all) {
	int i = all ? 1 : strlen(src) + 1;
	src[i-1] = '\0';

	while (i < totalSize) {
		src[i] = '@';
		i++;
	}
}

/** Prints a binary file to stdout. @author Matheus Carvalho */
void bin_printScreenOpen(FILE *fp) {
	unsigned char *mb;
	unsigned long i;
	size_t fl;
	fseek(fp, 0, SEEK_END);
	fl = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fp);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
}

/** Prints a binary file to stdout. @author Matheus Carvalho */
void bin_printScreenClosed(char *fileName) {
	unsigned char *mb;
	unsigned long i;
	size_t fl;
	
	FILE *fs;
	if(fileName == NULL || !(fs = fopen(fileName, "rb"))) {
		fprintf(stderr, "Error on bin_printScreenClosed - invalid fileName");
		return;
	}

	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
	fclose(fs);
}