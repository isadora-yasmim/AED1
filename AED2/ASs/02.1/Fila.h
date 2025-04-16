#ifndef FILA_H
#define FILA_H

#define MAX 500

// Estrutura de um elemento da fila
struct elemento {
    struct NO *dados;       // Ponteiro para um no da arvore
    struct elemento *prox;  // Ponteiro para o proximo elemento
};

typedef struct elemento Elem;

// Estrutura da fila
struct fila {
    struct elemento *inicio;  // Ponteiro para o inicio da fila
    struct elemento *final;   // Ponteiro para o final da fila
    int qtd;                  // Quantidade de elementos na fila
};

typedef struct fila Fila;

// Prototipos das funcoes
Fila* cria_Fila();                      // Cria uma fila vazia
void libera_Fila(Fila* fi);             // Libera a memoria da fila
int Fila_vazia(Fila* fi);               // Verifica se a fila esta vazia
int insere_Fila(Fila* fi, struct NO *al);  // Insere um elemento na fila
int remove_Fila(Fila* fi);              // Remove um elemento da fila
int consulta_Fila(Fila* fi, struct NO **al);  // Consulta o primeiro elemento da fila

#endif
