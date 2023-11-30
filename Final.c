#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

struct info_veiculos
{
    char proprietario[100];
    int combustivel;
    char modelo[40];
    char cor[15];
    int chassi;
    int ano;
    char placa[11];
    int tipoCombustivel;
};

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void cadastrarVeiculo(struct info_veiculos **veiculos, int *totalVeiculos)
{
    *veiculos = realloc(*veiculos, (*totalVeiculos + 1) * sizeof(struct info_veiculos));

    if (*veiculos == NULL)
    {
        printf("Erro ao alocar memoria para o veiculo.\n");
        return;
    }
    limparBuffer();
    printf("Informe o proprietario: ");
    fgets((*veiculos)[*totalVeiculos].proprietario, sizeof((*veiculos)[*totalVeiculos].proprietario), stdin);
    fflush(stdin);

    printf("Informe o combustivel em litros: ");
    scanf("%d", &(*veiculos)[*totalVeiculos].combustivel);
    fflush(stdin);

    printf("Qual tipo de combustivel? 1- Alcool / 2- Diesel / 3- Gasolina: ");
    scanf("%d", &(*veiculos)[*totalVeiculos].tipoCombustivel);
    fflush(stdin);

    printf("Informe o modelo: ");
    fgets((*veiculos)[*totalVeiculos].modelo, sizeof((*veiculos)[*totalVeiculos].modelo), stdin);

    printf("Informe a cor: ");
    fgets((*veiculos)[*totalVeiculos].cor, sizeof((*veiculos)[*totalVeiculos].cor), stdin);

    int chassiExistente;

    do {
        chassiExistente = 0;  

        printf("Informe o numero do chassi: ");
        fflush(stdin);
        scanf("%d", &(*veiculos)[*totalVeiculos].chassi);
        fflush(stdin);

        for (int i = 0; i < *totalVeiculos; i++) {
            if ((*veiculos)[i].chassi == (*veiculos)[*totalVeiculos].chassi) {
                printf("Erro: Este chassi ja foi cadastrado. Por favor, informe um novo numero de chassi.\n");
                chassiExistente = 1;
                break;
            }
        }

    } while (chassiExistente);

    printf("Informe o ano: ");
    fflush(stdin);
    scanf("%d", &(*veiculos)[*totalVeiculos].ano);
    fflush(stdin);

    int placaValida = 0;
    do {
        printf("Informe a Placa (3 letras seguidas de 4 numeros): ");
        fgets((*veiculos)[*totalVeiculos].placa, sizeof((*veiculos)[*totalVeiculos].placa), stdin);

        int i;
        for (i = 0; i < 3; i++) {
            if (!isalpha((*veiculos)[*totalVeiculos].placa[i])) {
                printf("Erro: Os primeiros 3 caracteres da placa devem ser letras.\n");
                break;
            }
        }
        if (i == 3) {
            for (; i < 7; i++) {
                if (!isdigit((*veiculos)[*totalVeiculos].placa[i])) {
                    printf("Erro: Os ultimos 4 caracteres da placa devem ser numeros.\n");
                    break;
                }
            }
        }
        if (i == 7) {
            placaValida = 1;
        }
    } while (!placaValida);

    printf("Veiculo cadastrado com sucesso!\n");
    (*totalVeiculos)++;
    printf("---------------------------------------------\n");
    printf("Total de veiculos cadastrados ate o momento: %d\n", *totalVeiculos);
}

void listarProprietarios(struct info_veiculos *veiculos, int totalVeiculos)
{

    int retornar;
    printf("Proprietarios dos veiculos do ano de 2010 ou posterior e movidos a diesel:\n \n");
    for (int i = 0; i < totalVeiculos; i++)
    {
        if (veiculos[i].ano >= 2010 && veiculos[i].tipoCombustivel == 2)
        {
            printf("Proprietario: %s\n Veiculo: %s\n Placa: %s", veiculos[i].proprietario, veiculos[i].modelo, veiculos[i].placa);
            printf("---------------------------------------------\n");
        }
    }
    printf("Deseja retornar ao menu de opcoes? (1) = Sim / (0) = Fechar o programa\n Digite: ");
    scanf("%d", &retornar);

    switch (retornar)
    {
    case 1:
        return;
        break;

    case 0:
        exit(retornar);
        break;

    default:
        return;
        break;
    }
}

void listarPlacasJ(struct info_veiculos *veiculos, int totalVeiculos)
{
    int retornar;

    printf("Placas que comecem com a letra J e terminem com 0, 2, 4 ou 7 e seus respectivos proprietarios:\n");
    for (int i = 0; i < totalVeiculos; i++)
    {
        if (veiculos[i].placa[0] == 'J' &&
            (veiculos[i].placa[6] == '0' || veiculos[i].placa[6] == '2' || veiculos[i].placa[6] == '4' || veiculos[i].placa[6] == '7'))
        {

            size_t len = strlen(veiculos[i].proprietario);
            if (len > 0 && veiculos[i].proprietario[len - 1] == '\n')
            {
                veiculos[i].proprietario[len - 1] = '\0';
            }

            printf("Placa: %s \nProprietario: %s\n", veiculos[i].placa, veiculos[i].proprietario);
            printf("---------------------------------------------\n");
        }
    }

    printf("---------------------------------------------\n");
    printf("Deseja retornar ao menu de opcoes? (1) = Sim / (0) = Fechar o programa\nDigite: ");
    scanf("%d", &retornar);

    switch (retornar)
    {
    case 1:
        return;
        break;

    case 0:
        exit(retornar);
        break;

    default:
        return;
        break;
    }
}

void listarModelosCores(struct info_veiculos *veiculos, int totalVeiculos)
{
    printf("Modelos e cores dos veiculos (placas com segunda letra vogal e soma dos valores numericos e par):\n");

    for (int i = 0; i < totalVeiculos; i++)
    {
        if (strchr("AEIOUaeiou", veiculos[i].placa[1]) != NULL)
        {
            int somaNumeros = 0;
            for (int j = 0; j < strlen(veiculos[i].placa); j++)
            {
                if (isdigit(veiculos[i].placa[j]))
                {
                    somaNumeros = somaNumeros * 10 + (veiculos[i].placa[j] - '0');
                }
            }

            if (somaNumeros % 2 == 0)
            {
                size_t lenModelo = strlen(veiculos[i].modelo);
                if (lenModelo > 0 && veiculos[i].modelo[lenModelo - 1] == '\n')
                {
                    veiculos[i].modelo[lenModelo - 1] = '\0';
                }

                size_t lenCor = strlen(veiculos[i].cor);
                if (lenCor > 0 && veiculos[i].cor[lenCor - 1] == '\n')
                {
                    veiculos[i].cor[lenCor - 1] = '\0';
                }

                printf("Modelo: %s, Cor: %s\n", veiculos[i].modelo, veiculos[i].cor);
                printf("---------------------------------------------\n");
            }
        }
    }
}

void trocarProprietario(struct info_veiculos *veiculos, int totalVeiculos) {
    int numeroChassi;

    printf("Informe o numero do chassi para troca de proprietario: ");
    scanf("%d", &numeroChassi);
    limparBuffer(); 

    int indiceVeiculo = -1;
    for (int i = 0; i < totalVeiculos; i++) {
        if (veiculos[i].chassi == numeroChassi && !strchr(veiculos[i].placa, '0')) {
            indiceVeiculo = i;
            break;
        }
    }

    if (indiceVeiculo == -1) {
        printf("Nenhum veiculo encontrado com o numero do chassi informado ou a placa possui digito zero.\n");
    } else {
        printf("Informe o novo proprietario: ");
        fgets(veiculos[indiceVeiculo].proprietario, sizeof(veiculos[indiceVeiculo].proprietario), stdin);
        fflush(stdin);

        printf("Proprietario trocado com sucesso!\n");
    }

    printf("---------------------------------------------------------------\n");
}

int main()
{
    struct info_veiculos *veiculos = NULL;
    int totalVeiculos = 0;
    int switchOptions;

    do
    {
        printf("---------------------------------------------\n");
        printf("Selecione uma opcao:\n 1- Cadastrar um novo veiculo\n 2- Listar proprietarios (cujos carros sao do ano de 2010 ou posterior e que sejam movidos a diesel.)\n 3- Listar Placas que comecem com a letra J e terminem com 0, 2, 4 ou 7 e seus respectivos proprietarios.\n 4- Listar modelos e cores dos veiculos (cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numericos fornece um numero par.)\n 5- Trocar proprietario do veiculo (apenas para carros com placas que nao possuam nenhum digito igual a zero.)\n 0- Sair\n Digite: ");
        scanf("%d", &switchOptions);
        printf("---------------------------------------------\n");

        switch (switchOptions)
        {
        case 1:
            cadastrarVeiculo(&veiculos, &totalVeiculos);
            break;
        case 2:
            listarProprietarios(veiculos, totalVeiculos);

            break;
        case 3:
            listarPlacasJ(veiculos, totalVeiculos);

            break;
        case 4:
            listarModelosCores(veiculos, totalVeiculos);
            break;
        case 5:
            trocarProprietario(veiculos, totalVeiculos);
            break;
        case 0:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (switchOptions != 0);

    free(veiculos);

    return 0;
}