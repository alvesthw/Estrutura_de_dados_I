#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó
typedef struct no {
    int valor;
    struct no* proximo;
} No;

// Estrutura da Lista
typedef struct lista {
    No* cabeca;
    No* calda;
} Lista;

// Função para criar um nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

// Função para adicionar nó ao final da lista
void adicionarNo(Lista* lista, int valor) {
    No* novo = criarNo(valor);
    if (lista->cabeca == NULL) {
        lista->cabeca = novo;
        lista->calda = novo;
    } else {
        lista->calda->proximo = novo;
        lista->calda = novo;
    }
}

// Função para percorrer a lista
void imprimirLista(Lista* lista) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// Função para liberar memória
void liberarLista(Lista* lista) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        No* tmp = atual;
        atual = atual->proximo;
        free(tmp);
    }
    lista->cabeca = NULL;
    lista->calda = NULL;
}

int main() {
    Lista lista = {NULL, NULL};

    adicionarNo(&lista, 10);
    adicionarNo(&lista, 20);
    adicionarNo(&lista, 30);

    imprimirLista(&lista);
    liberarLista(&lista);

    return 0;
}
