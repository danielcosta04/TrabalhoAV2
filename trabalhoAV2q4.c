#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��o da estrutura de ve�culo
typedef struct {
    int id;
    char modelo[50];
    char placa[10];
    int ano;
} Veiculo;

// Fun��es para manipula��o de ve�culos
void adicionarVeiculo();
void alterarVeiculo();
void excluirVeiculo();
void consultarVeiculo();
void listarVeiculos();

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  // Configura��o de localidade

    int opcao;
    do {
        printf("\nRegistro de Ve�culos\n");
        printf("1. Adicionar um novo ve�culo\n");
        printf("2. Alterar os dados de um ve�culo\n");
        printf("3. Excluir um ve�culo pelo ID\n");
        printf("4. Consultar as informa��es de um ve�culo pela placa\n");
        printf("5. Listar todos os ve�culos cadastrados\n");
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida. Tente novamente.\n");
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
    printf("Digite o ano de fabrica��o: ");
    scanf("%d", &veiculo.ano);
    getchar();  // Limpar buffer

    fprintf(arquivo, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);

    fclose(arquivo);
    printf("Ve�culo adicionado com sucesso!\n");
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
    printf("Digite o ID do ve�culo a ser alterado: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    while (fscanf(arquivo, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (veiculo.id == id) {
            encontrado = 1;
            printf("Ve�culo encontrado. Digite os novos dados.\n");
            printf("Digite o novo modelo: ");
            fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
            strtok(veiculo.modelo, "\n");
            printf("Digite a nova placa: ");
            fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
            strtok(veiculo.placa, "\n");
            printf("Digite o novo ano de fabrica��o: ");
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
        printf("Dados do ve�culo alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Ve�culo n�o encontrado!\n");
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
    printf("Digite o ID do ve�culo a ser exclu�do: ");
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
        printf("Ve�culo exclu�do com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Ve�culo n�o encontrado!\n");
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
    printf("Digite a placa do ve�culo a ser consultado: ");
    fgets(placa, sizeof(placa), stdin);
    strtok(placa, "\n");

    while (fscanf(arquivo, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        if (strcmp(veiculo.placa, placa) == 0) {
            encontrado = 1;
            printf("ID: %d\n", veiculo.id);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Placa: %s\n", veiculo.placa);
            printf("Ano de Fabrica��o: %d\n", veiculo.ano);
            break;  // Adicionado para evitar repeti��o
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Ve�culo n�o encontrado!\n");
    }
}

void listarVeiculos() {
    FILE *arquivo = fopen("veiculos.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Veiculo veiculo;
    printf("Lista de Ve�culos:\n");

    while (fscanf(arquivo, "%d,%49[^,],%9[^,],%d\n", &veiculo.id, veiculo.modelo, veiculo.placa, &veiculo.ano) != EOF) {
        printf("ID: %d\n", veiculo.id);
        printf("Modelo: %s\n", veiculo.modelo);
        printf("Placa: %s\n", veiculo.placa);
        printf("Ano de Fabrica��o: %d\n", veiculo.ano);
        printf("\n");
    }

    fclose(arquivo);
}
