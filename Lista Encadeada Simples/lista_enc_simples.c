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
} Lista;

// Função para criar a lista 
void criarLista(Lista* lista) {
    lista->cabeca = NULL; 
}

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

// adicionar um nó na lista (bota no final da lista) x-> x -> x -> aqui
void adicionarNo(Lista* lista, int valor) {
    No* novo = criarNo(valor);
    
    if (lista->cabeca == NULL) {  // Se vazia o novo no é o primeiro
        lista->cabeca = novo;
    } else {
        No* atual = lista->cabeca;
        // Vai até o final da lista
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;  // O Ultimo no aponta para o novo no
    }
}

// remover o primeiro nó da lista
void removerPrimeiro(Lista* lista) {
    if (lista->cabeca == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    No* temp = lista->cabeca;
    lista->cabeca = lista->cabeca->proximo; // Atualiza a cabeça para o próximo nó
    free(temp);  // Libera a memória do nó removido
}

// remover um nó com valor específico
void removerPorValor(Lista* lista, int valor) {
    if (lista->cabeca == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    No* atual = lista->cabeca;
    No* anterior = NULL;

    // Caso especial: remover o primeiro nó
    if (atual != NULL && atual->valor == valor) {
        lista->cabeca = atual->proximo;  // A cabeça aponta para o próximo nó
        free(atual);
        return;
    }

    // Percorre a lista para encontrar o nó com o valor desejado
    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o valor não for encontrado
    if (atual == NULL) {
        printf("Elemento com valor %d não encontrado.\n", valor);
        return;
    }

    // Desvincula o nó de sua posição na lista
    anterior->proximo = atual->proximo;
    free(atual);  // Libera a memória do nó removido
}

// buscar um valor
No* buscarPorValor(Lista* lista, int valor) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual;  // Produto encontrado
        }
        atual = atual->proximo;
    }
    return NULL;  // Produto não encontrado
}

// imprimir a lista
void imprimirLista(Lista* lista) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// liberar a memória
void liberarLista(Lista* lista) {
    No* atual = lista->cabeca;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->cabeca = NULL;
}

int main() {
    Lista lista;
    criarLista(&lista);  

    // Adicionando elementos à lista
    adicionarNo(&lista, 10);
    adicionarNo(&lista, 20);
    adicionarNo(&lista, 30);
    adicionarNo(&lista, 40);

    printf("Lista após inserções:\n");
    imprimirLista(&lista);

    // Buscando um valor
    int valorBusca = 20;
    No* resultado = buscarPorValor(&lista, valorBusca);
    if (resultado != NULL) {
        printf("\nElemento com valor %d encontrado na lista.\n", valorBusca);
    } else {
        printf("\nElemento com valor %d não encontrado.\n", valorBusca);
    }

    // Remover primeiro nó
    removerPrimeiro(&lista);
    printf("\nLista após remover o primeiro elemento:\n");
    imprimirLista(&lista);

    // Remover nó com valor 
    removerPorValor(&lista, 30);
    printf("\nLista após remover o valor 30:\n");
    imprimirLista(&lista);

    liberarLista(&lista);
    
    return 0;
}
