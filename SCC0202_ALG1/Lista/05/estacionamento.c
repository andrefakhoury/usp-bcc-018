#include "estacionamento.h"

struct est {
	Pilha vagas;
};

estacionamento* criaEstacionamento() {
	estacionamento* est = malloc(sizeof(estacionamento));
	cria_pilha(&est->vagas);
	return est;
}

void apagaEstacionamento(estacionamento* est) {
	if (est != NULL)
		free(est);
}

int estaciona_carro(estacionamento* est, char* placa) {
	if (est == NULL || tamanho(est->vagas) >= maxCarro)
		return 0;
	
	return !push(&est->vagas, placa);
}

int retira_carro(estacionamento* est, char* placa) {
	if (est == NULL || !tamanho(est->vagas))
		return 0;
	
	Pilha aux;
	cria_pilha(&aux);
	
	char *doTopo;
	int jaAchou = 0;
	
	while(!pop(&est->vagas, &doTopo)) {
		//compara o doTopo com a Placa
		int igual = 1;
		for (int i = 0; doTopo[i] != '\0' || placa[i] != '\0'; i++) {
			if (doTopo[i] != '\0' && placa[i] == '\0' || doTopo[i] == '\0' && placa[i] != '\0') { 
				igual = 0;
				break;
			} else if (doTopo[i] != placa[i]) {
				igual = 0;
				break;
			}
		}
		if (!igual) {
			push(&aux, doTopo);
			continue;
		} else {
			jaAchou = 1;
			break;
		}
	}
	
	if (jaAchou) {
		while(!pop(&aux, &doTopo)) {
			estaciona_carro(est, doTopo);
		}
	}
			
	return 1;
}
