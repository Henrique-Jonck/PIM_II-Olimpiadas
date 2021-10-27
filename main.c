/// VERS�O 1.0

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int cod_AtualUsuario, cod_UltimoUsuario, num_cadastros;

///----------------------------------------------------------------------------------------------------------------------------------/
/// FUN��O PRINCIPAL                                                                                                                 /
///----------------------------------------------------------------------------------------------------------------------------------/

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Logo();
    Menu_Login();
    Menu_Principal();

    return 0;
}

///----------------------------------------------------------------------------------------------------------------------------------/
/// TELA DE INICIALIZA��O                                                                                                            /
///----------------------------------------------------------------------------------------------------------------------------------/

void Logo()
{// Fun��o para a impress�o de uma imagem com as informa��es do trabalho

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|             Gerenciador das Olimp�adas de Paris 2024            |\n"
            "|                Projeto PIM II - 'Nome do projeto'               |\n"
            "|                    UNIP Paulista - 00/00/2021                   |\n"
            "+-----------------------------------------------------------------+\n"
            "|                                                                 |\n"
            "|           .,::OOO::,.     .,ooOOOoo,.     .,::OOO::,.           |\n"
            "|         .:'         `:. .8'         `8. .:'         `:.         |\n"
            "|         :\"           \": 8\"           \"8 :\"           \":         |\n"
            "|         :,        .,:::\"\"::,.     .,:o8OO::,.        ,:         |\n"
            "|          :,,    .:' ,:   8oo`:. .:'oo8   :,,`:.    ,,:          |\n"
            "|           `^OOoo:\"O^'     `^88oo:\"8^'     `^O\":ooOO^'           |\n"
            "|                 :,           ,: :,           ,:                 |\n"
            "|                  :,,       ,,:   :,,       ,,:                  |\n"
            "|                   `^Oo,,,oO^'     `^OOoooOO^'                   |\n"
            "|                                                                 |\n"
            "|                                                                 |\n"
            "|-------------------------- Integrantes --------------------------|\n"
            "|                                                                 |\n"
            "|            Fabio Stein Miranda de Oliveira - G243447            |\n"
            "|                 Felipe Porto Rodrigues - N698381                |\n"
            "|          Guilherme Augusto dos Santos Ribeiro - G247850         |\n"
            "|                 Henrique Campos Jonck - G298AB3                 |\n"
            "|            Petra Eduarda de Jesus Furlanis - G27EHB1            |\n"
            "|                Vin�cius Riqueza Moeller - G27BAH0               |\n"
            "+-----------------------------------------------------------------+\n\n");

    system("pause");
}

///----------------------------------------------------------------------------------------------------------------------------------/
/// TELAS DE LOGIN                                                                                                                   /
///----------------------------------------------------------------------------------------------------------------------------------/

void Menu_Login()
{// Fun��o para a impress�o e sele��o do menu de login.

    /// DECLARA��O DE VARIAVEIS
    int opcao;

    /// IMPRESS�O DO MENU
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                              Login                              |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Entrar                                                       |\n"
            "| 2- Novo Usu�rio                                                 |\n"
            "| 3- Sair                                                         |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    /// FILTRAR SELE��O
    switch(opcao)
    {
        case 1:
            Login_Entrar();
            break;
        case 2:
            Login_Cadastrar();
            break;
        case 3:
            exit(0);
        default:
            Menu_Login();
    }
}

void Login_Entrar()
{// Fun��o utilizada na realiza��o de login do usu�rio.

    /// DECLARA��O DE VARIAVEIS
    char verificacao, usuario[30], senha[30];
    int acesso = 0;

    /// IMPRESS�O DO MENU
    Imprime_Login_Entrar();

    /// ENTRADA DE DADOS
    printf(" Login: ");
    setbuf(stdin, NULL);
    scanf("%s", usuario);

    printf(" Senha: ");
    setbuf(stdin, NULL);
    scanf("%s", senha);

    /// CHECAGEM DOS DADOS
    acesso = Buscar_Usuario(3, usuario, senha);

    if(acesso == 1)
        Menu_Principal();
    else
    {
        Imprime_Login_Entrar();

        if(Msg_Pergunta("Usu�rio ou Senha Incorretos!\n\nDeseja realizar o cadastro de um novo usu�rio?") == 1)
            Login_Cadastrar();
        else
            Login_Entrar();
    }
}

void Login_Cadastrar()
{// Fun��o utilizada no cadastro de um novo usu�rio.

    /// DECLARA��O DE VARIAVEIS
    char usuario[50], senha1[30], senha2[30];
    char verificacao;
    int comparacao, tamUsuario, tamSenha;

    /// IMPRESS�O DO MENU
    Imprime_Login_Cadastro();

    /// ENTRADA DE DADOS
    printf(" Usu�rio: ");
    setbuf(stdin, NULL);
    scanf("%s", usuario);

    printf("\n Senha: ");
    setbuf(stdin, NULL);
    scanf("%s", senha1);

    printf(" Confirme a Senha: ");
    setbuf(stdin, NULL);
    scanf("%s", senha2);

    /// COMPARA��O DOS DADOS
    comparacao = strcmp(senha1, senha2);
    tamSenha = strlen(senha1);
    tamUsuario = strlen(usuario);

    if(comparacao != 0) Verificar_Cadastro("As senhas n�o correspondem!");
    else if(tamSenha < 8) Verificar_Cadastro("Senha muito curta!");
    else if(tamSenha > 29) Verificar_Cadastro("Senha muito longa!");
    else if(tamUsuario > 49) Verificar_Cadastro("Usu�rio muito longo!");
    else
    {
        Imprime_Login_Cadastro();
        Adicionar_Usuario(usuario, senha1);
        Menu_Login();
    }
}

int Buscar_Usuario(int modo, char usuario[50], char senha[30])
{// Fun��o para buscar o usuario informado no arquivo de texto.
    // Modo 1 - Retorna se o usu�rio est� ou n�o cadastrado.
    // Modo 2 - Retorna se o usu�rio e senha est�o cadastrados e se correspondem.
    // Modo 3 - Retorna se o usu�rio e senha est�o cadastrados, se correspondem e informa seu c�digo.

    /// DECLARA��O DE VARIAVEIS
    FILE *arquivo;
    char verificacao, dados1[50], dados2[50], info[3][50], *resultado, *pedacos;
    int index, acesso = 0;

    /// ABERTURA DO ARQUIVO
    arquivo = fopen("usuarios.txt", "a+");

    /// VERIFICA��O DA ABERTURA DO ARQUIVO
    if(arquivo == NULL)
    {
        printf("N�o foi possivel encontrar o arquivo de usu�rios!\n\n");
        system("pause");
        Menu_Login();
    }

    /// PERCORRER CADA LINHA DO ARQUIVO
    while(!feof(arquivo))
    {
        // Retornar a string da linha atual
        resultado = fgets(dados1, 100, arquivo);

        // Copiar o valor de um vetor para o outro
        strcpy(dados2, dados1);

        /// VERIFICAR SE A LINHA RETORNOU ALGO
        index = 0;
        if(resultado)
        {
            /// REPARTIR O RESULTADO DA LINHA
            pedacos = strtok(dados2, "�");

            /// PERCORRER CADA REPARTI��O
            while(pedacos)
            {
                // Atribui o valor da reparti��o atual para o vetor
                strcpy(info[index], pedacos);
                cod_UltimoUsuario = atoi(pedacos);
                pedacos = strtok(NULL, "�");

                index++;
            }
        }else
            cod_UltimoUsuario = 0;

        /// VERIFICAR E RETORNAR OS DADOS COM BASE NO MODO INFORMADO
        if(modo == 1){
            if(!strcmp(usuario, info[0])) acesso = 1;
        }
        if(modo == 2){
            if((!strcmp(info[0], usuario))&(!strcmp(info[1], senha)))
                acesso = 1;
        }
        if(modo == 3){
            if((!strcmp(usuario, info[0]))&&(!strcmp(senha, info[1]))){
                acesso = 1;
                cod_AtualUsuario = atoi(info[2]);
            }
        }
    }
    /// FECHAMENTO DO ARQUIVO
    fclose(arquivo);

    /// RETORNA SE ENCONTROU OU N�O O USUARIO
    // 0 - N�o encontrado
    // 1 - Encotrado
    return acesso;
}

int Adicionar_Usuario(char usuario[50], char senha[30])
{// Fun��o para adicionar um novo usu�rio ao arquivo de texto.

    /// DECLARA��O DE VARIAVEIS
    FILE *arquivo;
    char verificacao;
    int acesso;

    /// VERIFICAR SE USU�RIO JA EXISTE
    acesso = Buscar_Usuario(1, usuario, senha);
    if(acesso == 1)
    {
        if(Msg_Pergunta("Usu�rio ja existente!\n\nDeseja realizar o cadastro novamente?") == 1)
            Login_Cadastrar();
        else
            Menu_Login();
    }else
    {
        /// ABERTURA DO ARQUIVO
        arquivo = fopen("usuarios.txt", "a+");

        /// VERIFICA��O DA ABERTURA DO ARQUIVO
        if(arquivo == NULL)
        {
            printf("N�o foi possivel encontrar o arquivo de usu�rios!\n");
            system("pause");
            Menu_Login();
        }

        /// ESCREVER NO ARQUIVO TEXTO COM SEPARA��O POR '�'
        fprintf(arquivo, "\n%s�%s�%d�", usuario, senha, (cod_UltimoUsuario + 1));
        printf("Usu�rio cadastrado com sucesso!\n\n");
        system("pause");

        /// FECHAMENTO DO ARQUIVO
        fclose(arquivo);
    }
    return 0;
}

///----------------------------------------------------------------------------------------------------------------------------------/
/// TELA DE MENU PRINCIPAL                                                                                                           /
///----------------------------------------------------------------------------------------------------------------------------------/

void Menu_Principal()
{// Fun��o para a impress�o e sele��o do menu principal.

    /// DECLARA��O DE VARIAVEIS
    int opcao;
    char verificacao;

    /// IMPRESS�O DO MENU
    Imprime_Menu_Principal();

    printf("--> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    /// FILTRAR SELE��O
    switch(opcao)
    {
        case 1:
            Menu_Cadastros();
            break;
        case 2:
            Menu_Gerenciamentos();
            break;
        case 3:
            if(Msg_Pergunta("\nDeseja deslogar do usu�rio atual?") == 1) Menu_Login();
            else Menu_Principal();
            break;
        case 4:
            if(Msg_Pergunta("\nDeseja sair do programa?") == 1) exit(0);
            else Menu_Principal();
            break;
        default:
            Menu_Principal();
    }
}

///----------------------------------------------------------------------------------------------------------------------------------/
/// AREA DE CADASTROS                                                                                                                /
///----------------------------------------------------------------------------------------------------------------------------------/

void Menu_Cadastros()
{// Fun��o para a impress�o e sele��o do menu de cadastros.

    /// DECLARA��O DE VARIAVEIS
    int opcao;

    /// IMPRESS�O DO MENU
    Imprime_Menu_Cadastro();

    printf("--> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    /// FILTRAR SELE��O
    switch(opcao)
    {
        case 1:
            Cadastro_Atleta();
            break;
        case 2:
            Cadastro_Localidade();
            break;
        case 3:
            Cadastro_Equipamento();
            break;
        case 4:
            Cadastro_Agendamento();
            break;
        case 5:
            Cadastro_Medico();
            break;
        case 6:
            Cadastro_Funcionario();
            break;
        case 7:
            Cadastro_Voluntario();
            break;
        case 8:
            Cadastro_Protocolo();
            break;
        case 9:
            Menu_Principal();
            break;
        case 10:
            if(Msg_Pergunta("\nDeseja sair do programa?") == 1) exit(0);
            else Menu_Cadastros();
            break;
        default:
            Menu_Cadastros();
    }
}

void Cadastro_Atleta()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                         Cadastrar Atleta                        |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    setbuf(stdin, NULL);
    Menu_Principal();
}
void Cadastro_Localidade()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Localidade                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Cadastro_Equipamento()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Equipamento                     |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Cadastro_Agendamento()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Agendamento                     |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
}
void Cadastro_Medico()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                         Cadastrar M�dico                        |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Cadastro_Funcionario()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Funcion�rio                     |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Cadastro_Voluntario()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Volunt�rio                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Cadastro_Protocolo()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                        Cadastrar Protocolo                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}

///----------------------------------------------------------------------------------------------------------------------------------/
/// AREA DE GERENCIAMENTO                                                                                                            /
///----------------------------------------------------------------------------------------------------------------------------------/

void Menu_Gerenciamentos()
{// Fun��o para a impress�o e sele��o do menu de gerenciamentos.

    /// DECLARA��O DE VARIAVEIS
    int opcao;

    /// IMPRESS�O DO MENU
    Imprime_Menu_Gerenciamento();

    printf("--> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    /// FILTRAR SELESS�O
    switch(opcao)
    {
        case 1:
            Gerencia_Calendario();
            break;
        case 2:
            Gerencia_Ranqueamento();
            break;
        case 3:
            Gerencia_Medalhistas();
            break;
        case 4:
            Gerencia_Contabilizacao();
            break;
        case 5:
            Menu_Principal();
            break;
        case 6:
            if(Msg_Pergunta("\nDeseja sair do programa?") == 1) exit(0);
            else Menu_Gerenciamentos();
            break;
        default:
            Menu_Gerenciamentos();
    }
}

void Gerencia_Calendario()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                        Calendario Ol�mpico                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Gerencia_Ranqueamento()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                      Ranqueamento de Medalhas                   |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Gerencia_Medalhistas()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                      Medalhistas Ol�mpicos                      |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}
void Gerencia_Contabilizacao()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                    Contabiliza��o de Medalhas                   |\n"
            "+-----------------------------------------------------------------+\n");

    system("pause");
    Menu_Principal();
}

///----------------------------------------------------------------------------------------------------------------------------------/
/// FUN��ES GENERICAS                                                                                                                /
///----------------------------------------------------------------------------------------------------------------------------------/

int Msg_Pergunta(char txt[200])
{
    /// DECLARA��O DE VARIAVEIS
    char pergunta;

    /// IMPRESS�O DA MENSAGEM
    printf("%s\n[S,N]--> ", txt);
    setbuf(stdin, NULL);
    scanf("%c", &pergunta);

    /// RETORNO DA RESPOSTA
    if((pergunta == 's')|(pergunta == 'S')) return 1;
    else return 0;
}

void Verificar_Cadastro(char txt[100])
{
    /// DECLARA��O DE VARIAVEIS
    char verificacao;

    /// IMPRESS�O DA MENSAGEM
    Imprime_Login_Cadastro();

    if(Msg_Pergunta(("%s\n\nDeseja cadastrar novamente?", txt)) == 1)
        Login_Cadastrar();
    else
        Menu_Login();
}

void Imprime_Menu_Principal()
{
    system("cls");
    printf( "+--------------+--------------------------------------------------+\n"
            "| Usu�rio: %.3d |           Menu Principal                         |\n"
            "+--------------+--------------------------------------------------+\n"
            "| 1- Tela de Cadastros                                            |\n"
            "| 2- Tela de Gerenciamentos                                       |\n"
            "| 3- Tela de Login                                                |\n"
            "| 4- Sair                                                         |\n"
            "+-----------------------------------------------------------------+\n\n", cod_AtualUsuario);
}

void Imprime_Menu_Cadastro()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                        Menu de Cadastros                        |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Atleta                                                       |\n"
            "| 2- Localidade                                                   |\n"
            "| 3- Equipamento                                                  |\n"
            "| 4- Agendamento                                                  |\n"
            "| 5- M�dico                                                       |\n"
            "| 6- Funcion�rio                                                  |\n"
            "| 7- Volunt�rio                                                   |\n"
            "| 8- Protocolo de conting�ncia ao Covid-19                        |\n"
            "| 9- Voltar                                                       |\n"
            "|10- Sair                                                         |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Menu_Gerenciamento()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                      Menu de Gerenciamentos                     |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Calendario Ol�mpico                                          |\n"
            "| 2- Ranqueamento de Medalhas                                     |\n"
            "| 3- Medalhistas Ol�mpicos                                        |\n"
            "| 4- Contabiliza��o de Medalhas Distribuidas                      |\n"
            "| 5- Voltar                                                       |\n"
            "| 6- Sair                                                         |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Login_Entrar()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                              Entrar                             |\n"
            "+-----------------------------------------------------------------+\n");
}

void Imprime_Login_Cadastro()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                           Novo Usu�rio                          |\n"
            "+-----------------------------------------------------------------+\n");
}
