#include "register.h"
#include <stdio.h>
#include <string.h>

void fillEmpty(char* src, int totalSize, int all) {
	int i = all ? 1 : strlen(src) + 1;
	src[i-1] = '\0';

	while (i < totalSize) {
		src[i] = '@';
		i++;
	}
}

void printEmpty(int size, FILE* dest) {
	char empty = '@';
	for (int i = 0; i < size; i++)
		fwrite(&empty, 1, 1, dest);
}

void csv_loadHeader(HeaderRegister* hr, FILE* source) {	
	hr->status = '1';
	hr->topoLista = -1;

	hr->tagCampo1 = 'i';
	fscanf(source, "%[^,],", hr->desCampo1);
	fillEmpty(hr->desCampo1, 40, 0);

	hr->tagCampo2 = 's';
	fscanf(source, "%[^,],", hr->desCampo2);
	fillEmpty(hr->desCampo2, 40, 0);

	hr->tagCampo3 = 't';
	fscanf(source, "%[^,],", hr->desCampo3);
	fillEmpty(hr->desCampo3, 40, 0);

	hr->tagCampo4 = 'n';
	fscanf(source, "%[^,],", hr->desCampo4);
	fillEmpty(hr->desCampo4, 40, 0);

	hr->tagCampo5 = 'c';
	fscanf(source, "%[^\n\r] ", hr->desCampo5);
	fillEmpty(hr->desCampo5, 40, 0);
}

void csv_printHeader(HeaderRegister hr, FILE* dest) {
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

	printEmpty(MAXPAGE - 214, dest);
}

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
		fillEmpty(dr->telefoneServidor, 14, 1);
	fscanf(fp, ",");

	if (fscanf(fp, "%[^,]s", dr->nomeServidor.desc) == 0)
		dr->nomeServidor.size = 0;
	else
		dr->nomeServidor.size = strlen(dr->nomeServidor.desc);
	fscanf(fp, ",");

	if (fscanf(fp, "%[^\n\r]s", dr->cargoServidor.desc) == 0)
		dr->cargoServidor.size = 0;
	else 
		dr->cargoServidor.size = strlen(dr->cargoServidor.desc);
	fscanf(fp, "\n\r");

	dr->nomeServidor.tag = 'n';
	dr->cargoServidor.tag = 'c';

	dr->tamanhoRegistro = register_size(*dr);
	return 1;
}

/** Prints a register on destination file stream */
void csv_printRegister(DataRegister dr, FILE* dest) {

	fwrite(&dr.removido, 1, 1, dest);
	
	int tamanhoRegistro = dr.tamanhoRegistro - 5; // ignoring the fixed sized
	fwrite(&tamanhoRegistro, 4, 1, dest);

	fwrite(&dr.encadeamentoLista, 8, 1, dest);

	fwrite(&dr.idServidor, 4, 1, dest);
	fwrite(&dr.salarioServidor, 8, 1, dest);
	fwrite(&dr.telefoneServidor, 14, 1, dest);

	if (dr.nomeServidor.size > 0) {
		fwrite(&dr.nomeServidor.size, 4, 1, dest);
		fwrite(&dr.nomeServidor.tag, 1, 1, dest);
		fwrite(&dr.nomeServidor.desc, strlen(dr.nomeServidor.desc), 1, dest);		
	}

	if (dr.cargoServidor.size > 0) {
		fwrite(&dr.cargoServidor.size, 4, 1, dest);
		fwrite(&dr.cargoServidor.tag, 1, 1, dest);
		fwrite(&dr.cargoServidor.desc, strlen(dr.cargoServidor.desc), 1, dest);
	}
}

int bin_testEmpty(FILE* bin) {
	char temp;
	fread(&temp, 1, 1, bin);
	fseek(bin, -1, SEEK_CUR);
	return temp == EMPTY;
}

int bin_readRegister(FILE* bin, DataRegister* dr, int* numPaginas) {
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
		(*numPaginas)++;
		fseek(bin, dr->tamanhoRegistro - bytesReaden, SEEK_CUR);
	}

	return 1;
}

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

int register_check(char tag, char value[], HeaderRegister hr, DataRegister dr) {
	if (dr.removido == '*') return 0;

	if (tag == hr.tagCampo1) {
		int reg;
		sscanf(value, "%d", &reg);
		return reg == dr.idServidor;
	} else if (tag == hr.tagCampo2) {
		double salario;
		sscanf(value, "%lf", &salario);
		return salario == dr.salarioServidor;
	} else if (tag == hr.tagCampo3) {
		return !strcmp(dr.telefoneServidor, value);
	} else if (tag == hr.tagCampo4) {
		return dr.nomeServidor.size > 0 && !strcmp(dr.nomeServidor.desc, value);
	} else if (tag == hr.tagCampo5) {
		return dr.cargoServidor.size > 0 && !strcmp(dr.cargoServidor.desc, value);
	}

	return 0;
}

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