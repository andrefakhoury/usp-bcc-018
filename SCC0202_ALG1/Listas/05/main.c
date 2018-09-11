#include <stdio.h>
#include "estacionamento.h"

int main() {
	estacionamento* est = criaEstacionamento();
	char* placas[10];
	
	scanf(" %m[^\n\r]", &placas[0]);
	estaciona_carro(est, placas[0]);
	
	scanf(" %m[^\n\r]", &placas[1]);
	estaciona_carro(est, placas[1]);
	
	scanf(" %m[^\n\r]", &placas[2]);
	estaciona_carro(est, placas[2]);
	
	retira_carro(est, placas[0]);
	retira_carro(est, placas[1]);
	
	apagaEstacionamento(est);
	return 0;
}
