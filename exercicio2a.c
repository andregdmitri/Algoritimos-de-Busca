#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

// Definição do tipo string
typedef char * string;

#define MAX_STRING_LEN 20


unsigned converter(string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = h * 256 + s[i];
   return h;
}

string* ler_strings(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");
    
    string* strings = (string *) malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++) {
        strings[i] = (string) malloc(sizeof(char) * MAX_STRING_LEN);
        fscanf(f, "%s\n", strings[i]);
    }

    fclose(f);

    return strings;
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

unsigned h_div(unsigned x, unsigned i, unsigned B)
{
    return ((x % B) + i) % B;
}

unsigned h_mul(unsigned x, unsigned i, unsigned B)
{
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}

bool inserir_div(int* tabela, unsigned elemento, unsigned B) {
    int i, posicao;
    for (i = 0; i < B; i++) {
        posicao = h_div(elemento, i, B);
        if (tabela[posicao] == -1) { //Insere se a posicao estiver disponivel
            tabela[posicao] = elemento;
            return TRUE;
        }
    }
    // tabela cheia
    return FALSE;
}

bool inserir_mul(int* tabela, unsigned elemento, unsigned B) {
    int i, posicao;
    for (i = 0; i < B; i++) {
        posicao = h_mul(elemento, i, B);
        if (tabela[posicao] == -1) { //Insere se a posicao estiver disponivel
            tabela[posicao] = elemento;
            return TRUE;
        }
    }
    // tabela cheia
    return FALSE;
}

bool busca_div (int* tabela, unsigned elemento, unsigned B) {
    int i, posicao;
    for (i = 0; i < B; i++) {
        posicao = h_div(elemento, i, B);
        // Se o elemento estiver na posicao fornecida ou nas proximas, sucesso
        if (tabela[posicao] == elemento)
            return TRUE;
    }
    // Elemento nao encontrado na tabela
    return FALSE;
}

bool busca_mul (int* tabela, unsigned elemento, unsigned B) {
    int i, posicao;
    for (i = 0; i < B; i++) {
        posicao = h_mul(elemento, i, B);
        // Se o elemento estiver na posicao fornecida ou nas proximas, sucesso
        if (tabela[posicao] == elemento)
            return TRUE;
    }
    // Elemento nao encontrado na tabela
    return FALSE;
}

int main(int argc, char const *argv[])
{
    int i;
    unsigned N = 50000;
    unsigned M = 70000;
    unsigned B = 150001;

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);


    // cria tabela hash com hash por divisão
    int* tabela_div = (int*) malloc(B * sizeof(int));
    for (i = 0; i < B; i++)
        tabela_div[i] = -1;
    
    // inserção dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        inserir_div(tabela_div, converter(insercoes[i]), B);
    }
    double tempo_insercao_h_div = finaliza_tempo();

    // consulta dos dados na tabela hash usando hash por divisãos
    inicia_tempo();
    for (i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        if (busca_div(tabela_div, converter(consultas[i]), B) == TRUE)
            encontrados_h_div++;
    }
    double tempo_busca_h_div = finaliza_tempo();

    // limpa a tabela hash com hash por divisão
    for (i = 0; i < B; i++)
        tabela_div[i] = -1;


//******************************* Hash por MULTIPLICACAO *******************************
    // cria tabela hash com hash por multiplicação
    int* tabela_mul = (int*) malloc(B * sizeof(int));
    for (i = 0; i < B; i++)
        tabela_mul[i] = -1;

    // inserção dos dados na tabela hash usando hash por multiplicação
    inicia_tempo();
    for (i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        inserir_mul(tabela_mul, converter(insercoes[i]), B);
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
         if (busca_mul(tabela_mul, converter(consultas[i]), B) == TRUE)
            encontrados_h_mul++;
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // limpa a tabela hash com hash por multiplicação
    for (i = 0; i < B; i++)
        tabela_mul[i] = -1;

    printf("Hash por Divisão\n");
    printf("Colisões na inserção: %d\n", colisoes_h_div);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_div);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
    printf("Itens encontrados   : %d\n", encontrados_h_div);
    printf("\n");
    printf("Hash por Multiplicação\n");
    printf("Colisões na inserção: %d\n", colisoes_h_mul);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_mul);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
    printf("Itens encontrados   : %d\n", encontrados_h_mul);

    return 0;
}
