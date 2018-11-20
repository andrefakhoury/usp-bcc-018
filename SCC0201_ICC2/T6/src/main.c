#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "md5.h"

bool cadastraUser(char *nome, char *senha) {
	//"Cadastro realizado com sucesso."
	//"Nome de usuario invalido."
}

bool autenticaUser(char *nome, char *senha) {
	//"Autenticacao feita com sucesso." :
	//"Nome de usuario ou senha invalidos.");

}

void deletaUser(char *nome, char *senha) {


}

void exibeTudo() {

}

int main() {
	char op[5];

	while(scanf(" %s", op) != EOF) {
		if (!strcmp(op, "exib")) {
			exibeTudo();
			continue;
		}

		char *nome, *senha;
		scanf(" %ms %ms", &nome, &senha);

		if (!strcmp(op, "cad")) cadastraUser(nome, senha);
		if (!strcmp(op, "aut")) autenticaUser(nome, senha);
		if (!strcmp(op, "del")) deletaUser(nome, senha);
	}

	return 0;
}