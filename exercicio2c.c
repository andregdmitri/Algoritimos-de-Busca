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

unsigned h_div(unsigned x, unsigned B)
{
    return x % B;
}

unsigned h_mul(unsigned x, unsigned B)
{
    const double A = 0.6180;
    return fmod(x * A, 1) * B;
}

bool inserir_div(int* tabela, unsigned elemento, unsigned B) {
    int i, posicao, elem;
    elem = converter(elemento);
    posicao = h_div(elem, B);
    lista_inserir(tabela[posicao], elem);
}

bool inserir_mul(int* tabela, unsigned elemento, unsigned B) {
    int i, posicao, elem;
    elem = converter(elemento);
    posicao = h_mul(elem, B);
    lista_inserir(tabela[posicao], elem);
}

bool busca_div (int* tabela, string elemento, unsigned B) {
    int i, posicao, elem;
    elem = converter(elemento);
    posicao = h_div(elem, B);
    lista_buscar(tabela[posicao], elem);
}

bool busca_mul (int* tabela, string elemento, unsigned B) {
    int i, posicao, elem;
    elem = converter(elemento);
    posicao = h_mul(elem, B);
    lista_buscar(tabela[posicao], elem);
}

typedef struct {
    int dado;
    NO* prox;
} NO;

typedef struct {
    int dado;
    int tamanho;
    NO* inicio;
    NO* fim;
} lista;

lista *lista_criar(void){ 
	lista *l = (lista*) malloc(sizeof(lista*));
	if (l !=NULL){ 
		l->inicio = NULL;
		l->tamanho = 0;
        l->dado = -1; //Dado valido para ser substituido
	}
	return(l);
}

void lista_inserir(lista *l, int dado){
    NO *pnovo = (NO *) malloc(sizeof (NO));
    if (l->inicio == NULL)
        l->inicio = pnovo; //Caso seja inicio da lista
    else
        pnovo->prox = NULL; //Caso nao seja inicio da lista
    pnovo->dado = dado;
    pnovo->prox = NULL;
    l->fim = pnovo;
    l->tamanho++;
}

void lista_esvazia(NO *ptr){ 
	if (ptr != NULL){
		if(ptr->prox != NULL)
			lista_esvazia(ptr->prox);
		item_apagar(&ptr->dado);
		free(ptr);
		ptr = NULL;
	}
}

void lista_apagar(lista **ptr){
	if (*ptr == NULL)
		return;
	lista_esvazia((*ptr)->inicio);
	free(*ptr);
	*ptr = NULL;
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

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);
    

    // cria tabela hash com hash por divisão
    int* tabela_div = (int*) malloc(B * sizeof(int));
    for (i = 0; i < B; i++)
        tabela_div[i] = -1;

    // inserção dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
    }
    double tempo_insercao_h_div = finaliza_tempo();

    // busca dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
    }
    double tempo_busca_h_div = finaliza_tempo();

    // destroi tabela hash com hash por divisão
    free(tabela_div);



    // cria tabela hash com hash por multiplicação

    // inserção dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // destroi tabela hash com hash por multiplicação



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
