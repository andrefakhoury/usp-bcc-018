#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main() {
    printf("Ø");

    char aux[20];
    while (scanf(" %s", aux), strcmp(aux, "Ø"));

    printf("%s Ø\n", aux);
}