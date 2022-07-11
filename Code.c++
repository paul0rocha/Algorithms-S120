#include <stdio.h>
#include <string.h>
#define LINE 200

int qtdQuestoes;
char nomeAluno[LINE][50];
char mRespostaAluno[LINE][10];
float resultado[LINE];
int faltas[LINE];
int situacao[LINE];

// situacao == 1 aprovado, situacao == 2 recuperaÃ§Ã£o, situacao == 3 reprovado

char nomeProf[50];
char materia[50];
char gabarito[10];

cadastrar(qtdQuestoes)
{
    int numQuest;

    printf("\n Digite seu nome Professor(a): ");
    scanf("%s", &nomeProf);
    setbuf(stdin, NULL);

    printf("\n Digite a materia: ");
    scanf("%s", &materia);

    for (numQuest = 0; numQuest < qtdQuestoes; numQuest++)
    {
        printf("\n Digite a alternativa correta da questao %d: ", numQuest + 1);
        scanf("%s", &gabarito[numQuest]);
    }
}

cadastrarAluno(qtdQuestoes)
{
    static int linha;
    int sit;

    do
    {
        int numQuest;

        printf("\n Digite o nome do aluno: ");
        scanf("%s", &nomeAluno[linha]);

        printf("\n Digite a quantidade de faltas: ");
        scanf("%d", &faltas[linha]);

        for (numQuest = 0; numQuest < qtdQuestoes; numQuest++)
        {
            printf("\n Digite a alternativa selecionada pelo aluno na questao %d: ", numQuest + 1);
            scanf("%s", &mRespostaAluno[linha][numQuest]);
        }
        printf("\n Digite 1 para continuar ou outro valor para sair ");
        scanf("%d", &sit);

        linha++;

    } while (sit == 1);

    corrigir(qtdQuestoes);
}

corrigir(qtdQuestoes)
{
    int contAluno, contQuest, numAc;

    for (contAluno = 0; contAluno < LINE; contAluno++)
    {
        if (situacao[contAluno] == 0)
        {
            numAc = 0;
            for (contQuest = 0; contQuest < qtdQuestoes; contQuest++)
            {
                if (mRespostaAluno[contAluno][contQuest] == gabarito[contQuest])
                {
                    numAc++;
                }
            }
            resultado[contAluno] = (10 / qtdQuestoes) * numAc * 1.0;
        }
    }
}

void listar()
{
    int i, x;

    system("cls");

    do
    {
        for (i = 0; strlen(nomeAluno[i]) != 0; i++)
        {
            if (situacao[i] == 0)
            {
                if (faltas[i] >= 20)
                {
                    situacao[i] = 3;
                    printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Reprovado\n", i + 1, nomeAluno[i], resultado[i]);
                }
                else
                {
                    if (resultado[i] >= 5)
                    {
                        situacao[i] = 1;
                        printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Aprovado\n", i + 1, nomeAluno[i], resultado[i]);
                    }
                    else
                    {
                        situacao[i] = 2;
                        printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Recuperacao\n", i + 1, nomeAluno[i], resultado[i]);
                    }
                }
            }
            else
            {
                if (situacao[i] == 3)
                {
                    printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Reprovado\n", i + 1, nomeAluno[i], resultado[i]);
                }
                else if (situacao[i] == 1)
                {
                    printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Aprovado\n", i + 1, nomeAluno[i], resultado[i]);
                }
                else if (situacao[i] == 2)
                {
                    printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Recuperacao\n", i + 1, nomeAluno[i], resultado[i]);
                }
            }
        }
        printf("\n\nDigite 1 para voltar ao menu ");
        scanf("%d", &x);

    } while (x != 1);
}

void recuperar()
{
    int i, x, y;
    float subst;

    do
    {
        system("cls");

        printf("\n----ALUNOS DE RECUPERACAO----\n");

        for (i = 0; strlen(nomeAluno[i]) != 0; i++)
        {
            if (situacao[i] == 2)
            {
                printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Recuperacao\n", i + 1, nomeAluno[i], resultado[i]);

                printf("\nDigite o numero do aluno caso queira que adicione uma nota de recuperacao, se nao digite qualquer numero para continuar ");
                scanf("%d", &x);

                if ((x - 1) == i)
                {
                    printf("\nInsira a nota com um peso de 40%% ");
                    scanf("%f", &subst);

                    resultado[i] = ((resultado[i] * 6) + (subst * 4)) / 10;
                }
            }

            if (resultado[i] >= 5)
            {
                situacao[i] = 1;
                printf("\n-Nova Nota-\nAluno %d:\nNome: %s - %.2f\nSituacao: Aprovado\n", i + 1, nomeAluno[i], resultado[i]);
            }
            else
            {
                situacao[i] = 3;
                printf("\nAluno %d:\nNome: %s - %.2f\nSituacao: Reprovado\n", i + 1, nomeAluno[i], resultado[i]);
            }
        }

        printf("\n\nDigite 1 para voltar ao menu ");
        scanf("%d", &y);

    } while (y != 1);
}

void menu()
{
    int op;

    do
    {
        system("cls");
        printf("Ola professor(a)%s da disciplina %s\n", nomeProf, materia);
        printf("\n ---MENU--- \n\n1 - Cadastrar Aluno \n2 - Listar Alunos\n3 - Entrar com pedido de Recuperacao\n4 - Sair\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastrarAluno(qtdQuestoes);
            break;
        case 2:
            listar();
            break;
        case 3:
            recuperar();
            break;
        case 4:
            system("exit");
            break;

        default:
            printf("\n Opcao Invalida");
            getchar();
            getchar();
            break;
        }

    } while (op != 4);
}

int main()
{
    printf("------------GESTOR ESCOLAR------------\n");

    printf("\nInsira a quantidade de questoes na avaliacao: ");
    scanf("%i", &qtdQuestoes);

    cadastrar(qtdQuestoes);
    menu();

    return 0;
}
