#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Necessário para a função exit() em um loop real de jogo.

// Constante para o tamanho máximo da mochila
#define MAX_ITENS 10

// --------------------------------------------------------------------------------
// 1. Definição da Struct (Requisito Funcional: Criação da struct)
// --------------------------------------------------------------------------------
/**
 * @brief Representa um item que pode ser armazenado na mochila do jogador.
 */
typedef struct {
    char nome[30];     // Nome do item (ex: Pistola, Kit Médico)
    char tipo[20];     // Tipo do item (ex: arma, munição, cura, ferramenta)
    int quantidade;    // Quantidade do item
} Item;

// --------------------------------------------------------------------------------
// 2. Variáveis Globais para o Inventário
// --------------------------------------------------------------------------------
// Vetor de structs: Representa a mochila de loot (Requisito Funcional: Vetor de structs)
Item mochila[MAX_ITENS];
// Contador que rastreia quantos slots estão ocupados (o "tamanho" lógico do vetor)
int totalItens = 0;

// --------------------------------------------------------------------------------
// 3. Protótipos das Funções
// --------------------------------------------------------------------------------
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void menuPrincipal();

// --------------------------------------------------------------------------------
// 4. Implementação das Funções
// --------------------------------------------------------------------------------

/**
 * @brief Lista todos os itens atualmente na mochila.
 * (Requisito Funcional: Listagem dos itens registrados)
 */
void listarItens() {
    printf("\n--- 🎒 INVENTÁRIO ATUAL (Total: %d/%d) ---\n", totalItens, MAX_ITENS);
    if (totalItens == 0) {
        printf("Mochila vazia. Hora de coletar recursos!\n");
        printf("----------------------------------------\n");
        return;
    }

    // Uso de laço (for) para percorrer o vetor de itens (Requisito Detalhado)
    for (int i = 0; i < totalItens; i++) {
        printf("[%02d] Nome: %-25s | Tipo: %-15s | Qtd: %d\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------------\n");
}

/**
 * @brief Insere um novo item na primeira posição vazia da mochila.
 * (Requisito Funcional: Cadastro de itens)
 */
void inserirItem() {
    // Verifica se a mochila está cheia
    if (totalItens >= MAX_ITENS) {
        printf("\n🛑 Mochila Cheia! Não é possível carregar mais itens. 🛑\n");
        return;
    }

    printf("\n--- ➕ CADASTRAR NOVO ITEM ---\n");
    
    // Leitura de dados (Requisito Detalhado)
    
    // Nome
    printf("Nome do Item (max 29 caracteres): ");
    scanf("%29s", mochila[totalItens].nome); 
    
    // Tipo
    printf("Tipo (ex: arma, munição, cura, ferramenta): ");
    scanf("%19s", mochila[totalItens].tipo);
    
    // Quantidade
    printf("Quantidade: ");
    while (scanf("%d", &mochila[totalItens].quantidade) != 1 || mochila[totalItens].quantidade <= 0) {
        printf("⚠️ Entrada inválida. Digite uma quantidade válida (número inteiro positivo): ");
        while(getchar() != '\n'); // Limpa o buffer
    }

    // Atualiza o contador de itens
    totalItens++;
    printf("\n✅ Item '%s' adicionado à mochila.\n", mochila[totalItens - 1].nome);
    listarItens(); // Listagem após a operação (Requisito Funcional)
}

/**
 * @brief Remove um item da mochila buscando-o pelo nome.
 * (Requisito Funcional: Remoção de itens)
 */
void removerItem() {
    if (totalItens == 0) {
        printf("\nℹ️ A mochila já está vazia. Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- ➖ REMOVER ITEM ---\n");
    printf("Digite o NOME do item a ser removido: ");
    scanf("%29s", nomeBusca);

    int encontrado = 0;
    // Uso de laço (for) para percorrer o vetor na busca (Requisito Detalhado)
    for (int i = 0; i < totalItens; i++) {
        // Compara a string (Requisito Detalhado: Uso de string.h)
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            
            // Item encontrado. Inicia o deslocamento (remoção eficiente em lista sequencial).
            encontrado = 1;
            printf("\n🗑️ Item '%s' removido da mochila.\n", mochila[i].nome);
            
            // Desloca todos os itens seguintes uma posição para trás
            // (Substitui a posição 'i' pelo item 'i+1', e assim por diante)
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            
            // Diminui o contador total de itens
            totalItens--;
            break; // Sai do loop após remover o item
        }
    }

    if (!encontrado) {
        printf("\n❌ Item com nome '%s' não encontrado na mochila.\n", nomeBusca);
    }
    
    listarItens(); // Listagem após a operação (Requisito Funcional)
}

/**
 * @brief Realiza uma busca sequencial por um item na mochila pelo nome.
 * (Requisito Funcional: Busca sequencial)
 */
void buscarItem() {
    if (totalItens == 0) {
        printf("\nℹ️ A mochila está vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- 🔍 BUSCAR ITEM ---\n");
    printf("Digite o NOME do item que deseja buscar: ");
    scanf("%29s", nomeBusca);

    int encontrado = 0;
    
    // Implementação da Busca Sequencial: percorre o vetor do início ao fim
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            printf("\n--- ✅ ITEM ENCONTRADO (Slot %d) ---\n", i + 1);
            printf("  Nome:      %s\n", mochila[i].nome);
            printf("  Tipo:      %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            printf("--------------------------------------\n");
            // Para um inventário simples, podemos parar na primeira ocorrência
            return; 
        }
    }

    if (!encontrado) {
        printf("\n❌ Item com nome '%s' não foi localizado na mochila.\n", nomeBusca);
    }
}

/**
 * @brief Exibe o menu principal e gerencia as escolhas do jogador.
 * (Requisito Não Funcional: Usabilidade - Interface clara e orientativa)
 */
void menuPrincipal() {
    int escolha;

    do {
        printf("\n========================================\n");
        printf("         MOCHILA DE LOOT INICIAL\n");
        printf("========================================\n");
        printf("1. ➕ Cadastrar Novo Item\n");
        printf("2. ➖ Remover Item por Nome\n");
        printf("3. 🔍 Buscar Item por Nome\n");
        printf("4. 📋 Listar Todos os Itens\n");
        printf("0. 🚪 Sair do Inventário (Continuar Jogo)\n");
        printf("----------------------------------------\n");
        printf("Escolha sua ação estratégica: ");

        // Loop para garantir que a entrada é um número inteiro válido
        while (scanf("%d", &escolha) != 1) {
            printf("⚠️ Entrada inválida. Por favor, digite um número de 0 a 4: ");
            while(getchar() != '\n'); // Limpa o buffer de entrada
        }
        
        // Limpa o buffer restante para evitar problemas com próximas leituras de string
        while(getchar() != '\n');

        switch (escolha) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                buscarItem();
                break;
            case 4:
                listarItens();
                break;
            case 0:
                printf("\n👋 Fechando inventário. Boa sorte no jogo!\n");
                break;
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
                break;
        }
    } while (escolha != 0);
}


// --------------------------------------------------------------------------------
// 5. Função Principal (main)
// --------------------------------------------------------------------------------
int main() {
    // Inicializa o sistema de inventário
    menuPrincipal();
    
    return 0;
}

/*
Comentários Adicionais de Documentação (Requisito Não Funcional: Documentação):
- O código usa 'typedef struct' para simplificar a declaração de variáveis do tipo 'Item'.
- A variável 'totalItens' é crucial para o desempenho, pois o código só percorre as posições
  do vetor que estão realmente ocupadas, e não as 10 posições fixas, otimizando as buscas e listagens.
- O uso das funções string.h (strcmp) é essencial para manipular e comparar strings (nomes dos itens).
- A nomenclatura das funções e variáveis é clara (Requisito Não Funcional: Manutenibilidade).
*/