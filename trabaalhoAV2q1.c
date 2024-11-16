#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��o da estrutura de aluno
typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
    int idade;
} Aluno;

// Fun��es para manipula��o de alunos
void incluirAluno();
void alterarAluno();
void excluirAluno();
void consultarAluno();
void listarAlunos();

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int opcao;
    do {
        printf("\nSistema de Gerenciamento de Alunos\n");
        printf("1. Incluir um novo aluno\n");
        printf("2. Alterar informa��es de um aluno\n");
        printf("3. Excluir um aluno pelo n�mero de matr�cula\n");
        printf("4. Consultar informa��es de um aluno\n");
        printf("5. Listar todos os alunos cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        switch (opcao) {
            case 1:
                incluirAluno();
                break;
            case 2:
                alterarAluno();
                break;
            case 3:
                excluirAluno();
                break;
            case 4:
                consultarAluno();
                break;
            case 5:
                listarAlunos();
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

void incluirAluno() {
    FILE *arquivo = fopen("alunos.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Aluno aluno;
    printf("Digite o n�mero de matr�cula: ");
    scanf("%d", &aluno.matricula);
    getchar();
    printf("Digite o nome: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    strtok(aluno.nome, "\n");
    printf("Digite o curso: ");
    fgets(aluno.curso, sizeof(aluno.curso), stdin);
    strtok(aluno.curso, "\n");
    printf("Digite a idade: ");
    scanf("%d", &aluno.idade);

    fprintf(arquivo, "%d,%s,%s,%d\n", aluno.matricula, aluno.nome, aluno.curso, aluno.idade);

    fclose(arquivo);
    printf("Aluno inclu�do com sucesso!\n");
}

void alterarAluno() {
    FILE *arquivo = fopen("alunos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Aluno aluno;
    int matricula, encontrado = 0;
    printf("Digite o n�mero de matr�cula do aluno a ser alterado: ");
    scanf("%d", &matricula);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &aluno.matricula, aluno.nome, aluno.curso, &aluno.idade) != EOF) {
        if (aluno.matricula == matricula) {
            encontrado = 1;
            printf("Aluno encontrado. Digite os novos dados.\n");
            printf("Digite o novo nome: ");
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            strtok(aluno.nome, "\n");
            printf("Digite o novo curso: ");
            fgets(aluno.curso, sizeof(aluno.curso), stdin);
            strtok(aluno.curso, "\n");
            printf("Digite a nova idade: ");
            scanf("%d", &aluno.idade);
        }
        fprintf(temp, "%d,%s,%s,%d\n", aluno.matricula, aluno.nome, aluno.curso, aluno.idade);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("alunos.txt");
        rename("temp.txt", "alunos.txt");
        printf("Informa��es do aluno alteradas com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Aluno n�o encontrado!\n");
    }
}

void excluirAluno() {
    FILE *arquivo = fopen("alunos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Aluno aluno;
    int matricula, encontrado = 0;
    printf("Digite o n�mero de matr�cula do aluno a ser exclu�do: ");
    scanf("%d", &matricula);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &aluno.matricula, aluno.nome, aluno.curso, &aluno.idade) != EOF) {
        if (aluno.matricula != matricula) {
            fprintf(temp, "%d,%s,%s,%d\n", aluno.matricula, aluno.nome, aluno.curso, aluno.idade);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("alunos.txt");
        rename("temp.txt", "alunos.txt");
        printf("Aluno exclu�do com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Aluno n�o encontrado!\n");
    }
}

void consultarAluno() {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Aluno aluno;
    int matricula, encontrado = 0;
    printf("Digite o n�mero de matr�cula do aluno a ser consultado: ");
    scanf("%d", &matricula);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &aluno.matricula, aluno.nome, aluno.curso, &aluno.idade) != EOF) {
        if (aluno.matricula == matricula) {
            encontrado = 1;
            printf("Matr�cula: %d\n", aluno.matricula);
            printf("Nome: %s\n", aluno.nome);
            printf("Curso: %s\n", aluno.curso);
            printf("Idade: %d\n", aluno.idade);
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Aluno n�o encontrado!\n");
    }
}

void listarAlunos() {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Aluno aluno;
    printf("Lista de Alunos:\n");

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%d\n", &aluno.matricula, aluno.nome, aluno.curso, &aluno.idade) != EOF) {
        printf("Matr�cula: %d\n", aluno.matricula);
        printf("Nome: %s\n", aluno.nome);
        printf("Curso: %s\n", aluno.curso);
        printf("Idade: %d\n", aluno.idade);
        printf("\n");
    }

    fclose(arquivo);
}