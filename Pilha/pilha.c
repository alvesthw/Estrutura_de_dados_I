#include <iostream>  // Para entrada e saída (std::cin, std::cout)
#include <cstdlib>   // Para malloc e free
#include <cstring>   // Para funções de string como strcpy

// Nó da pilha representando um prato
typedef struct No {
    char prato[50];     // nome do prato
    struct No* cima;    // prato que está acima deste nó (mais novo)
    struct No* baixo;   // prato que está abaixo deste nó (mais antigo)
} No;

// Pilha de pratos
typedef struct {
    No* topo; // ponteiro para o prato que está no topo da pilha
} Pilha;

// Inicializa a pilha definindo o topo como NULL (pilha vazia)
void inicializar(Pilha* p) {
    p->topo = NULL;
}

// Verifica se a pilha está vazia
bool seVazia(Pilha* p) {
    return p->topo == NULL;
}

// Função para empilhar (colocar prato no topo da pilha)
void empilhar(Pilha* p, const char* valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        std::cout << "Erro: memória insuficiente!" << std::endl;
        return;
    }
    strcpy(novo->prato, valor);  // Copia o nome do prato para o novo nó
    novo->cima = NULL;           // Como será o topo, não tem prato acima
    novo->baixo = p->topo;       // Aponta para o prato que estava no topo (que fica abaixo)

    if (p->topo != NULL)
        p->topo->cima = novo;   // O antigo topo agora tem um prato acima (o novo)

    p->topo = novo;              // Atualiza o topo da pilha para o novo prato
}

// Função para desempilhar (remover prato do topo)
char* desenpilhar(Pilha* p) {
    if (seVazia(p)) {
        std::cout << "Erro: pilha vazia!" << std::endl;
        return NULL;  // Retorna NULL para indicar que não tem prato para remover
    }

    No* remover = p->topo;  // Nó que será removido (topo da pilha)
    static char valor[50];  // Variável estática para guardar o nome do prato removido

    strcpy(valor, remover->prato); // Copia o nome do prato que será removido

    p->topo = remover->baixo;  // Atualiza o topo para o prato abaixo do removido

    if (p->topo != NULL)
        p->topo->cima = NULL;  // Novo topo não tem prato acima

    free(remover);  // Libera a memória do nó removido

    return valor;  // Retorna o nome do prato removido
}

// Função para mostrar o prato que está no topo da pilha
char* mostraTopo(Pilha* p) {
    if (seVazia(p)) {
        std::cout << "Pilha vazia!" << std::endl;
        return NULL;
    }
    return p->topo->prato;
}

// Exibir pilha do topo para a base 
void exibirTopoParaBase(Pilha* pilha) {
    if (seVazia(pilha)) {
        std::cout << "Pilha vazia" << std::endl;
        return;
    }

    std::cout << "Pilha (topo -> base):\n";

    No* atual = pilha->topo;

    // Percorre do topo até o prato mais antigo
    while (atual != NULL) {
        std::cout << atual->prato << std::endl;
        atual = atual->baixo;  // Desce para o prato abaixo
    }
}

// Exibir pilha da base para o topo (de baixo para cima)
void exibirBaseParaTopo(Pilha* pilha) {
    if (seVazia(pilha)) {
        std::cout << "Pilha vazia" << std::endl;
        return;
    }

    // Vai até a base da pilha (prato mais antigo)
    No* atual = pilha->topo;
    while (atual != NULL && atual->baixo != NULL) {
        atual = atual->baixo;
    }

    std::cout << "Pilha (base -> topo):\n";

    // Sobe do prato mais baixo até o topo
    while (atual != NULL) {
        std::cout << atual->prato << std::endl;
        atual = atual->cima;  // Sobe para o prato acima
    }
}

// Função do menu interativo para manipular a pilha de pratos
void menu() {
    Pilha pratos; // declarar a pilha p"pratos"
    inicializar(&pratos); // inicializar para definir o topo como null

    int opcao;		// guardar a minha escolha no menu
    char prato[50]; // nome do prato

    do {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Empilhar prato\n";
        std::cout << "2. Desempilhar prato\n";
        std::cout << "3. Mostrar prato do topo\n";
        std::cout << "4. Exibir pilha (topo -> base)\n";
        std::cout << "5. Exibir pilha (base -> topo)\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao; // Lê a opção digitada pelo usuário
        std::cin.ignore(); // Ignora o caractere de nova linha deixado no buffer

        switch(opcao) {
            case 1:
                std::cout << "Digite o nome do prato para empilhar: ";
                std::cin.getline(prato, sizeof(prato));  // Lê o nome do prato com espaços
                empilhar(&pratos, prato); // Chama função para empilhar
                break;
            case 2:
                {
                    char* removido = desenpilhar(&pratos);  // Remove o prato do topo
                    if (removido != NULL)
                        std::cout << "Prato desempilhado: " << removido << std::endl;
                }
                break;
            case 3:
                {
                    char* topo = mostraTopo(&pratos);
                    if (topo != NULL)
                        std::cout << "Prato do topo: " << topo << std::endl;
                }
                break;
            case 4:
                exibirTopoParaBase(&pratos);
                break;
            case 5:
                exibirBaseParaTopo(&pratos);
                break;
            case 0:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida! Tente novamente." << std::endl;
        }

    } while(opcao != 0);
}

int main() {
    menu();
    return 0;
}
