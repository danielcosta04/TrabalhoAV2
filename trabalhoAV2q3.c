#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��o da estrutura de livro
typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

// Fun��es para manipula��o de livros
void adicionarLivro();
void alterarLivro();
void excluirLivro();
void consultarLivro();
void listarLivros();

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configura��o de localidade

    int opcao;
    do {
        printf("\nGerenciamento de Livros\n");
        printf("1. Adicionar um novo livro\n");
        printf("2. Alterar os dados de um livro\n");
        printf("3. Excluir um livro pelo c�digo\n");
        printf("4. Consultar informa��es de um livro pelo c�digo\n");
        printf("5. Listar todos os livros cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
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
    printf("Digite o c�digo: ");
    scanf("%d", &livro.codigo);
    getchar();  // Limpar buffer
    printf("Digite o t�tulo: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    strtok(livro.titulo, "\n");
    printf("Digite o autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    strtok(livro.autor, "\n");
    printf("Digite o ano de publica��o: ");
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
    printf("Digite o c�digo do livro a ser alterado: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("Livro encontrado. Digite os novos dados.\n");
            printf("Digite o novo t�tulo: ");
            fgets(livro.titulo, sizeof(livro.titulo), stdin);
            strtok(livro.titulo, "\n");
            printf("Digite o novo autor: ");
            fgets(livro.autor, sizeof(livro.autor), stdin);
            strtok(livro.autor, "\n");
            printf("Digite o novo ano de publica��o: ");
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
        printf("Livro n�o encontrado!\n");
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
    printf("Digite o c�digo do livro a ser exclu�do: ");
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
        printf("Livro exclu�do com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Livro n�o encontrado!\n");
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
    printf("Digite o c�digo do livro a ser consultado: ");
    scanf("%d", &codigo);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%49[^,],%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) != EOF) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            printf("C�digo: %d\n", livro.codigo);
            printf("T�tulo: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano de Publica��o: %d\n", livro.ano);
            break;  // Adicionado para evitar repeti��o
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Livro n�o encontrado!\n");
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
        printf("C�digo: %d\n", livro.codigo);
        printf("T�tulo: %s\n", livro.titulo);
        printf("Autor: %s\n", livro.autor);
        printf("Ano de Publica��o: %d\n", livro.ano);
        printf("\n");
    }

    fclose(arquivo);
}
