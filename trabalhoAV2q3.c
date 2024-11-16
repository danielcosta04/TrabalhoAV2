#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura de livro
typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

// Funções para manipulação de livros
void adicionarLivro();
void alterarLivro();
void excluirLivro();
void consultarLivro();
void listarLivros();

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configuração de localidade

    int opcao;
    do {
        printf("\nGerenciamento de Livros\n");
        printf("1. Adicionar um novo livro\n");
        printf("2. Alterar os dados de um livro\n");
        printf("3. Excluir um livro pelo código\n");
        printf("4. Consultar informações de um livro pelo código\n");
        printf("5. Listar todos os livros cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                alterarLivro();
                break;
            case 3:
                excluirLivro();
                break;
            case 4:
                consultarLivro();
                break;
            case 5:
                listarLivros();
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

void adicionarLivro() {
    FILE *arquivo = fopen("livros.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Livro livro;
    printf("Digite o código: ");
    scanf("%d", &livro.codigo);
    getchar();  // Limpar buffer
    printf("Digite o título: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    strtok(livro.titulo, "\n");
    printf("Digite o autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    strtok(livro.autor, "\n");
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro.ano);
    getchar();  // Limpar buffer

    fprintf(arquivo, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);

    fclose(arquivo);
    printf("Livro adicionado com sucesso!\n");
}

void alterarLivro() {
    FILE *arquivo = fopen("livros.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Livro livro;
    int codigo, encontrado = 0;
    printf("Digite o código do livro a ser alterado: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("Livro encontrado. Digite os novos dados.\n");
            printf("Digite o novo título: ");
            fgets(livro.titulo, sizeof(livro.titulo), stdin);
            strtok(livro.titulo, "\n");
            printf("Digite o novo autor: ");
            fgets(livro.autor, sizeof(livro.autor), stdin);
            strtok(livro.autor, "\n");
            printf("Digite o novo ano de publicação: ");
            scanf("%d", &livro.ano);
            getchar();  // Limpar buffer
        }
        fprintf(temp, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("livros.txt");
        rename("temp.txt", "livros.txt");
        printf("Dados do livro alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Livro não encontrado!\n");
    }
}

void excluirLivro() {
    FILE *arquivo = fopen("livros.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Livro livro;
    int codigo, encontrado = 0;
    printf("Digite o código do livro a ser excluído: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo != codigo) {
            fprintf(temp, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("livros.txt");
        rename("temp.txt", "livros.txt");
        printf("Livro excluído com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Livro não encontrado!\n");
    }
}

void consultarLivro() {
    FILE *arquivo = fopen("livros.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Livro livro;
    int codigo, encontrado = 0;
    printf("Digite o código do livro a ser consultado: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("Código: %d\n", livro.codigo);
            printf("Título: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano de Publicação: %d\n", livro.ano);
            break;  // Adicionado para evitar repetição
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Livro não encontrado!\n");
    }
}

void listarLivros() {
    FILE *arquivo = fopen("livros.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Livro livro;
    printf("Lista de Livros:\n");

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        printf("Código: %d\n", livro.codigo);
        printf("Título: %s\n", livro.titulo);
        printf("Autor: %s\n", livro.autor);
        printf("Ano de Publicação: %d\n", livro.ano);
        printf("\n");
    }

    fclose(arquivo);
}
