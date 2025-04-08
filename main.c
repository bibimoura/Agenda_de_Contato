#include <stdio.h>
#include <string.h>
#define TAM 50

// Struct
typedef struct
{
    char nome[128];
    char telefone[15];
} Contato;

void cadastrar(Contato *listContato, int *totalContato, int *modificado);
void imprimir(Contato *listContato, int totalContato);
void deletar(Contato *listContato, int *totalContato, int *modificado);
void salvarContatos(Contato *listContato, int totalContato);
void lerContatos(Contato *listContato, int *totalContato);

int main()
{
    Contato agenda[TAM];
    int op = 0, modificado = 0;
    int totalContato = 0;

    lerContatos(agenda, &totalContato);

    // Menu
    do
    {
        printf("=-=-=-=-=-=-=-=-=-=-= Agenda de contatos =-=-=-=-=-=-=-=-=-=-=\n");
        printf("1 - Cadastro de novo contato\n");
        printf("2 - Imprimir agenda\n");
        printf("3 - Deletar um contato\n");
        printf("4 - Salvar\n");
        printf("5 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf(" %d", &op);


        printf("=-=-=-=-==--=-==-=-==-=-==-=-=-==-=-=-==-=-=-=-=-==-=-=-==-=-=\n");

        switch (op)
        {
        case 1:
            cadastrar(agenda, &totalContato, &modificado);
            break;
        case 2:
            imprimir(agenda, totalContato);
            break;
        case 3:
            deletar(agenda, &totalContato, &modificado);
            break;
        case 4:
            salvarContatos(agenda, totalContato);
            break;
        case 5:
            if (modificado == 1)
            {
                salvarContatos(agenda, totalContato);
            }
            printf("Saindo...");

            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (op != 5);

    return 0;
}

// Funcao para cadastrar um novo contato
void cadastrar(Contato *listContato, int *totalContato, int *modificado)
{

    printf("Quantidade de contatos: %d\n", *totalContato);

    if (*totalContato < TAM)
    {
        printf("Digite o nome do contato: ");
        scanf(" %127[^\n]", listContato[*totalContato].nome);

        printf("Digite o telefone (63 99999-9999): ");
        scanf(" %14[^\n]", listContato[*totalContato].telefone);

        (*totalContato)++;
        *modificado = 1;
        printf("Contato adicionado!\n");
    }
    else
    {
        printf("Agenda cheia!\n");
    }
}

// Função para imprimir a agenda
void imprimir(Contato *listContato, int totalContato)
{

    if (totalContato > 0)
    {
        printf("Lista de Contatos\n");
        for (int i = 0; i < totalContato; i++)
        {
            printf("Nome: %-20s  Telefone: %s\n", listContato[i].nome, listContato[i].telefone);
        }
    }
    else
    {
        printf("Agenda vazia!\n");
    }
}

// Funcao para deletar um contato
void deletar(Contato *listContato, int *totalContato, int *modificado)
{

    if (*totalContato > 0)
    {

        printf("Informe o contato a ser deletado: ");

        char nome[128];
        scanf(" %127[^\n]", nome);

        int achou = 0;

        for (int i = 0; i < *totalContato; i++)
        {
            if (strcmp(listContato[i].nome, nome) == 0)
            {
                achou = 1;
                for (int j = i; j < *totalContato - 1; j++)
                {
                    listContato[j] = listContato[j + 1];
                }

                (*totalContato)--;
                *modificado = 1;
                break;
            }
        }
        if (achou == 1)
        {
            printf("Contato removido. \n");
        }
        else
        {
            printf("Contato nao encontrado.\n");
        }
    }
    else
    {
        printf("Agenda vazia!\n");
    }
}

// Funcao para salvar em arquivo
void salvarContatos(Contato *listContato, int totalContato)
{

    FILE *arq_agenda = fopen("agenda.csv", "w");
    if (arq_agenda == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        return;
    }

    fprintf(arq_agenda, "%d", totalContato);
    for (int i = 0; i < totalContato; i++)
    {
        fprintf(arq_agenda, " %s, %s\n", listContato[i].nome, listContato[i].telefone);
    }

    fclose(arq_agenda);
    printf("Agenda salva!\n");
}

// Funcao para ler o arquivo
void lerContatos(Contato *listContato, int *totalContato)
{

    FILE *arq_agenda = fopen("agenda.csv", "r");
    if (arq_agenda == NULL)
    {
        printf("Erro na leitura do arquivo");
        return;
    }
    printf("=-=-=-=-==--=-==-=-==-=-==-=-=-==-=-=-==-=-=-=-=-==-=-=-==-=-=\n");
    printf("Carregando a agenda...\n");

    fscanf(arq_agenda, "%d\n", totalContato);

    for (int i = 0; i < *totalContato; i++)
    {
        fscanf(arq_agenda, " %127[^,], %14[^\n]\n", listContato[i].nome, listContato[i].telefone);
    }

    fclose(arq_agenda);
}