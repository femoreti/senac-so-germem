#include <stdio.h>
#include <stdlib.h>

void *Aloca(unsigned int memory);
void Libera(void *index);

typedef struct dl_elementoLista {
	void *dado;
	struct dl_elementoLista *anterior;
	struct dl_elementoLista*seguinte;
} ListaObj;

typedef struct dl_ListaDetectada {
	ListaObj *início;
	ListaObj *fim;
	int tamanho;
} Lista;

void initList(Lista *lista)
{
	lista->início = NULL;
	lista->fim = NULL;
	lista->tamanho = 0;
}
ListaObj *aloc(ListaObj *novo_elemento, void* dado)
{
	novo_elemento->anterior = NULL;
	novo_elemento->seguinte = NULL;
	novo_elemento->dado = Aloca(sizeof(dado));
	return novo_elemento;
}

int ins_na_lista_vazia(Lista * lista, void* dado) {
	ListaObj *novo_elemento = Aloca(sizeof(ListaObj));
	novo_elemento = aloc(novo_elemento, dado);
	if (novo_elemento == NULL)
		return -1;
	novo_elemento->dado = dado;
	novo_elemento->anterior = lista->início;
	novo_elemento->seguinte = lista->fim;
	lista->início = novo_elemento;
	lista->fim = novo_elemento;
	lista->tamanho++;
	return 0;
}

int ins_inicio_lista(Lista * lista, void* dado) {
	ListaObj *novo_elemento = Aloca(sizeof(ListaObj));
	novo_elemento = aloc(novo_elemento, dado);
	if (novo_elemento == NULL)
		return -1;
	novo_elemento->dado = dado;
	novo_elemento->anterior = NULL;
	novo_elemento->seguinte = lista->início;
	lista->início->anterior = novo_elemento;
	lista->início = novo_elemento;
	lista->tamanho++;
	return 0;
}

int ins_fim_lista(Lista * lista, void* dado) {
	ListaObj *novo_elemento = Aloca(sizeof(ListaObj));
	novo_elemento = aloc(novo_elemento, dado);
	if (novo_elemento == NULL)
		return -1;
	novo_elemento->dado = dado;
	novo_elemento->seguinte = NULL;
	novo_elemento->anterior = lista->fim;
	lista->fim->seguinte = novo_elemento;
	lista->fim = novo_elemento;
	lista->tamanho++;
	return 0;
}

int ins_depois(Lista * lista, void* dado, int pos) {
	int i;
	ListaObj *novo_elemento = Aloca(sizeof(ListaObj)), *emAndamento = Aloca(sizeof(ListaObj));
	novo_elemento = aloc(novo_elemento, dado);
	if (novo_elemento == NULL)
		return -1;
	novo_elemento->dado = dado;
	emAndamento = lista->início;
	for (i = 1; i < pos; ++i)
		emAndamento = emAndamento->seguinte;
	novo_elemento->seguinte = emAndamento->seguinte;
	novo_elemento->anterior = emAndamento;
	if (emAndamento->seguinte == NULL)
		lista->fim = novo_elemento;
	else
		emAndamento->seguinte->anterior = novo_elemento;
	emAndamento->seguinte = novo_elemento;
	lista->tamanho++;
	return 0;
}

int ins_antes(Lista * lista, void* dado, int pos) {
	int i;
	ListaObj *novo_elemento = Aloca(sizeof(ListaObj)), *emAndamento = Aloca(sizeof(ListaObj));
	novo_elemento = aloc(novo_elemento, dado);
	if (novo_elemento == NULL)
		return -1;
	novo_elemento->dado = dado;
	emAndamento = lista->início;
	for (i = 1; i < pos; ++i)
		emAndamento = emAndamento->seguinte;
	novo_elemento->seguinte = emAndamento;
	novo_elemento->anterior = emAndamento->anterior;
	if (emAndamento->anterior == NULL)
		lista->início = novo_elemento;
	else
		emAndamento->anterior->seguinte = novo_elemento;
	emAndamento->anterior = novo_elemento;
	lista->tamanho++;
	return 0;
}


int remov(Lista *lista, int pos) {
	int i;
	ListaObj *remov_elemento, *emAndamento;

	if (lista->tamanho == 0)
		return -1;

	if (pos == 1) { 
		remov_elemento = lista->início;
		lista->início = lista->início->seguinte;
		if (lista->início == NULL)
			lista->fim = NULL;
		else
			lista->início->anterior == NULL;
	}
	else if (pos == lista->tamanho) { 
		remov_elemento = lista->fim;
		lista->fim->anterior->seguinte = NULL;
		lista->fim = lista->fim->anterior;
	}
	else { 
		emAndamento = lista->início;
		for (i = 1; i<pos; ++i)
			emAndamento = emAndamento->seguinte;
		remov_elemento = emAndamento;
		emAndamento->anterior->seguinte = emAndamento->seguinte;
		emAndamento->seguinte->anterior = emAndamento->anterior;
	}
	Libera(remov_elemento->dado);
	Libera(remov_elemento);
	lista->tamanho--;
	return 0;
}

void ShowList(Lista *lista) { 
	ListaObj *emAndamento;
	emAndamento = lista->início; 
	printf("[ ");
	while (emAndamento != NULL) {
		printf("%d ", emAndamento->dado);
		emAndamento = emAndamento->seguinte;
	}
	printf("]\n");
}

void ShowList_Inv(Lista *lista) { 
	ListaObj *emAndamento;
	emAndamento = lista->fim; 
	printf("[ ");
	while (emAndamento != NULL) {
		printf("%d : ", emAndamento->dado);
		emAndamento = emAndamento->anterior;
	}
	printf("]\n");
}

void destruir(Lista *lista) {
	while (lista->tamanho > 0)
		remov(lista, 1);
}
