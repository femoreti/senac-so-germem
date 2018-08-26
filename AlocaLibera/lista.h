typedef struct dl_elementoLista {
	void *dado;
	struct dl_elementoLista *anterior;
	struct dl_elementoLista *seguinte;
} ListaObj;

typedef struct dl_ListaDetectada {
	ListaObj *inicio;
	ListaObj *fim;
	int tamanho;
} Lista;

void initList(Lista *lista);
ListaObj *aloc(ListaObj *novo_elemento, void* dado);

int ins_na_lista_vazia(Lista * lista, void* dado);

int ins_inicio_lista(Lista * lista, void* dado);

int ins_fim_lista(Lista * lista, void* dado);

int ins_depois(Lista * lista, void* dado, int pos);

int ins_antes(Lista * lista, void* dado, int pos);


int remov(Lista *lista, int pos);

void ShowList(Lista *lista);

void ShowList_Inv(Lista *lista);

void destruir(Lista *lista);
