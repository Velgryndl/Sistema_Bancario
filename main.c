#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Limpar() {
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif
}

struct Lista {
    char nome[50];
    int idade;
    int cpf;
    char senha[50];
    float saldo;
};

void Conta(struct Lista *pessoa) {
    Limpar();
    int escolha;

    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fscanf(arquivo, "%s %d %lld %s %f", pessoa->nome, &pessoa->idade, &pessoa->cpf, pessoa->senha, &pessoa->saldo);
    fclose(arquivo);

    while (1) {
        printf("\t\t\t  Bem-Vindo(a), %s\n\n", pessoa->nome);
        printf("\t\t    Voce possui um Saldo de %.2f\n\n", pessoa->saldo);
        printf("\t\t(1) Depositar | (2) Sacar | (3) Voltar \n\t\t\t\t     ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            float deposito;
            printf("Depositar: ");
            scanf("%f", &deposito);

            pessoa->saldo += deposito;

            arquivo = fopen("dados.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo\n");
                exit(1);
            }

            fprintf(arquivo, "%s %d %lld %s %.2f\n", pessoa->nome, pessoa->idade, pessoa->cpf, pessoa->senha, pessoa->saldo);

            fclose(arquivo);
        } else if (escolha == 2) {
            float saque;
            printf("Sacar: ");
            scanf("%f", &saque);

            if (saque <= pessoa->saldo) {

                pessoa->saldo -= saque;

                arquivo = fopen("dados.txt", "w");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo\n");
                    exit(1);
                }

                fprintf(arquivo, "%s %d %lld %s %.2f\n", pessoa->nome, pessoa->idade, pessoa->cpf, pessoa->senha, pessoa->saldo);

                fclose(arquivo);
            } else {
                printf("Saldo insuficiente para sacar.\n");
            }
        } else if (escolha == 3) {

            main();
            return;
        } else {
            printf("Opcao invalida.\n");
        }
    }
}


int Entrar(struct Lista pessoa) {
    Limpar();

    char Vernome[50];
    int Veridade;
    int Vercpf;
    char Versenha[50];
    int tentativas = 3;

    while (tentativas > 0) {

        printf("\n\t\tLogin.\n\n");

        printf("Nome: ");
        scanf("%s", Vernome);

        printf("\nIdade: ");
        scanf("%d", &Veridade);

        printf("\nCPF: ");
        scanf("%d", &Vercpf);

        printf("\nSenha: ");
        scanf("%s", Versenha);

        if (strcmp(Vernome, pessoa.nome) == 0 && Veridade == pessoa.idade && Vercpf == pessoa.cpf && strcmp(Versenha, pessoa.senha) == 0) {
            Conta(&pessoa);
            return;
        } else {
            Limpar();
            printf("Acesso negado. Tente novamente. Tentativas restantes: %d\n", tentativas - 1);
            tentativas--;
        }
    }

    printf("Número máximo de tentativas atingido.\n");
    system("pause");
}

void Cadastrar(struct Lista *pessoa) {
    Limpar();

     printf("\n\t\tCadastrar.\n\n");

    printf("Nome: ");
    scanf("%s", pessoa->nome);

    printf("\nIdade: ");
    scanf("%d", &pessoa->idade);

    if (pessoa->idade < 18) {
        printf("Cadastro Negado\n");
        return;
    }

    printf("\nCPF: ");
    scanf("%d", &pessoa->cpf);

    printf("\nSenha: ");
    scanf("%s", pessoa->senha);

    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    fprintf(arquivo, "%s %d %d %s\n", pessoa->nome, pessoa->idade, pessoa->cpf, pessoa->senha);

    fclose(arquivo);
    printf("\nCadastro Completo !\n\n");
    system("pause");
}

int main() {
    Limpar();
    struct Lista pessoa;
    int Escolha = 0;

    printf("\t     Banco\n\n\n");
    printf("\t( 1 ) Entrar\n\n");
    printf("\t( 2 ) Cadastrar\n\n\t\t");
    scanf("%d", &Escolha);

    if (Escolha == 1) {
        FILE *arquivo = fopen("dados.txt", "r");
        if (arquivo == NULL) {
            printf("Nenhum usuário cadastrado. Cadastre-se primeiro.\n");
            return 1;
        }

        fscanf(arquivo, "%s %d %d %s", pessoa.nome, &pessoa.idade, &pessoa.cpf, pessoa.senha);
        fclose(arquivo);

        Entrar(pessoa);
    } else if (Escolha == 2) {
        Cadastrar(&pessoa);
        main();
    } else {
        printf("Opção inválida.\n");
    }

    return 0;
}
