/* 
 * File:   item.h
 * André Guarnier De Mitri - 11395579
 * Rui Emanuel Lima Vieira - 11810182
 * 
 */

#ifndef LISTA_H

	#define LISTA_H
    typedef unsigned char bool;
    #define TRUE  1
    #define FALSE 0
    typedef struct lista_ LISTA;

    LISTA *lista_criar(void);
    bool lista_inserir(LISTA *lista, unsigned elemento);
    void lista_destruir(LISTA **ptr);
    bool lista_busca(LISTA *lista, unsigned elemento);
    bool lista_vazia(LISTA *lista);
    bool lista_remover_item(LISTA *lista, unsigned elemento);

#endif