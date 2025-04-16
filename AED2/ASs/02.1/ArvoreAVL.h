#ifndef ARVOREAVL_H
#define ARVOREAVL_H

// Definicao da estrutura da arvore AVL
typedef struct NO* ArvAVL;

// Estrutura de no da arvore AVL
struct NO {
    char *info;         // Ponteiro para a string armazenada no no
    int altura;         // Altura do no na arvore
    struct NO *esq;     // Ponteiro para o filho esquerdo
    struct NO *dir;     // Ponteiro para o filho direito
};

// Prototipos das funcoes
ArvAVL* cria_ArvAVL();  // Cria uma arvore AVL vazia
void libera_ArvAVL(ArvAVL* raiz);  // Libera a memoria da arvore
int insere_ArvAVL(ArvAVL *raiz, char *valor);  // Insere um novo valor na arvore
void autocomplete(ArvAVL *raiz, char prefixo[]);  // Busca palavras com determinado prefixo
void carregaVocabulario(ArvAVL *raiz, char *dados[], int n);  // Carrega varias palavras na arvore
int ehStringVazia(const char *str);  // Verifica se uma string esta vazia ou contem apenas espacos

// Funcoes auxiliares para autocompletar
void listaPalavrasComPrefixo(struct NO* no, const char* prefixo, int *encontrou);  // Lista palavras com prefixo
struct NO* encontraNoComPrefixo(struct NO* no, const char* prefixo);  // Encontra no com determinado prefixo

#endif
