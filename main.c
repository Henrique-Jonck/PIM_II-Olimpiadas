// VERS�O 0.2

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>


int main()
{
    setlocale(LC_ALL, "Portuguese");

    Logo();
    Entrada();
    MenuPrincipal();

    return 0;
}

void Logo()
{
    /********************************************************************/
    /// Imprime uma logo das olimpiadas com as informa��es do trabalho ///
    /********************************************************************/

    system("cls");
    printf( "             Gerenciador das Olimp�adas de Paris 2024              \n"
            "                Projeto PIM II - 'Nome do projeto'                 \n"
            "                     UNIP Paulista - 00/00/2021                  \n\n"
            "            .,::OOO::,.     .,ooOOOoo,.     .,::OOO::,.            \n"
            "          .:'         `:. .8'         `8. .:'         `:.          \n"
            "          :\"           \": 8\"           \"8 :\"           \":    \n"
            "          :,        .,:::\"\"::,.     .,:o8OO::,.        ,:        \n"
            "           :,,    .:' ,:   8oo`:. .:'oo8   :,,`:.    ,,:           \n"
            "            `^OOoo:\"O^'     `^88oo:\"8^'     `^O\":ooOO^'         \n"
            "                  :,           ,: :,           ,:                  \n"
            "                   :,,       ,,:   :,,       ,,:                   \n"
            "                    `^Oo,,,oO^'     `^OOoooOO^'                  \n\n");

    printf( "                            Integrantes                            \n"
            "             Fabio Stein Miranda de Oliveira - G243447             \n"
            "                  Felipe Porto Rodrigues - N698381                 \n"
            "           Guilherme Augusto dos Santos Ribeiro - G247850          \n"
            "                  Henrique Campos Jonck - G298AB3                  \n"
            "             Petra Eduarda de Jesus Furlanis - G27EHB1             \n"
            "                 Vin�cius Riqueza Moeller - G27BAH0            \n\n\n");

    system("pause");
}

///---------------------------------------------------------------------------------------------------/
/// TELA DE LOGIN
///

void Entrada()
{
    /*********************************************************/
    /// Menu para sele��o de Login ou de Cadastro de usu�rio */
    /*********************************************************/

    /// Declara��o de Variaveis
    int opcao;

    /// Impress�o do Menu
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                          Tela de Login                          |\n"
            "+-----------------------------------------------------------------+\n"
            " 1- Login                                                          \n"
            " 2- Cadastrar                                                    \n\n");

    printf("--> ");
    scanf("%d", &opcao);

    /// Filtar sele��o
    switch(opcao)
    {
        case 1:
            UsuarioLogin();
            break;
        case 2:
            UsuarioCadastro();
            break;
        default:
            Entrada();
    }
}

void UsuarioLogin()
{
    /***********************************/
    /// Login de um usu�rio existente ///
    /***********************************/

    /// Declara��o de Variaveis
    FILE *arquivo;
    char *resultado, *pedaco;
    char verificacao, usuario[30], senha[30], dados1[100], dados2[100], matriz[2][50];
    int i, acesso = 0;

    /// Impress�o do Menu
    ImprimeMenuLogin();

    /// Abertura do Arquivo de Usu�rios
    arquivo = fopen("usuarios.txt", "r");

    /// Verifica a Abertura do Arquivo
    if(arquivo == NULL)
    {
        printf(" Erro na abertura do arquivo!\n");
        getch();
        Entrada();
    }

    /// Entrada dos Dados
    printf(" Login: ");
    scanf("%s", usuario);
    printf(" Senha: ");
    scanf("%s", senha);

    // Pergunta se os dados est�o corretos
    printf("\nDados corretos? \n[S,N]--> ");
    setbuf(stdin, NULL);
    scanf("%c", &verificacao);

    // Verifica caso os dados estejam corretos
    if((verificacao == 's')||(verificacao == 'S'))
    {
        // Percorre cada linha do arquivo
        while(!feof(arquivo))
        {
            // Retorna a linha para a variavel "dados"
            resultado = fgets(dados1, 100, arquivo);

            // Copia os valores do primeiro vetor para o segundo vetor
            for(int a = 0; a < 100; a++)
            {
                dados2[a] = dados1[a];
            }

            // Verifica se foi possivel retornar alguma string da linha
            i = 0;
            if(resultado)
            {
                // Reparte a varivel "dados" a cada caractere "�" e envia para o ponteiro "pedaco"
                pedaco = strtok(dados2, "�");

                // Percorre por cada reparti��o em "pedaco"
                while(pedaco)
                {
                    // Atribui a "matriz" cada valor de "padaco" separadamente
                    strcpy(matriz[i],pedaco);
                    pedaco = strtok(NULL, "�");
                    i++;
                }
            }
            // Verifica se os dados digitados batem com os do sistema, se sim retorna 1
            if((!strcmp(matriz[0], usuario))&(!strcmp(matriz[1], senha)))
                acesso = 1;
        }

        /// Fechamento do Arquivo de Usu�rios
        fclose(arquivo);

        /// Verifica��o dos Dados
        if(acesso == 0)
        {
            ImprimeMenuLogin();
            printf(" Usu�rio ou Senha incorretos!\n\nCadastrar novo usu�rio? \n[S,N]--> ");
            setbuf(stdin, NULL);
            scanf("%c", &verificacao);

            if((verificacao == 's')||(verificacao == 'S'))
            {
                UsuarioCadastro();
            }else
            {
                UsuarioLogin();
            }
        }else
        {
            MenuPrincipal();
        }
    }else
    {
        UsuarioLogin();
    }
}

void UsuarioCadastro()
{
    /*********************************/
    /// Cadastro de um novo usu�rio ///
    /*********************************/

    /// Declara��o de Variaveis
    FILE *arquivo;
    char usuario[50], senha[30];
    char verificacao;

    /// Impress�o do Menu
    ImprimeMenuCadastro();

    /// Abertura do Arquivo de Usu�rios
    arquivo = fopen("usuarios.txt", "a");

    /// Verifica a Abertura do Arquivo
    if(arquivo == NULL)
    {
        printf(" Erro na abertura do arquivo!\n");
        getch();
        Entrada();
    }

    /// Entrada dos Dados
    printf(" Usu�rio: ");
    scanf("%s", usuario);
    printf(" Senha: ");
    scanf("%s", senha);
    setbuf(stdin, NULL);

    // Verifica se o usu�rio digitou os dados corretamente
    ImprimeMenuCadastro();
    printf("Dados Corretos? \n"
           " Login: [%s]    \n"
           " Senha: [%s]  \n\n", usuario, senha);

    printf("[S,N]--> ");
    setbuf(stdin, NULL);
    scanf("%c", &verificacao);

    // Verifica caso os dados estejam corretos
    if((verificacao == 's')|(verificacao == 'S'))
    {
        /// Escreve no Arquivo TXT e separado por "�"
        fprintf(arquivo, "\n%s�%s�", usuario, senha);
        ImprimeMenuCadastro();
        printf(" Usu�rio cadastrado com sucesso!");
    }else
    {
        ImprimeMenuCadastro();
        printf("Deseja retornar para a tela de login? \n[S,N]--> ");
        setbuf(stdin, NULL);
        scanf("%c", &verificacao);

        if((verificacao == 's')|(verificacao == 'S'))
        {
            Entrada();
        }else
        {
            UsuarioCadastro();
        }
    }

    /// Fechamento do Arquivo de Usu�rios
    fclose(arquivo);

    getch();
    Entrada();
}

void ImprimeMenuLogin()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                              Login                              |\n"
            "+-----------------------------------------------------------------+\n");
}

void ImprimeMenuCadastro()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                             Cadastro                            |\n"
            "+-----------------------------------------------------------------+\n");
}

///---------------------------------------------------------------------------------------------------/
/// TELA DE MENU
///

void MenuPrincipal()
{
    /*******************************/
    /// Menu de sele��o principal ///
    /*******************************/

    /// Declara��o de Variaveis
    int opcao;

    /// Impress�o do Menu
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                          Menu Principal                         |\n"
            "+-----------------------------------------------------------------+\n"
            " 1- Tela de Cadastros                                              \n"
            " 2- Tela de Gerenciamentos                                         \n"
            " 3- Tela de Login                                                  \n"
            " 4- Sair                                                         \n\n");

    printf("--> ");
    scanf("%d", &opcao);

    /// Filtar Sele��o
    switch(opcao)
    {
        case 1:
            MenuCadastros();
            break;
        case 2:
            MenuGerenciamentos();
            break;
        case 3:
            Entrada();
        case 4:
            exit(0);
        default:
            MenuPrincipal();
    }
}

///---------------------------------------------------------------------------------------------------/
/// AREA DE CADASTROS
///

void MenuCadastros()
{
    /*********************************************************/
    /// Menu de sele��o para cadastrar uma determinada area ///
    /*********************************************************/

    /// Declara��o de Variaveis
    int opcao;

    /// Impress�o do Menu
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                        Menu de Cadastros                        |\n"
            "+-----------------------------------------------------------------+\n"
            " 1- Atleta                                                         \n"
            " 2- Localidade                                                     \n"
            " 3- Equipamento                                                    \n"
            " 4- Agendamento                                                    \n"
            " 5- M�dico                                                         \n"
            " 6- Funcion�rio                                                    \n"
            " 7- Volunt�rio                                                     \n"
            " 8- Protocolo de conting�ncia ao Covid-19                          \n"
            " 9- Voltar                                                         \n"
            "10- Sair                                                         \n\n");

    printf("--> ");
    scanf("%d", &opcao);

    /// Filtrar Sele��o
    switch(opcao)
    {
        case 1:
            CadastrarAtleta();
            break;
        case 2:
            CadastrarLocalidade();
            break;
        case 3:
            CadastrarEquipamento();
            break;
        case 4:
            CadastrarAgendamento();
            break;
        case 5:
            CadastrarMedico();
            break;
        case 6:
            CadastrarFuncionario();
            break;
        case 7:
            CadastrarVoluntario();
            break;
        case 8:
            CadastrarProtocolo();
            break;
        case 9:
            MenuPrincipal();
            break;
        case 10:
            exit(0);
        default:
            MenuCadastros();
    }
}

void CadastrarAtleta()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                         Cadastrar Atleta                        |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void CadastrarLocalidade()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Localidade                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void CadastrarEquipamento()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Equipamento                     |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void CadastrarAgendamento()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Agendamento                     |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
}
void CadastrarMedico()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                         Cadastrar M�dico                        |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void CadastrarFuncionario()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Funcion�rio                     |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void CadastrarVoluntario()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Volunt�rio                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void CadastrarProtocolo()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                        Cadastrar Protocolo                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}

///
/// AREA DE GERENCIAMENTO
///

void MenuGerenciamentos()
{
    /****************************************************************/
    /// Menu de sele��o para o gerenciamento de uma determida area ///
    /****************************************************************/

    /// Declara��o de Variaveis
    int opcao;

    /// Impress�o do Menu
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                      Menu de Gerenciamentos                     |\n"
            "+-----------------------------------------------------------------+\n"
            " 1- Calendario Ol�mpico                                            \n"
            " 2- Ranqueamento de Medalhas                                       \n"
            " 3- Medalhistas Ol�mpicos                                          \n"
            " 4- Contabiliza��o de Medalhas Distribuidas                        \n"
            " 5- Voltar                                                         \n"
            " 6- Sair                                                         \n\n");

    printf("--> ");
    scanf("%d", &opcao);

    /// Filtar Sele��o
    switch(opcao)
    {
        case 1:
            GerenciarCalendario();
            break;
        case 2:
            GerenciarRanqueamento();
            break;
        case 3:
            GerenciarMedalhistas();
            break;
        case 4:
            GerenciarContabilizacao();
            break;
        case 5:
            MenuPrincipal();
            break;
        case 6:
            exit(0);
        default:
            MenuGerenciamentos();
    }
}

void GerenciarCalendario()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                        Calendario Ol�mpico                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void GerenciarRanqueamento()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                      Ranqueamento de Medalhas                   |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void GerenciarMedalhistas()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                      Medalhistas Ol�mpicos                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
void GerenciarContabilizacao()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                    Contabiliza��o de Medalhas                   |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    MenuPrincipal();
}
