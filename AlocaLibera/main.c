#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "memoria.h"

int main(void)
{
	initialize();

	Lista *list = Aloca(sizeof(Lista));

	int *x = (int*)list;
	printf("%d\n", *x);
	initList(list); //iniciei a lista e ela mudou o valor, nao sei pq
	int *q = (int*)list;
	printf("%d\n", *q);
	//ins_na_lista_vazia(list, "fe");
	//int *v = (int*)list;
	//printf("%d\n", *v);

	//show();
	//printf("\n");
	//Libera(list);
	//remov(list, 1);
	//show();

	return 0;
}
