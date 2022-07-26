#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

// Definição do tipo string
typedef char *string;

#define MAX_STRING_LEN 20

unsigned converter(string s)
{
    unsigned h = 0;
    for (int i = 0; s[i] != '\0'; i++)
        h = h * 256 + s[i];
    return h;
}

string *ler_strings(const char *arquivo, const int n)
{
    FILE *f = fopen(arquivo, "r");

    string *strings = (string *)malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++)
    {
        strings[i] = (string)malloc(sizeof(char) * MAX_STRING_LEN);
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
    return ((double)(_fim - _ini)) / CLOCKS_PER_SEC;
}

unsigned h_div(unsigned x, unsigned i, unsigned B)
{
    return ((x % B) + i) % B;
}

unsigned h_mul(unsigned x, unsigned i, unsigned B)
{
    const double A = 0.6180;
    return ((int)((fmod(x * A, 1) * B) + i)) % B;
}

unsigned hash_duplo(unsigned x, unsigned i, unsigned B)
{
    unsigned hx = (h_mul(x, i, B) + (i * h_div(x, i, B))) % B;
    return hx;
}

bool inserir(string *tabela, string elemento, unsigned B, unsigned *colisoes)
{
    int i, posicao, conversao;
    conversao = converter(elemento);
    for (i = 0; i < B; i++)
    {
        posicao = hash_duplo(conversao, i, B);
        if (tabela[posicao] == NULL)
        { // Insere se a posicao estiver disponivel
            tabela[posicao] = malloc(sizeof(char) * MAX_STRING_LEN);
            strcpy(tabela[posicao], elemento);
            return TRUE;
        }
        (*colisoes)++; // Cada vez que nao der para inserir eh uma colisao
    }
    // tabela cheia
    return FALSE;
}

bool buscar(string *tabela, string elemento, unsigned B)
{
    int i, posicao, conversao;
    conversao = converter(elemento);
    for (i = 0; i < B; i++)
    {
        posicao = hash_duplo(conversao, i, B);
        // Se nulo, o elemento nao foi armazenado
        if (tabela[posicao] == NULL)
            return FALSE;
        // Se o elemento estiver na posicao fornecida ou nas proximas, sucesso
        if (strcmp(tabela[posicao], elemento) == 0)
            return TRUE;
    }
    // Elemento nao encontrado na tabela
    return FALSE;
}

int main(int argc, char const *argv[])
{
    int i;
    const int N = 50000;
    const int M = 70000;
    const int B = 150001;

    unsigned colisoes = 0;
    unsigned encontrados = 0;

    string *insercoes = ler_strings("strings_entrada.txt", N);
    string *consultas = ler_strings("strings_busca.txt", M);

    // cria tabela hash com hash por hash duplo
    string *tabela = (string *)calloc(sizeof(string), B);

    // inserção dos dados na tabela hash
    inicia_tempo();
    for (i = 0; i < N; i++)
    {
        // inserir insercoes[i] na tabela hash
        inserir(tabela, insercoes[i], B, &colisoes);
    }
    double tempo_insercao = finaliza_tempo();

    // busca dos dados na tabela hash
    inicia_tempo();
    for (i = 0; i < M; i++)
    {
        // buscar consultas[i] na tabela hash
        if (buscar(tabela, consultas[i], B))
            encontrados++;
    }
    double tempo_busca = finaliza_tempo();

    // limpa a tabela hash
    for (i = 0; i < B; i++)
        free(tabela[i]);
    free(tabela);

    printf("Colisões na inserção: %d\n", colisoes);
    printf("Tempo de inserção   : %fs\n", tempo_insercao);
    printf("Tempo de busca      : %fs\n", tempo_busca);
    printf("Itens encontrados   : %d\n", encontrados);

    // Liberando memoria
    free(insercoes);
    free(consultas);

    return 0;
}
