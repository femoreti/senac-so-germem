#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define SIZE 4096

static char memoria[SIZE];

void initialize()
{
	int i;
	int lenght = sizeof(memoria) / sizeof(char);
	for (i = 0; i < lenght; i++)
	{
		memoria[i] = '0';

	}
}

void show()
{
	int i;
	int lenght = sizeof(memoria) / sizeof(char);

	for (i = 0; i < lenght; i++)
	{
		printf("%c", memoria[i]);
		if (i % 100 == 0 && i != 0)
			printf("\n");
	}
	printf("\n");
}

void *Aloca(unsigned int memory)
{
	int i;
	int lenght = sizeof(memoria) / sizeof(char);

	int index = 0;
	int canUse = 1;

	for (i = 0; i < lenght; i++)
	{
		if (memoria[i] == '-')
		{
			canUse = 0;
		}
		if (memoria[i] == NULL)
		{
			canUse = 1;
			index = i + 1;
			continue;
		}
		if (canUse == 0)
			continue;

		if (canUse == 1 && (i - index == memory + 1))
		{
			memoria[index] = '-';
			memoria[i] = NULL;

			index++;

			return (index);
		}
	}

	printf("out of memory to alloc %d of space\n", memory);
	return NULL;
}



void Libera(void *index)
{
	int i;
	int lenght = sizeof(memoria) / sizeof(char);

	int x = (int)index - 1;

	for (i = x; i < lenght; i++)
	{
		if (memoria[i] == NULL)
		{
			memoria[i] = '0';
			memoria[x] = '0';
			break;
		}
	}
}

int main(void) 
{
	/*initialize();

	int test = Aloca(364);
	int test1 = Aloca(59);
	int test2 = Aloca(400);
	printf("aloca\n");
	show();

	Libera(test1);
	printf("libera\n");
	show();
	int test3 = Aloca(2000);
	printf("aloca\n");
	show();
	test1 = Aloca(199);
	printf("aloca\n");
	show();*/

	Lista *list = malloc(sizeof(Lista));
	initList(list);
	ins_na_lista_vazia(list, 0);

	for (int i = 1; i <= 10; i++)
	{
		ins_fim_lista(list, i);

	}
	ShowList(list);


	//scanf("");

	return 0;
}
