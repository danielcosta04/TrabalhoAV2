#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��o da estrutura de funcion�rio
typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    float salario;  // Alterado para float
} Funcionario;

// Fun��es para manipula��o de funcion�rios
void cadastrarFuncionario();
void alterarFuncionario();
void excluirFuncionario();
void consultarFuncionario();
void listarFuncionarios();

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configura��o de localidade

    int opcao;
    do {
        printf("\nCadastro de Funcion�rios\n");
        printf("1. Cadastrar um novo funcion�rio\n");
        printf("2. Alterar dados de um funcion�rio\n");
        printf("3. Excluir um funcion�rio pelo ID\n");
        printf("4. Consultar informa��es de um funcion�rio pelo ID\n");
        printf("5. Listar todos os funcion�rios cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        switch (opcao) {
            case 1:
                cadastrarFuncionario();
                break;
            case 2:
                alterarFuncionario();
                break;
            case 3:
                excluirFuncionario();
                break;
            case 4:
                consultarFuncionario();
                break;
            case 5:
                listarFuncionarios();
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

void cadastrarFuncionario() {
    FILE *arquivo = fopen("funcionarios.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Funcionario funcionario;
    printf("Digite o ID: ");
    scanf("%d", &funcionario.id);
    getchar();
    printf("Digite o nome: ");
    fgets(funcionario.nome, sizeof(funcionario.nome), stdin);
    strtok(funcionario.nome, "\n");
    printf("Digite o cargo: ");
    fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
    strtok(funcionario.cargo, "\n");
    printf("Digite o sal�rio: ");
    scanf("%f", &funcionario.salario);  // Alterado para %f
    getchar();

    fprintf(arquivo, "%d,%s,%s,%.2f\n", funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);  // Alterado para %.2f

    fclose(arquivo);
    printf("Funcion�rio cadastrado com sucesso!\n");
}

void alterarFuncionario() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Funcionario funcionario;
    int id, encontrado = 0;
    printf("Digite o ID do funcion�rio a ser alterado: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%f\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("Funcion�rio encontrado. Digite os novos dados.\n");
            printf("Digite o novo cargo: ");
            fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
            strtok(funcionario.cargo, "\n");
            printf("Digite o novo sal�rio: ");
            scanf("%f", &funcionario.salario);  // Alterado para %f
            getchar();
        }
        fprintf(temp, "%d,%s,%s,%.2f\n", funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);  // Alterado para %.2f
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("funcionarios.txt");
        rename("temp.txt", "funcionarios.txt");
        printf("Dados do funcion�rio alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Funcion�rio n�o encontrado!\n");
    }
}

void excluirFuncionario() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Funcionario funcionario;
    int id, encontrado = 0;
    printf("Digite o ID do funcion�rio a ser exclu�do: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%f\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id != id) {
            fprintf(temp, "%d,%s,%s,%.2f\n", funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);  // Alterado para %.2f
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("funcionarios.txt");
        rename("temp.txt", "funcionarios.txt");
        printf("Funcion�rio exclu�do com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Funcion�rio n�o encontrado!\n");
    }
}

void consultarFuncionario() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Funcionario funcionario;
    int id, encontrado = 0;
    printf("Digite o ID do funcion�rio a ser consultado: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%f\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("ID: %d\n", funcionario.id);
            printf("Nome: %s\n", funcionario.nome);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Sal�rio: %.2f\n", funcionario.salario);  // Alterado para %.2f
            break; //evita repeti��es teacher           
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Funcion�rio n�o encontrado!\n");
    }
}

void listarFuncionarios() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Funcionario funcionario;
    printf("Lista de Funcion�rios:\n");

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%f\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        printf("ID: %d\n", funcionario.id);
        printf("Nome: %s\n", funcionario.nome);
        printf("Cargo: %s\n", funcionario.cargo);
        printf("Sal�rio: %.2f\n", funcionario.salario);  // Alterado para %.2f
        printf("\n");
    }

    fclose(arquivo);
}
