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

    #include "item.h"

    LISTA *lista_criar(void);
    boolean lista_inserir(LISTA *lista, unsigned elemento);
    void lista_destruir(LISTA **ptr);
    boolean lista_busca(LISTA *lista, unsigned elemento);
    boolean lista_vazia(LISTA *lista);
    boolean lista_remover_item(LISTA *lista, unsigned elemento);

#endif