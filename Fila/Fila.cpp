#include <iostream>
#include <cstdlib>
#include <cstring>


// Estrutura da pessoa na fila
typedef struct Pessoa {
    int senha;
    char nome[50];
    bool prioridade;
    Pessoa* pessoaDaFrente;  // Ponteiro para a pessoa na frente (anterior)
    Pessoa* pessoaDeTras;    // Ponteiro para a pessoa atrás (próximo)
} Pessoa;

// Estrutura da fila
typedef struct {
    Pessoa* primeira;  // Primeira pessoa da fila (frente)
    Pessoa* ultima;    // Última pessoa da fila (tras)
} Fila;

// Inicializa a fila vazia
void inicializarFila(Fila* f) {
    f->primeira = NULL;
    f->ultima = NULL;
}

// Verifica se a fila está vazia
bool filaVazia(Fila* f) {
    return f->primeira == NULL;
}

// Enfileira uma pessoa no final da fila
void enfileirar(Fila* fila, const char* nome, int senha, bool prioridade) {
    Pessoa* nova = (Pessoa*)malloc(sizeof(Pessoa));
    if (!nova) {
        std::cout << "Erro: memória insuficiente!" << std::endl;
        return;
    }

    strcpy(nova->nome, nome);
    nova->senha = senha;
    nova->prioridade = prioridade;
    nova->pessoaDeTras = NULL;      // Ninguém atrás dela (é a última)
    nova->pessoaDaFrente = fila->ultima; // A pessoa que estava atrás agora fica na frente dela

    if (filaVazia(fila)) {
        fila->primeira = nova;
        fila->ultima = nova;
    } else {
        fila->ultima->pessoaDeTras = nova;  // A antiga última pessoa aponta para a nova
        fila->ultima = nova;                 // Atualiza a última pessoa
    }
}

// Desenfileira a primeira pessoa da fila
Pessoa* desenfileirar(Fila* fila) {
    if (filaVazia(fila))
        return NULL;

    Pessoa* remover = fila->primeira;
    fila->primeira = remover->pessoaDeTras; // A próxima pessoa atrás passa a ser a primeira

    if (fila->primeira != NULL)
        fila->primeira->pessoaDaFrente = NULL; // Como é a primeira agora, não tem ninguém na frente
    else
        fila->ultima = NULL; // A fila ficou vazia

    return remover; // O chamador deve liberar a memória
}

// Exibe a fila (do primeiro ao último)
void exibirFila(Fila* fila, const char* titulo) {
    std::cout << "\n--- " << titulo << " ---\n";

    if (filaVazia(fila)) {
        std::cout << "Fila vazia.\n";
        return;
    }

    Pessoa* atual = fila->primeira;
    while (atual != NULL) {
        std::cout << "Senha: " << atual->senha
                  << " | Nome: " << atual->nome
                  << (atual->prioridade ? " (PRIORITÁRIA)" : "")
                  << std::endl;
        atual = atual->pessoaDeTras;  // Vai para a pessoa atrás (próxima na fila)
    }
}

// Libera toda a memória da fila
void liberarFila(Fila* fila) {
    Pessoa* atual = fila->primeira;
    while (atual != NULL) {
        Pessoa* temp = atual;
        atual = atual->pessoaDeTras;
        free(temp);
    }
    fila->primeira = NULL;
    fila->ultima = NULL;
}

// Menu interativo
void menu() {
    Fila filaNormal, filaPrioritaria;
    inicializarFila(&filaNormal);
    inicializarFila(&filaPrioritaria);

    int opcao;
    int contadorSenha = 1;

    do {
        std::cout << "\n=== SISTEMA DE FILA COM PRIORIDADE ===\n";
        std::cout << "1. Adicionar pessoa\n";
        std::cout << "2. Chamar proxima pessoa\n";
        std::cout << "3. Consultar filas\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1: {
                char nome[50];
                int prio;

                std::cout << "Digite o nome da pessoa: ";
                std::cin.getline(nome, sizeof(nome));

                std::cout << "A pessoa tem prioridade? (1 - Sim / 0 - Nao): ";
                std::cin >> prio;
                std::cin.ignore();

                bool prioridade = prio == 1;

                if (prioridade)
                    enfileirar(&filaPrioritaria, nome, contadorSenha, true);
                else
                    enfileirar(&filaNormal, nome, contadorSenha, false);

                std::cout << "Pessoa adicionada com senha: " << contadorSenha
                          << (prioridade ? " (PRIORITARIA)" : "") << std::endl;

                contadorSenha++;
                break;
            }

            case 2: {
                Pessoa* chamada = NULL;

                if (!filaVazia(&filaPrioritaria)) {
                    chamada = desenfileirar(&filaPrioritaria);
                } else if (!filaVazia(&filaNormal)) {
                    chamada = desenfileirar(&filaNormal);
                }

                if (chamada != NULL) {
                    std::cout << "\n==> Proxima pessoa chamada:\n";
                    std::cout << "Senha: " << chamada->senha
                              << " | Nome: " << chamada->nome
                              << (chamada->prioridade ? " (PRIORITARIA)" : "") << std::endl;
                    free(chamada);
                } else {
                    std::cout << "Nenhuma pessoa na fila.\n";
                }
                break;
            }

            case 3:
                exibirFila(&filaPrioritaria, "Fila prioritaria");
                exibirFila(&filaNormal, "Fila Normal");
                break;

            case 0:
                std::cout << "Finalizando e liberando memoria..." << std::endl;
                liberarFila(&filaPrioritaria);
                liberarFila(&filaNormal);
                break;

            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
        }

    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}

