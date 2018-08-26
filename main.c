#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lista.h"
#include "memoria.h"

int main(void)
{
	initialize();

	Lista *list = Aloca(sizeof(Lista));
	initList(list);

	float f = 11.59f;
	ins_na_lista_vazia(list, (void *)5);
	ins_fim_lista(list, "felipe");
	ins_fim_lista(list, &f);

	remov(list, 1); //Nao esta removendo da memoria a lista nem o dado pois o int* nao é o mesmo que é alocado

	show();
	//scanf("");

	return 0;
}
