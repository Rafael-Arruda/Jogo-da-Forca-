#include <stdio.h>
#include <stdlib.h> //Biblioteca para a funcao exit()
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define TAMANHO_PALAVRA 20 //Constante para o tamanho da palavra

//Lista de funcoes que aparecer�o no meu c�digo (Declarando as fun��es)
int ganhou();
void chuta();
int enforcou();
void abertura();
int letraexiste(char letra);
int chuteserrados();
void desenhaforca();
void escolhepalavra();
void adicionapalavra();
int jachutou(char letra);
void abreCategoria();
void menuCategoria();
void menuNivel();
int palavraValida(char palavra[TAMANHO_PALAVRA]);

//Vari�veis Globais
FILE* f;
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int categoria;
int nivel;

//Implementa��o das Fun��es
void abertura(){
    printf("/*****************/\n");
    printf("/* Jogo da Forca */\n");
    printf("/*****************/\n\n");
}

void menuCategoria(){
    printf("-- Categorias --\n");
    printf("1 - Frutas\n2 - Animais\n3 - Casa\n");
    printf("Escolha uma categoria: ");
    scanf("%i", &categoria);
}

void menuNivel(){
    printf("\n-- Dificuldade --\n");
    printf("1 - F�cil\n2 - M�dio\n3 - Dif�cil\n");
    printf("Escolha o n�vel: ");
    scanf("%i", &nivel);
}

int ganhou(){
    for(int i=0 ;i <strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int letraexiste(char letra){
    for(int j=0; j < strlen(palavrasecreta); j++){
        if(letra == palavrasecreta[j]){
            return 1;
        }
    }
    return 0;
}

int chuteserrados(){
    int erros = 0;

    for(int i=0; i < chutesdados; i++){

        if(!letraexiste(chutes[i])){
            erros++;
        }
    }
    return erros;
}

int enforcou(){
    if(nivel == 1){
        return chuteserrados() >= 7;  //Se a expressao for verdadeira ir� retornar o valor 1, se nao, ir� retornar o valor 0
    }else if(nivel == 2){
        return chuteserrados() >= 5;  //Se a expressao for verdadeira ir� retornar o valor 1, se nao, ir� retornar o valor 0
    }else if(nivel == 3){
        return chuteserrados() >= 4;  //Se a expressao for verdadeira ir� retornar o valor 1, se nao, ir� retornar o valor 0
    }
}


//Fun��o que verifica se o meu chute � v�lido(se o chute j� foi dado e se o caracter � uma letra.)
int Valido(char chute){
    for(int i=0;i<chutesdados;i++){
        if(chutes[i] == chute){
            printf("Voc� j� chutou esta letra.\n");
            return 0;
        }
    }
    //Verificando se o caractere � uma letra
    if((chute >= 'A' && chute <= 'Z') || (chute >= 'a' && chute <= 'z')){
        return 1;
    }

    printf("S� � permitido letras.\n");
    return 0;
}

void chuta(){
    char chute;
    do{
        printf("Qual letra: ");
        scanf(" %c", &chute); //espa�o antes do %c para evitar o problema do buffer.
        chute = toupper(chute); //JOGANDO A LETRA PARA MAIUSCULA
    }while(!Valido(chute));

    //chute = toupper(chute); //JOGANDO A LETRA PARA MAIUSCULA

    if(letraexiste(chute)){
        printf("Voc� acertou: a palavra t�m a letra %c\n\n", chute);
    }else{
        printf("\nVoc� errou: a palavra N�O t�m a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra){
    int achou = 0;
    for(int j=0; j<chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca(){
    int erros = chuteserrados();

    if(nivel == 1){ //Nivel facil
        printf("  ______       \n");
        printf(" |/     |      \n");
        printf(" |     %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
        printf(" |     %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=4?'/':' '));
        printf(" |      %c     \n", (erros>=2?'|':' '));
        printf(" |     %c %c   \n", (erros>=5?'/':' '), (erros>=6?'\\':' '));
        printf("_|___          \n");
        printf("\n\n");
    }else if(nivel == 2){   //Nivel medio
        printf("  ______       \n");
        printf(" |/     |      \n");
        printf(" |     %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
        printf(" |     %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/':' '));
        printf(" |      %c     \n", (erros>=2?'|':' '));
        printf(" |     %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
        printf("_|___          \n");
        printf("\n\n");
    }else if(nivel == 3){   //Nivel dificil
        printf("  ______       \n");
        printf(" |/     |      \n");
        printf(" |     %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
        printf(" |     %c%c%c  \n", (erros>=2?'\\':' '), (erros>=2?'|':' '), (erros>=2?'/':' '));
        printf(" |      %c     \n", (erros>=2?'|':' '));
        printf(" |     %c %c   \n", (erros>=3?'/':' '), (erros>=3?'\\':' '));
        printf("_|___          \n");
        printf("\n\n");
    }

    for(int i=0; i<strlen(palavrasecreta); i++){

        if(jachutou(palavrasecreta[i])){
            printf("\a%c ", palavrasecreta[i]); // "\a" emite um som do sistema
        }else{
            printf("_ ");
        }
        sleep(1);
    }
    printf("\n");
}

void abreCategoria(){
    if(categoria == 1){
        f = fopen("palavras.txt", "r"); //Frutas
    }else if(categoria == 2){
        f = fopen("animais.txt", "r");  //Animais
    }else if(categoria == 3){
        f = fopen("casa.txt", "r");    //Itens de casa
    }
}

void escolhepalavra(){
    abreCategoria();
    if(f == 0){
        printf("Banco de dados de palavras n�o dispon�vel \n");
        exit(1); //Funcao que indica ao meu sistema que o programa terminou de modo n�o esperado.
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0)); //Ou srand(time(NULL)); //Garante que n�o haja repeti��es
    int randomico = rand() % qtddepalavras;

    for(int i=0; i<=randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }
    fclose(f);
}

//Est� fun��o zera todos os chutes dados para iniciar um novo jogo
void zerarChutes(){
    for(int i=0;i<TAMANHO_PALAVRA;i++){
        chutes[i] = ' ';
    }
    chutesdados = 0;
}

int palavraValida(char palavra[TAMANHO_PALAVRA]){ //Recebe como parametro a palavra que o usuario quer adicionar
    abreCategoria();

    char palavraArq[TAMANHO_PALAVRA];

    int qtd;
    fscanf(f ,"%d", &qtd);

    for(int i=0;i<qtd;i++){
        fscanf(f, "%s", palavraArq);
        if(!strcmp(palavraArq, palavra)){
            fclose(f);
            printf("Est� palavra j� foi cadastrada...Tente outra!\n\n");
            return 0;
        }
    }
    printf("Palavra adicionada com sucesso no banco de dados!\n\n");
    fclose(f);
    return 1;
}

void adicionapalavra(){
    char quer;
    printf("Voc� deseja adicionar uma nova palavra no jogo (S/N)? ");
    scanf(" %c", &quer);

    if(quer == 'S'){
        char novapalavra[TAMANHO_PALAVRA];

        do{

            printf("Digite uma palavra relacionada a categoria escolhida: ");
            scanf("%s", novapalavra);

            //colocando a palavra digitada toda em maiusculo
            for(int i=0; novapalavra[i] != '\0'; i++){
                novapalavra[i] = toupper(novapalavra[i]);
            }

        }while(!palavraValida(novapalavra));

        if(categoria == 1){
            f = fopen("palavras.txt", "r+");  //r+ permite lermos e alterar o arquivo de texto.
        }else if(categoria == 2){
            f = fopen("animais.txt", "r+");  //r+ permite lermos e alterar o arquivo de texto.
        }else if(categoria == 3){
            f = fopen("casa.txt", "r+");  //r+ permite lermos e alterar o arquivo de texto.
        }

        if(f == 0){ //Indica que deu problema
            printf("Banco de dados de palavras n�o dispon�vel.\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0 , SEEK_SET); //Modificando a posi��o do ponteiro para o inicio(come�o) do arquivo
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END); //Modificando a posi��o do ponteiro para o final do arquivo
        fprintf(f, "\n%s", novapalavra);

        //Fecha o arquivo
        fclose(f);
    }
}

int main()
{
    setlocale(LC_ALL,"");
    int resp;
    do{
        abertura();
        menuCategoria();
        menuNivel();
        escolhepalavra();

        do{

            desenhaforca();
            chuta();
            sleep(2);
            system("cls");

        }while(!ganhou() && !enforcou());

        if(ganhou()){
            printf("\nParab�ns, voc� ganhou!\n\n");

            printf("       ___________     \n");
            printf("      '._==_==_=_.'    \n");
            printf("      .-\\:      /-.   \n");
            printf("      | (|:.    |) |   \n");
            printf("       '-|:.    |-'    \n");
            printf("         \\::.   /     \n");
            printf("          '::. .'      \n");
            printf("            ) (        \n");
            printf("          _.' '._      \n");
            printf("         '- - - -'     \n");

            adicionapalavra();

        }else{
            printf("\nPuxa, voc� foi enforcado!\n\n");
            printf("A palavra era **%s** \n\n", palavrasecreta);

            printf("    ______________          \n");
            printf("   /              \\        \n");
            printf("  /                \\       \n");
            printf("//                  \\/\\   \n");
            printf("\\|   XXXX    XXXX   | /    \n");
            printf("  |   XXXX    XXXX   |/     \n");
            printf("  |   XXX      XXX   |      \n");
            printf("  |                  |      \n");
            printf("  \\__    XXX       __/     \n");
            printf("   |\\    XXX      /|       \n");
            printf("   | |           | |        \n");
            printf("   | I I I I I I I |        \n");
            printf("   |  I I I I I I  |        \n");
            printf("   \\_             _/       \n");
            printf("     \\_         _/         \n");
            printf("       \\_______/           \n");
        }

        zerarChutes();

        printf("Deseja jogar novamente?\n1 - SIM\n2 - N�O\nSua resposta: ");
        scanf("%i",&resp);

        system("cls");

    }while(resp != 2);
    return 0;
}
