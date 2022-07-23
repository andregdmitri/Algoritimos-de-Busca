/* 
 * File:   item.h
 * André Guarnier De Mitri - 11395579
 * Rui Emanuel Lima Vieira - 11810182
 * 
 */

#ifndef LISTA_H

	#define LISTA_H
    #define TRUE 1
    #define FALSE 0
    #define boolean int
    #define inicial 0
    #define ERRO -32000
    typedef struct lista_ LISTA;

    #include "item.h"

    LISTA *lista_criar(void);
    boolean lista_inserir_fim(LISTA *lista, ITEM *i);
    void lista_apagar(LISTA **ptr);
    int lista_busca(LISTA *lista, int cidade_A, int cidade_B); //Se as cidades A e B se conectam, retorna sua distancia. Caso contrário, retorna -1
    boolean lista_vazia(LISTA *lista);
    boolean lista_remover_item(LISTA *lista, int chave);

#endif