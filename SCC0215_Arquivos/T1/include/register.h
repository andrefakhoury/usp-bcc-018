#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <stdint.h>

#define EMPTY '@'
#define MAXPAGE 32000

typedef struct _Header {
	char status;
	int64_t topoLista;

	char tagCampo1, desCampo1[40]; //idServidor
	char tagCampo2, desCampo2[40]; //salarioServidor
	char tagCampo3, desCampo3[40]; //telefoneServidor
	char tagCampo4, desCampo4[40]; //nomeServidor
	char tagCampo5, desCampo5[40]; //cargoServidor
} HeaderRegister;

typedef struct _varReg {
	size_t size;
	char tag;
	char desc[1024];
} varSizeRegister;

typedef struct _Data {
	char removido;
	int tamanhoRegistro;
	int64_t encadeamentoLista;

	int idServidor;
	double salarioServidor;
	char telefoneServidor[14];

	varSizeRegister nomeServidor;
	varSizeRegister cargoServidor;	
} DataRegister;

void csv_ignoreLine(FILE* fp);
void csv_loadHeader(HeaderRegister* hr);
void csv_printHeader(HeaderRegister hr, FILE* dest);
int csv_readRegister(FILE* fp, DataRegister* dr);
void csv_printRegister(DataRegister dr, FILE* dest);
size_t register_size(DataRegister dr);
void fillEmpty(char* src, size_t totalSize, int all);
void printEmpty(size_t size, FILE* dest);

#endif