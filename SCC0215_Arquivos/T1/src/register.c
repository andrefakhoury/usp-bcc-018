#include "register.h"
#include <stdio.h>
#include <string.h>

void csv_ignoreLine(FILE* fp) {
	if (fp != NULL) {
		fscanf(fp, "%*[^\n\r] ");
	}
}

void fillEmpty(char* src, size_t totalSize, int all) {
	int i;

	if (all) {
		src[0] = '\0';
		i = 1;
	} else {
		i = strlen(src) + 1;
	}
	while (i < totalSize) {
		src[i] = '@';
		i++;
	}
}

void printEmpty(size_t size, FILE* dest) {
	char empty = '@';
	for (size_t i = 0; i < size; i++)
		fwrite(&empty, 1, 1, dest);
}

void csv_loadHeader(HeaderRegister* hr) {
	hr->status = '1';
	hr->topoLista = -1;

	hr->tagCampo1 = 'i';
	strcpy(hr->desCampo1, "numero de identificacao do servidor");
	fillEmpty(hr->desCampo1, 40, 0);

	hr->tagCampo2 = 's';
	strcpy(hr->desCampo2, "salario do servidor");
	fillEmpty(hr->desCampo2, 40, 0);

	hr->tagCampo3 = 't';
	strcpy(hr->desCampo3, "telefone celular do servidor");
	fillEmpty(hr->desCampo3, 40, 0);

	hr->tagCampo4 = 'n';
	strcpy(hr->desCampo4, "nome do servidor");
	fillEmpty(hr->desCampo4, 40, 0);

	hr->tagCampo5 = 'c';
	strcpy(hr->desCampo5, "cargo do servidor");
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

size_t register_size(DataRegister dr) {

	size_t ans = 39;

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

	if (fscanf(fp, "%[^,]14s", dr->telefoneServidor) == 0)
		fillEmpty(dr->telefoneServidor, 14, 1);
	fscanf(fp, ",");

	if (fscanf(fp, "%lf", &dr->salarioServidor) == 0)
		dr->salarioServidor = -1;
	fscanf(fp, ",");

	if (fscanf(fp, "%[^,]s", dr->cargoServidor.desc) == 0)
		dr->cargoServidor.size = 0;
	else 
		dr->cargoServidor.size = strlen(dr->cargoServidor.desc) + 1;
	fscanf(fp, ",");

	if (fscanf(fp, "%[^\n\r]s", dr->nomeServidor.desc) == 0)
		dr->nomeServidor.size = 0;
	else
		dr->nomeServidor.size = strlen(dr->nomeServidor.desc) + 1;
	fscanf(fp, "\n\r");

	dr->nomeServidor.tag = 'n';
	dr->cargoServidor.tag = 'c';

	dr->tamanhoRegistro = register_size(*dr);
	return 1;
}

/** Prints a register on destination file stream */
void csv_printRegister(DataRegister dr, FILE* dest) {

	fwrite(&dr.removido, 1, 1, dest);
	fwrite(&dr.tamanhoRegistro, 4, 1, dest);
	fwrite(&dr.encadeamentoLista, 8, 1, dest);

	fwrite(&dr.idServidor, 4, 1, dest);
	fwrite(&dr.salarioServidor, 8, 1, dest);
	fwrite(&dr.telefoneServidor, 14, 1, dest);

	if (dr.nomeServidor.size > 0) {
		fwrite(&dr.nomeServidor.size, 4, 1, dest);
		fwrite(&dr.nomeServidor.tag, 1, 1, dest);
		fwrite(&dr.nomeServidor.desc, strlen(dr.nomeServidor.desc) + 1, 1, dest);		
	}

	if (dr.cargoServidor.size > 0) {
		fwrite(&dr.cargoServidor.size, 4, 1, dest);
		fwrite(&dr.cargoServidor.tag, 1, 1, dest);
		fwrite(&dr.cargoServidor.desc, strlen(dr.cargoServidor.desc) + 1, 1, dest);
	}
}