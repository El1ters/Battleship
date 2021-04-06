#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>


int Linhas,Colunas;
int Tab[16][25][2];
int Modo_Jogo,Modo_Disparo,Modo_Posicionamento;
int n_pecas=0;
int Verificacao_Tabuleiro(int linhas, int colunas);
void Tabuleiro(int tab[Linhas+1][Colunas+1][2]);
void Matriz(int tab[Linhas+1][Colunas+1][2]);
int Desenha_Pecas(int index,int ID);
int Restricao1(int tab[Linhas + 1][Colunas + 1][2]);
void Modo_Disparo1(int tab[Linhas+1][Colunas+1][2]);
void CommandLineHelp();
int main(int argc, char *argv[]) {
    srand(time(NULL));
    int opt;
    int k;
    while((opt=getopt(argc,argv,"ht:j:p:d:1:2:3:4:5:6:7:8:"))!=-1){
        switch(opt){
            case 'p':
                Modo_Posicionamento = atoi(optarg);
                double Aux = ((Linhas / 3) * (Colunas / 3)) / 2;
                    if(Modo_Posicionamento <1 || Modo_Posicionamento > 2){
                        printf("Modo de Posicionamento invalido");
                        exit(0);
                    }
                    if(Modo_Posicionamento==2 && n_pecas>(int) Aux){
                            printf("Numero de pecas foi excedido");
                            exit(0);
                    }
                break;
            case 't':
                sscanf(optarg,"%d x%d",&Linhas,&Colunas);
            if ((Linhas % 3!= 0 || Colunas % 3 != 0 || Linhas <= 8 || Linhas >= 16) || (Colunas <= 8 || Colunas >= 25)){
                printf("Dimensoes Invalidas");
                exit(0);
            }
                break;

            case 'h':
                CommandLineHelp();
                break;
            case 'j':
                Modo_Jogo = atoi(optarg);
                    if(Modo_Jogo < 0 || Modo_Jogo > 3){
                        printf("Modo de Jogo invalido");
                        exit(0);
                    }
                break;
            case 'd':
                Modo_Disparo=atoi(optarg);
                    if(Modo_Disparo<1 || Modo_Disparo>3){
                        printf("Modo de Disparo invalido");
                        exit(0);
                    }

                break;
            case '1':
                n_pecas+=atoi(optarg);
                break;
            case '2':
                n_pecas+=atoi(optarg);
                break;
            case '3':
                n_pecas+=atoi(optarg);
                break;
            case '4':
                n_pecas+=atoi(optarg);
                break;
            case '5':
                n_pecas+=atoi(optarg);
                break;
            case '6':
                n_pecas+=atoi(optarg);
                break;
            case '7':
                n_pecas+=atoi(optarg);
                break;
            case '8':
                n_pecas+=atoi(optarg);
                break;
            default:
                printf("Comando Invalido");
                break;
    }



  }
    printf("%d\n",n_pecas);
    Matriz(Tab);
    Tabuleiro(Tab);
    return 0;
}
void Tabuleiro(int tab[Linhas+1][Colunas+1][2]){
    int number = Linhas;
    char Letra = 'A';
    for(int linha = 1;linha<=Linhas;linha++){
        for(int coluna=0;coluna<=Colunas;coluna++){
            if(coluna == 0) {
                if(number>=10){
                    printf("%d ",number);
                }else {
                    printf(" %d ", number);
                }
            }else{
                if(tab[linha][coluna][1]!=0){
                    printf("%d ", tab[linha][coluna][1]);
                }else{
                    printf("_ ");
                }
            }
        }
        printf("\n");
        number--;
    }
    printf("   ");
    for(int a = 1; a <= Colunas; a++ , Letra++) {
        printf("%c ", Letra);
    }
}
void Matriz(int tab[Linhas+1][Colunas+1][2]) { /*agrupar as partes do tabuleiro em 3x3*/
    int number = 0;
    int ID;
    int index;
    for (int linhas = 1; linhas <= Linhas - 2; linhas += 3){
        for (int colunas = 1; colunas <= Colunas - 2; colunas += 3){
            if(Modo_Posicionamento==1){
                ID=rand()%42+1;
                index=0;
            }
            for (int i = 0; i < 3; i++){/*como nas peças começa a preencher na posição 6, vai se somando 5 para apenas por na matriz as partes que interessa*/
                for (int j = 0; j < 3; j++) {
                    tab[linhas + i][colunas + j][1] = Desenha_Pecas(index, ID);
                    index++;
                }
            }/*acaba uma matriz*/
               int AUX_P1=0;
               while(Restricao1(tab)==0 && Modo_Posicionamento == 1){/*Modo P1*/
                    printf("%d-",ID);
                    ID = rand()%42+1;
                    index = 0;
                    AUX_P1++;
                  if(AUX_P1==3){
                      ID = 5;
                  }
                   for (int i = 0; i < 3; i++) {
                       for (int j = 0; j < 3; j++) {
                           tab[linhas + i][colunas + j][1] = Desenha_Pecas(index, ID);
                           index++;
                       }
                   }
               }
              printf("%d certa\n",ID);
               if (ID >= 1 && ID <= 42) {
                 number++;
               }
        }
    }
}
int Verificacao_Tabuleiro(int linhas, int colunas) {
    if (linhas % 3 == 0 && colunas % 3 == 0) {
        if ((linhas >= 9 && linhas <= 15) && (colunas >= 9 && colunas <= 24)) {
            return 1;
        } else
            return 0;
    } else
        return 0;
}
int Desenha_Pecas(int index, int ID){
    /**double k = ((Linhas / 3) * (Colunas / 3)) / 2; Restriçao 4 que vai ser apenas usada para o modo p2
    if (Piece_Number >= (int) k && Modo_Posicionamento == 2){
            return 0;
    }
    */
    if(ID==1){
        int Peca[]={1,0,0,
                    0,0,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==2){
        int Peca[]={0,1,0,
                    0,0,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==3){
        int Peca[]={0,0,1,
                    0,0,0,
                    0,0,0};


        return Peca[index];
    }else if(ID==4){
        int Peca[]={0,0,0,
                    1,0,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==5){
        int Peca[]={0,0,0,
                    0,1,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==6) {
        int Peca[]={0,0,0,
                    0,0,1,
                    0,0,0};

        return Peca[index];
    }else if(ID==7) {
        int Peca[]={0,0,0,
                    0,0,0,
                    1,0,0};

        return Peca[index];
    }else if(ID==8) {
        int Peca[]={0,0,0,
                    0,0,0,
                    0,1,0};


        return Peca[index];
    }else if(ID==9) {
        int Peca[]={0,0,0,
                    0,0,0,
                    0,0,1};

        return Peca[index];
    }else if(ID==10) {
        int Peca[]={2,2,0,
                    0,0,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==11) {
        int Peca[]={0,2,2,
                    0,0,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==12) {
        int Peca[]={0,0,0,
                    2,2,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==13) {
        int Peca[]={0,0,0,
                    0,2,2,
                    0,0,0};

        return Peca[index];
    }else if(ID==14) {
        int Peca[]={0,0,0,
                    0,0,0,
                    2,2,0};

        return Peca[index];
    }else if(ID==15) {
        int Peca[]={0,0,0,
                    0,0,0,
                    0,2,2};

        return Peca[index];
    }else if(ID==16) {
        int Peca[]={2,0,0,
                    2,0,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==17) {
        int Peca[]={0,0,0,
                    2,0,0,
                    2,0,0};

        return Peca[index];
    }else if(ID==18) {
        int Peca[]={0,2,0,
                    0,2,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==19) {
        int Peca[]={0,0,0,
                    0,2,0,
                    0,2,0};

        return Peca[index];
    }else if(ID==20) {
        int Peca[]={0,0,2,
                    0,0,2,
                    0,0,0};

        return Peca[index];
    }else if(ID==21) {
        int Peca[]={0,0,0,
                    0,0,2,
                    0,0,2};

        return Peca[index];
    }else if(ID==22) {
        int Peca[]={3,3,3,
                    0,0,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==23) {
        int Peca[]={0,0,0,
                    3,3,3,
                    0,0,0};

        return Peca[index];
    }else if(ID==24) {
        int Peca[]={0,0,0,
                    0,0,0,
                    3,3,3};

        return Peca[index];
    }else if(ID==25) {
        int Peca[]={3,0,0,
                    3,0,0,
                    3,0,0};

        return Peca[index];
    }else if(ID==26) {
        int Peca[]={0,3,0,
                    0,3,0,
                    0,3,0};

        return Peca[index];
    }else if(ID==27) {
        int Peca[]={0,0,3,
                    0,0,3,
                    0,0,3};

        return Peca[index];
    }else if(ID==28) {
        int Peca[]={4,4,0,
                    4,4,0,
                    0,0,0};

        return Peca[index];
    }else if(ID==29) {
        int Peca[]={0,4,4,
                    0,4,4,
                    0,0,0};

        return Peca[index];
    }else if(ID==30) {
        int Peca[]={0,0,0,
                    4,4,0,
                    4,4,0};

        return Peca[index];
    }else if(ID==31) {
        int Peca[]={0,0,0,
                    0,4,4,
                    0,4,4};

        return Peca[index];
    }else if(ID==32) {
        int Peca[]={5,5,5,
                    0,5,0,
                    0,5,0};

        return Peca[index];
    }else if(ID==33) {
        int Peca[]={5,0,0,
                    5,5,5,
                    5,0,0};

        return Peca[index];
    }else if(ID==34) {
        int Peca[]={0,5,0,
                    0,5,0,
                    5,5,5};

        return Peca[index];
    }else if(ID==35) {
           int Peca[]={0,0,5,
                       5,5,5,
                       0,0,5};

           return Peca[index];
    }else if(ID==36) {
        int Peca[]={0,6,0,
                    6,0,6,
                    6,6,6};

        return Peca[index];
    }else if(ID==37) {
        int Peca[]={0,6,6,
                    6,0,6,
                    0,6,6};

        return Peca[index];
    }else if(ID==38) {
        int Peca[]={6,6,6,
                    6,0,6,
                    0,6,0};

        return Peca[index];
    }else if(ID==39) {
        int Peca[]={6,6,0,
                    6,0,6,
                    6,6,0};

        return Peca[index];
    }else if(ID==40) {
        int Peca[]={7,0,7,
                    7,7,7,
                    7,0,7};

        return Peca[index];
    }else if(ID==41) {
        int Peca[]={7,7,7,
                    0,7,0,
                    7,7,7};

        return Peca[index];
    }else if(ID==42) {
        int Peca[]={8,8,8,
                    8,0,8,
                    8,8,8};

        return Peca[index];
    }
    return 0;
}
void CommandLineHelp(){
    printf("-t dimensões do tabuleiro (linha x coluna).\n");
    printf("-j modo de jogo (0 a 2)\n");
    printf("-p modo de posicionamento de peças pelo computador (1 a 2)\n");
    printf("-d modo de disparo de peças pelo computador (1 a 3)\n");
    printf("-1 número de peças tipo 1 (mínimo 1)\n");
    printf("-2 número de peças tipo 2\n");
    printf("-3 número de peças tipo 3\n");
    printf("-4 número de peças tipo 4\n");
    printf("-5 número de peças tipo 5\n");
    printf("-6 número de peças tipo 6\n");
    printf("-7 número de peças tipo 7\n");
    printf("-8 número de peças tipo 8\n");
}
int Restricao1(int tab[Linhas + 1][Colunas + 1][2]){ //Restriçao=1 se a restrição está a ser executada tudo foi cumprido
    int Verifica_Matriz;
    for (int linhas = 1; linhas <= Linhas; linhas++) {
        for (int colunas = 1; colunas <= Colunas; colunas++) {
            Verifica_Matriz=((colunas-1)/3)*(Colunas/3)+((linhas-1)/3)+1; //formula de verificação da matriz
                if(tab[linhas][colunas][1]!=0){
                    for(int j=-1;j<=1;j++){
                        for(int k=-1;k<=1;k++){
                            if(tab[linhas+j][colunas+k][1]!=0 && Verifica_Matriz != ((((colunas-1+k)/3)*(Colunas/3)+(linhas-1+j)/3)+1))
                                    return 0;
                        }
                    }
                }
        }
    }
    return 1;
}
void Modo_Disparo1(int tab[Linhas+1][Colunas+1][2]){
    int Rand_Linha=rand()%Linhas+1;
    int Rand_Coluna=rand()%Colunas+1;
    if(tab[Rand_Linha][Rand_Coluna][1] == 0){
        char Missed = 'X';
        tab[Rand_Linha][Rand_Coluna][1]= Missed;
    }
}



