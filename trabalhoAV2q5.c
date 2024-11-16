#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��o da estrutura de filme
typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int ano;
} Filme;

// Fun��es para manipula��o de filmes
void adicionarFilme();
void alterarFilme();
void excluirFilme();
void consultarFilme();
void listarFilmes();

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configura��o de localidade

    int opcao;
    do {
        printf("\nControle de Filmes\n");
        printf("1. Adicionar um novo filme\n");
        printf("2. Alterar os dados de um filme\n");
        printf("3. Excluir um filme pelo ID\n");
        printf("4. Consultar as informa��es de um filme pelo ID\n");
        printf("5. Listar todos os filmes cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
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
    printf("Digite o t�tulo: ");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    strtok(filme.titulo, "\n");
    printf("Digite o g�nero: ");
    fgets(filme.genero, sizeof(filme.genero), stdin);
    strtok(filme.genero, "\n");
    printf("Digite o ano de lan�amento: ");
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
            printf("Digite o novo t�tulo: ");
            fgets(filme.titulo, sizeof(filme.titulo), stdin);
            strtok(filme.titulo, "\n");
            printf("Digite o novo g�nero: ");
            fgets(filme.genero, sizeof(filme.genero), stdin);
            strtok(filme.genero, "\n");
            printf("Digite o novo ano de lan�amento: ");
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
        printf("Filme n�o encontrado!\n");
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
    printf("Digite o ID do filme a ser exclu�do: ");
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
        printf("Filme exclu�do com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Filme n�o encontrado!\n");
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
            printf("T�tulo: %s\n", filme.titulo);
            printf("G�nero: %s\n", filme.genero);
            printf("Ano de Lan�amento: %d\n", filme.ano);
            break;  // Adicionado para evitar repeti��o
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Filme n�o encontrado!\n");
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
        printf("T�tulo: %s\n", filme.titulo);
        printf("G�nero: %s\n", filme.genero);
        printf("Ano de Lan�amento: %d\n", filme.ano);
        printf("\n");
    }

    fclose(arquivo);
}
