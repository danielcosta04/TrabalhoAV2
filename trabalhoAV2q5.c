#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura de filme
typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int ano;
} Filme;

// Funções para manipulação de filmes
void adicionarFilme();
void alterarFilme();
void excluirFilme();
void consultarFilme();
void listarFilmes();

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configuração de localidade

    int opcao;
    do {
        printf("\nControle de Filmes\n");
        printf("1. Adicionar um novo filme\n");
        printf("2. Alterar os dados de um filme\n");
        printf("3. Excluir um filme pelo ID\n");
        printf("4. Consultar as informações de um filme pelo ID\n");
        printf("5. Listar todos os filmes cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        switch (opcao) {
            case 1:
                adicionarFilme();
                break;
            case 2:
                alterarFilme();
                break;
            case 3:
                excluirFilme();
                break;
            case 4:
                consultarFilme();
                break;
            case 5:
                listarFilmes();
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

void adicionarFilme() {
    FILE *arquivo = fopen("filmes.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Filme filme;
    printf("Digite o ID: ");
    scanf("%d", &filme.id);
    getchar();  // Limpar buffer
    printf("Digite o título: ");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    strtok(filme.titulo, "\n");
    printf("Digite o gênero: ");
    fgets(filme.genero, sizeof(filme.genero), stdin);
    strtok(filme.genero, "\n");
    printf("Digite o ano de lançamento: ");
    scanf("%d", &filme.ano);
    getchar();  // Limpar buffer

    fprintf(arquivo, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);

    fclose(arquivo);
    printf("Filme adicionado com sucesso!\n");
}

void alterarFilme() {
    FILE *arquivo = fopen("filmes.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Filme filme;
    int id, encontrado = 0;
    printf("Digite o ID do filme a ser alterado: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        if (filme.id == id) {
            encontrado = 1;
            printf("Filme encontrado. Digite os novos dados.\n");
            printf("Digite o novo título: ");
            fgets(filme.titulo, sizeof(filme.titulo), stdin);
            strtok(filme.titulo, "\n");
            printf("Digite o novo gênero: ");
            fgets(filme.genero, sizeof(filme.genero), stdin);
            strtok(filme.genero, "\n");
            printf("Digite o novo ano de lançamento: ");
            scanf("%d", &filme.ano);
            getchar();  // Limpar buffer
        }
        fprintf(temp, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("filmes.txt");
        rename("temp.txt", "filmes.txt");
        printf("Dados do filme alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Filme não encontrado!\n");
    }
}

void excluirFilme() {
    FILE *arquivo = fopen("filmes.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Filme filme;
    int id, encontrado = 0;
    printf("Digite o ID do filme a ser excluído: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        if (filme.id != id) {
            fprintf(temp, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("filmes.txt");
        rename("temp.txt", "filmes.txt");
        printf("Filme excluído com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Filme não encontrado!\n");
    }
}

void consultarFilme() {
    FILE *arquivo = fopen("filmes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Filme filme;
    int id, encontrado = 0;
    printf("Digite o ID do filme a ser consultado: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        if (filme.id == id) {
            encontrado = 1;
            printf("ID: %d\n", filme.id);
            printf("Título: %s\n", filme.titulo);
            printf("Gênero: %s\n", filme.genero);
            printf("Ano de Lançamento: %d\n", filme.ano);
            break;  // Adicionado para evitar repetição
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Filme não encontrado!\n");
    }
}

void listarFilmes() {
    FILE *arquivo = fopen("filmes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Filme filme;
    printf("Lista de Filmes:\n");

    while (fscanf(arquivo, "%d,%49[^,],%19[^,],%d\n", &filme.id, filme.titulo, filme.genero, &filme.ano) != EOF) {
        printf("ID: %d\n", filme.id);
        printf("Título: %s\n", filme.titulo);
        printf("Gênero: %s\n", filme.genero);
        printf("Ano de Lançamento: %d\n", filme.ano);
        printf("\n");
    }

    fclose(arquivo);
}
