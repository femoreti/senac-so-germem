#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define SIZE 4096

char memoria[SIZE];

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
		if (i % 50 == 0 && i != 0)
			printf("\n");
	}
	printf("\n");
}

void *Aloca(unsigned int memory)
{
	int i;
	int lenght = sizeof(memoria) / sizeof(char);

	int *index = malloc(sizeof(int));
	*index = 0;
	int canUse = 1;

	for (i = 0; i < lenght; i++)
	{
		if (memoria[i] == '-')
		{
			canUse = 0;
		}
		if (memoria[i] == 'N')
		{
			canUse = 1;
			*index = i + 1;
			continue;
		}
		if (canUse == 0)
			continue;

		if (canUse == 1 && (i - *index == memory + 1))
		{
			memoria[*index] = '-';
			memoria[i] = 'N';

			*index = *index + 1;

			return (void *)index;
		}
	}

	printf("out of memory to alloc %d of space\n", memory);
	return NULL;
}



void Libera(void *index)
{
	int i;
	int lenght = sizeof(memoria) / sizeof(char);

	int *x = (int *)index - 1;

	for (i = *x; i < lenght; i++)
	{
		if (memoria[i] == 'N')
		{
			memoria[i] = '0';
			memoria[*x] = '0';
			break;
		}
	}
}

int main(void)
{
	initialize();

	//Lista *list;
	//initList(list);

	int *test = Aloca(sizeof(Lista));
	int *test1 = Aloca(sizeof(char));
	//Libera(test);
	show();

	//scanf("");

	return 0;
}
