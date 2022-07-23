  #include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "lista.h"

typedef struct no_ NO;

struct no_{
	int *item;
	NO *proximo;
}; 

struct lista_{ 
	NO *inicio;
	NO *fim;
	int tamanho;
};

LISTA *lista_criar(void){ 
	LISTA *lista = (LISTA*) malloc(sizeof(LISTA*));
	if (lista !=NULL){ 
		lista->inicio = NULL;
		lista->fim = NULL;
		lista->tamanho = 0;
	}
	return(lista);
}

boolean lista_inserir(LISTA *lista, unsigned elemento){
	if (lista != NULL) {
		NO *pnovo = (NO *) malloc(sizeof (NO));
		if (lista->inicio == NULL){
			lista->inicio = pnovo;
			pnovo->item = elemento;
			pnovo->proximo = NULL;
		}
		else {
			lista->fim->proximo = pnovo;
			pnovo->item = elemento;
			pnovo->proximo = NULL;
		}
		lista->fim = pnovo;
		lista->tamanho++;
		return (TRUE);
	}
	else 
		return(FALSE);
}

void lista_esvazia(NO *ptr){ 
	if (ptr != NULL){
		if(ptr->proximo != NULL)
			lista_esvazia(ptr->proximo);
		item_apagar(&ptr->item);
		free(ptr);
		ptr = NULL;
	}
}

void lista_apagar(LISTA **ptr){
	if (*ptr == NULL)
		return;
	lista_esvazia((*ptr)->inicio);
	free(*ptr);
	*ptr = NULL;
}

bool lista_busca(LISTA *lista, unsigned elemento){ 
	NO *p;
	if (lista != NULL){
		p = lista->inicio;
		while (p != NULL) {
			//Se dado encontrado retorna verdadeiro
			if (l->item == elemento)
				return TRUE; 
			p = p->proximo;
		}
	}
	//nao encontrado
	return FALSE;
}

boolean lista_vazia(LISTA *lista){
	if((lista != NULL) && lista->inicio == NULL)
		return (TRUE);
	return (FALSE);
}

boolean lista_remover_item(LISTA *lista, unsigned elemento) {
	if (lista != NULL){
		NO *p = lista->inicio; NO *aux = NULL;
		while(p != NULL && p->item != elemento){/*procura até achar chave ou fim lista*/
			aux = p; /*aux - guarda posição anterior ao nó sendo pesquisado (p)*/
			p = p->proximo;
		}
		if(p != NULL) {
			if(p == lista->inicio) { /*se a chave está no 1o nó (Exceção a ser tratada!)*/
				lista->inicio = p->proximo;
				p->proximo = NULL;
			}
			else {
				aux->proximo = p->proximo;
				p->proximo = NULL;
			}
			if(p == lista->fim) /*se chave está no último nó*/
				lista->fim = aux;
			lista->tamanho--; free(p); return (TRUE);
		}
	}
	return (FALSE);
}