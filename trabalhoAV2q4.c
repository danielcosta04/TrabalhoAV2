#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura de veículo
typedef struct {
    int id;
    char modelo[50];
    char placa[10];
    int ano;
} Veiculo;

// Funções para manipulação de veículos
void adicionarVeiculo();
void alterarVeiculo();
void excluirVeiculo();
void consultarVeiculo();
void listarVeiculos();

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configuração de localidade

    int opcao;
    do {
        printf("\nRegistro de Veículos\n");
        printf("1. Adicionar um novo veículo\n");
        printf("2. Alterar os dados de um veículo\n");
        printf("3. Excluir um veículo pelo ID\n");
        printf("4. Consultar as informações de um veículo pela placa\n");
        printf("5. Listar todos os veículos cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        switch (opcao) {
            case 1:
                adicionarVeiculo();
                break;
            case 2:
                alterarVeiculo();
                break;
            case 3:
                excluirVeiculo();
                break;
            case 4:
                consultarVeiculo();
                break;
            case 5:
                listarVeiculos();
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

void adicionarVeiculo() {
    FILE *arquivo = fopen("veiculos.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Veiculo veiculo;
    printf("Digite o ID: ");
    scanf("%d", &veiculo.id);
    getchar();  // Limpar buffer
    printf("Digite o modelo: ");
    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
    strtok(veiculo.modelo, "\n");
    printf("Digite a placa: ");
    fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
    strtok(veiculo.placa, "\n");
    printf("Digite o ano de fabricação: ");
    scanf("%d", &veiculo.ano);
    getchar();  // Limpar buffer

    fprintf(arquivo, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);

    fclose(arquivo);
    printf("Veículo adicionado com sucesso!\n");
}

void alterarVeiculo() {
    FILE *arquivo = fopen("veiculos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Veiculo veiculo;
    int id, encontrado = 0;
    printf("Digite o ID do veículo a ser alterado: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (veiculo.id == id) {
            encontrado = 1;
            printf("Veículo encontrado. Digite os novos dados.\n");
            printf("Digite o novo modelo: ");
            fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
            strtok(veiculo.modelo, "\n");
            printf("Digite a nova placa: ");
            fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
            strtok(veiculo.placa, "\n");
            printf("Digite o novo ano de fabricação: ");
            scanf("%d", &veiculo.ano);
            getchar();  // Limpar buffer
        }
        fprintf(temp, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("veiculos.txt");
        rename("temp.txt", "veiculos.txt");
        printf("Dados do veículo alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Veículo não encontrado!\n");
    }
}

void excluirVeiculo() {
    FILE *arquivo = fopen("veiculos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Veiculo veiculo;
    int id, encontrado = 0;
    printf("Digite o ID do veículo a ser excluído: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (veiculo.id != id) {
            fprintf(temp, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove("veiculos.txt");
        rename("temp.txt", "veiculos.txt");
        printf("Veículo excluído com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Veículo não encontrado!\n");
    }
}

void consultarVeiculo() {
    FILE *arquivo = fopen("veiculos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Veiculo veiculo;
    char placa[10];
    int encontrado = 0;
    printf("Digite a placa do veículo a ser consultado: ");
    fgets(placa, sizeof(placa), stdin);
    strtok(placa, "\n");

    while (fscanf(arquivo, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (strcmp(veiculo.placa, placa) == 0) {
            encontrado = 1;
            printf("ID: %d\n", veiculo.id);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Placa: %s\n", veiculo.placa);
            printf("Ano de Fabricação: %d\n", veiculo.ano);
            break;  // Adicionado para evitar repetição
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Veículo não encontrado!\n");
    }
}

void listarVeiculos() {
    FILE *arquivo = fopen("veiculos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Veiculo veiculo;
    printf("Lista de Veículos:\n");

    while (fscanf(arquivo, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        printf("ID: %d\n", veiculo.id);
        printf("Modelo: %s\n", veiculo.modelo);
        printf("Placa: %s\n", veiculo.placa);
        printf("Ano de Fabricação: %d\n", veiculo.ano);
        printf("\n");
    }

    fclose(arquivo);
}
