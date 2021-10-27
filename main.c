// VERSÃO 0.1

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Logo();
    //Login();

    while(1)
    {
        system("pause");
        MenuPrincipal();
    }

    return 0;
}

void Logo()
{
    /***************************************/
    /* */
    /***************************************/


    system("cls");

    printf("      Gerenciador das Olimpíadas de Paris 2024\n");
    printf("         Projeto PIM II - 'Nome do projeto'\n\n");
    printf("     .,::OOO::,.     .,ooOOOoo,.     .,::OOO::,.\n");
    printf("   .:'         `:. .8'         `8. .:'         `:.\n");
    printf("   :\"           \": 8\"           \"8 :\"           \":\n");
    printf("   :,        .,:::\"\"::,.     .,:o8OO::,.        ,:\n");
    printf("    :,,    .:' ,:   8oo`:. .:'oo8   :,,`:.    ,,:\n");
    printf("     `^OOoo:\"O^'     `^88oo:\"8^'     `^O\":ooOO^'\n");
    printf("           :,           ,: :,           ,:\n");
    printf("            :,,       ,,:   :,,       ,,:\n");
    printf("             `^Oo,,,oO^'     `^OOoooOO^'\n\n");

    printf("                     Integrantes\n");
    printf("      Fabio Stein Miranda de Oliveira - G243447 \n");
    printf("           Felipe Porto Rodrigues - N698381 \n");
    printf("    Guilherme Augusto dos Santos Ribeiro - G247850 \n");
    printf("           Henrique Campos Jonck - G298AB3 \n");
    printf("      Petra Eduarda de Jesus Furlanis - G27EHB1 \n");
    printf("          Vinícius Riqueza Moeller - G27BAH0 \n\n");

    system("pause");
}

void Login()
{
    char usuario[30], senha[30], verificacao;
    system("cls");

    printf("                           Tela de Login\n");
    printf("-------------------------------------------------------------------\n");
    printf(" Usuário: ");
    scanf("%s", usuario);
    printf(" Senha: ");
    scanf("%s", senha);

    printf("\nDados corretos? [s,n]: ");
    setbuf(stdin, NULL);
    scanf("%c", &verificacao);


    if((verificacao == 's')||(verificacao == 'S'))
    {
        // Verificar se o Usuário e Senha correspondem
        return;
    }else
    {
        Login();
    }
}

void MenuPrincipal()
{
    char opcao;

    system("cls");

    printf("                            Menu Principal\n");
    printf("-------------------------------------------------------------------\n");
    printf(" 1- Tela de Cadastros\n");
    printf(" 2- Tela de Gerenciamentos\n");
    printf(" 3- Configurações\n");
    printf(" 4- Sair\n\n");

    printf("Digite a opção que deseja: ");
    scanf("%c", &opcao);

    switch(opcao)
    {
        case '1':
            MenuCadastros();
            break;
        case '2':
            MenuGerenciamentos();
            break;
        case '3':
            MenuConfiguracoes();
            break;
        case '4':
            return;
        default:
            MenuPrincipal();
    }
}

///
/// AREA DE CADASTROS
///

void MenuCadastros()
{
    char opcao;

    system("cls");

    printf("                         Menu de Cadastros\n");
    printf("-------------------------------------------------------------------\n");
    printf(" 1- Atleta\n");
    printf(" 2- Localidade\n");
    printf(" 3- Equipamento\n");
    printf(" 4- Agendamento\n");
    printf(" 5- Médico\n");
    printf(" 6- Funcionário\n");
    printf(" 7- Voluntário\n");
    printf(" 8- Protocolo de contingência ao Covid-19\n");
    printf(" 9- Sair\n\n");

    printf("Digite a opção que deseja: ");
    scanf("%c", &opcao);

    switch(opcao)
    {
        case '1':
            CadastrarAtleta();
            break;
        case '2':
            CadastrarLocalidade();
            break;
        case '3':
            CadastrarEquipamento();
            break;
        case '4':
            CadastrarAgendamento();
            break;
        case '5':
            CadastrarMedico();
            break;
        case '6':
            CadastrarFuncionario();
            break;
        case '7':
            CadastrarVoluntario();
            break;
        case '8':
            CadastrarProtocolo();
            break;
        case '9':
            return;
        default:
            MenuCadastros();
    }
}

void CadastrarAtleta()
{
    system("cls");
    printf("                       Cadastrar Atleta\n");
    printf("-------------------------------------------------------------------\n");
}
void CadastrarLocalidade()
{
    system("cls");
    printf("                       Cadastrar Localidade\n");
    printf("-------------------------------------------------------------------\n");
}
void CadastrarEquipamento()
{
    system("cls");
    printf("                       Cadastrar Equipamento\n");
    printf("-------------------------------------------------------------------\n");
}
void CadastrarAgendamento()
{
    system("cls");
    printf("                       Cadastrar Agendamento\n");
    printf("-------------------------------------------------------------------\n");
}
void CadastrarMedico()
{
    system("cls");
    printf("                       Cadastrar Médico\n");
    printf("-------------------------------------------------------------------\n");
}
void CadastrarFuncionario()
{
    system("cls");
    printf("                       Cadastrar Funcionário\n");
    printf("-------------------------------------------------------------------\n");
}
void CadastrarVoluntario()
{
    system("cls");
    printf("                       Cadastrar Voluntário\n");
    printf("-------------------------------------------------------------------\n");
}
void CadastrarProtocolo()
{
    system("cls");
    printf("                       Cadastrar Protocolo\n");
    printf("-------------------------------------------------------------------\n");
}

///
/// AREA DE GERENCIAMENTO
///

void MenuGerenciamentos()
{
    char opcao;

    system("cls");
    printf("                       Menu de Gerenciamentos\n");
    printf("-------------------------------------------------------------------\n");
    printf(" 1- Calendario Olímpico\n");
    printf(" 2- Ranqueamento de Medalhas\n");
    printf(" 3- Medalhistas Olímpicos\n");
    printf(" 4- Contabilização de Medalhas Distribuidas\n");
    printf(" 5- Sair\n\n");

    printf("Digite a opção que deseja: ");
    scanf("%c", &opcao);

    switch(opcao)
    {
        case '1':
            GerenciarCalendario();
            break;
        case '2':
            GerenciarRanqueamento();
            break;
        case '3':
            GerenciarMedalhistas();
            break;
        case '4':
            GerenciarContabilizacao();
            break;
        case '5':
            return;
        default:
            MenuGerenciamentos();
    }
}

void GerenciarCalendario()
{
    system("cls");
    printf("                           Calendario Olímpico\n");
    printf("-------------------------------------------------------------------\n");
}
void GerenciarRanqueamento()
{
    system("cls");
    printf("                           Configurações\n");
    printf("-------------------------------------------------------------------\n");
}
void GerenciarMedalhistas()
{
    system("cls");
    printf("                           Configurações\n");
    printf("-------------------------------------------------------------------\n");
}
void GerenciarContabilizacao()
{
    system("cls");
    printf("                           Configurações\n");
    printf("-------------------------------------------------------------------\n");
}

///
/// AREA DE CONFIGURAÇÕES
///

void MenuConfiguracoes()
{
    system("cls");
    printf("                           Configurações\n");
    printf("-------------------------------------------------------------------\n");
}
