// VERSÃO 1.1

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


int main()
{
    setlocale(LC_ALL, "Portuguese");

    Logo();
    Menu_Login();
    Menu_Principal();

    return 0;
}

void Logo()
{
    /********************************************************************/
    /// Imprime uma logo das olimpiadas com as informa��es do trabalho ///
    /********************************************************************/

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

///---------------------------------------------------------------------------------------------------/
/// TELA DE LOGIN
///

void Menu_Login()
{
    /*********************************************************/
    /// Menu para sele��o de Login ou de Cadastro de usu�rio */
    /*********************************************************/

    /// Declara��o de Variaveis
    int opcao;

    /// Impress�o do Menu
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

    /// Filtar sele��o
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
    Imprime_Login_Entrar();

    /// Abertura do Arquivo de Usu�rios
    arquivo = fopen("usuarios.txt", "r");

    /// Verifica a Abertura do Arquivo
    if(arquivo == NULL)
    {
        printf(" Erro na abertura do arquivo!\n");
        system("pause");
        Menu_Login();
    }

    /// Entrada dos Dados
    printf(" Login: ");
    setbuf(stdin, NULL);
    scanf("%s", usuario);

    printf(" Senha: ");
    setbuf(stdin, NULL);
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
            Imprime_Login_Entrar();
            printf(" Usu�rio ou Senha incorretos!\n\nCadastrar novo usu�rio? \n[S,N]--> ");
            setbuf(stdin, NULL);
            scanf("%c", &verificacao);

            if((verificacao == 's')||(verificacao == 'S')) Login_Cadastrar();
            else Login_Entrar();

        }else
        {
            Menu_Principal();
        }
    }else
    {
        Login_Entrar();
    }
}

void Login_Cadastrar()
{
    /*********************************/
    /// Cadastro de um novo usu�rio ///
    /*********************************/

    /// Declara��o de Variaveis
    FILE *arquivo;
    char usuario[50], senha[30];
    char verificacao;

    /// Impress�o do Menu
    Imprime_Login_Cadastro();

    /// Abertura do Arquivo de Usu�rios
    arquivo = fopen("usuarios.txt", "a");

    /// Verifica a Abertura do Arquivo
    if(arquivo == NULL)
    {
        printf(" Erro na abertura do arquivo!\n");
        system("pause");
        Menu_Login();
    }

    /// Entrada dos Dados
    printf(" Usu�rio: ");
    setbuf(stdin, NULL);
    scanf("%s", usuario);

    printf(" Senha: ");
    setbuf(stdin, NULL);
    scanf("%s", senha);

    // Verifica se o usu�rio digitou os dados corretamente
    Imprime_Login_Cadastro();
    printf("Dados Corretos? \n"
           " Login: [%s]    \n"
           " Senha: [%s]  \n\n", usuario, senha);

    printf("[S,N]--> ");
    setbuf(stdin, NULL);
    scanf("%c", &verificacao);

    // Verifica caso os dados estejam corretos
    if((verificacao == 's')|(verificacao == 'S'))
    {
        Imprime_Login_Cadastro();

        /// Escreve no Arquivo TXT e separado por "�"
        fprintf(arquivo, "\n%s�%s�", usuario, senha);
        printf(" Usu�rio cadastrado com sucesso!\n");
        system("pause");

    }else
    {
        Imprime_Login_Cadastro();

        printf("Deseja retornar para a tela de login? \n[S,N]--> ");
        setbuf(stdin, NULL);
        scanf("%c", &verificacao);

        if((verificacao == 's')|(verificacao == 'S')) Menu_Login();
        else Login_Cadastrar();
    }

    /// Fechamento do Arquivo de Usu�rios
    fclose(arquivo);
    Menu_Login();
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

void Imprime_Menu_Principal()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                          Menu Principal                         |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Tela de Cadastros                                            |\n"
            "| 2- Tela de Gerenciamentos                                       |\n"
            "| 3- Tela de Login                                                |\n"
            "| 4- Sair                                                         |\n"
            "+-----------------------------------------------------------------+\n\n");
}

///---------------------------------------------------------------------------------------------------/
/// TELA DE MENU
///

void Menu_Principal()
{
    /*******************************/
    /// Menu de sele��o principal ///
    /*******************************/

    /// Declara��o de Variaveis
    int opcao;
    char verificacao;

    /// Impress�o do Menu
    Imprime_Menu_Principal();

    printf("--> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    /// Filtar Sele��o
    switch(opcao)
    {
        case 1:
            Menu_Cadastros();
            break;
        case 2:
            Menu_Gerenciamentos();
            break;
        case 3:
            Imprime_Menu_Principal();

            printf("Deseja deslogar do usu�rio atual?\n[S,N]--> ");
            setbuf(stdin, NULL);
            scanf("%c", &verificacao);

            if((verificacao == 's')|(verificacao == 'S')) Menu_Login();
            else Menu_Principal();

        case 4:
            printf("\nDeseja sair do programa?\n[S,N]--> ");
            setbuf(stdin, NULL);
            scanf("%c", &verificacao);

            if((verificacao == 's')|(verificacao == 'S')) exit(0);
            else Menu_Principal();
            break;
        default:
            Menu_Principal();
    }
}

///---------------------------------------------------------------------------------------------------/
/// AREA DE CADASTROS
///

void Imprime_Menu_Cadastro()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                        Menu de Cadastros                        |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Atleta                                                       |\n"
            "| 2- Modalidade Olímpica                                          |\n"
            "| 3- Localidade                                                   |\n" //Removi os equipamento e coloquei localidade no lugar(Coloquei os equipamento no cadastro da modalidade)
            "| 4- Agendamento de Treino                                        |\n" // Mudei o nome de agendamento para agendamento de treino
            "| 5- Agendamento de Jogo                                          |\n" // Adicionei o agendamento de jogos
            "| 6- M�dico                                                       |\n"
            "| 7- Funcion�rio                                                  |\n"
            "| 8- Volunt�rio                                                   |\n"
            "| 9- Voltar                                                       |\n"
            "|10- Sair                                                         |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Menu_Cadastros()
{
    /*********************************************************/
    /// Menu de sele��o para cadastrar uma determinada area ///
    /*********************************************************/

    /// Declara��o de Variaveis
    int opcao;
    char verificacao;

    /// Impress�o do Menu
    Imprime_Menu_Cadastro();

    printf("--> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    /// Filtrar Sele��o
    switch(opcao)
    {
        case 1:
            Cadastro_Atleta();
            break;
        case 2:
            Cadastro_Modalidade_Olimpica();
            break;
        case 3:
            Cadastro_Localidade();
            break;
        case 4:
            Cadastro_Agendamento_Treino();
            break;
        case 5:
            Cadastro_Medico();
            break;
        case 6:
            Cadastro_Medico();
            break;
        case 7:
            Cadastro_Funcionario();
            break;
        case 8:
            Cadastro_Voluntario();
            break;
        case 9:
            Menu_Principal();
            break;
        case 10:
            printf("\nDeseja sair do programa?\n[S,N]--> ");
            setbuf(stdin, NULL);
            scanf("%c", &verificacao);

            if((verificacao == 's')|(verificacao == 'S')) exit(0);
            else Menu_Cadastros();

            break;
        default:
            Menu_Cadastros();
    }
}

void Cadastro_De_Atleta_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_de_Atleta_Finalizado();

    printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Atleta();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_De_Atleta_Finalizado();
    }
}

// Fiz daqui

void Cadastro_Atleta()
{
    int
    quantidadeDeAtletas,
    idadeDoAtleta,
    count;
    char nomeDoAtleta[100], paisDoAtleta[100], sexoDoAtleta[12], passaporteDoAtleta[15], modalidadeQueOAtletaVaiJogar[30];


    system("cls");
    printf("+-----------------------------------------------------------------+\n"
           "|                         Cadastrar Atleta                        |\n"
           "+-----------------------------------------------------------------+\n");

    printf(
           "| Deseja cadastrar quantos atletas:                               |\n"
           "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeAtletas);
    setbuf(stdin, NULL);

    for (count = 0; count < quantidadeDeAtletas; count++)
    {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                     Cadastrando novo Atleta                     |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome Completo do Atléta: ");
        setbuf(stdin, NULL);
        fgets(nomeDoAtleta, 100, stdin);

        printf("\nPaís de Origem do atleta: ");
        setbuf(stdin, NULL);
        fgets(paisDoAtleta, 100, stdin);

        printf("\nSexo do Atleta: Homem / Mulher: ");
        setbuf(stdin, NULL);
        fgets(sexoDoAtleta, 12, stdin);

        printf("\nNumero do passaporte do Atleta: ");
        setbuf(stdin, NULL);
        fgets(passaporteDoAtleta, 18, stdin);

        printf("\nModalidade Olímpica que o atleta vai jogar: ");
        setbuf(stdin, NULL);
        fgets(modalidadeQueOAtletaVaiJogar, 30, stdin);
    }

    system("pause");
    Cadastro_De_Atleta_Finalizado();
}

void Cadastro_Modalidade_Olimpica_Finalizado()
{
    int escolhaDoUsuario;
    Imprime_Cadastro_Modalidade_Olimpica_Finalizado();

    printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Modalidade_Olimpica();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_Modalidade_Olimpica_Finalizado();
    }
}

void Cadastro_Modalidade_Olimpica()
{
    int count, quantidadeDeModalidade;
    char nomeDaModalidade[20], equipamentoDaModalidade[200], alojamentoDaModalidade[30];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Modalidade Olímpica                       |\n"
            "+-----------------------------------------------------------------+\n");
    printf(
           "| Deseja cadastrar quantas Modalidades:                           |\n"
           "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeModalidade);

    for (count = 0; count < quantidadeDeModalidade; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                   Cadastrando nova Modalidade                   |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome da Modalidade: ");
        setbuf(stdin, NULL);
        fgets(nomeDaModalidade, 20, stdin);

        printf("\nEquipamentos que a equipe vai utlizar (Separe os nomes dos equipamentos por vírgulas): ");
        setbuf(stdin, NULL);
        fgets(equipamentoDaModalidade, 200, stdin);

        printf("\nOnde será o alojamento dessa modalidade?: ");
        setbuf(stdin, NULL);
        fgets(alojamentoDaModalidade, 30, stdin);
    }
    system("pause");
    Cadastro_Modalidade_Olimpica_Finalizado();
}

void Cadastro_Localidade_Finalizado()
{
    int escolhaDoUsuario;
    Imprime_Cadastro_Localidade_Finalizado();

    printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Localidade();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Imprime_Cadastro_Localidade_Finalizado();
    }
}

void Cadastro_Localidade()
{
    int count, quantidadeDeLocal;
    char estadioQueVaiAcontecerOsJogos[30], cidadeQueVaiAcontecerOsJogos[30];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Localidade                      |\n"
            "+-----------------------------------------------------------------+\n");
    printf(
            "| Deseja cadastrar quantos Local:                                 |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeLocal);

    for (count = 0; count < quantidadeDeLocal; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                   Cadastrando novo Local                        |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome da Cidade: ");
        setbuf(stdin, NULL);
        fgets(cidadeQueVaiAcontecerOsJogos, 30, stdin);

        printf("\nNome do estádio: ");
        setbuf(stdin, NULL);
        fgets(estadioQueVaiAcontecerOsJogos, 30, stdin);
    }

    system("pause");
    Cadastro_Localidade_Finalizado();
}

void Cadastro_Agendamento_Treino_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_Agendamento_Treino_Finalizado();

     printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Agendamento_Treino();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_Agendamento_Treino_Finalizado();
    }
}

void Cadastro_Agendamento_Treino()
{
    int count, quantidadeDeAgendamento;
    char modalidadeQueVaiTreinar[30], localDoTreino[40];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Treino                          |\n"
            "+-----------------------------------------------------------------+\n");
    printf(
            "| Deseja cadastrar quantos treinos:                               |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeAgendamento);

    for (count = 0; count < quantidadeDeAgendamento; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                  Novo Cadastro de Treino                        |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nQual modalidade olímpica vai treinar: ");
        setbuf(stdin, NULL);
        fgets(modalidadeQueVaiTreinar, 30, stdin);

        printf("\nLocal do treino: ");
        setbuf(stdin, NULL);
        fgets(localDoTreino, 40, stdin);
    }

    system("pause");
    Cadastro_Agendamento_Treino_Finalizado();
}

void Cadastro_Agendamento_Jogo_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_Agendamento_Jogo_Finalizado();

     printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Agendamento_Jogo();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_Agendamento_Jogo_Finalizado();
    }
}

void Cadastro_Agendamento_Jogo()
{
    int count, quantidadeDeAgendamento;
    char modalidadeQueVaiJogar[40], localDoJogo[40], horarioDoJogo[4];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Jogos                          |\n"
            "+-----------------------------------------------------------------+\n");
    printf(
            "| Deseja cadastrar quantos Jogos:                                 |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeAgendamento);

    for (count = 0; count < quantidadeDeAgendamento; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                  Novo Cadastro de Jogo                          |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nQual modalidade olímpica vai jogar: ");
        setbuf(stdin, NULL);
        fgets(modalidadeQueVaiJogar, 30, stdin);

        printf("\nEm qual estádio será o jogo: ");
        setbuf(stdin, NULL);
        fgets(localDoJogo, 40, stdin);

        printf("\nHorario do Jogo(Formato 24h. Apenas número!!!): ");
        setbuf(stdin, NULL);
        fgets(horarioDoJogo, 4, stdin);
    }

    system("pause");
    Cadastro_Agendamento_Jogo_Finalizado();
}

void Cadastro_Medico_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_Medico_Finalizado();

    printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Medico();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_Medico_Finalizado();
    }
}

void Cadastro_Medico()
{
    int count, quantidadeDeMedicos;
    char modalidadeDeAtuacao[20];
    char nomeDoMedico[50];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                         Cadastrar M�dico                        |\n"
            "+-----------------------------------------------------------------+\n");
   printf(
            "| Deseja cadastrar quantos agendamento de treinos:                |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeMedicos);

    for (count = 0; count < quantidadeDeMedicos; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                   Novo Cadastro de Médico                       |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome do médico: ");
        setbuf(stdin, NULL);
        fgets(nomeDoMedico, 50, stdin);

        printf("\nQual modalidade o médico vai atuar: ");
        setbuf(stdin, NULL);
        fgets(modalidadeDeAtuacao, 20, stdin);
    }

    system("pause");
    Cadastro_Medico_Finalizado();
}

void Cadastro_Funcionario_Finalizado() {
    int escolhaDoUsuario;

    Imprime_Cadastro_Funcionario_Finalizado();

    printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Funcionario();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_Funcionario_Finalizado();
    }
}

void Cadastro_Funcionario()
{
    int count, quantidadeDeFuncionarios, horasATrabalhar;
    char nomeDoFuncionario[30], trabalhoDesteFuncionario[50], numeroPassaporte[15];
    float salarioDoFuncionario;

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Funcion�rio                     |\n"
            "+-----------------------------------------------------------------+\n");
   printf(
            "| Deseja cadastrar quantos funcionarios:                          |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeFuncionarios);

    for (count = 0; count < quantidadeDeFuncionarios; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                   Novo Funcionário                              |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome do funcionario: ");
        setbuf(stdin, NULL);
        fgets(nomeDoFuncionario, 30, stdin);

        printf("\nQual trabalho ele vai fazer: ");
        setbuf(stdin, NULL);
        fgets(trabalhoDesteFuncionario, 50, stdin);

        printf("\nQuantas horas por dia este funcionário vai trabalhar(Apenas números): ");
        setbuf(stdin, NULL);
        scanf("%d", &horasATrabalhar);

        printf("\nSalário do funcionário(Ex: 1.600): ");
        setbuf(stdin, NULL);
        scanf("%f", &salarioDoFuncionario);

        printf("\nPassaporte do funcionário: ");
        setbuf(stdin, NULL);
        scanf("%s", numeroPassaporte);
    }

    system("pause");
    Cadastro_Funcionario_Finalizado();
}

void Cadastro_Voluntario_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_Voluntario_Finalizado();

    printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Funcionario();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_Funcionario_Finalizado();
    }
}

void Cadastro_Voluntario()
{
    int count, quantidadeDeVoluntarios, horasAVoluntariar;
    char nomeDoVoluntario[30], tarefaDoVoluntario[60], numeroPassaporte[15];
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Volunt�rio                     |\n"
            "+-----------------------------------------------------------------+\n");

            printf(
            "| Deseja cadastrar quantos voluntarios:                           |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeVoluntarios);

    for (count = 0; count < quantidadeDeVoluntarios; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                   Novo Voluntario                               |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome do funcionario: ");
        setbuf(stdin, NULL);
        fgets(nomeDoVoluntario, 30, stdin);

        printf("\nQual trabalho ele vai fazer: ");
        setbuf(stdin, NULL);
        fgets(tarefaDoVoluntario, 60, stdin);

        printf("\nQuantas horas por dia este voluntario vai ajudar(Apenas números): ");
        setbuf(stdin, NULL);
        scanf("%d", &horasAVoluntariar);

        printf("\nPassaporte do funcionário: ");
        setbuf(stdin, NULL);
        fgets(numeroPassaporte, 60, stdin);
    }

    system("pause");
    Cadastro_Voluntario_Finalizado();
}

// ate aqui

///
/// AREA DE GERENCIAMENTO
///

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

void Menu_Gerenciamentos()
{
    char verificacao;

    /****************************************************************/
    /// Menu de sele��o para o gerenciamento de uma determida area ///
    /****************************************************************/

    /// Declara��o de Variaveis
    int opcao;

    /// Impress�o do Menu
    Imprime_Menu_Gerenciamento();

    printf("--> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    /// Filtar Sele��o
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
            printf("\nDeseja sair do programa?\n[S,N]--> ");
            setbuf(stdin, NULL);
            scanf("%c", &verificacao);

            if((verificacao == 's')|(verificacao == 'S')) exit(0);
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


void Imprime_Cadastro_de_Atleta_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                    Cadastro de Atleta Finalizado                |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais Atletas                                       |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Modalidade_Olimpica_Finalizado()
{
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Modalidade Olímpica, Finalizado           |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais modalidades                                   |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Localidade_Finalizado()
{
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Localidade, Finalizado                    |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais Localidade                                    |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Agendamento_Treino_Finalizado()
{
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Agendamento, Finalizado                   |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais treino                                        |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Agendamento_Jogo_Finalizado()
{
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Jogo, Finalizado                          |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais jogo                                          |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Medico_Finalizado()
{
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Medico(s), Finalizado                       |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais médicos                                       |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Funcionario_Finalizado()
{
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Funcionario(s), Finalizado                  |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais funcionario(s)                                |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Voluntario_Finalizado()
{
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Voluntario(s), Finalizado                 |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais voluntario(s)                                 |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}
