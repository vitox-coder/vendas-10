#include <stdio.h>

#define TAM_CLI 3

#define TAM_PROD 3

#define TAM_VENDAS 10

typedef struct {
    int id;
    char nome[30];
    int quantidade;
    float valor;
} Produto;

typedef struct {
    int id;
    char nome[30];
} Cliente;

typedef struct {
    int idCliente;
    int idProduto;
    int quantProduto;
    float valorTotal;
} Venda;

void cadastrarCliente(Cliente clientes[]) {
    for (int i = 0; i < TAM_CLI; i++) {
        printf("Informe o nome do cliente %d: ", i + 1);
        scanf("%s", clientes[i].nome);
        getchar();
        clientes[i].id = i + 1;
    }
}

void cadastrarProduto(Produto produtos[]) {
    for (int i = 0; i < TAM_PROD; i++) {
        printf("Nome do produto %d: ", i + 1);
        scanf("%s", produtos[i].nome);
        getchar();
        printf("Quantidade disponível: ");
        scanf("%d", &produtos[i].quantidade);
        printf("Preço do produto: ");
        scanf("%f", &produtos[i].valor);
        produtos[i].id = i + 1;
    }
}

void consultarCliente(Cliente clientes[]) {
    printf("\nLista de Clientes:\n");
    for (int i = 0; i < TAM_CLI; i++) {
        printf("ID: %d - Nome: %s\n", clientes[i].id, clientes[i].nome);
    }
}

void consultarProduto(Produto produtos[]) {
    printf("\nLista de Produtos:\n");
    for (int i = 0; i < TAM_PROD; i++) {
        printf("ID: %d - Nome: %s - Quantidade: %d - Preço: R$%.2f\n",
               produtos[i].id, produtos[i].nome, produtos[i].quantidade, produtos[i].valor);
    }
}

void realizarVenda(Cliente clientes[], Produto produtos[], Venda vendas[], int *totalVendas) {
    int idCliente, idProduto, quantidade;

    printf("Informe o ID do cliente: ");
    scanf("%d", &idCliente);
    printf("Informe o ID do produto: ");
    scanf("%d", &idProduto);
    printf("Quantidade desejada: ");
    scanf("%d", &quantidade);

    if (idCliente < 1 || idCliente > TAM_CLI || idProduto < 1 || idProduto > TAM_PROD) {
        printf("Erro: Cliente ou Produto inexistente!\n");
        return;
    }

    if (produtos[idProduto - 1].quantidade < quantidade) {
        printf("Erro: Estoque insuficiente!\n");
        return;
    }

    produtos[idProduto - 1].quantidade -= quantidade;
    vendas[*totalVendas].idCliente = idCliente;
    vendas[*totalVendas].idProduto = idProduto;
    vendas[*totalVendas].quantProduto = quantidade;
    vendas[*totalVendas].valorTotal = quantidade * produtos[idProduto - 1].valor;
    (*totalVendas)++;

    printf("Venda realizada com sucesso!\n");
}

void consultarVendas(Venda vendas[], int totalVendas) {
    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    printf("\nRegistro de Vendas:\n");
    for (int i = 0; i < totalVendas; i++) {
        printf("Venda %d - Cliente ID: %d - Produto ID: %d - Quantidade: %d - Total: R$%.2f\n",
               i + 1, vendas[i].idCliente, vendas[i].idProduto, vendas[i].quantProduto, vendas[i].valorTotal);
    }
}

int main() {
    int opcao, sair = 0;
    Cliente clientes[TAM_CLI];
    Produto produtos[TAM_PROD];
    Venda vendas[TAM_VENDAS];
    int totalVendas = 0;

    do {
        printf("\n======= Sistema de Vendas =======\n");
        printf("1 - Cadastrar Clientes\n");
        printf("2 - Cadastrar Produtos\n");
        printf("3 - Consultar Clientes\n");
        printf("4 - Consultar Produtos\n");
        printf("5 - Realizar Venda\n");
        printf("6 - Consultar Vendas\n");
        printf("7 - Sair\n");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n');
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1: cadastrarCliente(clientes); break;
            case 2: cadastrarProduto(produtos); break;
            case 3: consultarCliente(clientes); break;
            case 4: consultarProduto(produtos); break;
            case 5: realizarVenda(clientes, produtos, vendas, &totalVendas); break;
            case 6: consultarVendas(vendas, totalVendas); break;
            case 7: sair = 1; break;
            default: printf("Opção inválida, tente novamente.\n");
        }
    } while (!sair);

    return 0;
}
