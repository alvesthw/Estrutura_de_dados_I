#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó
typedef struct no {
    int valor;
    struct no* proximo;
    struct no* anterior;
} No;

// Estrutura da Lista
typedef struct lista {
    No* cabeca;
    No* cauda;
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
    novo->anterior = NULL;
    return novo;
    // A estrutura no da lista dupla é assim [anteior|valor|proximo]
}

// Função para adicionar nó ao final da lista
void adicionarNo(Lista* lista, int valor) {
    No* novo = criarNo(valor);
    if (lista->cabeca == NULL) { // Se a cabeça for NULL, significa que não há nenhum nó ainda.
        // Como a lista está vazia, o novo nó será o primeiro e o último ao mesmo tempo.
        lista->cabeca = novo;
        lista->cauda = novo;
    } else { // Se a lista não está vazia:
        novo->anterior = lista->cauda; //O novo nó aponta para o nó anterior, que é a cauda atual.
        lista->cauda->proximo = novo; //A cauda atual precisa apontar para o novo nó como seu próximo.
        lista->cauda = novo; //Atualiza a cauda da lista, que agora será o novo nó.
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
    lista->cauda = NULL;
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
