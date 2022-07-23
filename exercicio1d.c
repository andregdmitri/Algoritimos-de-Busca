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

void merge_sort_recursivo(int* entradas, int inicio, int fim, int *copia_entradas) {
    int i, j, k, meio = (inicio+fim)/2;

    //Condicao de parada
    if (inicio == fim)
        return;

    //Divisao do vetor
    merge_sort_recursivo(entradas, inicio, meio, copia_entradas);
    merge_sort_recursivo(entradas, meio+1, fim, copia_entradas);

    //Ordenacao
    i = inicio;
    j = meio+1;
    k = inicio;
    while(i <= meio && j <= fim) {
        if (entradas[i] < entradas[j]) {
            copia_entradas[k] = entradas[i];
            i++;
        }
        else {
            copia_entradas[k] = entradas[j];
            j++;
        }
        k++;
    }

    //Coloca dados faltantes
    while(i <= meio) {
        copia_entradas[k] = entradas[i];
        i++;
        k++;
    }
    while(j <= fim) {
        copia_entradas[k] = entradas[j];
        j++;
        k++;
    }

    //Passa o vetor ordenado para entrada
    for (i = inicio; i <= fim; i++)
        entradas[i] = copia_entradas[i];
}

void merge_sort(int* entradas, int inicio, int tamanho) 
{
    int *copia_entradas = (int *) malloc(tamanho*sizeof(int));
    merge_sort_recursivo(entradas, 0, tamanho-1, copia_entradas);
    free(copia_entradas);
}

bool busca_kindex (int consulta, int* entradas, int T, int** tabela) {
    int inferior, superior;
    for(superior = 1; superior < T; superior++)
        if(consulta <= *tabela[superior]) //Percorre tabela de indices ate o achar o indice superior (maior que o valor buscado)
            break; //Percorre tabela de indices ate o achar o indice superior (maior que o valkor buscado)
    for (inferior = (superior - 1) * 10000; inferior < superior * 10000; inferior++)//Busca sequencial no intervalo entre o indice inferior e o superior
        if (consulta == entradas[inferior])
            return TRUE;
    return FALSE; //Consulta nao encontrada na Entrada
}

int main(int argc, char const *argv[])
{
    int i, j, k;
    const int N = 50000;
    const int S = 10000;
    const int T = N/S;
    const int index_size = 10000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);
    
    // ordenar entrada
    merge_sort(entradas, 0, N);

    // criar tabela de indice
    int** tabela = (int **) malloc(T * sizeof(int*));
    for (i = 10000; i <= 50000; i += 10000)
        tabela[(i-1)/10000] = &entradas[i-1];
        
    // realizar consultas na tabela de indices
    inicia_tempo();
    for (i = 0; i < N; i++) 
    {
        //buscar o elemento consultas[i] na entrada
        if (busca_kindex(consultas[i], entradas, T, tabela))
            encontrados++;
    }
    double tempo_busca = finaliza_tempo();

    printf("\nTempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}
