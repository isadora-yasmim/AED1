#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "ArvoreAVL.h"
#include "Fila.h"


// Verifica se uma string esta vazia ou contem apenas espacos
int ehStringVazia(const char *str) {
    if(str == NULL) return 1;
    
    while(*str) {
        if(!isspace((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

// Comparacao case-insensitive entre strings
int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if (diff != 0) return diff;
        s1++; s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

// Comparacao case-insensitive entre os primeiros n caracteres de strings
int strncasecmp(const char *s1, const char *s2, size_t n) {
    if (n == 0) return 0;
    while (n-- && *s1 && *s2) {
        int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if (diff != 0) return diff;
        s1++; s2++;
    }
    return 0;
}

// Cria uma arvore AVL vazia
ArvAVL* cria_ArvAVL() {
    ArvAVL* raiz = (ArvAVL*)malloc(sizeof(ArvAVL));
    if(raiz == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memoria para a arvore.\n");
        return NULL;
    }
    *raiz = NULL;
    return raiz;
}

// Libera a memoria de um no e seus descendentes
void libera_NO(struct NO* no) {
    if(no == NULL) return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    if(no->info != NULL) free(no->info);
    free(no);
}

// Libera a memoria de toda a arvore
void libera_ArvAVL(ArvAVL* raiz) {
    if(raiz == NULL) return;
    libera_NO(*raiz);
    free(raiz);
}

// Retorna a altura de um no
int altura_NO(struct NO* no) {
    if(no == NULL) return -1;
    return no->altura;
}

// Calcula o fator de balanceamento de um no
int fatorBalanceamento_NO(struct NO* no) {
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

// Retorna o maior entre dois numeros
int maior(int x, int y) {
    return (x > y) ? x : y;
}

// Rotacao simples a esquerda (LL)
void RotacaoLL(ArvAVL *A) {
    struct NO *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

// Rotacao simples a direita (RR)
void RotacaoRR(ArvAVL *A) {
    struct NO *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

// Rotacao dupla esquerda-direita (LR)
void RotacaoLR(ArvAVL *A) {
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

// Rotacao dupla direita-esquerda (RL)
void RotacaoRL(ArvAVL *A) {
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

// Insere um novo valor na arvore AVL
int insere_ArvAVL(ArvAVL *raiz, char *valor) {
    if(raiz == NULL) {
        fprintf(stderr, "Erro: Ponteiro de arvore invalido.\n");
        return 0;
    }

    if(valor == NULL || ehStringVazia(valor)) {
        fprintf(stderr, "Erro: Tentativa de inserir palavra vazia ou nula.\n");
        return 0;
    }

    // Se a arvore estiver vazia, cria um novo no
    if(*raiz == NULL) {
        struct NO *novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL) {
            fprintf(stderr, "Erro: Falha ao alocar novo no.\n");
            return 0;
        }

        novo->info = strdup(valor);
        if(novo->info == NULL) {
            free(novo);
            fprintf(stderr, "Erro: Falha ao alocar memoria para a palavra.\n");
            return 0;
        }

        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    int cmp = strcasecmp(valor, atual->info);
    
    // Insere na subarvore esquerda
    if(cmp < 0) {
        if(insere_ArvAVL(&(atual->esq), valor)) {
            if(fatorBalanceamento_NO(atual) >= 2) {
                if(strcasecmp(valor, (*raiz)->esq->info) < 0)
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    } 
    // Insere na subarvore direita
    else if(cmp > 0) {
        if(insere_ArvAVL(&(atual->dir), valor)) {
            if(fatorBalanceamento_NO(atual) >= 2) {
                if(strcasecmp((*raiz)->dir->info, valor) < 0)
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    } else {
        return 0; // Palavra duplicada
    }

    // Atualiza a altura do no atual
    atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;
    return 1;
}

// Encontra o primeiro no que comeca com o prefixo especificado
struct NO* encontraNoComPrefixo(struct NO* no, const char* prefixo) {
    if (no == NULL) return NULL;
    
    int cmp = strncasecmp(prefixo, no->info, strlen(prefixo));
    
    if (cmp < 0) {
        return encontraNoComPrefixo(no->esq, prefixo);
    } else if (cmp > 0) {
        return encontraNoComPrefixo(no->dir, prefixo);
    } else {
        return no;
    }
}

// Lista todas as palavras que comecam com o prefixo especificado
void listaPalavrasComPrefixo(struct NO* no, const char* prefixo, int *encontrou) {
    if (no == NULL) return;
    
    // Primeiro verifica a subarvore esquerda (ordem alfabetica)
    listaPalavrasComPrefixo(no->esq, prefixo, encontrou);
    
    // Verifica se o no atual comeca com o prefixo
    if (strncasecmp(prefixo, no->info, strlen(prefixo)) == 0) {
        printf("%s\n", no->info);
        *encontrou = 1;
    } else {
        // Se nao comecar mais com o prefixo, podemos parar (arvore ordenada)
        return;
    }
    
    // Continua na subarvore direita
    listaPalavrasComPrefixo(no->dir, prefixo, encontrou);
}

// Funcao de autocompletar que busca palavras com o prefixo especificado
void autocomplete(ArvAVL *raiz, char prefixo[]) {
    if(raiz == NULL || *raiz == NULL) {
        printf("Erro: Dicionario nao inicializado ou vazio\n");
        return;
    }

    if(prefixo == NULL || ehStringVazia(prefixo)) {
        printf("Erro: Prefixo invalido (vazio ou apenas espacos)\n");
        return;
    }

    int encontrou = 0;
    printf("Sugestoes para '%s':\n", prefixo);
    
    // Encontra o primeiro no com o prefixo (O(log n))
    struct NO* no = encontraNoComPrefixo(*raiz, prefixo);
    
    // Lista palavras a partir desse no (O(k))
    if (no != NULL) {
        listaPalavrasComPrefixo(no, prefixo, &encontrou);
    }
    
    if(!encontrou) {
        printf("Nenhuma sugestao encontrada.\n");
    }
}

// Carrega varias palavras na arvore a partir de um array
void carregaVocabulario(ArvAVL *raiz, char *dados[], int n) {
    if(raiz == NULL || dados == NULL || n <= 0) {
        fprintf(stderr, "Erro: Parametros invalidos para carregamento.\n");
        return;
    }
	int i;
    for(i = 0; i < n; i++) {
        if(dados[i] != NULL && !ehStringVazia(dados[i])) {
            insere_ArvAVL(raiz, dados[i]);
        }
    }
}
