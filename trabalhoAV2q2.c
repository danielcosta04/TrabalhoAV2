#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura de funcionário
typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    float salario;  // Alterado para float
} Funcionario;

// Funções para manipulação de funcionários
void cadastrarFuncionario();
void alterarFuncionario();
void excluirFuncionario();
void consultarFuncionario();
void listarFuncionarios();

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configuração de localidade

    int opcao;
    do {
        printf("\nCadastro de Funcionários\n");
        printf("1. Cadastrar um novo funcionário\n");
        printf("2. Alterar dados de um funcionário\n");
        printf("3. Excluir um funcionário pelo ID\n");
        printf("4. Consultar informações de um funcionário pelo ID\n");
        printf("5. Listar todos os funcionários cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
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
                printf("Opção inválida. Tente novamente.\n");
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
    printf("Digite o salário: ");
    scanf("%f", &funcionario.salario);  // Alterado para %f
    getchar();

    fprintf(arquivo, "%d,%s,%s,%.2f\n", funcionario.id, funcionario.nome, funcionario.cargo, funcionario.salario);  // Alterado para %.2f

    fclose(arquivo);
    printf("Funcionário cadastrado com sucesso!\n");
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
    printf("Digite o ID do funcionário a ser alterado: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%f\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("Funcionário encontrado. Digite os novos dados.\n");
            printf("Digite o novo cargo: ");
            fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
            strtok(funcionario.cargo, "\n");
            printf("Digite o novo salário: ");
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
        printf("Dados do funcionário alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Funcionário não encontrado!\n");
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
    printf("Digite o ID do funcionário a ser excluído: ");
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
        printf("Funcionário excluído com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Funcionário não encontrado!\n");
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
    printf("Digite o ID do funcionário a ser consultado: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%f\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        if (funcionario.id == id) {
            encontrado = 1;
            printf("ID: %d\n", funcionario.id);
            printf("Nome: %s\n", funcionario.nome);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salário: %.2f\n", funcionario.salario);  // Alterado para %.2f
            break; //evita repetições teacher           
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Funcionário não encontrado!\n");
    }
}

void listarFuncionarios() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Funcionario funcionario;
    printf("Lista de Funcionários:\n");

    while (fscanf(arquivo, "%d,%49[^,],%29[^,],%f\n", &funcionario.id, funcionario.nome, funcionario.cargo, &funcionario.salario) != EOF) {
        printf("ID: %d\n", funcionario.id);
        printf("Nome: %s\n", funcionario.nome);
        printf("Cargo: %s\n", funcionario.cargo);
        printf("Salário: %.2f\n", funcionario.salario);  // Alterado para %.2f
        printf("\n");
    }

    fclose(arquivo);
}
