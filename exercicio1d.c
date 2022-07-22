#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
unsigned char typedef bool;
#define TRUE  1
#define FALSE 0

int* ler_inteiros(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");

    int* inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        fscanf(f, "%d\n", &inteiros[i]);

    fclose(f);

    return inteiros;
}

void inicia_tempo()
{
    srand(time(NULL));
    _ini = clock();
}

double finaliza_tempo()
{
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}

void merge_sort(int* entradas, int inicio, int fim) {
    int i, j, k, meio = (ini+fim)/2;
    int aux[ini+fim+1]

    //Condicao de parada
    if (inicio = fim)
        return;

    //Divisao do vetor
    merge_sort(entradas, ini, meio);
    merge_sort(entradas, meio+1, fim);

    //Ordenacao
    i = inicio;
    j = meio+1;
    k = 0;
    while(i <= meio && j <= fim) {
        if (entradas[i] < entradas[j]) {
            aux[k] = entradas[i];
            i++;
        }
        else {
            aux[k] = entradas[j];
            j++;
        }
        k++;
    }

    while(i <= meio) {
        aux[k] = entradas[i];
        i++;
        k++;
    }
    while(j <= fim) {
        aux[k] = entradas[j];
        j++;
        k++;
    }

    for (i = inicio; i <= fim; i++)
        entradas[i] = aux[i];
}

int main(int argc, char const *argv[])
{
    int i;
    const int N = 50000;
    const int S = 10000;
    const int T = N/S;
    const int index_size = 10000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);
    
    // ordenar entrada
    merge_sort(entradas, 0, N-1);

    // criar tabela de indice
    int* tabela = malloc(T * sizeof(int*));
    for (i = 0; i < T; i += 10000)
        tabela = &entradas[i];

    // realizar consultas na tabela de indices 
    inicia_tempo();
    for (i = 0; i < N; i++) {
        // buscar o elemento consultas[i] na entrada
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}
