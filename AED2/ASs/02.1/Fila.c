#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

// Cria uma fila vazia
Fila* cria_Fila() {
    Fila *fi = (Fila*) malloc(sizeof(struct fila));
    if(fi != NULL) {
        fi->inicio = NULL;
        fi->final = NULL;
        fi->qtd = 0;
    }
    return fi;
}

// Libera a memoria da fila
void libera_Fila(Fila* fi) {
    if(fi != NULL) {
        Elem *no;
        while(fi->inicio != NULL) {
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

// Verifica se a fila esta vazia
int Fila_vazia(Fila* fi) {
    if(fi == NULL) return 1;
    if(fi->inicio == NULL) return 1;
    return 0;
}

// Insere um elemento no final da fila
int insere_Fila(Fila* fi, struct NO *al) {
    if(fi == NULL) return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    
    no->dados = al;
    no->prox = NULL;
    
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
        
    fi->final = no;
    fi->qtd++;
    return 1;
}

// Remove um elemento do inicio da fila
int remove_Fila(Fila* fi) {
    if(fi == NULL) return 0;
    if(fi->inicio == NULL) return 0;
    
    Elem *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

// Consulta o elemento no inicio da fila
int consulta_Fila(Fila* fi, struct NO **al) {
    if(fi == NULL) return 0;
    if(fi->inicio == NULL) return 0;
    *al = fi->inicio->dados;
    return 1;
}
