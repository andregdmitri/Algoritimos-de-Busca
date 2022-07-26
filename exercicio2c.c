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

typedef struct no_ NO;

typedef struct no_
{
    string item;
    NO *proximo;
} NO;

typedef struct lista_
{
    NO *inicio;
    NO *fim;
    int tamanho;
} LISTA;

LISTA *lista_criar(void);
bool lista_inserir(LISTA *lista, string elemento);
bool lista_vazia(LISTA *lista);
void lista_apagar(LISTA **ptr);
bool lista_busca(LISTA *lista, string elemento);

LISTA *lista_criar(void)
{
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA *));
    if (lista != NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return (lista);
}

bool lista_inserir(LISTA *lista, string elemento)
{
    if (lista != NULL)
    {
        NO *pnovo = (NO *)malloc(sizeof(NO));
        if (lista->inicio == NULL)
        { // Se for o primeiro NO
            lista->inicio = pnovo;
            pnovo->item = malloc(sizeof(char) * MAX_STRING_LEN);
            strcpy(pnovo->item, elemento);
            pnovo->proximo = NULL;
        }
        else
        { // Se nao for o primeiro NO da lista
            lista->fim->proximo = pnovo;
            pnovo->item = malloc(sizeof(char) * MAX_STRING_LEN);
            strcpy(pnovo->item, elemento);
            pnovo->proximo = NULL;
        }
        lista->fim = pnovo;
        lista->tamanho++;
        return TRUE;
    }
    else
        return FALSE;
}

bool lista_vazia(LISTA *lista)
{
    if ((lista != NULL) && lista->inicio == NULL)
        return (TRUE);
    return (FALSE);
}

void lista_esvazia(NO *ptr)
{
    if (ptr != NULL)
    {
        if (ptr->proximo != NULL)
            lista_esvazia(ptr->proximo);
        free(ptr);
    }
}

void lista_apagar(LISTA **ptr)
{
    if (*ptr == NULL)
        return;
    lista_esvazia((*ptr)->inicio);
    free(*ptr);
    *ptr = NULL;
}

bool lista_busca(LISTA *lista, string elemento)
{
    NO *p;
    if (lista != NULL)
    {
        p = lista->inicio;
        while (p != NULL)
        {
            // Se dado encontrado retorna verdadeiro
            if (strcmp(p->item, elemento) == 0)
                return TRUE;
            p = p->proximo;
        }
    }
    // nao encontrado
    return FALSE;
}

unsigned h_div(unsigned x, unsigned B)
{
    return x % B;
}

unsigned h_mul(unsigned x, unsigned B)
{
    const double A = 0.6180;
    return fmod(x * A, 1) * B;
}

bool inserir_div(LISTA **tabela, string elemento, unsigned B, unsigned *colisoes)
{
    int i, posicao, conversao;
    conversao = converter(elemento);
    posicao = h_div(conversao, B);
    if (!lista_vazia(tabela[posicao])) // Lista nao vazia entao tem Colisao
        (*colisoes)++;
    return lista_inserir(tabela[posicao], elemento);
}

bool inserir_mul(LISTA **tabela, string elemento, unsigned B, unsigned *colisoes)
{
    int i, posicao, conversao;
    conversao = converter(elemento);
    posicao = h_mul(conversao, B);
    if (!lista_vazia(tabela[posicao])) // Lista nao vazia entao tem Colisao
        (*colisoes)++;
    return lista_inserir(tabela[posicao], elemento);
}

bool busca_div(LISTA **tabela, string elemento, unsigned B)
{
    int i, posicao, conversao;
    conversao = converter(elemento);
    posicao = h_div(conversao, B);
    return lista_busca(tabela[posicao], elemento);
}

bool busca_mul(LISTA **tabela, string elemento, unsigned B)
{
    int i, posicao, conversao;
    conversao = converter(elemento);
    posicao = h_mul(conversao, B);
    return lista_busca(tabela[posicao], elemento);
}

int main(int argc, char const *argv[])
{
    int i;
    const int N = 50000;
    const int M = 70000;
    const int B = 150001;

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;

    string *insercoes = ler_strings("strings_entrada.txt", N);
    string *consultas = ler_strings("strings_busca.txt", M);

    // cria tabela hash com hash por divisão
    LISTA **tabela_div = (LISTA **)malloc(B * sizeof(LISTA));
    for (i = 0; i < B; i++)
        tabela_div[i] = lista_criar();

    // inserção dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (i = 0; i < N; i++)
    {
        // inserir insercoes[i] na tabela hash
        inserir_div(tabela_div, insercoes[i], B, &colisoes_h_div);
    }
    double tempo_insercao_h_div = finaliza_tempo();

    // busca dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (i = 0; i < M; i++)
    {
        // buscar consultas[i] na tabela hash
        if (busca_div(tabela_div, consultas[i], B))
            encontrados_h_div++;
    }
    double tempo_busca_h_div = finaliza_tempo();

    // destroi tabela hash com hash por divisão
    for (i = 0; i < B; i++)
        free(tabela_div[i]);
    free(tabela_div);

    // cria tabela hash com hash por multiplicação
    LISTA **tabela_mul = (LISTA **)malloc(B * sizeof(LISTA));
    for (i = 0; i < B; i++)
        tabela_mul[i] = lista_criar();

    // inserção dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++)
    {
        // inserir insercoes[i] na tabela hash
        inserir_div(tabela_mul, insercoes[i], B, &colisoes_h_mul);
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++)
    {
        // buscar consultas[i] na tabela hash
        if (busca_div(tabela_mul, consultas[i], B))
            encontrados_h_mul++;
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // destroi tabela hash com hash por multiplicação
    for (i = 0; i < B; i++)
        free(tabela_mul[i]);
    free(tabela_mul);

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
