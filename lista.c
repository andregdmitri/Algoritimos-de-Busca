  #include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "lista.h"

typedef struct no_ NO;

struct no_{
	ITEM *item;
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

boolean lista_inserir_fim(LISTA *lista, ITEM *item){
	if (lista != NULL) {
		NO *pnovo = (NO *) malloc(sizeof (NO));
		if (lista->inicio == NULL){
			pnovo->item = item;
			lista->inicio = pnovo;
			pnovo->proximo = NULL;
		}
		else {
			lista->fim->proximo = pnovo;
			pnovo->item = item;
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

//Se as cidades A e B se conectam, retorna sua distancia. Caso contrário, retorna -1
int lista_busca(LISTA *lista, int cidade_A, int cidade_B){ 
	NO *p;
	if (lista != NULL){
		p = lista->inicio;
		while (p != NULL) {
			//Se A e B se conectam, retorna sua distancia, caso contrario, retornara -1 no return a abaixo.
			if ((item_get_cidade_A(p->item) == cidade_A && item_get_cidade_B(p->item) == cidade_B) || (item_get_cidade_A(p->item) == cidade_B && item_get_cidade_B(p->item) == cidade_A))
				return (item_get_distancia(p->item)); 
			p = p->proximo;
		}
	}
	//A e B nao se conectam
	return(-1);
}

boolean lista_vazia(LISTA *lista){
	if((lista != NULL) && lista->inicio == NULL)
		return (TRUE);
	return (FALSE);
}

boolean lista_remover_item(LISTA *lista, int chave) {
	if (lista != NULL){
		NO *p = lista->inicio; NO *aux = NULL;
		while(p != NULL && (item_get_chave(p->item)) != chave){/*procura até achar chave ou fim lista*/
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