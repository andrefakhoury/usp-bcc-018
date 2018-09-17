#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

#define maxCarro 10

typedef struct est estacionamento;

estacionamento* criaEstacionamento();
void apagaEstacionamento(estacionamento* est);
int estaciona_carro(estacionamento* est, char* placa);
int retira_carro(estacionamento* est, char* placa);
