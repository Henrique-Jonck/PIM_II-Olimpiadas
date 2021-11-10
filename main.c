// VERS�O 1.3

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int cod_AtualUsuario, cod_UltimoUsuario, num_cadastros;
char informacoes[10][100];

///----------------------------------------------------------------------------------------------------------------------------------/
/// FUN��O PRINCIPAL                                                                                                                 /
///----------------------------------------------------------------------------------------------------------------------------------/

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Logo();
    //Menu_Login();
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
            Cadastro_Modalidade();
            break;
        case 3:
            Cadastro_Localidade();
            break;
        case 4:
            Cadastro_AgendamentoTreino();
            break;
        case 5:
            Cadastro_AgendamentoJogo();
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
            if(Msg_Pergunta("\nDeseja sair do programa?") == 1) exit(0);
            else Menu_Cadastros();
            break;
        default:
            Menu_Cadastros();
    }
}

void Cadastro_Atleta()
{
    int quantidadeDeAtletas, idadeDoAtleta, count;
    char nomeDoAtleta[100], paisDoAtleta[100], sexoDoAtleta[12], passaporteDoAtleta[15], modalidadeQueOAtletaVaiJogar[30];

    system("cls");
    printf("+-----------------------------------------------------------------+\n"
           "|                         Cadastrar Atleta                        |\n"
           "+-----------------------------------------------------------------+\n"
           "| Deseja cadastrar quantos atletas?                               |\n"
           "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeAtletas);
    setbuf(stdin, NULL);

    for (count = 0; count < quantidadeDeAtletas; count++)
    {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                     Cadastrando novo Atleta                     |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome Completo do Atleta: ");
        setbuf(stdin, NULL);
        fgets(nomeDoAtleta, 100, stdin);

        printf("\nPa�s de Origem: ");
        setbuf(stdin, NULL);
        fgets(paisDoAtleta, 100, stdin);

        printf("\nSexo [M/F]: ");
        setbuf(stdin, NULL);
        fgets(sexoDoAtleta, 12, stdin);

        printf("\nN�mero do passaporte: ");
        setbuf(stdin, NULL);
        fgets(passaporteDoAtleta, 18, stdin);

        printf("\nModalidade Ol�mpica do atleta: ");
        setbuf(stdin, NULL);
        fgets(modalidadeQueOAtletaVaiJogar, 30, stdin);
    }

    system("pause");
    Cadastro_Atleta_Finalizado();
}

void Cadastro_Modalidade()
{
    int count, quantidadeDeModalidade;
    char nomeDaModalidade[20], equipamentoDaModalidade[200], alojamentoDaModalidade[30];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Modalidade Ol�mpica                       |\n"
            "+-----------------------------------------------------------------+\n"
            "| Deseja cadastrar quantas Modalidades?                           |\n"
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

        printf("\nEquipamentos que a equipe vai utlizar (Separe os nomes dos equipamentos por v�rgulas): ");
        setbuf(stdin, NULL);
        fgets(equipamentoDaModalidade, 200, stdin);

        printf("\nOnde ser� o alojamento dessa modalidade?: ");
        setbuf(stdin, NULL);
        fgets(alojamentoDaModalidade, 30, stdin);
    }
    system("pause");
    Cadastro_Modalidade_Finalizado();
}


void Cadastro_Localidade()
{
    int count, quantidadeDeLocal;
    char estadioQueVaiAcontecerOsJogos[30], cidadeQueVaiAcontecerOsJogos[30];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Localidade                      |\n"
            "+-----------------------------------------------------------------+\n"
            "| Deseja cadastrar quantos Locais?                                |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeLocal);

    for (count = 0; count < quantidadeDeLocal; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                      Cadastrando novo Local                     |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome da Cidade: ");
        setbuf(stdin, NULL);
        fgets(cidadeQueVaiAcontecerOsJogos, 30, stdin);

        printf("\nNome do est�dio: ");
        setbuf(stdin, NULL);
        fgets(estadioQueVaiAcontecerOsJogos, 30, stdin);
    }

    system("pause");
    Cadastro_Localidade_Finalizado();
}

void Cadastro_AgendamentoTreino()
{
    int count, quantidadeDeAgendamento;
    char modalidadeQueVaiTreinar[30], localDoTreino[40];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                         Cadastrar Treino                        |\n"
            "+-----------------------------------------------------------------+\n"
            "| Deseja agendar quantos treinos?                                 |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeAgendamento);

    for (count = 0; count < quantidadeDeAgendamento; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                     Novo Cadastro de Treino                     |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nQual modalidade ol�mpica vai treinar: ");
        setbuf(stdin, NULL);
        fgets(modalidadeQueVaiTreinar, 30, stdin);

        printf("\nLocal do treino: ");
        setbuf(stdin, NULL);
        fgets(localDoTreino, 40, stdin);
    }

    system("pause");
    Cadastro_AgendamentoTreino_Finalizado();
}

void Cadastro_AgendamentoJogo()
{
    int count, quantidadeDeAgendamento;
    char modalidadeQueVaiJogar[40], localDoJogo[40], horarioDoJogo[4];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                          Cadastrar Jogo                         |\n"
            "+-----------------------------------------------------------------+\n"
            "| Deseja agendar quantos Jogos?                                   |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeAgendamento);

    for (count = 0; count < quantidadeDeAgendamento; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                      Novo Cadastro de Jogo                      |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nQual modalidade ol�mpica vai jogar: ");
        setbuf(stdin, NULL);
        fgets(modalidadeQueVaiJogar, 30, stdin);

        printf("\nEm qual est�dio ser� o jogo: ");
        setbuf(stdin, NULL);
        fgets(localDoJogo, 40, stdin);

        printf("\nHorario do Jogo(Formato 24h. Apenas n�mero!!!): ");
        setbuf(stdin, NULL);
        fgets(horarioDoJogo, 4, stdin);
    }

    system("pause");
    Cadastro_AgendamentoJogo_Finalizado();
}

void Cadastro_Medico()
{
    int count, quantidadeDeMedicos;
    char modalidadeDeAtuacao[20];
    char nomeDoMedico[50];

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                         Cadastrar M�dico                        |\n"
            "+-----------------------------------------------------------------+\n"
            "| Deseja cadastrar quantos m�dicos?                               |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeMedicos);

    for (count = 0; count < quantidadeDeMedicos; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                     Novo Cadastro de M�dico                     |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome do m�dico: ");
        setbuf(stdin, NULL);
        fgets(nomeDoMedico, 50, stdin);

        printf("\nQual modalidade o m�dico vai atuar: ");
        setbuf(stdin, NULL);
        fgets(modalidadeDeAtuacao, 20, stdin);
    }

    system("pause");
    Cadastro_Medico_Finalizado();
}

void Cadastro_Funcionario()
{
    int count, quantidadeDeFuncionarios, horasATrabalhar;
    char nomeDoFuncionario[30], trabalhoDesteFuncionario[50], numeroPassaporte[15];
    float salarioDoFuncionario;

    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                      Cadastrar Funcion�rio                      |\n"
            "+-----------------------------------------------------------------+\n"
            "| Deseja cadastrar quantos funcion�rios?                          |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeFuncionarios);

    for (count = 0; count < quantidadeDeFuncionarios; count++) {
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                         Novo Funcion�rio                        |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome do funcionario: ");
        setbuf(stdin, NULL);
        fgets(nomeDoFuncionario, 30, stdin);

        printf("\nQual trabalho ele ir� fazer: ");
        setbuf(stdin, NULL);
        fgets(trabalhoDesteFuncionario, 50, stdin);

        printf("\nQuantas horas por dia este funcion�rio ir� trabalhar(Apenas n�meros): ");
        setbuf(stdin, NULL);
        scanf("%d", &horasATrabalhar);

        printf("\nSal�rio do funcion�rio(Ex: 1.600): ");
        setbuf(stdin, NULL);
        scanf("%f", &salarioDoFuncionario);

        printf("\nPassaporte do funcion�rio: ");
        setbuf(stdin, NULL);
        scanf("%s", numeroPassaporte);
    }

    system("pause");
    Cadastro_Funcionario_Finalizado();
}

void Cadastro_Voluntario()
{
    /// DECLARA��O DE VARIAVEIS
    int count, quantidadeDeVoluntarios, horasAVoluntariar;
    char nomeDoVoluntario[30], tarefaDoVoluntario[60], numeroPassaporte[15], textoFinal[200];

    /// IMPRESS�O DO MENU
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                       Cadastrar Volunt�rio                      |\n"
            "+-----------------------------------------------------------------+\n"
            "| Deseja cadastrar quantos voluntarios?                           |\n"
            "+-----------------------------------------------------------------+\n\n");

    printf("--> ");
    scanf("%d", &quantidadeDeVoluntarios);

    /// INSERS�O DE CADA ENTRADA
    for (count = 0; count < quantidadeDeVoluntarios; count++) {
        system("cls");
        printf("\n+-----------------------------------------------------------------+\n"
                 "|                         Novo Voluntario                         |\n"
                 "+-----------------------------------------------------------------+\n");

        printf("\nNome do voluntario: ");
        setbuf(stdin, NULL);
        fgets(nomeDoVoluntario, 30, stdin);

        printf("\nQual trabalho ele vai fazer: ");
        setbuf(stdin, NULL);
        fgets(tarefaDoVoluntario, 60, stdin);

        printf("\nQuantas horas por dia este voluntario vai ajudar(Apenas n�meros): ");
        setbuf(stdin, NULL);
        scanf("%d", &horasAVoluntariar);

        printf("\nPassaporte do funcion�rio: ");
        setbuf(stdin, NULL);
        fgets(numeroPassaporte, 60, stdin);

        //Substituir quebra de linha pelo final da string
        Substituir_QuebraLinha(&nomeDoVoluntario, 30);
        Substituir_QuebraLinha(&tarefaDoVoluntario, 60);
        Substituir_QuebraLinha(&numeroPassaporte, 15);

        sprintf(textoFinal, "\n%s�%s�%d�%s�", nomeDoVoluntario, tarefaDoVoluntario, horasAVoluntariar, numeroPassaporte);
        Arquivo_Escrever("Voluntarios.txt", textoFinal);
    }

    system("pause");
    Cadastro_Voluntario_Finalizado();
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
    /// IMPRESS�O DO MENU
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                    Contabiliza��o de Medalhas                   |\n"
            "+-----------------------------------------------------------------+\n\n\n");


    /// IMPRESS�O DA TABELA
    printf( "+-----------------+-----------------+-----------------+-----------------+\n"
            "| Nome            | Fun��o          | Horas           | Passaporte      |\n"
            "+-----------------+-----------------+-----------------+-----------------+\n");
    for(int i = 1; i < 4; i++)
    {
        Arquivo_Ler("Voluntarios.txt", i);

        printf("|%17s|%17s|%17s|%17s|\n", informacoes[0], informacoes[1], informacoes[2], informacoes[3]);
    }
    printf( "+-----------------+-----------------+-----------------+-----------------+\n");


    /// SAIDA DO MENU
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

void Substituir_QuebraLinha(char *variavel, int tamanho)
{
    for(int i = 0; i < tamanho; i++) if(variavel[i] == 10) variavel[i] = '\0';
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

int Arquivo_Escrever(char nomeArquivo[30], char texto[300])
{
    /// DECLARA��O DE VARIAVEIS
    FILE *arquivo;

    /// ABRIR E VERIFICAR ARQUIVO
    arquivo = fopen(nomeArquivo, "a");
    if(arquivo == NULL) return 1;

    /// ESCREVER NO ARQUIVO
    fprintf(arquivo, texto);

    /// FECHAR O ARQUIVO
    fclose(arquivo);
    return 0;
}

int Arquivo_Ler(char nomeArquivo[30], int linha)
{
    /// DECLARA��O DE VARIAVEIS
    FILE *arquivo;
    char texto[100], *pedaco;
    int contador = 0, index;

    /// ABRIR E VERIFICAR ARQUIVO
    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL) return 1;

    /// PERCORRER CADA LINHA DO ARQUIVO
    while (fgets(texto, 100, arquivo) > 0)
    {
        // Verifica se o contador esta na linha requisitada
        if(linha == contador)
        {
            // Divide a linha entre os delimitadores
            pedaco = strtok(texto, "�");

            // Percorre cada divis�o da linha
            index = 0;
            while(pedaco != NULL)
            {
                // Copia a informa��o dividida para a matriz
                strcpy(informacoes[index], pedaco);
                pedaco = strtok(NULL, "�");
                index++;
            }

            /// FECHA O ARQUIVO INDICANDO "ENCONTRADO"
            fclose(arquivo);
            return 0;
        }
        contador++;
    }

    /// FECHA O ARQUIVO INDICANDO "N�O ENCONTRADO"
    fclose(arquivo);
    return 2;
}

/// CADASTRO FINALIZADO -------------------------------------------------------------------------------------------------------------|

void Cadastro_Atleta_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_Atleta_Finalizado();

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
        Cadastro_Atleta_Finalizado();
    }
}

void Cadastro_Modalidade_Finalizado()
{
    int escolhaDoUsuario;
    Imprime_Cadastro_Modalidade_Finalizado();

    printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_Modalidade();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_Modalidade_Finalizado();
    }
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

void Cadastro_AgendamentoTreino_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_AgendamentoTreino_Finalizado();

     printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_AgendamentoTreino();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_AgendamentoTreino_Finalizado();
    }
}

void Cadastro_AgendamentoJogo_Finalizado()
{
    int escolhaDoUsuario;

    Imprime_Cadastro_AgendamentoJogo_Finalizado();

     printf("--> ");
    scanf("%d", &escolhaDoUsuario);

    switch (escolhaDoUsuario)
    {
    case 1:
        Cadastro_AgendamentoJogo();
        break;
    case 2:
        Menu_Cadastros();
        break;
    default:
        Cadastro_AgendamentoJogo_Finalizado();
    }
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

/// IMPRESS�O -----------------------------------------------------------------------------------------------------------------------|

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
            "| 2- Modalidade Ol�mpica                                          |\n"
            "| 3- Localidade                                                   |\n"
            "| 4- Agendar Treino                                               |\n"
            "| 5- Agendar Jogo                                                 |\n"
            "| 6- M�dico                                                       |\n"
            "| 7- Funcion�rio                                                  |\n"
            "| 8- Volunt�rio                                                   |\n"
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

void Imprime_Cadastro_Atleta_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|                    Cadastro de Atleta Finalizado                |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais Atletas                                       |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Modalidade_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Modalidade Ol�mpica, Finalizado           |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais modalidades                                   |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Localidade_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Localidade, Finalizado                    |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais Localidade                                    |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_AgendamentoTreino_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Agendamento, Finalizado                   |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais treino                                        |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_AgendamentoJogo_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Jogo, Finalizado                          |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais jogo                                          |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Medico_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Medico(s), Finalizado                       |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais m�dicos                                       |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Funcionario_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Funcionario(s), Finalizado                  |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais funcionario(s)                                |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

void Imprime_Cadastro_Voluntario_Finalizado()
{
    system("cls");
    printf( "+-----------------------------------------------------------------+\n"
            "|           Cadastro de Voluntario(s), Finalizado                 |\n"
            "+-----------------------------------------------------------------+\n"
            "| 1- Cadastrar mais voluntario(s)                                 |\n"
            "| 2- Voltar para tela de Cadastros                                |\n"
            "+-----------------------------------------------------------------+\n\n");
}

