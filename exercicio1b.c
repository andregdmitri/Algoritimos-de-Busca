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

    int * inteiros = (int *) malloc(sizeof(int) * n);

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

int main(int argc, char const *argv[])
{
    int i, j, m, numero_encontrado;
    const int N = 50000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);

    // realiza busca sequencia com realocação usando o MOVE-FOWARD
    inicia_tempo();
    for (i = 0; i < N; i++) {
        // buscar o elemento consultas[i] na entrada
        for (j = 0; j < N; j++) {
            if (entradas[i] == consultas[j]) {
                encontrados++;
                numero_encontrado = entradas[i]; //Guarda o numero encontado na busca
                for(m = i; m > 0; m--)
                    entradas[m] = entradas[m-1]; //Move todo vetor para frente, do inicio ate o numero encontrado
                entradas[0] = numero_encontrado;//O numero encontrado na busca ocupa Inicio do vetor
            }
        }
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}
