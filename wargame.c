#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>


#define TAB_COL 15
#define TAB_ROW 24



/*Variáveis Globais*/
int g_lines,g_columns;
int Tab[TAB_COL][TAB_ROW][2];
int Modo_Jogo,Modo_Disparo,Modo_Posicionamento;
int n_pecas=0,Tipo_Peca[9],Default[9];

/*Funções*/
void Contador(int modo_posicionamento);
void Tabuleiro(void);
void Conta_Tipo_Peca(int ID,int decide);
void Matriz(void);
int Volta_Primeira_Variante(int ID, int Var);
int Desenha_Pecas(int index,int ID);
int Restricao1(void);
void Confirma_Disparo(int linhas,int colunas);
int Modo_Disparo1(int number_of_squares);
void regiao_restringida(int linhas,int colunas);
void Modo_Disparo_2_ou_3(int shoot_line,int shoot_column,int seleciona_modo);
int Verfica_Numero_Pecas(int linhas,int colunas,int confirma_numero);
void CommandLineHelp();
int Modo_P2(int AUX_P2[9]);



/*Função que irá ser executada pelo compilador*/
int main(int argc, char *argv[]){

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
                if(Modo_Jogo < 0 || Modo_Jogo > 2){
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
                Tipo_Peca[1] = atoi(optarg);
                n_pecas += Tipo_Peca[1];
                Default[1] = Tipo_Peca[1];
                break;

            case '2':
                Tipo_Peca[2] = atoi(optarg);
                n_pecas += Tipo_Peca[2];
                Default[2] = Tipo_Peca[2];
                break;

            case '3':
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

        if(		Tipo_Peca[8] > Tipo_Peca[7] ||
                Tipo_Peca[7] > Tipo_Peca[6] ||
                Tipo_Peca[6] > Tipo_Peca[5] ||
                Tipo_Peca[5] > Tipo_Peca[4] ||
                Tipo_Peca[4] > Tipo_Peca[3] ||
                Tipo_Peca[3] > Tipo_Peca[2] ||
                Tipo_Peca[2] > Tipo_Peca[1])   /* Restrição 3*/
        {
            printf("não está de acordo com a Restricao 3\n");
            exit(0);
        }

        if(Modo_Posicionamento==2 && n_pecas > (int) Aux){
            printf("o numero de pecas excede metade do numero total de matrizes\n");
            exit(0);
        }

        if((Modo_Posicionamento != 2) &&
                (Tipo_Peca[8]!=0 ||
                 Tipo_Peca[7]!=0 ||
                 Tipo_Peca[6]!=0 ||
                 Tipo_Peca[5]!=0 ||
                 Tipo_Peca[4]!=0 ||
                 Tipo_Peca[3]!=0 ||
                 Tipo_Peca[2]!=0 ||
                 Tipo_Peca[1]!=0))
        {
            printf("o comando -[1 a 8] apenas é valido para o modo p 2 e j\n");
            exit(0);
        }

    }

    int number_of_squares = g_lines * g_columns; /*Usado para o modo de disparo 1, para verificar a quantidade de quadrados de um tabuleiro*/
    int total_of_pieces = Tipo_Peca[1] * 1 + Tipo_Peca[2] * 2 + Tipo_Peca[3] * 3 + Tipo_Peca[4] * 4 +
		Tipo_Peca[5] * 5 + Tipo_Peca[6] * 6 + Tipo_Peca[7] * 7 * Tipo_Peca[8] * 8;/*calcular a quantidade de quadrados diferentes de 0 para o modo de disparo 1*/

    Tipo_Peca[0] = (g_lines * g_columns / 9) - n_pecas;
    Default[0] = Tipo_Peca[0];

    int disparo = 1;/*variavel auxiliar para verificar a quantidade de tiros efetuados pelo computador*/

    if(Modo_Jogo == 0){
    	int a;
    	int b;
    	for(a = 0;a <= g_lines-1;a++){
    		for(b = 0;b <= g_columns-1;b++){
    			Tab[a][b][0] = 1;
    		}
    	}
    	Matriz();
    	Contador (Modo_Posicionamento);
    	printf(" %dx%d %d %d %d %d %d",g_lines,g_columns,Tipo_Peca[1],Tipo_Peca[2],Tipo_Peca[3],Tipo_Peca[4],Tipo_Peca[5]);
    	printf(" %d %d %d\n",Tipo_Peca[6],Tipo_Peca[7],Tipo_Peca[8]);
    	Tabuleiro();
    }

    if(Modo_Jogo == 1){
    	printf("* ================================\n");
    	printf("* Modo de Jogo 1\n");
    	printf("* Insira as Coordenadas de Disparo\n");
    	printf("* ================================\n");
    	int a;
    	int b;
    	Matriz();

    	int numero_total_quadriculas = 0;
    	for(a = 0; a <= g_lines-1;a++){
    		for(b = 0;b <= g_columns-1;b++){
    			if(Tab[a][b][1] != 0){
    				numero_total_quadriculas++;

    			}
    		}
    	}
    	char letra;
    	int coluna;
    	int linha;
    	int k;   	
    	do{
    		//Tabuleiro();
    		scanf("%c %d",&letra,&k);
    		linha = g_lines - k;
    		coluna =  letra - 65;
    		if(linha >= 0 && linha <= g_lines && coluna >=0 && coluna <= g_columns){ /*adicionar a gama de valores que permite o disparo para nao ocorrer segmentaion fault*/
    			printf("%d\n",Tab[linha][coluna][1]);
    			Tab[linha][coluna][0] = 1;
    		}
    		
    		//system("clear");
    		//printf("\n");
    		if(Tab[linha][coluna][1] != 0 && linha>=0 && linha <= g_lines && coluna >=0 && coluna <= g_columns){
    			numero_total_quadriculas--;
    		}
    		
    	}while(numero_total_quadriculas > 0);

    	Contador(Modo_Posicionamento);
    	printf(" %dx%d %d %d %d %d %d",g_lines,g_columns,Tipo_Peca[1],Tipo_Peca[2],Tipo_Peca[3],Tipo_Peca[4],Tipo_Peca[5]);
    	printf(" %d %d %d\n",Tipo_Peca[6],Tipo_Peca[7],Tipo_Peca[8]);
    	Tabuleiro();
    }
    
    if(Modo_Jogo == 2){
    	printf("* ================================\n");
    	printf("* Modo de Jogo 2\n");
    	printf("* Crie um tabuleiro com as caracteríticas indicadas\n");
    	printf("* Reponda aos disparos do programa\n");
    	printf("* ================================\n");
    	printf(" %dx%d %d %d %d %d %d",g_lines,g_columns,Tipo_Peca[1],Tipo_Peca[2],Tipo_Peca[3],Tipo_Peca[4],Tipo_Peca[5]);
    	printf(" %d %d %d\n",Tipo_Peca[6],Tipo_Peca[7],Tipo_Peca[8]);

    	if(Modo_Disparo == 1){
    		do{
    			if(Modo_Disparo1(number_of_squares) == 1){
    				total_of_pieces--;
    			}
    			number_of_squares--;
    		}while(number_of_squares >= 0 && total_of_pieces > 0);
    		Tabuleiro();
    	}
    	else{ /*Modo de disparo 2 ou 3*/
    			int shoot_line;
        	for(shoot_line = 1; shoot_line <= g_lines - 2; shoot_line += 3){
            	int shoot_column;
	           for(shoot_column=1; shoot_column <= g_columns - 2; shoot_column += 3){
	           		if(n_pecas == 0){
	           			break;
	           		}
    	            Modo_Disparo_2_ou_3(shoot_line,shoot_column,Modo_Disparo);
            	}
    		}
    		Tabuleiro();
    	}
	}
}

void Contador(int modo_posicionamento){
	if(modo_posicionamento == 2){
		Tipo_Peca[0] = Default[0];
        Tipo_Peca[1] = Default[1];
        Tipo_Peca[2] = Default[2];
        Tipo_Peca[3] = Default[3];
        Tipo_Peca[4] = Default[4];
        Tipo_Peca[5] = Default[5];
        Tipo_Peca[6] = Default[6];
        Tipo_Peca[7] = Default[7];
        Tipo_Peca[8] = Default[8];
	}
}


/*Função para gerar o tabuleiro*/
void Tabuleiro(void){

    int number = g_lines;
    char Letra = 'A';
    int number_aux;

    int linha;
    for(linha = 0; linha <= g_lines-1; linha++){
        int coluna;
        for(coluna = -1; coluna <= g_columns-1; coluna++){
            if(coluna == -1){
                if(number >= 10){
                    printf("%d ",number);
                }
                else{
                    printf(" %d ", number);
                }
            }
            else{
                printf("%c ",Tab[linha][coluna][0] == 0 ? ' ' : (Tab[linha][coluna][1] == 0 ? '-' : '0' + Tab[linha][coluna][1]));
            }
            if(linha == g_lines-1 && coluna == g_columns-1){
            	printf("\n   ");
            	int a;
            	for(a = 1; a <= g_columns; a++, Letra++){
        			printf("%c ", Letra);
    			}

            }
        }
        printf("\n");
        number--;
    }
}


void Conta_Tipo_Peca(int ID,int decide){
	if(ID == 0){
		if(decide == 1){
			Tipo_Peca[0]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[0] <= 0){
				Tipo_Peca[0] = 0;

			}
			else
				Tipo_Peca[0]--;
		}
	}

	else if(ID >= 1 && ID <= 9){
		if(decide == 1){
			Tipo_Peca[1]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[1] <= 0){
				Tipo_Peca[1] = 0;
			}
			else
				Tipo_Peca[1]--;
		}
		
	}

	else if(ID >= 10 && ID <= 21){
		if(decide == 1){
			Tipo_Peca[2]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[2] <= 0){
				Tipo_Peca[2] = 0;
			}
			else
				Tipo_Peca[2]--;
		}
	}

	else if(ID >= 22 && ID <= 27){
		if(decide == 1){
			Tipo_Peca[3]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[3] <= 0){
				Tipo_Peca[3] = 0;
			}
			else
				Tipo_Peca[3]--;
		}
	}

	else if(ID >= 28 && ID <= 31){
		if(decide == 1){
			Tipo_Peca[4]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[4] <= 0){
				Tipo_Peca[4] = 0;

			}
			else
				Tipo_Peca[4]--;
		}
	}

	else if(ID >= 32 && ID <= 35){
		if(decide == 1){
			Tipo_Peca[5]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[5] <= 0){
				Tipo_Peca[5] = 0;
			}
			else
				Tipo_Peca[5]--;
		}
	}
	else if(ID >= 36 && ID <= 39){
		if(decide == 1){
			Tipo_Peca[6]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[6] <= 0){
				Tipo_Peca[6] = 0;
			}
			else
				Tipo_Peca[6]--;
		}
	}
	else if(ID >= 40 && ID <= 41){
		if(decide == 1){
			Tipo_Peca[7]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[7] <= 0){
				Tipo_Peca[7] = 0;
			}
			else
				Tipo_Peca[7]--;
		}
	}
	else if(ID == 42){
		if(decide == 1){
			Tipo_Peca[8]++;
		}
		else if(decide == -1){
			if(Tipo_Peca[8] <= 0){
				Tipo_Peca[8] = 0;
			}
			else
				Tipo_Peca[8]--;
		}
	}
	else{

	}
}

void Matriz(void){/*Funçao que coloca as peças no tabuleiro*/

    int ID;
    int index;
	int i;
	int linhas;
	int colunas;
	int reset = 0;

  	for(i=0; i < 1000;i++ ){
  		
  		int AUX_P2[9]= {0,0,0,0,0,0,0,0,0};
    	
    	for (linhas = 0; linhas <= g_lines - 1; linhas += 3){
        	
        	for (colunas = 0; colunas <= g_columns - 1 ; colunas += 3){
            	if(Modo_Posicionamento == 1){
                	ID = rand() % 43;
                	index = 0;
            	}
            	else if(Modo_Posicionamento == 2){
                	ID = Modo_P2(AUX_P2);
                		if(ID == -1){
                 	
                		Tipo_Peca[0] = Default[0];
                		Tipo_Peca[1] = Default[1];
                		Tipo_Peca[2] = Default[2];
                		Tipo_Peca[3] = Default[3];
                		Tipo_Peca[4] = Default[4];
                		Tipo_Peca[5] = Default[5];
                		Tipo_Peca[6] = Default[6];
                		Tipo_Peca[7] = Default[7];
                		Tipo_Peca[8] = Default[8];
                		int d;
                		int f;
                		for(d = 0;d <= g_lines - 1;d++){
                			for(f = 0;f <= g_columns - 1;f++){
                				Tab[d][f][1] = 0;
                			}
                		}
                		reset++;
                		}
                		if(ID == -2){
                			return;
                		}

                	index = 0;
            	}

            	/*Ciclo em que mete as peças numa matriz 3x3*/
            	int i;
            	for (i = 0; i < 3; i++){
                	int j;
                	for (j = 0; j < 3; j++){
                    		Tab[linhas+i][colunas+j][1] = Desenha_Pecas(index, ID);

                    	index++;
                	}
            	}/*Acaba uma matriz*/

            	int AUX_P1 = 0;
            	while(Restricao1() == 0 && Modo_Posicionamento == 1) /*Modo P1*/{

                	ID = rand() % 43;
                	index = 0;
                	AUX_P1++;

                	if(AUX_P1==3){
                   		ID = 5;
                	}

                	int i;
                	for (i = 0; i < 3; i++){
                    	int j;
                    	for (j = 0; j < 3; j++){
                        	Tab[linhas + i][colunas + j][1] = Desenha_Pecas(index, ID);
                        	index++;
                    	}
                	}
            	}

            	if(Modo_Posicionamento == 1){
            		Conta_Tipo_Peca(ID,1);
            	}

            		if(Tipo_Peca[1] != 0){
                		AUX_P2[1] = 0;
                	}
                	else
                		AUX_P2[1] = 1;

                	if(Tipo_Peca[2] != 0){
                		AUX_P2[2] = 0;
                	}
                	else
                		AUX_P2[2] = 1;

                	if(Tipo_Peca[3] != 0){
                		AUX_P2[3] = 0;
                	}
                	else
                		AUX_P2[3] = 1;

                	if(Tipo_Peca[4] != 0){
                		AUX_P2[4] = 0;
                	}
                	else
                		AUX_P2[4] = 1;

                	if(Tipo_Peca[5] != 0){
                		AUX_P2[5] = 0;
                	}
                	else
                		AUX_P2[5] = 1;

                	if(Tipo_Peca[6] != 0){
                		AUX_P2[6] = 0;
                	}
                	else
                		AUX_P2[6] = 1;

                	if(Tipo_Peca[7] != 0){
                		AUX_P2[7] = 0;
                	}
                	else
                		AUX_P2[7] = 1;

                	if(Tipo_Peca[8] != 0){
                		AUX_P2[8] = 0;
                	}
                	else
                		AUX_P2[8] = 1; 

            	int Var = 0;
            	while(Restricao1() == 0 && Modo_Posicionamento == 2) /*Modo P2*/{
            	    
            	    if(Restricao1() == 0){
            	    	ID = Volta_Primeira_Variante(ID,Var);
            	    }
                	
                		
                	Var=1;
                
                	if(ID == 9){
                    	AUX_P2[1] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                	}
                 	else if(ID == 21){
                    	AUX_P2[2] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                 	}

                 	else if(ID == 27){
                    	AUX_P2[3] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                 	}

                 	else if(ID == 31){
                    	AUX_P2[4] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                 	}

                 	else if(ID == 35){ 
                    	AUX_P2[5] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                 	}

                 	else if(ID == 39){
                    	AUX_P2[6] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                 	}
                 	else if(ID == 41){
                    	AUX_P2[7] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                 	}
                 	else if(ID == 42){
                    	AUX_P2[8] = 1;
                    	ID = Modo_P2(AUX_P2);

                    	Var = 0;
                 	}

                 	if(ID == -1){
                 	
                	Tipo_Peca[0] = Default[0];
                	Tipo_Peca[1] = Default[1];
                	Tipo_Peca[2] = Default[2];
                	Tipo_Peca[3] = Default[3];
                	Tipo_Peca[4] = Default[4];
                	Tipo_Peca[5] = Default[5];
                	Tipo_Peca[6] = Default[6];
                	Tipo_Peca[7] = Default[7];
                	Tipo_Peca[8] = Default[8];
                	int d;
                	int f;

                		for(d=0;d <= g_lines-1;d++){
                			for(f=0;f <= g_columns-1;f++){
                				Tab[d][f][1] = 0;
                			}
                		}
                		reset++;
                		break;
                	}
                	else if(ID == -2){
                		return;
                	}
                	
                	

                	index = 0;

                	int i;
                	for (i = 0; i < 3; i++){
                    	int j;
                    	for (j = 0; j < 3; j++){
                        		Tab[linhas + i][colunas + j][1] = Desenha_Pecas(index,ID);

                        	index++;
                    	}
                	}

                	if(Restricao1() == 0 && ID != 42 && ID != -1){
                		ID++;
                	}

            	} /*fim do ciclo while*/
            		if(ID ==-1){
        				break;
        			}

            		if(Modo_Posicionamento == 2){
            			Conta_Tipo_Peca(ID,-1);
            		}

            		if(Tipo_Peca[1] == 0){
                		AUX_P2[1] = 1;
                	}

                	if(Tipo_Peca[2] == 0){
                		AUX_P2[2] = 1;
                	}

                	if(Tipo_Peca[3] == 0){
                		AUX_P2[3] = 1;
                	}
                	if(Tipo_Peca[4] == 0){
                		AUX_P2[4] = 1;
                	}
                	if(Tipo_Peca[5] == 0){
                		AUX_P2[5] = 1;
                	}
                	if(Tipo_Peca[6] == 0){
                		AUX_P2[6] = 1;
                	}
                	if(Tipo_Peca[7] == 0){
                		AUX_P2[7] = 1;
                	}
                	if(Tipo_Peca[8] == 0){
                		AUX_P2[8] = 1;
                	} 
            		//printf("%d certa\n",ID);

        	} /*fim do 2 for*/
        	if(ID == -1){
        			break;
        		}
    	} /* fim do 1 for*/

    		if(Modo_Posicionamento == 1){   			
    			return;
    		}

    		if(Tipo_Peca[0] == 0 &&
    	   	   Tipo_Peca[1] == 0 &&
    	   	   Tipo_Peca[2] == 0 &&
    	   	   Tipo_Peca[3] == 0 &&
    	   	   Tipo_Peca[4] == 0 &&
    	   	   Tipo_Peca[5] == 0 &&
    	   	   Tipo_Peca[6] == 0 &&
    	   	   Tipo_Peca[7] == 0 &&
    	   	   Tipo_Peca[8] == 0){
    			return;
    		}
    	 		   	 
  	}
  	return;
}

int Volta_Primeira_Variante(int ID, int Var){
	if((ID >= 1 && ID <= 9) && Var == 0){
        ID = 1;
    }

    else if((ID >= 10 && ID <= 21) && Var == 0){
        ID = 10;
    }

    else if((ID >= 22 && ID <= 27) && Var == 0){
        ID = 22;
    }

    else if((ID >= 28 && ID <= 31) && Var == 0){
        ID = 28;
    }

    else if((ID >= 32 && ID <= 35) && Var == 0){
        ID = 32;
    }

    else if((ID >= 36 && ID <= 39) && Var == 0){
    	ID = 36;
    }

    else if((ID >= 40 && ID <= 41) && Var == 0){
    	ID = 40;
    }
	return ID;             
}
/*Função para gerar todas as combinações possíveis das peças*/
int Desenha_Pecas(int index, int ID){

    if(ID==0){
        int Peca[]= {0,0,0,
                     0,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==1){
        int Peca[]= {1,0,0,
                     0,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==2){
        int Peca[]= {0,1,0,
                     0,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==3){
        int Peca[]= {0,0,1,
                     0,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==4){
        int Peca[]= {0,0,0,
                     1,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==5){
        int Peca[]= {0,0,0,
                     0,1,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==6){
        int Peca[]= {0,0,0,
                     0,0,1,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==7){
        int Peca[]= {0,0,0,
                     0,0,0,
                     1,0,0
                    };
        return Peca[index];
    }

    else if(ID==8){
        int Peca[]= {0,0,0,
                     0,0,0,
                     0,1,0
                    };
        return Peca[index];
    }

    else if(ID==9){
        int Peca[]= {0,0,0,
                     0,0,0,
                     0,0,1
                    };
        return Peca[index];
    }

    else if(ID==10){
        int Peca[]= {2,2,0,
                     0,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==11){
        int Peca[]= {0,2,2,
                     0,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==12){
        int Peca[]= {0,0,0,
                     2,2,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==13){
        int Peca[]= {0,0,0,
                     0,2,2,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==14){
        int Peca[]= {0,0,0,
                     0,0,0,
                     2,2,0
                    };
        return Peca[index];
    }

    else if(ID==15){
        int Peca[]= {0,0,0,
                     0,0,0,
                     0,2,2
                    };
        return Peca[index];
    }

    else if(ID==16){
        int Peca[]= {2,0,0,
                     2,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==17){
        int Peca[]= {0,0,0,
                     2,0,0,
                     2,0,0
                    };
        return Peca[index];
    }

    else if(ID==18){
        int Peca[]= {0,2,0,
                     0,2,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==19){
        int Peca[]= {0,0,0,
                     0,2,0,
                     0,2,0
                    };
        return Peca[index];
    }

    else if(ID==20){
        int Peca[]= {0,0,2,
                     0,0,2,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==21){
        int Peca[]= {0,0,0,
                     0,0,2,
                     0,0,2
                    };
        return Peca[index];
    }

    else if(ID==22){
        int Peca[]= {3,3,3,
                     0,0,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==23){
        int Peca[]= {0,0,0,
                     3,3,3,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==24){
        int Peca[]= {0,0,0,
                     0,0,0,
                     3,3,3
                    };
        return Peca[index];
    }

    else if(ID==25){
        int Peca[]= {3,0,0,
                     3,0,0,
                     3,0,0
                    };
        return Peca[index];
    }

    else if(ID==26){
        int Peca[]= {0,3,0,
                     0,3,0,
                     0,3,0
                    };
        return Peca[index];
    }

    else if(ID==27){
        int Peca[]= {0,0,3,
                     0,0,3,
                     0,0,3
                    };
        return Peca[index];
    }

    else if(ID==28){
        int Peca[]= {4,4,0,
                     4,4,0,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==29){
        int Peca[]= {0,4,4,
                     0,4,4,
                     0,0,0
                    };
        return Peca[index];
    }

    else if(ID==30){
        int Peca[]= {0,0,0,
                     4,4,0,
                     4,4,0
                    };
        return Peca[index];
    }

    else if(ID==31){
        int Peca[]= {0,0,0,
                     0,4,4,
                     0,4,4
                    };
        return Peca[index];
    }

    else if(ID==32){
        int Peca[]= {5,5,5,
                     0,5,0,
                     0,5,0
                    };
        return Peca[index];
    }

    else if(ID==33){
        int Peca[]= {5,0,0,
                     5,5,5,
                     5,0,0
                    };
        return Peca[index];
    }

    else if(ID==34){
        int Peca[]= {0,5,0,
                     0,5,0,
                     5,5,5
                    };
        return Peca[index];
    }

    else if(ID==35){
        int Peca[]= {0,0,5,
                     5,5,5,
                     0,0,5
                    };
        return Peca[index];
    }

    else if(ID==36){
        int Peca[]= {0,6,0,
                     6,0,6,
                     6,6,6
                    };
        return Peca[index];
    }

    else if(ID==37){
        int Peca[]= {0,6,6,
                     6,0,6,
                     0,6,6
                    };
        return Peca[index];
    }

    else if(ID==38){
        int Peca[]= {6,6,6,
                     6,0,6,
                     0,6,0
                    };
        return Peca[index];
    }

    else if(ID==39){
        int Peca[]= {6,6,0,
                     6,0,6,
                     6,6,0
                    };
        return Peca[index];
    }

    else if(ID==40){
        int Peca[]= {7,0,7,
                     7,7,7,
                     7,0,7
                    };
        return Peca[index];
    }

    else if(ID==41){
        int Peca[]= {7,7,7,
                     0,7,0,
                     7,7,7
                    };
        return Peca[index];
    }

    else if(ID==42){
        int Peca[]= {8,8,8,
                     8,0,8,
                     8,8,8
                    };
        return Peca[index];
    }

    return 0;
}


/*Função para a Linhas de Comandos */
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


/*Função para a Restrição 1*/
int Restricao1()  /*Restriçao=1 se a restrição está a ser executada tudo foi cumprido*/{

    int Verifica_Matriz;

    int linhas;
    for (linhas = 0; linhas <= g_lines-1; linhas++){
        int colunas;
        for (colunas = 0; colunas <= g_columns-1; colunas++){
            Verifica_Matriz = (colunas / 3) * (g_columns / 3) + (linhas / 3) + 1; //formula de verificação da matriz
            if(Tab[linhas][colunas][1] != 0){
                int j;
                for(j = -1; j <= 1; j++){
                    int k;
                    for(k = -1; k <= 1; k++){
                        if(linhas + j < 0 || linhas + j >= g_lines){
                            continue;
                        }

                        if(colunas + k < 0 || colunas + k >= g_columns){
                            continue;
                        }

                        if(Tab[linhas + j][colunas + k][1] != 0 && Verifica_Matriz != ((((colunas + k) / 3) * (g_columns / 3) + ( linhas + j ) / 3 ) + 1))
                            return 0;
                    }
                }
            }
        }
    }
    return 1;
}


/*Função para o modo de disparo 1*/
int Modo_Disparo1(int numero_quadriculas){
    int rand_coluna;
    int rand_linha;
    rand_linha = rand() % (g_lines);
    rand_coluna = rand() % (g_columns);

    while(Tab[rand_linha][rand_coluna][0]==1 && numero_quadriculas>0){
        rand_linha = rand() % (g_lines);
        rand_coluna = rand() % (g_columns);
    }

    Tab[rand_linha][rand_coluna][0] = 1;

    Confirma_Disparo(rand_linha,rand_coluna);

	if(Tab[rand_linha][rand_coluna][1] == 0){
		return 0;
	}
	else{
		return 1;
	}	
}


void Confirma_Disparo(int linhas,int colunas){

	char posicao;
    int posicao_transformada;

    char coluna = colunas + 65;
    int linha = g_lines - linhas;

    printf("coordenadas de disparo:%c%d\n",coluna,linha);
    printf("confirmacao:\n");

	do{ 
 
    scanf("%c",&posicao);/* posicao é a variavel que indicada qual é que foi a peça em que o disparo acertou*/
    if(posicao == '-'){
    	posicao_transformada = posicao - 45;
    }
    else{
    	posicao_transformada = posicao - 48;
    }

    Tab[linhas][colunas][1] = posicao_transformada;

	}while(posicao_transformada < 0 || posicao_transformada >= 9);
}

void regiao_restringida(int linhas,int colunas){
	int a;
	int b;
	for(a = -1;a <= 1;a++){
		for(b = -1;b <= 1;b++){
			if(Tab[linhas][colunas][1] != 0){
			   int verifica_matriz = (colunas / 3) * (g_columns / 3) + (linhas / 3) + 1;
			   int verifica_matriz_adjacente = ((((colunas + b) / 3) * (g_columns / 3) + (linhas + a) / 3) + 1);
				if(linhas + a < 0 || linhas + a >= g_lines){
					continue;
				}
				if(colunas + b < 0 || colunas + b >= g_columns){
					continue;
				}
				if(Tab[linhas + a][colunas + b][1] == 0 && verifica_matriz != verifica_matriz_adjacente){
				   	Tab[linhas + a][colunas + b][0] = 1;
				}
			}

		}
	}
}

/*Função para o modo de disparo 2 e 3*/
void Modo_Disparo_2_ou_3 (int linha_disparo,int coluna_disparo,int seleciona_modo){


	int passa_de_matriz=9;
	int primeira_vez = 1;
    	
    Tab[linha_disparo][coluna_disparo][0] = 1;  /*Disparo sobre a celula central da matriz*/
    Confirma_Disparo(linha_disparo,coluna_disparo);

    if(Tab[linha_disparo][coluna_disparo][1] != 0){
    	if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo][coluna_disparo][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas == 0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo,coluna_disparo);
    	}
    	//Tabuleiro();
    	return;       
    }
    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo,coluna_disparo);
    }

    //Tabuleiro();
    printf("\n");




    	/*Disparo sobre a célula imediatamente acima da central da matriz*/
    if(seleciona_modo == 2){
    	Tab[linha_disparo - 1][coluna_disparo][0] = 1;
    	Confirma_Disparo(linha_disparo-1,coluna_disparo);
    }
    else if(seleciona_modo == 3 && Tab[linha_disparo - 1][coluna_disparo][0] == 1) {
    	
    }
    else{

    	Tab[linha_disparo - 1][coluna_disparo][0] = 1;
    	Confirma_Disparo(linha_disparo - 1,coluna_disparo);
    }

    if(Tab[linha_disparo - 1][coluna_disparo][1] != 0 ){
    	if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo - 1][coluna_disparo][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas == 0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo-1,coluna_disparo);
    	}
    	//Tabuleiro();
    	return;	  
    }
    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo - 1,coluna_disparo);
    }
    
    //Tabuleiro();
    printf("\n");




    	/*Disparo sobre a célula imediatamente abaixo da central da matriz*/
    if(seleciona_modo == 2){

    	Tab[linha_disparo + 1][coluna_disparo][0] = 1;

    	Confirma_Disparo(linha_disparo + 1,coluna_disparo);
	}
	else if(seleciona_modo == 3 && Tab[linha_disparo + 1][coluna_disparo][0] == 1){
		
	}
	else{
		Tab[linha_disparo+1][coluna_disparo][0]=1;

		Confirma_Disparo(linha_disparo + 1,coluna_disparo);
	}

    if(Tab[linha_disparo + 1][coluna_disparo][1] != 0){
    	if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo + 1][coluna_disparo][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas==0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo+1,coluna_disparo);
    	}
    	//Tabuleiro();
    	return;   	  
    }
    else{

    }
    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo+1,coluna_disparo);
    }

    //Tabuleiro();
    printf("\n");





    	/*Disparo sobre a célula à esquerda da central*/
    if(seleciona_modo == 2){
    	Tab[linha_disparo][coluna_disparo - 1][0] = 1;

    	Confirma_Disparo(linha_disparo, coluna_disparo - 1);
	}
	else if(seleciona_modo == 3 && Tab[linha_disparo][coluna_disparo-1][0]==1){

	}
	else{
		Tab[linha_disparo][coluna_disparo-1][0]=1;

		Confirma_Disparo(linha_disparo, coluna_disparo - 1);
	}
    if(Tab[linha_disparo][coluna_disparo - 1][1] != 0 ){
    	if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo][coluna_disparo - 1][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas == 0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo,coluna_disparo-1);
    	}
    	//Tabuleiro();
    	return;  	   
    }
    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo,coluna_disparo-1);
    }

    //Tabuleiro();
    printf("\n");




    	/*Disparo sobre a célula à direita da central*/
    if(seleciona_modo == 2){
    	Tab[linha_disparo][coluna_disparo + 1][0] = 1;

    	Confirma_Disparo(linha_disparo,coluna_disparo + 1);
	}
	else if(seleciona_modo==3 && Tab[linha_disparo][coluna_disparo+1][0] == 1){

	}
	else{
		Tab[linha_disparo][coluna_disparo+1][0] = 1;

		Confirma_Disparo(linha_disparo,coluna_disparo + 1);
	}

    if(Tab[linha_disparo][coluna_disparo + 1][1] != 0 ){
    	if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo][coluna_disparo + 1][1];
    		primeira_vez--;
    	}
        n_pecas--;
        passa_de_matriz--;
    }

    if(n_pecas == 0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo,coluna_disparo + 1);
    	}
    	//Tabuleiro();
    	return;	   
    }
    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo,coluna_disparo + 1);
    }

    //Tabuleiro();
    printf("\n");




    	/*Disparo sobre a célula situada no canto sup. esquerdo da matriz*/
    if(seleciona_modo == 2){
    	Tab[linha_disparo - 1][coluna_disparo - 1][0] = 1;

    	Confirma_Disparo(linha_disparo - 1,coluna_disparo - 1);
    }
    else if(seleciona_modo == 3 && Tab[linha_disparo - 1][coluna_disparo - 1][0] == 1){

    }
    else{
    	Tab[linha_disparo - 1][coluna_disparo - 1][0] = 1;

    	Confirma_Disparo(linha_disparo - 1,coluna_disparo - 1);
    }	
    if(Tab[linha_disparo - 1][coluna_disparo - 1][1] != 0 ){
       if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo + 1][coluna_disparo][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas == 0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo - 1,coluna_disparo - 1);
    	}
    	//Tabuleiro();
    	return;  
    }

    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo - 1,coluna_disparo - 1);
    }

    //Tabuleiro();
    printf("\n");




    	/*disparo sobre a célula situada no canto inf. direito da matriz*/
    if(seleciona_modo == 2){
    	Tab[linha_disparo + 1][coluna_disparo + 1][0] = 1;

    	Confirma_Disparo(linha_disparo + 1,coluna_disparo + 1);
    }
    else if(seleciona_modo == 3 && Tab[linha_disparo + 1][coluna_disparo + 1][0] == 1){

    }
    else{
    	Tab[linha_disparo + 1][coluna_disparo + 1][0] = 1;

    	Confirma_Disparo(linha_disparo + 1,coluna_disparo + 1);
    }
    if(Tab[linha_disparo + 1][coluna_disparo + 1][1] != 0){
        if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo + 1][coluna_disparo + 1][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas == 0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo + 1, coluna_disparo + 1);
    	}
    	//Tabuleiro();
    	return;  
    }
    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo + 1, coluna_disparo + 1);
    }

    //Tabuleiro();
    printf("\n");




    	/*Disparo sobre a célula situado no canto sup. direito da matriz*/
    if(seleciona_modo == 2){
    	Tab[linha_disparo - 1][coluna_disparo + 1][0] = 1;

    	Confirma_Disparo(linha_disparo - 1,coluna_disparo + 1);
    }
    else if(seleciona_modo == 3 && Tab[linha_disparo - 1][coluna_disparo + 1][0] == 1){

    }
    else{
    	Tab[linha_disparo - 1][coluna_disparo + 1][0] = 1;

    	Confirma_Disparo(linha_disparo - 1,coluna_disparo + 1);
    }
    if(Tab[linha_disparo - 1][coluna_disparo + 1][1] !=0){
        if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo + 1][coluna_disparo][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas == 0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo - 1,coluna_disparo + 1);
    	}
    	//Tabuleiro();
    	return;   
    }

    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo - 1,coluna_disparo + 1);
    }
    
   // Tabuleiro();
    printf("\n");



    	/*Disparo sobre a célula situada no canto inf. esquerdo da matriz*/
    if(seleciona_modo == 2){
    	Tab[linha_disparo + 1][coluna_disparo - 1][0] = 1;

    	Confirma_Disparo(linha_disparo + 1,coluna_disparo - 1);
	}
	else if(seleciona_modo == 3 && Tab[linha_disparo + 1][coluna_disparo - 1][0] == 1){

	}
	else{
		Tab[linha_disparo + 1][coluna_disparo - 1][0] = 1;

		Confirma_Disparo(linha_disparo + 1,coluna_disparo - 1);
	}
    if(Tab[linha_disparo + 1][coluna_disparo - 1][1]!=0){
        if(primeira_vez == 1){
    		passa_de_matriz = Tab[linha_disparo + 1][coluna_disparo][1];
    		primeira_vez--;
    	}
    	n_pecas--;
    	passa_de_matriz--;
    }

    if(n_pecas==0 || passa_de_matriz == 0){
    	if(seleciona_modo == 3){
    		regiao_restringida(linha_disparo + 1, coluna_disparo - 1);
    	}
    	//Tabuleiro();
    	return; 
    }
    if(seleciona_modo == 3){
    	regiao_restringida(linha_disparo + 1, coluna_disparo - 1);
    }

    //Tabuleiro();
    printf("\n");
}

/*Função para o modo de posicionamento 2*/
int Modo_P2(int aux_p2[9]){

    int ID;
    int K = 0;
    int Rand;

    int tentativas=0;

    

    while(K == 0){
    		Rand = rand() % 9;
        if(Rand == 0 && Tipo_Peca[0] > 0){
    		ID = 0;
    		K = 1;
    	}

        else if(Rand == 1 && Tipo_Peca[1] > 0 && aux_p2[1] != 1){
            ID = 1 + rand() % 9;
            K = 1;
        }

        else if(Rand == 2 && Tipo_Peca[2] > 0 && aux_p2[2] != 1){
            ID = 10 + rand() % 12;
            K = 1;
        }

        else if(Rand == 3 && Tipo_Peca[3] > 0 && aux_p2[3] != 1){
            ID = 22 + rand() % 6;
            K = 1;
        }

        else if(Rand == 4 && Tipo_Peca[4] > 0 && aux_p2[4] != 1){
            ID = 28 + rand() % 4;
            K = 1;
        }

        else if(Rand == 5 && Tipo_Peca[5] > 0 && aux_p2[5] != 1){
            ID = 32 + rand() % 4;
            K = 1;
        }

        else if(Rand == 6 && Tipo_Peca[6] > 0 && aux_p2[6] != 1){
            ID = 36 + rand() % 4;
            K = 1;
        }

        else if(Rand == 7 && Tipo_Peca[7] > 0 && aux_p2[7] != 1){
            ID = 40 + rand() % 2;
            K = 1;
        }

        else if(Rand == 8 && Tipo_Peca[8] > 0 && aux_p2[8] != 1){
            ID = 42;
            K = 1;
        }

        else if(Tipo_Peca[0] == 0 &&
                Tipo_Peca[1] == 0 &&
                Tipo_Peca[2] == 0 &&
                Tipo_Peca[3] == 0 &&
                Tipo_Peca[4] == 0 &&
                Tipo_Peca[5] == 0 &&
                Tipo_Peca[6] == 0 &&
                Tipo_Peca[7] == 0 &&
                Tipo_Peca[8] == 0)
        {	
        	printf("ID:%d\n",ID);
        	/*printf("0-Tipo-%d Aux-%d\n",Tipo_Peca[0],aux_p2[0]);
        	printf("1-Tipo-%d Aux-%d\n",Tipo_Peca[1],aux_p2[1]);
        	printf("2-Tipo-%d Aux-%d\n",Tipo_Peca[2],aux_p2[2]);
        	printf("3-Tipo-%d Aux-%d\n",Tipo_Peca[3],aux_p2[3]);
        	printf("4-Tipo-%d Aux-%d\n",Tipo_Peca[4],aux_p2[4]);
        	printf("5-Tipo-%d Aux-%d\n",Tipo_Peca[5],aux_p2[5]);
        	printf("6-Tipo-%d Aux-%d\n",Tipo_Peca[6],aux_p2[6]);
        	printf("7-Tipo-%d Aux-%d\n",Tipo_Peca[7],aux_p2[7]);
        	printf("8-Tipo-%d Aux-%d\n",Tipo_Peca[8],aux_p2[8]);*/
        	printf("return time\n");
        	return -2;
        }
        else if(    (aux_p2[1]==1 &&
                    aux_p2[2]==1 &&
                    aux_p2[3]==1 &&
                    aux_p2[4]==1 &&
                    aux_p2[5]==1 &&
                    aux_p2[6]==1 &&
                    aux_p2[7]==1 &&
                    aux_p2[8]==1) &&
                    (Tipo_Peca[1] != 0||
                    Tipo_Peca[2] != 0 ||
                    Tipo_Peca[3] != 0 ||
                    Tipo_Peca[4] != 0 ||
                    Tipo_Peca[5] != 0 ||
                    Tipo_Peca[6] != 0 ||
                    Tipo_Peca[7] != 0 ||
                    Tipo_Peca[8] != 0))
					{	
            	ID = -1;
                return ID;
            }

        else{
            K=0;

        }
    }
    return ID;
}