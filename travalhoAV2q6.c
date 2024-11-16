#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura de cidade
typedef struct {
    int codigo;
    char nome[50];
    char estado[30];
    int populacao;
} Cidade;

// Funções para manipulação de cidades
void incluirCidade();
void alterarCidade();
void excluirCidade();
void consultarCidade();
void listarCidades();

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configuração de localidade

    int opcao;
    do {
        printf("\nCadastro de Cidades\n");
        printf("1. Incluir cidade\n");
        printf("2. Alterar dados de uma cidade\n");
        printf("3. Excluir cidade pelo código\n");
        printf("4. Consultar cidade pelo código\n");
        printf("5. Listar todas as cidades cadastradas\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        switch (opcao) {
            case 1:
                incluirCidade();
                break;
            case 2:
                alterarCidade();
                break;
            case 3:
                excluirCidade();
                break;
            case 4:
                consultarCidade();
                break;
            case 5:
                listarCidades();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

void incluirCidade() {
    FILE *arquivo = fopen("cidades.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Cidade cidade;
    printf("Digite o código: ");
    scanf("%d", &cidade.codigo);
    getchar();  // Limpar buffer
    printf("Digite o nome: ");
    fgets(cidade.nome, sizeof(cidade.nome), stdin);
    strtok(cidade.nome, "\n");
    printf("Digite o estado: ");
    fgets(cidade.estado, sizeof(cidade.estado), stdin);
    strtok(cidade.estado, "\n");
    printf("Digite a população: ");
    scanf("%d", &cidade.populacao);
    getchar();  // Limpar buffer

    fprintf(arquivo, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);

    fclose(arquivo);
    printf("Cidade incluída com sucesso!\n");
}

void alterarCidade() {
    FILE *arquivo = fopen("cidades.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Cidade cidade;
    int codigo, encontrado = 0;
    printf("Digite o código da cidade a ser alterada: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("Cidade encontrada. Digite os novos dados.\n");
            printf("Digite o novo nome: ");
            fgets(cidade.nome, sizeof(cidade.nome), stdin);
            strtok(cidade.nome, "\n");
            printf("Digite o novo estado: ");
            fgets(cidade.estado, sizeof(cidade.estado), stdin);
            strtok(cidade.estado, "\n");
            printf("Digite a nova população: ");
            scanf("%d", &cidade.populacao);
            getchar();  // Limpar buffer
        }
        fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("cidades.txt");
        rename("temp.txt", "cidades.txt");
        printf("Dados da cidade alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Cidade não encontrada!\n");
    }
}

void excluirCidade() {
    FILE *arquivo = fopen("cidades.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Cidade cidade;
    int codigo, encontrado = 0;
    printf("Digite o código da cidade a ser excluída: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo != codigo) {
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("cidades.txt");
        rename("temp.txt", "cidades.txt");
        printf("Cidade excluída com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Cidade não encontrada!\n");
    }
}

void consultarCidade() {
    FILE *arquivo = fopen("cidades.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Cidade cidade;
    int codigo, encontrado = 0;
    printf("Digite o código da cidade a ser consultada: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            encontrado = 1;
            printf("Código: %d\n", cidade.codigo);
            printf("Nome: %s\n", cidade.nome);
            printf("Estado: %s\n", cidade.estado);
            printf("População: %d\n", cidade.populacao);
            break;  // Adicionado para evitar repetição
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Cidade não encontrada!\n");
    }
}

void listarCidades() {
    FILE *arquivo = fopen("cidades.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Cidade cidade;
    printf("Lista de Cidades:\n");

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        printf("Código: %d\n", cidade.codigo);
        printf("Nome: %s\n", cidade.nome);
        printf("Estado: %s\n", cidade.estado);
        printf("População: %d\n", cidade.populacao);
        printf("\n");
    }

    fclose(arquivo);
}
