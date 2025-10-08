#include <stdio.h>
#include <stdlib.h>

/* ======== TAD: VetorDin ======== */
typedef struct {
    int *dados;
    size_t tamanho;
    size_t capacidade;
} VetorDin;

/* Cria vetor dinâmico */
VetorDin *criar_vetor(size_t capacidade_inicial) {
    VetorDin *vetor = (VetorDin*) malloc(sizeof(VetorDin));
    if (!vetor) {
        perror("Erro ao alocar memória para o vetor");
        exit(EXIT_FAILURE);
    }

    vetor->tamanho = 0;
    vetor->capacidade = (capacidade_inicial > 0) ? capacidade_inicial : 4;
    vetor->dados = (int*) malloc(vetor->capacidade * sizeof(int));
    if (!vetor->dados) {
        perror("Erro ao alocar memória para os dados");
        free(vetor);
        exit(EXIT_FAILURE);
    }

    return vetor;
}

/* Adiciona elemento ao vetor */
void adicionar_elemento(VetorDin *vetor, int valor) {
    if (vetor->tamanho >= vetor->capacidade) {
        vetor->capacidade *= 2;
        int *novo = (int*) realloc(vetor->dados, vetor->capacidade * sizeof(int));
        if (!novo) {
            perror("Erro ao realocar memória");
            free(vetor->dados);
            free(vetor);
            exit(EXIT_FAILURE);
        }
        vetor->dados = novo;
    }
    vetor->dados[vetor->tamanho++] = valor;
}

/* Libera memória do vetor */
void liberar_vetor(VetorDin *vetor) {
    if (vetor) {
        free(vetor->dados);
        free(vetor);
    }
}

/* ======== Estrutura auxiliar: Par (chave + índice original) ======== */
typedef struct {
    int chave;
    int indice_original;
} Par;

/* Função de comparação para qsort */
int comparar_par(const void *a, const void *b) {
    Par *pa = (Par*) a;
    Par *pb = (Par*) b;

    if (pa->chave < pb->chave) return -1;
    if (pa->chave > pb->chave) return 1;
    return 0;
}

/* ======== Funções de busca ======== */

/* Busca binária: retorna um índice qualquer onde a chave aparece */
int busca_binaria(Par *vetor, size_t tamanho, int chave) {
    int inicio = 0;
    int fim = (int)tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (vetor[meio].chave == chave)
            return meio;
        else if (vetor[meio].chave < chave)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1; // não encontrada
}

/* Coleta todas as posições onde a chave aparece */
VetorDin *coletar_posicoes(Par *vetor, size_t tamanho, int indice, int chave) {
    VetorDin *posicoes = criar_vetor(4);

    // busca para a esquerda
    int i = indice;
    while (i >= 0 && vetor[i].chave == chave) {
        adicionar_elemento(posicoes, vetor[i].indice_original);
        i--;
    }

    // busca para a direita
    i = indice + 1;
    while ((size_t)i < tamanho && vetor[i].chave == chave) {
        adicionar_elemento(posicoes, vetor[i].indice_original);
        i++;
    }

    // ordenar posições em ordem crescente
    if (posicoes->tamanho > 1)
        qsort(posicoes->dados, posicoes->tamanho, sizeof(int),
              (int (*)(const void*, const void*))comparar_par);

    return posicoes;
}

/* ======== Programa principal ======== */
int main() {
    int n;
    printf("Quantidade de elementos: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Quantidade inválida.\n");
        return 1;
    }

    VetorDin *lista = criar_vetor(n);

    printf("Digite os %d valores:\n", n);
    for (int i = 0; i < n; i++) {
        int valor;
        scanf("%d", &valor);
        adicionar_elemento(lista, valor);
    }

    int chave;
    printf("Digite a chave a ser buscada: ");
    scanf("%d", &chave);

    // cria vetor de pares (valor + índice original)
    Par *pares = (Par*) malloc(lista->tamanho * sizeof(Par));
    if (!pares) {
        perror("Erro ao alocar memória para pares");
        liberar_vetor(lista);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < lista->tamanho; i++) {
        pares[i].chave = lista->dados[i];
        pares[i].indice_original = (int)i;
    }

    // ordena pares por chave
    qsort(pares, lista->tamanho, sizeof(Par), comparar_par);

    // faz busca binária
    int pos = busca_binaria(pares, lista->tamanho, chave);

    if (pos == -1) {
        printf("\nChave %d não encontrada.\n", chave);
        printf("Lista original:\n");
        for (size_t i = 0; i < lista->tamanho; i++)
            printf("%d ", lista->dados[i]);
        printf("\n");
    } else {
        VetorDin *posicoes = coletar_posicoes(pares, lista->tamanho, pos, chave);

        if (posicoes->tamanho == 1) {
            printf("\nChave %d encontrada na posição %d (0-based).\n",
                   chave, posicoes->dados[0]);
        } else {
            printf("\nChave %d encontrada em %zu posições: ",
                   chave, posicoes->tamanho);
            for (size_t i = 0; i < posicoes->tamanho; i++)
                printf("%d ", posicoes->dados[i]);
            printf("\n");
        }

        liberar_vetor(posicoes);
    }

    // Liberação de memória
    liberar_vetor(lista);
    free(pares);

    return 0;
}

