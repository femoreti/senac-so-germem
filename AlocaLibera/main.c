#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lista.h"
#include "memoria.h"

int main(void)
{
	initialize();

	int *i = Aloca(10);
	int *j = Aloca(5);
	int *k = Aloca(15);
	char *f = Aloca(sizeof("felipe"));
	Lista *list = Aloca(sizeof(Lista));
	//initList(list); //se inicializar a lista ele para de remover da memoria, nao sei pq
	//ins_na_lista_vazia(list, (void *) 8);
	show();
	printf("\n");
	Libera(list);
	//remov(list, 1);
	show();

	return 0;
}
