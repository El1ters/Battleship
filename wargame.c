#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

#define TAB_COL 15
#define TAB_ROW 24


/*Global variables*/
int g_lines,g_columns;
int Tab[TAB_COL][TAB_ROW][2];
int Modo_Jogo,Modo_Disparo,Modo_Posicionamento;
int n_pecas=0,Tipo_Peca[9],Default[9];

/*Funcions*/
void Tabuleiro(void);
void Matriz(void);
void delay(int number_of_seconds);
int Desenha_Pecas(int index,int ID);
int Restricao1(void);
void Modo_Disparo1(int number_of_squares);
void Modo_Disparo2(int shoot_line,int shoot_column);
void CommandLineHelp();
int Modo_P2(int AUX_P2[9]);


int main(int argc, char *argv[]) {
    srand(time(NULL));
    int opt;
    double Aux;
    while((opt=getopt(argc,argv,"ht:j:p:d:1:2:3:4:5:6:7:8:"))!=-1){
        switch(opt){
            case 'p':
                Modo_Posicionamento = atoi(optarg);
                break;
            case 't':
                sscanf(optarg,"%d x%d",&g_lines,&g_columns);
                Aux = ((g_lines / 3) * (g_columns / 3)) / 2; /*Variavel auxiliar para ajudar a realizar a restriçao 3*/
            if ((g_lines % 3!= 0 || g_columns % 3 != 0 || g_lines <= 8 || g_lines >= 16) || (g_columns <= 8 || g_columns >= 25)){
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
                Modo_Disparo = atoi(optarg);

                    if (Modo_Disparo < 1 || Modo_Disparo > 3){
                        printf("Modo de Disparo invalido");
                        exit(0);
                    }

                break;
            case '1':
            printf("1");
                Tipo_Peca[1] = atoi(optarg);
                n_pecas += Tipo_Peca[1];
                Default[1] = Tipo_Peca[1];
                
                break;
            case '2':
            printf("2");
                Tipo_Peca[2] = atoi(optarg);
                n_pecas += Tipo_Peca[2];
                Default[2] = Tipo_Peca[2];
                
                break;
            case '3':
            printf("3");
                Tipo_Peca[3] = atoi(optarg);
                n_pecas += Tipo_Peca[3];
                Default[3] = Tipo_Peca[3];
                break;
            case '4':
                Tipo_Peca[4] = atoi(optarg);
                n_pecas += Tipo_Peca[4];
                Default[4] = Tipo_Peca[4];               
                break;
            case '5':
                Tipo_Peca[5] = atoi(optarg);
                n_pecas += Tipo_Peca[5];
                Default[5] = Tipo_Peca[5];            
                break;
            case '6':
                Tipo_Peca[6] = atoi(optarg);
                n_pecas += Tipo_Peca[6];
                Default[6] = Tipo_Peca[6];                
                break;
            case '7':
                Tipo_Peca[7] = atoi(optarg);
                n_pecas += Tipo_Peca[7];
                Default[7] = Tipo_Peca[7];                
                break;
            case '8':
                Tipo_Peca[8] = atoi(optarg); 
                n_pecas += Tipo_Peca[8];
                Default[8] = Tipo_Peca[8];
                               
                break;
            default:
                printf("Comando Invalido");
                break;
         
        }
            if(Tipo_Peca[8] > Tipo_Peca[7] || 
               Tipo_Peca[7] > Tipo_Peca[6] || 
               Tipo_Peca[6] > Tipo_Peca[5] ||
               Tipo_Peca[5] > Tipo_Peca[4] || 
               Tipo_Peca[4] > Tipo_Peca[3] || 
               Tipo_Peca[3] > Tipo_Peca[2] || 
               Tipo_Peca[2] > Tipo_Peca[1])  { /* Restrição 3*/
                printf("não está de acordo com a Restricao 3\n");
                exit(0);
            }
            if(Modo_Posicionamento==2 && n_pecas>(int) Aux){
                printf("%lf\n",Aux);
                exit(0);
            }
            if(Modo_Posicionamento==1 && 
            		 (Tipo_Peca[8]!=0 || 
            		  Tipo_Peca[7]!=0 || 
            		  Tipo_Peca[6]!=0 || 
            		  Tipo_Peca[5]!=0 || 
            		  Tipo_Peca[4]!=0 || 
            		  Tipo_Peca[3]!=0 || 
            		  Tipo_Peca[2]!=0 || 
            		  Tipo_Peca[1]!=0)){
                printf("o comando -[1 a 8] apenas é valido para o modo p 2\n");
                exit(0);
            }              

    }
    /*printf("row size:%d\n",g_lines);
    printf("columns size:%d\n",g_columns);
    printf("position mode:%d\n",Modo_Posicionamento);
    printf("0:%d\n",Tipo_Peca[0]);
    printf("1:%d\n",Tipo_Peca[1]);
    printf("2:%d\n",Tipo_Peca[2]);
    printf("3:%d\n",Tipo_Peca[3]);
    printf("4:%d\n",Tipo_Peca[4]);
    printf("5:%d\n",Tipo_Peca[5]);
    printf("6:%d\n",Tipo_Peca[6]);
    printf("7:%d\n",Tipo_Peca[7]);
    printf("8:%d\n",Tipo_Peca[8]);*/

    int number_of_squares = g_lines * g_columns;
    Tipo_Peca[0] = (g_lines * g_columns / 9) - n_pecas;
    Default[0] = Tipo_Peca[0];
    Matriz();
    int disparo=1;
    if(Modo_Disparo==1){
    	while(number_of_squares>=0){
    		delay(150);
    		printf("\n\n");
    		Modo_Disparo1(number_of_squares);
    		system("clear");
    		Tabuleiro();
    		number_of_squares--;	
    		disparo++;    	
    	}
    }
    int matrix_number = g_lines * g_columns / 9;
    while(Modo_Disparo==2 && matrix_number>0){
    	for(int shoot_line=1;shoot_line<=g_lines-2;shoot_line+=3){
    		for(int shoot_column=1;shoot_column<=g_lines-2;shoot_column+=3){
    			Modo_Disparo2(shoot_line,shoot_column);
    			Tabuleiro();
    			printf("\n");
    			matrix_number--;
    				
    		}
    	}

    	printf("%d\n",matrix_number);
    }
    
    /*		
    printf("verificar todas as pecas\n");
    printf("-0-%d\n",Tipo_Peca[0]);					
    printf("-1-%d\n",Tipo_Peca[1]);
    printf("-2-%d\n",Tipo_Peca[2]);
    printf("-3-%d\n",Tipo_Peca[3]);
    printf("-4-%d\n",Tipo_Peca[4]);
    printf("-5-%d\n",Tipo_Peca[5]);
    printf("-6-%d\n",Tipo_Peca[6]);
    printf("-7-%d\n",Tipo_Peca[7]);
    printf("-8-%d\n",Tipo_Peca[8]);
    return 0;
    */
    	
}
void Tabuleiro(void){
    int number = g_lines;
    char Letra = 'A';
    int number_aux;
    for(int linha = 0;linha <= g_lines-1; linha++){
        for(int coluna = -1; coluna <= g_columns-1; coluna++){
            if(coluna == -1) {
                if(number >= 10){
                    printf("%d ",number);
                }else {
                    printf(" %d ", number);
                }
            }else{
            	printf("%c ",Tab[linha][coluna][0] == 0 ? ' ' : (Tab[linha][coluna][1] == 0 ? '-' : '0' + Tab[linha][coluna][1]));
            	/*
                if(Tab[linha][coluna][1] != 0){
                    printf("%d ", Tab[linha][coluna][1]);
                }else{
                    printf("- ");
                 
                }*/
            }
        }
        printf("\n");
        number--;
    }
    printf("   ");
    for(int a = 1; a <= g_columns; a++ , Letra++) {
        printf("%c ", Letra);
    }
}
void Matriz(void) { /*agrupar as partes do tabuleiro em 3x3*/
    int ID;
    int index;
    int AUX_P2[9];

/*for(int i=0;i<1000;i++ ){}*/
    for (int linhas = 0; linhas <= g_lines - 1; linhas += 3){
        for (int colunas = 0; colunas <= g_columns - 1 ; colunas += 3){
            if(Modo_Posicionamento==1){
                ID = rand()%42 + 1;
                index = 0;
            }else if(Modo_Posicionamento == 2){
                ID=Modo_P2(AUX_P2);
                index=0;
            }
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    Tab[linhas+i][colunas+j][1] = Desenha_Pecas(index, ID);
                    index++;
                }
            }/*acaba uma matriz*/

                int AUX_P1 = 0;
                while(Restricao1() == 0 && Modo_Posicionamento == 1){/*Modo P1*/ 
                	   printf("%d-",ID);/*Debug para verificar restrição 1*/  
                       ID = rand()%42+1;
                       index = 0;
                       AUX_P1++;
                    if(AUX_P1==3){
                        ID = 5;
                    }
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            Tab[linhas+i][colunas+j][1] = Desenha_Pecas(index, ID);
                            index++;
                        }
                    }  
                }
                //printf("%d certa\n",ID);/*Debug para verificar Restrição 1*/
                AUX_P2[0] = 0;
                AUX_P2[1] = 0;
                AUX_P2[2] = 0;
                AUX_P2[3] = 0;
                AUX_P2[4] = 0;
                AUX_P2[5] = 0;
                AUX_P2[6] = 0;
                AUX_P2[7] = 0;
                AUX_P2[8] = 0;
                int Var = 0;/*variável auxiliar utilizada para verificar, quando trocar de tipo de peça dentro da função Modo_P2 e essa peça não couber voltar á variante inicial desse tipo de peça*/                               
                int tentativas;
                while(Restricao1() == 0 && Modo_Posicionamento == 2){/*Modo P2*/
                /*
                if(Modo_P2(AUX_P2)==-1){
                    	printf("ID:%d\n",ID);
                        printf("reset\n");
                        linhas=0;
                        colunas=0;
                        Tipo_Peca[0]=Default[0];
                        Tipo_Peca[1]=Default[1];
                        Tipo_Peca[2]=Default[2];
                        Tipo_Peca[3]=Default[3];
                        Tipo_Peca[4]=Default[4];
                        Tipo_Peca[5]=Default[5];
                        Tipo_Peca[6]=Default[6];
                        Tipo_Peca[7]=Default[7];
                        Tipo_Peca[8]=Default[8];
                        AUX_P2[1]=0;
                        AUX_P2[2]=0;
                        AUX_P2[3]=0;
                        AUX_P2[4]=0;
                        AUX_P2[5]=0;
                        AUX_P2[6]=0;
                        AUX_P2[7]=0;
                        AUX_P2[8]=0;

                    }*/              
                    if((ID >= 1 && ID <= 9) && Var == 0 /*&& Restricao1(Tab)==0*/){
                        ID = 1;
                        printf("(%d)-",ID);
                    }
                    if((ID >= 10 && ID <= 21) && Var == 0 /*&& Restricao1(Tab)==0*/){
                        ID = 10;
                        printf("(%d)-",ID);
                    }
                    if((ID >= 22 && ID <= 27) && Var == 0 /*&& Restricao1(Tab)==0*/){
                        ID = 22;
                        printf("(%d)-",ID); 
                    }
                    if((ID >= 28 && ID <= 31) && Var == 0 /*&& Restricao1(Tab)==0*/){
                        ID = 28;
                        printf("(%d)-",ID); 
                    }
                    if((ID >= 32 && ID <= 35) && Var == 0 /*&& Restricao1(Tab)==0*/){
                        ID = 32;
                        printf("(%d)-",ID); 
                    }
                    if((ID >= 36 && ID <= 39) && Var == 0 /*&& Restricao1(Tab)==0*/){
                        ID = 36;
                        printf("(%d)-",ID); 
                    }
                    if((ID >= 40 && ID <= 41) && Var == 0 /*&& Restricao1(Tab)==0*/){
                        ID = 40;
                        printf("(%d)-",ID); 
                    }
                    
                    Var++;
                    /*
                    if(Tipo_Peca[1]==0){
                        AUX_P2[1]=1;
                        
                    }
                    if(Tipo_Peca[2]==0){
                        AUX_P2[2]=1;
                        
                    }
                    if(Tipo_Peca[3]==0){
                        AUX_P2[3]=1;
                        
                    }
                    if(Tipo_Peca[4]==0){
                        AUX_P2[4]=1;
                        
                    }
                    if(Tipo_Peca[5]==0){
                        AUX_P2[5]=1;
                        
                    }
                    if(Tipo_Peca[6]==0){
                        AUX_P2[6]=1;
                        
                    }
                    if(Tipo_Peca[6]==0){
                        AUX_P2[6]=1;
                        
                    }
                    if(Tipo_Peca[7]==0){
                        AUX_P2[7]=1;
                       
                    }
                    if(Tipo_Peca[8]==0){
                        AUX_P2[8]=1;
                        
                    }*/
                    if(ID == 9 &&/* Restricao1()==0 &&*/ Var != 0){/*Verificar se a ultima variante da peça do tipo 1 cabe*/
                        printf("%d-",ID);
                        AUX_P2[1] = 1;
                        Tipo_Peca[1]++; 
                        ID=Modo_P2(AUX_P2);
                        
                        Var = 0;
                        tentativas++;                       
                    }
                    else if(ID == 21 &&/* Restricao1()==0 &&*/ Var != 0){/*Verificar se a ultima variante da peça do tipo 2 cabe*/
                        printf("%d-",ID);
                        AUX_P2[2] = 1;
                        Tipo_Peca[2]++; 
                        ID = Modo_P2(AUX_P2);
                        
                        Var = 0;
                        tentativas++; 
                    }
                    else if(ID == 27 &&/* Restricao1()==0 &&*/ Var != 0){/*Verificar se a ultima variante da peça do tipo 3 cabe*/
                        AUX_P2[3] = 1;
                        Tipo_Peca[3]++;
                        ID = Modo_P2(AUX_P2);
                        
                        Var = 0;
                        tentativas++;                        
                    }
                    else if(ID == 31  && /*Restricao1()==0 &&*/ Var != 0){/*Verificar se a ultima variante da peça do tipo 4 cabe*/
                        printf("%d-",ID);
                        AUX_P2[4] = 1;
                        Tipo_Peca[4]++; 
                        ID = Modo_P2(AUX_P2);
                        
                        Var = 0;
                        tentativas++;                        
                    }
                    else if(ID == 35 &&/* Restricao1()==0 &&*/ Var != 0){/*Verificar se a ultima variante da peça do tipo 5 cabe*/
                        printf("%d-",ID);
                        AUX_P2[5] = 1; 
                        Tipo_Peca[5]++;
                        ID = Modo_P2(AUX_P2);
                        
                        Var = 0;
                        tentativas++;
                        
                    }
                    else if(ID == 39 &&/* Restricao1()==0 &&*/ Var != 0){/*Verificar se a ultima variante da peça do tipo 6 cabe*/
                        printf("%d-",ID);
                        AUX_P2[6] = 1;
                        Tipo_Peca[6]++; 
                        ID = Modo_P2(AUX_P2);
                        
                        Var = 0;
                        tentativas++;
                    }
                    else if(ID == 41 &&/* Restricao1()==0 &&*/ Var != 0){/*Verificar se a ultima variante da peça do tipo 7 cabe*/;
                        printf("%d-",ID);
                        AUX_P2[7]=1;
                        Tipo_Peca[7]++; 
                        ID = Modo_P2(AUX_P2);
                        
                        Var = 0;
                        tentativas++;
                    }
                    else if(ID == 42 /*&& Restricao1()==0*/){/*Verificar se a ultima variante da peça do tipo 8 cabe*/
                        printf("%d-",ID);
                        AUX_P2[8] = 1;
                        Tipo_Peca[8]++;                         
                        ID=Modo_P2(AUX_P2);
                        Var = 0;
                        tentativas++;
                        
                    }else{ 
                        ID++;
                    }
                   
                    
                    

                    /*Falta ver os casos em que quando passa de uma variante para a outra e no caso da peça que for sorteada couber*/
                    index = 0;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            Tab[linhas + i][colunas + j][1] = Desenha_Pecas(index,ID);
                            index++;
                        }
                    }
                    printf("%d-",ID);                   
                    
                }
                printf("%d certa\n",ID);


        }
    }
}
int Desenha_Pecas(int index, int ID){
    if(ID==0){
        int Peca[]={0,0,0,
                    0,0,0,
                    0,0,0};

        return Peca[index];           
    }
    else if(ID==1){
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
int Restricao1(){ //Restriçao=1 se a restrição está a ser executada tudo foi cumprido
    int Verifica_Matriz;
    for (int linhas = 0; linhas <= g_lines-1; linhas++) {
        for (int colunas = 0; colunas <= g_columns-1; colunas++) {
            Verifica_Matriz = (colunas / 3) * (g_columns / 3) + (linhas / 3) + 1; //formula de verificação da matriz
                if(Tab[linhas][colunas][1] != 0){
                    for(int j = -1;j <= 1;j++){
                        for(int k = -1;k <= 1;k++){
                        	if(linhas + j < 0 || linhas + j >= g_lines){
                        		continue;
                        	}
                        	if(colunas + k < 0 || colunas + k >= g_columns){
                        		continue;
                        	}
                            if(Tab[linhas + j][colunas + k][1] != 0 && Verifica_Matriz != ((((colunas + k) / 3) * (g_columns / 3) + ( linhas  + j ) / 3 ) + 1))
                                return 0;
                        }
                    }
                }
        }
    }
    return 1;
}

void Modo_Disparo1(int numero_quadriculas){
		int rand_coluna;
		int rand_linha;
		rand_linha = rand() % (g_lines);
    	rand_coluna = rand() % (g_columns);
	while(Tab[rand_linha][rand_coluna][0]==1 && numero_quadriculas>0){
    	rand_linha = rand() % (g_lines);
    	rand_coluna = rand() % (g_columns);
    }
    	Tab[rand_linha][rand_coluna][0] = 1;    
}

/*	Funçao utilizada para fazer um delay nos modos de disparo,
para os tiros irem aparecendo ao longo do tempo*/
void delay(int number_of_seconds){
	int mili_seconds = 1000*number_of_seconds;

	clock_t start_time =clock();

	while(clock()<start_time+mili_seconds);
}

void Modo_Disparo2(int linha_disparo,int coluna_disparo){
			int ascii_conversion;
			int transfer_line;
			ascii_conversion=coluna_disparo+65;
			transfer_line=g_lines - linha_disparo;

			Tab[linha_disparo][coluna_disparo][0]=1;
			printf("%c%d-",ascii_conversion,transfer_line);

			Tab[linha_disparo+1][coluna_disparo][0]=1;
			printf("%c%d-",ascii_conversion,transfer_line+1);

			Tab[linha_disparo-1][coluna_disparo][0]=1;			
			printf("%c%d-",ascii_conversion,transfer_line-1);

			Tab[linha_disparo][coluna_disparo-1][0]=1;
			printf("%c%d-",ascii_conversion-1,transfer_line);

			Tab[linha_disparo][coluna_disparo+1][0]=1;
			printf("%c%d-",ascii_conversion+1,transfer_line);

			Tab[linha_disparo-1][coluna_disparo-1][0]=1;
			printf("%c%d-",ascii_conversion-1,transfer_line-1);

			Tab[linha_disparo+1][coluna_disparo+1][0]=1;
			printf("%c%d\n",ascii_conversion+1,transfer_line+1);
			//Tab[linha_disparo]
}

int Modo_P2(int AUX_P2[9]){
    int ID;
    int K = 0;
    int Rand;
    int tentativas=0;   
        while(K == 0){
                   Rand = rand() % 9;
                if(Rand == 0 && Tipo_Peca[0] > 0){
                    ID = 0;
                    Tipo_Peca[0]--;
                    K = 1;
                }   
                else if(Rand == 1  && Tipo_Peca[1] > 0 && AUX_P2[1] != 1){
                    ID= 1 + rand() % 9;
                    K = 1;
                    Tipo_Peca[1]--;
                }
                else if(Rand == 2 && Tipo_Peca[2] > 0 && AUX_P2[2] != 1){
                    ID = 10 + rand() % 12;
                    K = 1;
                    Tipo_Peca[2]--;
                }
                else if(Rand == 3 && Tipo_Peca[3] > 0 && AUX_P2[3] != 1){
                    ID = 22 + rand() % 6;
                    K = 1;
                    Tipo_Peca[3]--;
                }
                else if(Rand == 4 && Tipo_Peca[4] > 0 && AUX_P2[4] != 1){
                    ID = 28 + rand() % 4;
                    K=1;
                    Tipo_Peca[4]--;
                }
                else if(Rand == 5 && Tipo_Peca[5] > 0 && AUX_P2[5] != 1){
                    ID = 32 + rand() % 4;
                    K = 1;
                    Tipo_Peca[5]--;
                }
                else if(Rand == 6 && Tipo_Peca[6] > 0 && AUX_P2[6] != 1){
                    ID = 36 + rand() % 4;
                    K = 1;
                    Tipo_Peca[6]--;
                }
                else if(Rand == 7 && Tipo_Peca[7] > 0 && AUX_P2[7] != 1){
                    ID = 40 + rand() % 2;
                    K = 1;
                    Tipo_Peca[7]--;
                }
                else if(Rand == 8 && Tipo_Peca[8] > 0 && AUX_P2[8] != 1){
                    ID = 42;
                    K = 1;
                    Tipo_Peca[8]--;
                }
                else if(Tipo_Peca[0] == 0 && 
                		Tipo_Peca[1] == 0 && 
                		Tipo_Peca[2] == 0 &&
                		Tipo_Peca[3] == 0 && 
                		Tipo_Peca[4] == 0 && 
                		Tipo_Peca[5] == 0 && 
                		Tipo_Peca[6] == 0 && 
                		Tipo_Peca[7] == 0 && 
                		Tipo_Peca[8] == 0){

                        K=1;
                    	printf("todas a pecas utilizadas\n\n");
                    	printf("-0-%d %d\n",Tipo_Peca[0],AUX_P2[0]);
                        printf("-1-%d %d\n",Tipo_Peca[1],AUX_P2[1]);
                        printf("-2-%d %d\n",Tipo_Peca[2],AUX_P2[2]);
                        printf("-3-%d %d\n",Tipo_Peca[3],AUX_P2[3]);
                        printf("-4-%d %d\n",Tipo_Peca[4],AUX_P2[4]);
                        printf("-5-%d %d\n",Tipo_Peca[5],AUX_P2[5]);
                        printf("-6-%d %d\n",Tipo_Peca[6],AUX_P2[6]);
                        printf("-7-%d %d\n",Tipo_Peca[7],AUX_P2[7]);
                        printf("-8-%d %d\n",Tipo_Peca[8],AUX_P2[8]);
                        printf("-%d\n",ID);
                }
                else{
                        K=0;
                          	if(AUX_P2[1]==1 &&
                       		   AUX_P2[2]==1 &&
                       		   AUX_P2[3]==1 &&
                       		   AUX_P2[4]==1 &&
                       		   AUX_P2[5]==1 &&
                       		   AUX_P2[6]==1 &&
                       		   AUX_P2[7]==1 &&
                       		   AUX_P2[8]==1 ){
                        		return -1;

                    		}
                        printf("tentativas:%d\n",tentativas);
                        tentativas++;
                        /*if(tentativas==10){
                        		break;
                        }*/
                        printf("rand:%d\n",Rand);
                        printf("0-%d %d\n",Tipo_Peca[0],AUX_P2[0]);
                        printf("1-%d %d\n",Tipo_Peca[1],AUX_P2[1]);
                        printf("2-%d %d\n",Tipo_Peca[2],AUX_P2[2]);
                        printf("3-%d %d\n",Tipo_Peca[3],AUX_P2[3]);
                        printf("4-%d %d\n",Tipo_Peca[4],AUX_P2[4]);
                        printf("5-%d %d\n",Tipo_Peca[5],AUX_P2[5]);
                        printf("6-%d %d\n",Tipo_Peca[6],AUX_P2[6]);
                        printf("7-%d %d\n",Tipo_Peca[7],AUX_P2[7]);
                        printf("8-%d %d\n",Tipo_Peca[8],AUX_P2[8]);
                        printf("%d\n",ID);
                       

                }			

        }
        return ID;
}
